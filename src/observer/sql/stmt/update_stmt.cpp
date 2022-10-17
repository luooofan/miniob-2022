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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "storage/common/db.h"
#include "storage/common/table.h"

// UpdateStmt::UpdateStmt(Table *table, Value *values, int value_amount)
//     : table_(table), values_(values), value_amount_(value_amount)
UpdateStmt::UpdateStmt(Table *table, const char *attr_name, Value *value, FilterStmt *filter_stmt)
    : table_(table), attr_name_(attr_name), values_(value), filter_stmt_(filter_stmt)
{}

UpdateStmt::~UpdateStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, const Updates &update, Stmt *&stmt)
{
  const char *table_name = update.relation_name;
  const char *attr_name = update.attribute_name;
  if (nullptr == db || nullptr == table_name || nullptr == attr_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, field_name=%p", db, table_name, attr_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  bool field_exist = false;
  Value value = update.value;
  const TableMeta &table_meta = table->table_meta();
  const int sys_field_num = table_meta.sys_field_num();
  const int user_field_num = table_meta.field_num() - sys_field_num;
  for (int i = 0; i < user_field_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i + sys_field_num);
    const char *field_name = field_meta->name();
    if (0 != strcmp(field_name, attr_name)) {
      continue;
    }

    const AttrType field_type = field_meta->type();
    const AttrType value_type = value.type;
    if (field_type != value_type) {  // TODO try to convert the value type to field type
      LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
          table_name,
          field_meta->name(),
          field_type,
          value_type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }

    field_exist = true;
    break;
  }
  if (!field_exist) {
    LOG_WARN("Field %s.%s is not exist", table_name, attr_name);
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  // make filter
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, table, &table_map, update.conditions, update.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // everything alright
  stmt = new UpdateStmt(table, attr_name, &value, filter_stmt);
  return RC::SUCCESS;
}
