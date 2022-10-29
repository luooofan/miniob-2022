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
#include "sql/stmt/select_stmt.h"
#include "storage/common/db.h"
#include "storage/common/field_meta.h"
#include "storage/common/table.h"
#include "util/typecast.h"

// UpdateStmt::UpdateStmt(Table *table, Value *values, int value_amount)
//     : table_(table), values_(values), value_amount_(value_amount)
UpdateStmt::UpdateStmt(Table *table, std::vector<const char *> &attr_names, std::vector<const Expression *> &exprs,
    std::vector<const FieldMeta *> &fields, FilterStmt *filter_stmt)
    : table_(table), attr_names_(attr_names), exprs_(exprs), fields_(fields), filter_stmt_(filter_stmt)
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
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::vector<const char *> attr_names;
  std::vector<const Expression *> expressions;
  std::vector<const FieldMeta *> fields;
  const TableMeta &table_meta = table->table_meta();
  const int sys_field_num = table_meta.sys_field_num();
  const int extra_field_num = table_meta.extra_filed_num();
  const int user_field_num = table_meta.field_num() - sys_field_num - extra_field_num;

  for (size_t i = 0; i < update.attribute_num; i++) {
    bool field_exist = false;
    const char *attr_name = update.attribute_names[i].name;
    if (nullptr == attr_name) {
      LOG_WARN("invalid argument. attribute_name=%p", attr_name);
      return RC::INVALID_ARGUMENT;
    }

    const Expr *expr = &update.exprs[i];
    for (int j = 0; j < user_field_num; j++) {
      const FieldMeta *field_meta = table_meta.field(j + sys_field_num);
      const char *field_name = field_meta->name();
      if (0 != strcmp(field_name, attr_name)) {
        continue;
      }

      field_exist = true;

      Expression *expression = nullptr;
      const std::unordered_map<std::string, Table *> table_map;
      const std::vector<Table *> tables;
      if (ExpType::UNARY == expr->type) {
        const UnaryExpr *u_expr = expr->uexp;
        if (u_expr->is_attr) {
          return RC::SQL_SYNTAX;
        }
        RC rc = ValueExpr::create_expression(expr, table_map, tables, expression);
        if (RC::SUCCESS != rc) {
          LOG_ERROR("UpdateStmt Create ValueExpr Failed. RC = %d:%s", rc, strrc(rc));
          return rc;
        }
      } else if (ExpType::SUBQUERY == expr->type) {
        // will check projects num
        RC rc = SubQueryExpression::create_expression(expr, table_map, tables, expression, CompOp::EQUAL_TO, db);
        if (RC::SUCCESS != rc) {
          LOG_ERROR("UpdateStmt Create SubQueryExpression Failed. RC = %d:%s", rc, strrc(rc));
          return rc;
        }
      } else {
        return RC::SQL_SYNTAX;
      }

      assert(nullptr != expression);
      expressions.emplace_back(expression);
      fields.emplace_back(field_meta);
      break;
    }

    if (!field_exist) {
      LOG_WARN("Field %s.%s is not exist", table_name, attr_name);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    attr_names.emplace_back(attr_name);
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
  stmt = new UpdateStmt(table, attr_names, expressions, fields, filter_stmt);
  return RC::SUCCESS;
}
// const AttrType value_type = value->type;
// const AttrType field_type = field_meta->type();
// check null first
// if (AttrType::NULLS == value_type) {
//   if (!field_meta->nullable()) {
//     LOG_WARN("field type mismatch. can not be null. table=%s, field=%s, field type=%d, value_type=%d",
//         table_name,
//         field_meta->name(),
//         field_type,
//         value_type);
//     return RC::SCHEMA_FIELD_TYPE_MISMATCH;
//   }
//   break;  // pass check
// }
// // check typecast
// if (field_type != value_type && type_cast_not_support(value_type, field_type)) {
//   LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
//       table_name,
//       field_meta->name(),
//       field_type,
//       value_type);
//   return RC::SCHEMA_FIELD_TYPE_MISMATCH;
// }
