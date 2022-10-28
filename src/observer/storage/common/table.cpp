/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi & Wangyunlai on 2021/5/13.
//

#include <json/value.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <stdio.h>

#include "common/defs.h"
#include "common/lang/defer.h"
#include "sql/parser/parse_defs.h"
#include "common/lang/bitmap.h"
#include "storage/common/field_meta.h"
#include "storage/common/table.h"
#include "storage/common/table_meta.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/default/disk_buffer_pool.h"
#include "storage/record/record_manager.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/index/index.h"
#include "storage/index/bplus_tree_index.h"
#include "storage/trx/trx.h"
#include "storage/clog/clog.h"
#include "util/typecast.h"

Table::~Table()
{
  if (record_handler_ != nullptr) {
    delete record_handler_;
    record_handler_ = nullptr;
  }

  if (data_buffer_pool_ != nullptr) {
    BufferPoolManager::instance().close_file(table_data_file(base_dir_.c_str(), name()).c_str());
    // data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
  }

  for (std::vector<Index *>::iterator it = indexes_.begin(); it != indexes_.end(); ++it) {
    Index *index = *it;
    delete index;
  }
  indexes_.clear();

  LOG_INFO("Table has been closed: %s", name());
}

RC Table::create(const char *path, const char *name, const char *base_dir, int attribute_count,
    const AttrInfo attributes[], CLogManager *clog_manager)
{

  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attribute_count <= 0 || nullptr == attributes) {
    LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d, attributes=%p", name, attribute_count, attributes);
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 table_name.table记录一个表的元数据
  // 判断表文件是否已经存在
  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (fd < 0) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s", path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", path, errno, strerror(errno));
    return RC::IOERR;
  }

  close(fd);

  // 创建文件
  if ((rc = table_meta_.init(name, attribute_count, attributes)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc;  // delete table file
  }

  std::fstream fs;
  fs.open(path, std::ios_base::out | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
    return RC::IOERR;
  }

  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();

  std::string data_file = table_data_file(base_dir, name);
  BufferPoolManager &bpm = BufferPoolManager::instance();
  rc = bpm.create_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
    return rc;
  }

  rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create table %s due to init record handler failed.", data_file.c_str());
    // don't need to remove the data_file
    return rc;
  }

  base_dir_ = base_dir;
  clog_manager_ = clog_manager;
  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}

RC Table::remove(const char *name)
{
  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to remove table %s:%s", base_dir_.c_str(), name);

  // remove the relevant index files
  for (auto idx : indexes_) {
    std::string index_file = table_index_file(base_dir_.c_str(), name, idx->index_meta().name());
    delete idx;  // the file will be closed in dtor
    if (0 != ::unlink(index_file.c_str())) {
      LOG_ERROR("Delete index file failed. filename=%s, errmsg=%d:%s", index_file.c_str(), errno, strerror(errno));
      return RC::IOERR;
    }
  }
  indexes_.clear();

  // close the data file and clean relevant resources
  assert(nullptr != record_handler_);
  record_handler_->close();
  delete record_handler_;
  record_handler_ = nullptr;

  std::string data_file = table_data_file(base_dir_.c_str(), name);
  assert(nullptr != data_buffer_pool_);
  BufferPoolManager::instance().close_file(data_file.c_str());
  // NOTE: after bpm.close_file, the dbp has been released
  data_buffer_pool_ = nullptr;

  // remove the data file
  if (0 != ::unlink(data_file.c_str())) {
    LOG_ERROR("Delete data file failed. filename=%s, errmsg=%d:%s", data_file.c_str(), errno, strerror(errno));
    return RC::IOERR;
  }

  // remove the meta file
  std::string meta_file = table_meta_file(base_dir_.c_str(), name);
  if (0 != ::unlink(meta_file.c_str())) {
    LOG_ERROR("Delete data file failed. filename=%s, errmsg=%d:%s", meta_file.c_str(), errno, strerror(errno));
    return RC::IOERR;
  }

  return RC::SUCCESS;
  // after we invoke the func, the dtor do nothing.
}

