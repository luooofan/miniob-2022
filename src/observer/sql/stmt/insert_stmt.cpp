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

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "util/typecast.h"

InsertStmt::InsertStmt(Table *table, std::vector<const Value *> &rows, int row_amount, int value_amount)
    : table_(table), row_amount_(row_amount), value_amount_(value_amount), rows_(rows)
{}

RC InsertStmt::create(Db *db, const Inserts &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name;
  if (nullptr == db || nullptr == table_name || inserts.value_num <= 0) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d", db, table_name, inserts.value_num);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the fields number
  const int row_num = inserts.row_num;
  const int value_num = inserts.value_num;
  const TableMeta &table_meta = table->table_meta();
  const int sys_field_num = table_meta.sys_field_num();
  const int field_num = table_meta.field_num() - sys_field_num - table_meta.extra_filed_num();
  if (field_num != value_num) {
    LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
    return RC::SCHEMA_FIELD_MISSING;
  }

  std::vector<const Value *> rows;
  for (int i = 0; i < row_num; i++) {
    // check fields type
    const int sys_field_num = table_meta.sys_field_num();
    for (int j = 0; j < value_num; j++) {
      const Value *value = &inserts.values[i][j];
      const FieldMeta *field_meta = table_meta.field(j + sys_field_num);
      const AttrType field_type = field_meta->type();
      const AttrType value_type = value->type;
      // check null first
      if (AttrType::NULLS == value_type) {
        if (!field_meta->nullable()) {
          LOG_WARN("field type mismatch. can not be null. table=%s, field=%s, field type=%d, value_type=%d",
              table_name,
              field_meta->name(),
              field_type,
              value_type);
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
        rows.push_back(value);
        continue;
      }
      // check typecast
      if (field_type != value_type && type_cast_not_support(value_type, field_type)) {
        LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
            table_name,
            field_meta->name(),
            field_type,
            value_type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      rows.push_back(value);
    }
  }

  // everything alright
  stmt = new InsertStmt(table, rows, row_num, value_num);
  return RC::SUCCESS;
}
