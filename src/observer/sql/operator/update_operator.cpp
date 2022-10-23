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
// Created by ZhangCL on 2022/10/13.
//

#include "common/log/log.h"
#include "sql/operator/update_operator.h"
#include "storage/record/record.h"
#include "storage/common/table.h"
#include "sql/stmt/update_stmt.h"

RC UpdateOperator::open()
{
  RC rc = RC::SUCCESS;
  if (children_.size() != 1) {
    LOG_WARN("update operator must has 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  std::vector<Record> old_records;      // 存储更新前的record
  std::vector<Record> updated_records;  // 存储更新后的record

  Table *table = update_stmt_->table();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get current record. rc=%s", strrc(rc));
      break;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record &record = row_tuple->record();

    int record_size = table->table_meta().record_size();
    char *old_data = new char[record_size];        // old_record->data
    memcpy(old_data, record.data(), record_size);  // old_record->data
    char *data = new char[record_size];            // new_record->data
    memcpy(data, record.data(), record_size);      // new_record->data

    Record old_record = record;
    old_record.set_data(old_data);
    old_records.push_back(old_record);

    // construct new record
    for (size_t idx = 0; idx < update_stmt_->attr_names().size(); idx++) {
      int field_offset = -1;
      int field_length = -1;
      const int sys_field_num = table->table_meta().sys_field_num();
      const int user_field_num = table->table_meta().field_num() - sys_field_num;
      for (int i = 0; i < user_field_num; i++) {
        const FieldMeta *field_meta = table->table_meta().field(i + sys_field_num);
        const char *field_name = field_meta->name();
        if (0 != strcmp(field_name, update_stmt_->attr_names()[idx])) {
          continue;
        }

        const AttrType field_type = field_meta->type();
        const AttrType value_type = update_stmt_->values()[idx].type;
        if (field_type != value_type) {  // TODO try to convert the value type to field type
          LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
              table->name(),
              field_meta->name(),
              field_type,
              value_type);
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }

        field_offset = field_meta->offset();
        field_length = field_meta->len();
        break;
      }
      if (field_offset == -1 || field_length == -1) {
        LOG_ERROR("failed to get filed offset or length");
        return RC::SCHEMA_FIELD_NOT_EXIST;
      }
      memcpy(data + field_offset, update_stmt_->values()[idx].data, field_length);
    }

    // compare old_record_data and new_record_data. skip this reocrd when same
    if (0 == memcmp(data, old_data, record_size)) {
      LOG_WARN("duplicate value");
      continue;
    }
    record.set_data(data);

    // update record
    rc = table->update_record(trx_, &record, old_data);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: rid=%d.%d, ret=%s", record.rid().page_num, record.rid().slot_num, strrc(rc));

      // TO DO ROLLBACK RECORDS
      for (size_t i = 0; i < updated_records.size(); i++) {
        RC rc2 = table->update_record(trx_, &old_records[i], updated_records[i].data());
        if (rc2 != RC::SUCCESS) {
          LOG_ERROR("rollback record error, rid=%d.%d, ret=%s",
              old_records[i].rid().page_num,
              old_records[i].rid().slot_num,
              strrc(rc2));
          break;
        }
      }
      return rc;
    }
    updated_records.push_back(record);
    row_num_++;
  }

  // free memory
  for (size_t i = 0; i < old_records.size(); i++) {
    delete[] old_records[i].data();
  }
  for (size_t i = 0; i < updated_records.size(); i++) {
    delete[] updated_records[i].data();
  }

  if (RC::RECORD_EOF != rc) {
    LOG_WARN("update failed!");
    return rc;
  }

  return RC::SUCCESS;
}

RC UpdateOperator::next()
{
  return RC::RECORD_EOF;
}

RC UpdateOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}