RC Table::open(const char *meta_file, const char *base_dir, CLogManager *clog_manager)
{
  // 加载元数据文件
  std::fstream fs;
  std::string meta_file_path = std::string(base_dir) + common::FILE_PATH_SPLIT_STR + meta_file;
  fs.open(meta_file_path, std::ios_base::in | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file_path.c_str(), strerror(errno));
    return RC::IOERR;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file_path.c_str());
    fs.close();
    return RC::GENERIC_ERROR;
  }
  fs.close();

  // 加载数据文件
  RC rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open table %s due to init record handler failed.", base_dir);
    // don't need to remove the data_file
    return rc;
  }

  base_dir_ = base_dir;

  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {
    const IndexMeta *index_meta = table_meta_.index(i);
    const std::vector<std::string> *index_field_names = index_meta->field();
    std::vector<FieldMeta> field_metas;

    for (size_t i = 0; i < index_field_names->size(); i++) {
      const char *field_name = index_field_names->at(i).data();
      const FieldMeta *field_meta = table_meta_.field(field_name);
      if (field_meta == nullptr) {
        LOG_ERROR("Found invalid index meta info which has a non-exists field. table=%s, index=%s, field=%s",
            name(),
            index_meta->name(),
            index_meta->field());
        // skip cleanup
        //  do all cleanup action in destructive Table function
        return RC::GENERIC_ERROR;
      }
      field_metas.push_back(*field_meta);
    }

    BplusTreeIndex *index = new BplusTreeIndex();
    std::string index_file = table_index_file(base_dir, name(), index_meta->name());
    rc = index->open(index_file.c_str(), *index_meta, field_metas);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%d:%s",
          name(),
          index_meta->name(),
          index_file.c_str(),
          rc,
          strrc(rc));
      // skip cleanup
      //  do all cleanup action in destructive Table function.
      return rc;
    }
    indexes_.push_back(index);
  }

  if (clog_manager_ == nullptr) {
    clog_manager_ = clog_manager;
  }
  return rc;
}

RC Table::commit_insert(Trx *trx, const RID &rid)
{
  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to get record %s: %s", this->name(), rid.to_string().c_str());
    return rc;
  }

  return trx->commit_insert(this, record);
}

RC Table::rollback_insert(Trx *trx, const RID &rid)
{
  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to get record %s: %s", this->name(), rid.to_string().c_str());
    return rc;
  }

  // remove all indexes
  rc = delete_entry_of_indexes(record.data(), rid, false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d) while rollback insert, rc=%d:%s",
        rid.page_num,
        rid.slot_num,
        rc,
        strrc(rc));
    return rc;
  }

  rc = record_handler_->delete_record(&rid);
  return rc;
}

RC Table::insert_record(Trx *trx, int row_num, Record *records)
{
  RC rc = RC::SUCCESS;

  // insert data and index
  for (int i = 0; i < row_num; i++) {
    Record &current_record = records[i];
    if (trx != nullptr) {
      trx->init_trx_info(this, current_record);
    }

    rc = record_handler_->insert_record(current_record.data(), table_meta_.record_size(), &current_record.rid());
    if (rc != RC::SUCCESS) {
      LOG_ERROR("insert record failed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));

      // rollback when insert failed
      RC rc2 = RC::SUCCESS;
      for (int j = i - 1; j >= 0; j--) {
        Record &tmp_record = records[j];
        rc2 = rollback_insert(trx, tmp_record.rid());
        if (rc2 != RC::SUCCESS) {
          LOG_ERROR("failed to rollback insert, rid: %d.%d", tmp_record.rid().page_num, tmp_record.rid().slot_num);
          break;
        }
      }
      return rc;
    }

    rc = insert_entry_of_indexes(current_record.data(), current_record.rid());
    if (rc != RC::SUCCESS) {
      LOG_WARN("insert index failed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));

      // rollback when insert failed
      RC rc2 = RC::SUCCESS;
      rc2 = record_handler_->delete_record(&current_record.rid());
      if (rc2 != RC::SUCCESS) {
        LOG_ERROR(
            "failed to rollback insert, rid: %d.%d", current_record.rid().page_num, current_record.rid().slot_num);
        break;
      }

      for (int j = i - 1; j >= 0; j--) {
        Record &tmp_record = records[j];
        rc2 = rollback_insert(trx, tmp_record.rid());
        if (rc2 != RC::SUCCESS) {
          LOG_ERROR("failed to rollback insert, rid: %d.%d", tmp_record.rid().page_num, tmp_record.rid().slot_num);
          break;
        }
      }
      return rc;
    }
  }

  // after insert all record successfully, do the trx
  if (trx != nullptr) {
    for (int i = 0; i < row_num; i++) {
      Record &current_record = records[i];
      rc = trx->insert_record(this, &current_record);
      if (rc != RC::SUCCESS) {
        LOG_WARN("Failed to log operation(insertion) to trx");

        // rollback trx record
        RC rc2 = RC::SUCCESS;
        for (int j = i - 1; j >= 0; j--) {
          Record &tmp_record = records[j];
          rc2 = trx->delete_record(this, &tmp_record);
          if (rc2 != RC::SUCCESS) {
            LOG_ERROR("failed to rollback trx, rc=%d:%s", rc2, strrc(rc2));
            break;
          }
        }

        // rollback records data and index
        for (int j = row_num - 1; j >= 0; j--) {
          Record &tmp_record = records[j];
          rc2 = rollback_insert(trx, tmp_record.rid());
          if (rc2 != RC::SUCCESS) {
            LOG_ERROR("failed to rollback insert, rid: %d.%d", tmp_record.rid().page_num, tmp_record.rid().slot_num);
            break;
          }
        }
        return rc;
      }
    }
  }

  // write opertions into clog
  if (trx != nullptr) {
    for (int i = 0; i < row_num; i++) {
      Record &current_record = records[i];
      CLogRecord *clog_record = nullptr;
      rc = clog_manager_->clog_gen_record(CLogType::REDO_INSERT,
          trx->get_current_id(),
          clog_record,
          name(),
          table_meta_.record_size(),
          &current_record);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to create a clog record. rc=%d:%s", rc, strrc(rc));
        return rc;
      }
      rc = clog_manager_->clog_append_record(clog_record);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
  }

  return rc;
}

RC Table::recover_insert_record(Record *record)
{
  RC rc = RC::SUCCESS;

  rc = record_handler_->recover_insert_record(record->data(), table_meta_.record_size(), &record->rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));
    return rc;
  }

  return rc;
}

