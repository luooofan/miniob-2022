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

#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"

void FieldExpr::to_string(std::ostream &os) const
{
  if (with_brace()) {
    os << '(';
  }
  os << field_.table_name();
  os << '.';
  os << field_.field_name();
  if (with_brace()) {
    os << ')';
  }
}
RC FieldExpr::get_value(const Tuple &tuple, TupleCell &cell) const
{
  return tuple.find_cell(field_, cell);
}

void ValueExpr::to_string(std::ostream &os) const
{
  if (with_brace()) {
    os << '(';
  }
  tuple_cell_.to_string(os);
  if (with_brace()) {
    os << ')';
  }
}
RC ValueExpr::get_value(const Tuple &tuple, TupleCell &cell) const
{
  cell = tuple_cell_;
  return RC::SUCCESS;
}

const char BinaryExpression::get_op_char() const
{
  switch (op_) {
    case ADD_OP:
      return '+';
      break;
    case SUB_OP:
      return '-';
      break;
    case MUL_OP:
      return '*';
      break;
    case DIV_OP:
      return '/';
      break;
    default:
      LOG_ERROR("unsupported op");
      break;
  }
  return '?';
}
RC BinaryExpression::get_value(const Tuple &tuple, TupleCell &final_cell) const
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
void BinaryExpression::to_string(std::ostream &os) const
{
  if (with_brace()) {
    os << '(';
  }
  if (is_minus_) {
    os << '-';
  } else {
    left_expr_->to_string(os);
    os << get_op_char();
  }
  right_expr_->to_string(os);
  if (with_brace()) {
    os << ')';
  }
}

std::string AggrFuncExpr::get_func_name() const
{
  switch (type_) {
    case AggrFuncType::MAX:
      return "max";
    case AggrFuncType::MIN:
      return "min";
    case AggrFuncType::SUM:
      return "sum";
    case AggrFuncType::AVG:
      return "avg";
    case AggrFuncType::COUNT:
      return "count";
    default:
      break;
  }
  return "unknown_aggr_fun";
}
AttrType AggrFuncExpr::get_return_type() const
{
  switch (type_) {
    case AggrFuncType::MAX:
    case AggrFuncType::MIN:
    case AggrFuncType::SUM:
      return field_.attr_type();
      break;
    case AggrFuncType::AVG:
      // TODO(wbj)
      break;
    case AggrFuncType::COUNT:
      return INTS;
      break;
    default:
      return UNDEFINED;
      break;
  }
  return UNDEFINED;
}
void AggrFuncExpr::to_string(std::ostream &os) const
{
  if (with_brace()) {
    os << '(';
  }
  os << get_func_name();
  os << '(';
  os << field_.table_name();
  os << '.';
  os << field_.field_name();
  os << ')';
  if (with_brace()) {
    os << ')';
  }
}
RC AggrFuncExpr::get_value(const Tuple &tuple, TupleCell &cell) const
{
  // TOOD(wbj)
  return tuple.find_cell(field_, cell);
}
void AggrFuncExpr::get_aggrfuncexprs(const Expression *expr, std::vector<AggrFuncExpr *> &aggrfunc_exprs)
{
  switch (expr->type()) {
    case ExprType::AGGRFUNC: {
      const AggrFuncExpr *afexp = (const AggrFuncExpr *)expr;
      aggrfunc_exprs.emplace_back(const_cast<AggrFuncExpr *>(afexp));
    }
    case ExprType::BINARY: {
      const BinaryExpression *bexp = (const BinaryExpression *)expr;
      get_aggrfuncexprs(bexp->get_left(), aggrfunc_exprs);
      get_aggrfuncexprs(bexp->get_right(), aggrfunc_exprs);
      break;
    }
    default:
      break;
  }
  return;
}
