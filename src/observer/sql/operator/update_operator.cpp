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

#include "common/lang/defer.h"
#include "common/log/log.h"
#include "sql/executor/execute_stage.h"
#include "sql/operator/update_operator.h"
#include "storage/record/record.h"
#include "storage/common/table.h"
#include "sql/stmt/update_stmt.h"
#include "util/typecast.h"

RC UpdateOperator::open()
{
  RC rc = RC::SUCCESS;
  if (children_.size() != 1) {
    LOG_WARN("update operator must has 1 child");
    return RC::INTERNAL;
  }

  // execute sub query firstly
  auto get_cell_for_sub_query = [](const SubQueryExpression *expr, TupleCell &cell) {
    expr->open_sub_query();
    RC rc = expr->get_value(cell);
    if (RC::RECORD_EOF == rc) {
      // e.g. a = select a  -> a = null
      cell.set_null();
    } else if (RC::SUCCESS == rc) {
      TupleCell tmp_cell;
      if (RC::SUCCESS == (rc = expr->get_value(tmp_cell))) {
        // e.g. a = select a  -> a = (1, 2, 3)
        // std::cout << "Should not have rows more than 1" << std::endl;
        expr->close_sub_query();
        return RC::INTERNAL;
      }
    } else {
      expr->close_sub_query();
      return rc;
    }
    expr->close_sub_query();
    return RC::SUCCESS;
  };

  // std::cout << "DO PREDICATE: comp : " << comp << std::endl;
  // remember to release it
  std::vector<const Value *> values;
  DEFER([&]() {
    for (auto value : values) {
      if (nullptr != value) {
        delete value;
      }
    }
  });
  std::vector<Operator *> delete_opers;

  for (size_t i = 0; i < update_stmt_->exprs().size(); ++i) {
    auto expr = update_stmt_->exprs()[i];
    TupleCell cell;
    if (ExprType::SUBQUERYTYPE == expr->type()) {
      auto sub_query_expr = (SubQueryExpression *)expr;
      const SelectStmt *sub_select = sub_query_expr->get_sub_query_stmt();
      ProjectOperator *sub_project = nullptr;
      if (RC::SUCCESS != (rc = ExecuteStage::gen_physical_plan(sub_select, sub_project, delete_opers))) {
        return rc;
      }
      assert(nullptr != sub_project);
      sub_query_expr->set_sub_query_top_oper(sub_project);

      if (RC::SUCCESS != (rc = get_cell_for_sub_query((const SubQueryExpression *)expr, cell))) {
        LOG_ERROR("Update get cell for sub_query failed. RC = %d:%s", rc, strrc(rc));
        return rc;
      }
    } else {
      assert(ExprType::VALUE == expr->type());
      ((ValueExpr *)expr)->get_tuple_cell(cell);
    }

    auto field_meta = update_stmt_->fields()[i];
    const AttrType field_type = field_meta->type();
    const AttrType value_type = cell.attr_type();

    // check null first
    if (AttrType::NULLS == value_type) {
      if (!field_meta->nullable()) {
        LOG_WARN("field type mismatch. can not be null. table=%s, field=%s, field type=%d, value_type=%d",
            update_stmt_->table()->name(),
            field_meta->name(),
            field_type,
            value_type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    } else {
      // check typecast
      if (field_type != value_type && type_cast_not_support(value_type, field_type)) {
        LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
            update_stmt_->table()->name(),
            field_meta->name(),
            field_type,
            value_type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }

    Value *value = new Value();
    value->type = cell.attr_type();
    value->data = (char *)cell.data();
    values.emplace_back(value);
  }

  Operator *child = children_[0];
  rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  std::vector<Record> old_records;
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get current record. rc=%s", strrc(rc));
      break;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record record = row_tuple->record();
    old_records.emplace_back(record);
  }
  if (RC::RECORD_EOF != rc) {
    LOG_WARN("get record failed!");
    return rc;
  }

  Table *table = update_stmt_->table();
  rc = table->update_record(trx_, update_stmt_->attr_names(), old_records, values);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to update records: %s", strrc(rc));
  }

  return rc;
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