RC Table::insert_record(Trx *trx, int row_num, int value_num, std::vector<const Value *> &values)
{
  RC rc = RC::SUCCESS;
  if (row_num <= 0 || value_num <= 0) {
    LOG_ERROR("Invalid argument. table name: %s, value num=%d", name(), value_num);
    return RC::INVALID_ARGUMENT;
  }
  for (size_t i = 0; i < values.size(); i++) {
    if (nullptr == values[i]) {
      LOG_ERROR("Invalid argument. values=%p", values[i]);
      return RC::INVALID_ARGUMENT;
    }
  }

  std::vector<Record> records;
  for (int i = 0; i < row_num; i++) {
    Record record;
    char *record_data;
    rc = make_record(value_num, values[i * value_num], record_data);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to create a record. rc=%d:%s", rc, strrc(rc));
      for (size_t j = 0; j < records.size(); j++) {
        delete[] records[j].data();
      }
      return rc;
    }
    record.set_data(record_data);
    records.emplace_back(record);
  }

  rc = insert_record(trx, row_num, records.data());
  for (size_t i = 0; i < records.size(); i++) {
    delete[] records[i].data();
  }
  return rc;
}

const char *Table::name() const
{
  return table_meta_.name();
}

const TableMeta &Table::table_meta() const
{
  return table_meta_;
}

bool Table::record_field_is_null(const char *record, int idx) const
{
  const FieldMeta *field = table_meta_.field(idx);
  if (!field->nullable()) {
    return false;
  }
  const FieldMeta *null_field = table_meta_.null_bitmap_field();
  common::Bitmap bitmap(const_cast<char *>(record) + null_field->offset(), null_field->len());
  return bitmap.get_bit(idx);
}

