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
// Created by Wangyunlai on 2022/07/05.
//

#pragma once

#include <cassert>
#include <string.h>
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "storage/common/field.h"
#include "sql/expr/tuple_cell.h"

class Tuple;

enum class ExprType {
  NONE,
  FIELD,
  VALUE,
  BINARY,
};

class Expression {
public:
  Expression() = default;
  virtual ~Expression() = default;

  virtual RC get_value(const Tuple &tuple, TupleCell &cell) const = 0;
  virtual ExprType type() const = 0;
};

class FieldExpr : public Expression {
public:
  FieldExpr() = default;
  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field)
  {}

  virtual ~FieldExpr() = default;

  ExprType type() const override
  {
    return ExprType::FIELD;
  }

  Field &field()
  {
    return field_;
  }

  const Field &field() const
  {
    return field_;
  }

  const Table *table() const
  {
    return field_.table();
  }

  const char *table_name() const
  {
    return field_.table_name();
  }

  const char *field_name() const
  {
    return field_.field_name();
  }

  RC get_value(const Tuple &tuple, TupleCell &cell) const override;

private:
  Field field_;
};

class ValueExpr : public Expression {
public:
  ValueExpr() = default;
  ValueExpr(const Value &value) : tuple_cell_(value.type, (char *)value.data)
  {
    if (value.type == CHARS) {
      tuple_cell_.set_length(strlen((const char *)value.data));
    }
  }

  virtual ~ValueExpr() = default;

  RC get_value(const Tuple &tuple, TupleCell &cell) const override;
  ExprType type() const override
  {
    return ExprType::VALUE;
  }

  void get_tuple_cell(TupleCell &cell) const
  {
    cell = tuple_cell_;
  }

private:
  TupleCell tuple_cell_;
};

class BinaryExpression : public Expression {
public:
  BinaryExpression() = default;
  BinaryExpression(ExpOp op, Expression *left_expr, Expression *right_expr)
      : op_(op), left_expr_(left_expr), right_expr_(right_expr)
  {}

  virtual ~BinaryExpression() = default;

  RC get_value(const Tuple &tuple, TupleCell &final_cell) const override
  {
    TupleCell left_cell;
    TupleCell right_cell;
    RC rc = left_expr_->get_value(tuple, left_cell);
    rc = right_expr_->get_value(tuple, right_cell);
    // calculate
    assert(left_cell.attr_type() != DATES && right_cell.attr_type() != DATES);
    assert(left_cell.attr_type() != CHARS && right_cell.attr_type() != CHARS);
    switch (op_) {
      case ADD_OP:
        final_cell = TupleCell::add(left_cell, right_cell);
        break;
      case SUB_OP:
        final_cell = TupleCell::sub(left_cell, right_cell);
        break;
      case MUL_OP:
        final_cell = TupleCell::mul(left_cell, right_cell);
        break;
      case DIV_OP:
        final_cell = TupleCell::div(left_cell, right_cell);
        break;
      default:
        LOG_ERROR("unsupported calculate op");
        break;
    }

    // at first, convert to float
    return rc;
  }
  ExprType type() const override
  {
    return ExprType::BINARY;
  }

private:
  ExpOp op_ = NO_EXP_OP;
  Expression *left_expr_ = nullptr;
  Expression *right_expr_ = nullptr;
  TupleCell expr_result_;
};
