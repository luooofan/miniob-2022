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
// Created by Meiyi & Wangyunlai on 2021/5/12.
//

#ifndef __OBSERVER_STORAGE_COMMON_TABLE_H__
#define __OBSERVER_STORAGE_COMMON_TABLE_H__

#include "storage/common/table_meta.h"

struct RID;
class Record;
class DiskBufferPool;
class RecordFileHandler;
class RecordFileScanner;
class ConditionFilter;
class DefaultConditionFilter;
class Index;
class IndexScanner;
class RecordDeleter;
class Trx;
class CLogManager;

// TODO remove the routines with condition
class Table {
public:
  Table() = default;
  ~Table();

  /**
   * 创建一个表
   * @param path 元数据保存的文件(完整路径)
   * @param name 表名
   * @param base_dir 表数据存放的路径
   * @param attribute_count 字段个数
   * @param attributes 字段
   * @param clog_manager clog管理器，用于维护redo log
   */
  RC create(const char *path, const char *name, const char *base_dir, int attribute_count, const AttrInfo attributes[],
      CLogManager *clog_manager);

  /**
   * 打开一个表
   * @param meta_file 保存表元数据的文件完整路径
   * @param base_dir 表所在的文件夹，表记录数据文件、索引数据文件存放位置
   * @param clog_manager clog管理器
   */
  RC open(const char *meta_file, const char *base_dir, CLogManager *clog_manager);

  /**
   * remove a table
   * @param path the full path of table meta file (/path/to/table_name.table)
   * @param name the name of table to be removed
   */
  RC remove(const char *name);

  RC insert_record(Trx *trx, int value_num, const Value *values)
  {
    std::vector<const Value *> values_;
    for (int i = 0; i < value_num; i++) {
      values_.emplace_back(values + i);
    }
    return insert_record(trx, 1, value_num, values_);
  }
  RC insert_record(Trx *trx, int row_num, int value_num, std::vector<const Value *> &values);

  RC recover_update_record(Record *record);
  RC update_record(Trx *trx, const char *attribute_name, const Value *value, int condition_num,
      const Condition conditions[], int *updated_count);
  RC update_record(Trx *trx, std::vector<const char *> &attr_names, std::vector<Record> &records,
      std::vector<const Value *> &values);
  RC delete_record(Trx *trx, ConditionFilter *filter, int *deleted_count);
  RC delete_record(Trx *trx, Record *record);
  RC recover_delete_record(Record *record);

  RC scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context,
      void (*record_reader)(const char *data, void *context));

  RC create_index(Trx *trx, bool unique, const char *index_name, int attr_num, const AttrInfo *attribute_name);

  RC get_record_scanner(RecordFileScanner &scanner);

  RecordFileHandler *record_handler() const
  {
    return record_handler_;
  }

public:
  const char *name() const;

  const TableMeta &table_meta() const;

  RC sync();

public:
  RC commit_insert(Trx *trx, const RID &rid);
  RC commit_delete(Trx *trx, const RID &rid);
  RC rollback_insert(Trx *trx, const RID &rid);
  RC rollback_update(Trx *trx, Record &new_record, char *old_record_data);
  RC rollback_delete(Trx *trx, const RID &rid);

private:
  RC scan_record(
      Trx *trx, ConditionFilter *filter, int limit, void *context, RC (*record_reader)(Record *record, void *context));
  RC scan_record_by_index(Trx *trx, IndexScanner *scanner, ConditionFilter *filter, int limit, void *context,
      RC (*record_reader)(Record *record, void *context));
  IndexScanner *find_index_for_scan(const ConditionFilter *filter);
  IndexScanner *find_index_for_scan(const DefaultConditionFilter &filter);
  RC insert_record(Trx *trx, int row_num, Record *records);

public:
  RC recover_insert_record(Record *record);

private:
  friend class RecordUpdater;
  friend class RecordDeleter;

  RC insert_entry_of_indexes(const char *record, const RID &rid);
  RC delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists);

private:
  RC init_record_handler(const char *base_dir);
  bool record_field_is_null(const char *record, int idx) const;
  RC change_record_value(char *&record, int idx, const Value &value) const;
  RC make_record(int value_num, const Value *values, char *&record_out);

public:
  Index *find_index(const char *index_name) const;
  Index *find_index_by_field(const char *field_name) const;

private:
  std::string base_dir_;
  CLogManager *clog_manager_;
  TableMeta table_meta_;
  DiskBufferPool *data_buffer_pool_ = nullptr;   /// 数据文件关联的buffer pool
  RecordFileHandler *record_handler_ = nullptr;  /// 记录操作
  std::vector<Index *> indexes_;
};

#endif  // __OBSERVER_STORAGE_COMMON_TABLE_H__