RC Table::change_record_value(char *&record, int idx, const Value &value) const
{
  const FieldMeta *null_field = table_meta_.null_bitmap_field();
  common::Bitmap bitmap(record + null_field->offset(), null_field->len());

  const FieldMeta *field = table_meta_.field(idx);
  // do check null again
  if (AttrType::NULLS == value.type) {
    if (!field->nullable()) {
      LOG_ERROR("Invalid value type. Cannot be null. table name =%s, field name=%s, type=%d, but given=%d",
          table_meta_.name(),
          field->name(),
          field->type(),
          value.type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
    bitmap.set_bit(idx);
    assert(nullptr == value.data);
    // make sure data all zero bit
    memset(record + field->offset(), 0, field->len());
    return RC::SUCCESS;
  }
  bitmap.clear_bit(idx);

  // do typecast
  void *tmp_data = nullptr;
  if (field->type() != value.type) {
    tmp_data = cast_to[value.type][field->type()](value.data);
    if (nullptr == tmp_data) {
      LOG_ERROR("Invalid value type. table name =%s, field name=%s, type=%d, but given=%d",
          table_meta_.name(),
          field->name(),
          field->type(),
          value.type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  } else {
    tmp_data = value.data;
  }

  size_t copy_len = field->len();
  if (field->type() == CHARS) {
    const size_t data_len = strlen((const char *)tmp_data);
    if (copy_len > data_len) {
      copy_len = data_len + 1;
    }
  }
  memcpy(record + field->offset(), tmp_data, copy_len);

  // need to release memory
  if (field->type() != value.type) {
    assert(nullptr != tmp_data);
    free(tmp_data);
  }
  return RC::SUCCESS;
}

RC Table::make_record(int value_num, const Value *values, char *&record_out)
{
  // 检查字段类型是否一致
  if (value_num + table_meta_.sys_field_num() + table_meta_.extra_filed_num() != table_meta_.field_num()) {
    LOG_WARN("Input values don't match the table's schema, table name:%s", table_meta_.name());
    return RC::SCHEMA_FIELD_MISSING;
  }

  Value *casted_values = new Value[value_num];
  DEFER([&]() { delete[] casted_values; });

  const int normal_field_start_index = table_meta_.sys_field_num();

  // 复制所有字段的值
  int record_size = table_meta_.record_size();
  char *record = new char[record_size];
  memset(record, 0, record_size);

  RC rc = RC::SUCCESS;
  for (int i = 0; i < value_num; i++) {
    rc = change_record_value(record, i + normal_field_start_index, values[i]);
    if (RC::SUCCESS != rc) {
      LOG_ERROR("Change Record Value Failed. RC = %d", rc);
      return rc;
    }
  }

  record_out = record;  // release in caller
  return RC::SUCCESS;
}

RC Table::init_record_handler(const char *base_dir)
{
  std::string data_file = table_data_file(base_dir, table_meta_.name());

  RC rc = BufferPoolManager::instance().open_file(data_file.c_str(), data_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s", data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  record_handler_ = new RecordFileHandler();
  rc = record_handler_->init(data_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%d:%s", rc, strrc(rc));
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
    delete record_handler_;
    record_handler_ = nullptr;
    return rc;
  }

  return rc;
}

RC Table::get_record_scanner(RecordFileScanner &scanner)
{
  RC rc = scanner.open_scan(*data_buffer_pool_, nullptr);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%d:%s", rc, strrc(rc));
  }
  return rc;
}

/**
 * 为了不把Record暴露出去，封装一下
 */
class RecordReaderScanAdapter {
public:
  explicit RecordReaderScanAdapter(void (*record_reader)(const char *data, void *context), void *context)
      : record_reader_(record_reader), context_(context)
  {}

  void consume(const Record *record)
  {
    record_reader_(record->data(), context_);
  }

private:
  void (*record_reader_)(const char *, void *);
  void *context_;
};

static RC scan_record_reader_adapter(Record *record, void *context)
{
  RecordReaderScanAdapter &adapter = *(RecordReaderScanAdapter *)context;
  adapter.consume(record);
  return RC::SUCCESS;
}

RC Table::scan_record(
    Trx *trx, ConditionFilter *filter, int limit, void *context, void (*record_reader)(const char *data, void *context))
{
  RecordReaderScanAdapter adapter(record_reader, context);
  return scan_record(trx, filter, limit, (void *)&adapter, scan_record_reader_adapter);
}

RC Table::scan_record(
    Trx *trx, ConditionFilter *filter, int limit, void *context, RC (*record_reader)(Record *record, void *context))
{
  if (nullptr == record_reader) {
    return RC::INVALID_ARGUMENT;
  }

  if (0 == limit) {
    return RC::SUCCESS;
  }

  if (limit < 0) {
    limit = INT_MAX;
  }

  IndexScanner *index_scanner = find_index_for_scan(filter);
  if (index_scanner != nullptr) {
    return scan_record_by_index(trx, index_scanner, filter, limit, context, record_reader);
  }

  RC rc = RC::SUCCESS;
  RecordFileScanner scanner;
  rc = scanner.open_scan(*data_buffer_pool_, filter);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  int record_count = 0;
  Record record;
  while (scanner.has_next()) {
    rc = scanner.next(record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to fetch next record. rc=%d:%s", rc, strrc(rc));
      return rc;
    }
    if (trx == nullptr || trx->is_visible(this, &record)) {
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        break;
      }
      record_count++;
    }
  }

  scanner.close_scan();
  return rc;
}

RC Table::scan_record_by_index(Trx *trx, IndexScanner *scanner, ConditionFilter *filter, int limit, void *context,
    RC (*record_reader)(Record *, void *))
{
  RC rc = RC::SUCCESS;
  RID rid;
  Record record;
  int record_count = 0;
  while (record_count < limit) {
    rc = scanner->next_entry(&rid);
    if (rc != RC::SUCCESS) {
      if (RC::RECORD_EOF == rc) {
        rc = RC::SUCCESS;
        break;
      }
      LOG_ERROR("Failed to scan table by index. rc=%d:%s", rc, strrc(rc));
      break;
    }

    rc = record_handler_->get_record(&rid, &record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to fetch record of rid=%d:%d, rc=%d:%s", rid.page_num, rid.slot_num, rc, strrc(rc));
      break;
    }

    if ((trx == nullptr || trx->is_visible(this, &record)) && (filter == nullptr || filter->filter(record))) {
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        LOG_TRACE("Record reader break the table scanning. rc=%d:%s", rc, strrc(rc));
        break;
      }
    }

    record_count++;
  }

  scanner->destroy();
  return rc;
}

class IndexInserter {
public:
  explicit IndexInserter(Index *index) : index_(index)
  {}

  RC insert_index(const Record *record)
  {
    return index_->insert_entry(record->data(), &record->rid());
  }

private:
  Index *index_;
};

static RC insert_index_record_reader_adapter(Record *record, void *context)
{
  IndexInserter &inserter = *(IndexInserter *)context;
  return inserter.insert_index(record);
}

RC Table::create_index(Trx *trx, bool unique, const char *index_name, int attr_num, const AttrInfo *attribute_name)
{
  if (common::is_blank(index_name)) {
    LOG_INFO("Invalid input arguments, table name is %s, index_name is blank", name());
    return RC::INVALID_ARGUMENT;
  }
  if (table_meta_.index(index_name) != nullptr) {
    LOG_INFO("Invalid input arguments, table name is %s, index %s exist", name(), index_name);
    return RC::SCHEMA_INDEX_EXIST;
  }

  std::vector<std::string> field_names;
  for (int i = 0; i < attr_num; i++) {
    if (common::is_blank(attribute_name[i].name)) {
      LOG_INFO("Invalid input arguments, table name is %s, attribute_name is blank", name());
      return RC::INVALID_ARGUMENT;
    }
    std::string field_name = attribute_name[i].name;
    field_names.push_back(field_name);
  }
  if (table_meta_.find_index_by_field(field_names)) {
    LOG_INFO("Invalid input arguments, table name is %s, attribute %s exist index", name(), index_name, attribute_name);
    return RC::SCHEMA_INDEX_EXIST;
  }

  IndexMeta new_index_meta;
  RC rc = new_index_meta.init(index_name, unique, field_names);
  if (rc != RC::SUCCESS) {
    LOG_INFO("Failed to init IndexMeta in table:%s, index_name:%s, field_name:%s", name(), index_name, attribute_name);
    return rc;
  }

  std::vector<int> field_idx;  //  每一列在bitmap中的位置
  std::vector<FieldMeta> field_metas;
  // index的第0个field是标记NULL的bitmap
  field_metas.push_back(*table_meta_.null_bitmap_field());
  for (int i = 0; i < attr_num; i++) {
    const FieldMeta *field_meta = table_meta_.field(attribute_name[i].name);
    if (!field_meta) {
      LOG_INFO("Invalid input arguments, there is no field of %s in table:%s.", attribute_name, name());
      return RC::SCHEMA_FIELD_MISSING;
    }
    FieldMeta tmp_field_meat = *field_meta;
    field_metas.push_back(tmp_field_meat);
  }

  // 创建索引相关数据
  BplusTreeIndex *index = new BplusTreeIndex();
  std::string index_file = table_index_file(base_dir_.c_str(), name(), index_name);
  rc = index->create(index_file.c_str(), new_index_meta, field_metas);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  IndexInserter index_inserter(index);
  rc = scan_record(trx, nullptr, -1, &index_inserter, insert_index_record_reader_adapter);
  if (rc != RC::SUCCESS) {
    // rollback
    delete index;
    LOG_ERROR("Failed to insert index to all records. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }
  indexes_.push_back(index);

  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }
  // 创建元数据临时文件
  std::string tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  std::fstream fs;
  fs.open(tmp_file, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR;  // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR;
  }
  fs.close();

  // 覆盖原始元数据文件
  std::string meta_file = table_meta_file(base_dir_.c_str(), name());
  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). "
              "system error=%d:%s",
        tmp_file.c_str(),
        meta_file.c_str(),
        index_name,
        name(),
        errno,
        strerror(errno));
    return RC::IOERR;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("Successfully added a new index (%s) on the table (%s)", index_name, name());

  return rc;
}

// rollback one update operation
RC Table::rollback_update(Trx *trx, Record &new_record, char *old_record_data)
{
  RC rc = RC::SUCCESS;
  // delete new index
  rc = delete_entry_of_indexes(new_record.data(), new_record.rid(), false);
  if (RC::SUCCESS != rc) {
    LOG_WARN("failed to delete index of new record (rid:%d,%d). rc=%d:%s",
        new_record.rid().page_num,
        new_record.rid().slot_num,
        rc,
        strrc(rc));
    return rc;
  }

  // rollback record data
  new_record.set_data(old_record_data);
  rc = record_handler_->update_record(&new_record);
  if (RC::SUCCESS != rc) {
    LOG_WARN("failed to rollback record data (rid:%d,%d). rc=%d:%s",
        new_record.rid().page_num,
        new_record.rid().slot_num,
        rc,
        strrc(rc));
    return rc;
  }

  // insert old index
  rc = insert_entry_of_indexes(old_record_data, new_record.rid());
  if (RC::SUCCESS != rc) {
    LOG_WARN("failed to insert index for old record (rid:%d,%d). rc=%d:%s",
        new_record.rid().page_num,
        new_record.rid().slot_num,
        rc,
        strrc(rc));
  }
  return rc;
}

RC Table::recover_update_record(Record *record)
{
  RC rc = RC::SUCCESS;

  rc = record_handler_->recover_update_record(record->data(), table_meta_.record_size(), &record->rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Update record failed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));
    return rc;
  }

  return rc;
}

RC Table::update_record(Trx *trx, const char *attribute_name, const Value *value, int condition_num,
    const Condition conditions[], int *updated_count)
{
  return RC::GENERIC_ERROR;
}

RC Table::update_record(
    Trx *trx, std::vector<const char *> &attr_names, std::vector<Record> &records, std::vector<const Value *> &values)
{
  RC rc = RC::SUCCESS;

  std::vector<int> field_idx;
  std::vector<int> field_offset;
  std::vector<int> field_length;
  std::vector<bool> field_nullable;

  int record_size = table_meta_.record_size();
  int sys_field_num = table_meta_.sys_field_num();      // ignore __trx column
  int extra_filed_num = table_meta_.extra_filed_num();  // ignore __null column
  int user_field_num = table_meta_.field_num() - sys_field_num - extra_filed_num;

  // find field info according to field_name. must find.
  for (size_t i = 0; i < attr_names.size(); i++) {
    for (int j = 0; j < user_field_num; j++) {
      const FieldMeta *field_meta = table_meta_.field(j + sys_field_num);
      const char *field_name = field_meta->name();
      if (0 != strcmp(field_name, attr_names[i])) {
        continue;
      }

      field_idx.emplace_back(j + sys_field_num);
      field_offset.emplace_back(field_meta->offset());
      field_length.emplace_back(field_meta->len());
      field_nullable.emplace_back(field_meta->nullable());
      break;
    }
  }

  // make new record
  std::vector<char *> old_records_data;
  std::vector<char *> new_records_data;
  for (auto itor = records.begin(); itor != records.end(); itor++) {
    // check null
    bool duplicate = true;
    for (size_t c_idx = 0; c_idx < field_idx.size(); c_idx++) {
      if (field_nullable[c_idx]) {
        if (record_field_is_null(itor->data(), field_idx[c_idx])) {
          if (AttrType::NULLS == values[c_idx]->type)
            continue;
          else
            duplicate = false;
        } else {
          duplicate = false;
        }
      } else {
        duplicate = false;
      }
    }
    std::cout << "IS duplicate: " << duplicate << std::endl;
    if (duplicate) {
      // remove this record;
      itor = --records.erase(itor);
      continue;
    }

    char *old_data = itor->data();
    char *new_data = new char[record_size];
    memcpy(new_data, old_data, record_size);
    for (size_t c_idx = 0; c_idx < field_idx.size(); c_idx++) {
      rc = change_record_value(new_data, field_idx[c_idx], *values[c_idx]);
      if (RC::SUCCESS != rc) {
        LOG_ERROR("Change Record Value Failed. RC = %d", rc);
        // free memory before return
        for (size_t j = 0; j < new_records_data.size(); j++) {
          delete[] new_records_data[j];
        }
        return rc;
      }
    }
    if (0 == memcmp(old_data, new_data, record_size)) {
      LOG_WARN("duplicate value");
      // ignore record when new_data is duplicate with old
      delete[] new_data;
      itor = --records.erase(itor);
      continue;
    }
    old_records_data.emplace_back(old_data);
    new_records_data.emplace_back(new_data);
    itor->set_data(new_data);
  }

  // update records
  for (size_t i = 0; i < records.size(); i++) {
    if (trx != nullptr) {
      trx->init_trx_info(this, records[i]);
    }

    // delete index of old_record
    rc = delete_entry_of_indexes(old_records_data[i], records[i].rid(), false);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to delete indexes of record (rid=%d.%d). rc=%d:%s",
          records[i].rid().page_num,
          records[i].rid().slot_num,
          rc,
          strrc(rc));
      // rollback when update failed
      RC rc2 = RC::SUCCESS;
      for (int j = i - 1; j >= 0; j--) {
        rc2 = rollback_update(trx, records[j], old_records_data[j]);
        if (rc2 != RC::SUCCESS) {
          LOG_ERROR("Failed to rollback update (rid=%d.%d). rc=%d:%s",
              records[j].rid().page_num,
              records[j].rid().slot_num,
              rc2,
              strrc(rc2));
          break;
        }
      }
      // free memory before return
      for (size_t j = 0; j < new_records_data.size(); j++) {
        delete[] new_records_data[j];
      }
      return rc;
    }

    //  update record data
    rc = record_handler_->update_record(&records[i]);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to update record (rid=%d.%d). rc=%d:%s",
          records[i].rid().page_num,
          records[i].rid().slot_num,
          rc,
          strrc(rc));
      // rollback when update failed
      RC rc2 = RC::SUCCESS;
      rc2 = insert_entry_of_indexes(old_records_data[i], records[i].rid());
      if (rc2 != RC::SUCCESS) {
        LOG_ERROR("Failed to rollback index (rid:%d,%d) rc=%d:%s",
            records[i].rid().page_num,
            records[i].rid().slot_num,
            rc2,
            strrc(rc2));
      } else {
        for (int j = i - 1; j >= 0; j--) {
          rc2 = rollback_update(trx, records[j], old_records_data[j]);
          if (rc2 != RC::SUCCESS) {
            LOG_ERROR("Failed to rollback update (rid=%d.%d). rc=%d:%s",
                records[j].rid().page_num,
                records[j].rid().slot_num,
                rc2,
                strrc(rc2));
            break;
          }
        }
      }
      // free memory before return
      for (size_t j = 0; j < new_records_data.size(); j++) {
        delete[] new_records_data[j];
      }
      return rc;
    }

    // add index for new_record
    rc = insert_entry_of_indexes(records[i].data(), records[i].rid());
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to insert index for new record (rid=%d.%d), rc=%d:%s",
          records[i].rid().page_num,
          records[i].rid().slot_num,
          rc,
          strrc(rc));
      // rollback when update failed
      RC rc2 = RC::SUCCESS;
      records[i].set_data(old_records_data[i]);
      rc2 = record_handler_->update_record(&records[i]);
      if (rc2 != RC::SUCCESS) {
        LOG_ERROR("Failed to rollback record (rid:%d,%d). rc=%d:%s",
            records[i].rid().page_num,
            records[i].rid().slot_num,
            rc2,
            strrc(rc2));
      } else if (RC::SUCCESS != (rc2 = insert_entry_of_indexes(old_records_data[i], records[i].rid()))) {
        LOG_ERROR("Failed to rollback index (rid:%d,%d). rc=%d:%s",
            records[i].rid().page_num,
            records[i].rid().slot_num,
            rc2,
            strrc(rc2));
      } else {
        for (int j = i - 1; j >= 0; j--) {
          rc2 = rollback_update(trx, records[j], old_records_data[j]);
          if (rc2 != RC::SUCCESS) {
            LOG_ERROR("Failed to rollback update (rid=%d.%d). rc=%d:%s",
                records[j].rid().page_num,
                records[j].rid().slot_num,
                rc2,
                strrc(rc2));
            break;
          }
        }
      }
      // free memory before return
      for (size_t j = 0; j < new_records_data.size(); j++) {
        delete[] new_records_data[j];
      }
      return rc;
    }
  }

  if (trx != nullptr) {
    // make trx record
    for (size_t i = 0; i < records.size(); i++) {
      trx->update_record(this, &records[i]);
    }

    // DO CLOG
    for (size_t i = 0; i < records.size(); i++) {
      CLogRecord *clog_record = nullptr;
      rc = clog_manager_->clog_gen_record(
          CLogType::REDO_UPDATE, trx->get_current_id(), clog_record, name(), table_meta_.record_size(), &records[i]);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to create a clog record. rc=%d:%s", rc, strrc(rc));
        return rc;
      }
      rc = clog_manager_->clog_append_record(clog_record);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to append clog record. rc=%d:%s", rc, strrc(rc));
        return rc;
      }
    }
  }

  return rc;
}

class RecordDeleter {
public:
  RecordDeleter(Table &table, Trx *trx) : table_(table), trx_(trx)
  {}

  RC delete_record(Record *record)
  {
    RC rc = RC::SUCCESS;
    rc = table_.delete_record(trx_, record);
    if (rc == RC::SUCCESS) {
      deleted_count_++;
    }
    return rc;
  }

  int deleted_count() const
  {
    return deleted_count_;
  }

private:
  Table &table_;
  Trx *trx_;
  int deleted_count_ = 0;
};

static RC record_reader_delete_adapter(Record *record, void *context)
{
  RecordDeleter &record_deleter = *(RecordDeleter *)context;
  return record_deleter.delete_record(record);
}

RC Table::delete_record(Trx *trx, ConditionFilter *filter, int *deleted_count)
{
  RecordDeleter deleter(*this, trx);
  RC rc = scan_record(trx, filter, -1, &deleter, record_reader_delete_adapter);
  if (deleted_count != nullptr) {
    *deleted_count = deleter.deleted_count();
  }
  return rc;
}

RC Table::delete_record(Trx *trx, Record *record)
{
  RC rc = RC::SUCCESS;

  rc = delete_entry_of_indexes(record->data(), record->rid(), false);  // 重复代码 refer to commit_delete
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record (rid=%d.%d). rc=%d:%s",
        record->rid().page_num,
        record->rid().slot_num,
        rc,
        strrc(rc));
    return rc;
  }

  rc = record_handler_->delete_record(&record->rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR(
        "Failed to delete record (rid=%d.%d). rc=%d:%s", record->rid().page_num, record->rid().slot_num, rc, strrc(rc));
    return rc;
  }

  if (trx != nullptr) {
    rc = trx->delete_record(this, record);

    CLogRecord *clog_record = nullptr;
    rc = clog_manager_->clog_gen_record(CLogType::REDO_DELETE, trx->get_current_id(), clog_record, name(), 0, record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to create a clog record. rc=%d:%s", rc, strrc(rc));
      return rc;
    }
    rc = clog_manager_->clog_append_record(clog_record);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  return rc;
}

RC Table::recover_delete_record(Record *record)
{
  RC rc = RC::SUCCESS;
  rc = record_handler_->delete_record(&record->rid());

  return rc;
}

RC Table::commit_delete(Trx *trx, const RID &rid)
{
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = delete_entry_of_indexes(record.data(), record.rid(), false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d). rc=%d:%s",
        rid.page_num,
        rid.slot_num,
        rc,
        strrc(rc));  // panic?
  }

  rc = record_handler_->delete_record(&rid);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return rc;
}

RC Table::rollback_delete(Trx *trx, const RID &rid)
{
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return trx->rollback_delete(this, record);  // update record in place
}

RC Table::insert_entry_of_indexes(const char *record, const RID &rid)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->insert_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      break;
    }
  }
  return rc;
}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}

Index *Table::find_index(const char *index_name) const
{
  for (Index *index : indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }
  return nullptr;
}
Index *Table::find_index_by_field(const char *field_name) const
{
  const TableMeta &table_meta = this->table_meta();
  const IndexMeta *index_meta = table_meta.find_index_by_field(field_name);
  if (index_meta != nullptr) {
    return this->find_index(index_meta->name());
  }
  return nullptr;
}

IndexScanner *Table::find_index_for_scan(const DefaultConditionFilter &filter)
{
  const ConDesc *field_cond_desc = nullptr;
  const ConDesc *value_cond_desc = nullptr;
  if (filter.left().is_attr && !filter.right().is_attr) {
    field_cond_desc = &filter.left();
    value_cond_desc = &filter.right();
  } else if (filter.right().is_attr && !filter.left().is_attr) {
    field_cond_desc = &filter.right();
    value_cond_desc = &filter.left();
  }
  if (field_cond_desc == nullptr || value_cond_desc == nullptr) {
    return nullptr;
  }

  const FieldMeta *field_meta = table_meta_.find_field_by_offset(field_cond_desc->attr_offset);
  if (nullptr == field_meta) {
    LOG_PANIC("Cannot find field by offset %d. table=%s", field_cond_desc->attr_offset, name());
    return nullptr;
  }

  const IndexMeta *index_meta = table_meta_.find_index_by_field(field_meta->name());
  if (nullptr == index_meta) {
    return nullptr;
  }

  Index *index = find_index(index_meta->name());
  if (nullptr == index) {
    return nullptr;
  }

  const char *left_key = nullptr;
  const char *right_key = nullptr;
  int left_len = 4;
  int right_len = 4;
  bool left_inclusive = false;
  bool right_inclusive = false;
  switch (filter.comp_op()) {
    case EQUAL_TO: {
      left_key = (const char *)value_cond_desc->value;
      right_key = (const char *)value_cond_desc->value;
      left_inclusive = true;
      right_inclusive = true;
    } break;
    case LESS_EQUAL: {
      right_key = (const char *)value_cond_desc->value;
      right_inclusive = true;
    } break;
    case GREAT_EQUAL: {
      left_key = (const char *)value_cond_desc->value;
      left_inclusive = true;
    } break;
    case LESS_THAN: {
      right_key = (const char *)value_cond_desc->value;
      right_inclusive = false;
    } break;
    case GREAT_THAN: {
      left_key = (const char *)value_cond_desc->value;
      left_inclusive = false;
    } break;
    default: {
      return nullptr;
    }
  }

  if (filter.attr_type() == CHARS) {
    left_len = left_key != nullptr ? strlen(left_key) : 0;
    right_len = right_key != nullptr ? strlen(right_key) : 0;
  }
  return index->create_scanner(left_key, left_len, left_inclusive, right_key, right_len, right_inclusive);
}

IndexScanner *Table::find_index_for_scan(const ConditionFilter *filter)
{
  if (nullptr == filter) {
    return nullptr;
  }

  // remove dynamic_cast
  const DefaultConditionFilter *default_condition_filter = dynamic_cast<const DefaultConditionFilter *>(filter);
  if (default_condition_filter != nullptr) {
    return find_index_for_scan(*default_condition_filter);
  }

  const CompositeConditionFilter *composite_condition_filter = dynamic_cast<const CompositeConditionFilter *>(filter);
  if (composite_condition_filter != nullptr) {
    int filter_num = composite_condition_filter->filter_num();
    for (int i = 0; i < filter_num; i++) {
      IndexScanner *scanner = find_index_for_scan(&composite_condition_filter->filter(i));
      if (scanner != nullptr) {
        return scanner;  // 可以找到一个最优的，比如比较符号是=
      }
    }
  }
  return nullptr;
}

RC Table::sync()
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
          name(),
          index->index_meta().name(),
          rc,
          strrc(rc));
      return rc;
    }
  }
  LOG_INFO("Sync table over. table=%s", name());
  return rc;
}
