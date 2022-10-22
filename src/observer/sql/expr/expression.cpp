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
#include "common/lang/string.h"
#include "sql/expr/tuple.h"
#include <unordered_map>

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
bool FieldExpr::in_expression(const Expression *expr) const
{
  switch (expr->type()) {
    case ExprType::FIELD: {
      return field_.equal(((const FieldExpr *)expr)->field_);
    }
    case ExprType::AGGRFUNCTION: {
      const AggrFuncExpression *afexp = (const AggrFuncExpression *)expr;
      return in_expression(&afexp->fieldexpr());
    }
    case ExprType::BINARY: {
      const BinaryExpression *bexp = (const BinaryExpression *)expr;
      return in_expression(bexp->get_left()) || in_expression(bexp->get_right());
    }
    default:
      break;
  }
  return false;
}
void FieldExpr::get_fieldexprs_without_aggrfunc(const Expression *expr, std::vector<FieldExpr *> &field_exprs)
{
  switch (expr->type()) {
    case ExprType::FIELD: {
      const FieldExpr *fdexp = (const FieldExpr *)expr;
      field_exprs.emplace_back(const_cast<FieldExpr *>(fdexp));
      break;
    }
    case ExprType::AGGRFUNCTION: {
      // const AggrFuncExpression *afexp = (const AggrFuncExpression *)expr;
      // get_fieldexprs_without_aggrfunc(&afexp->fieldexpr(), field_exprs);
      break;
    }
    case ExprType::BINARY: {
      const BinaryExpression *bexp = (const BinaryExpression *)expr;
      get_fieldexprs_without_aggrfunc(bexp->get_left(), field_exprs);
      get_fieldexprs_without_aggrfunc(bexp->get_right(), field_exprs);
      break;
    }
    default:
      break;
  }
  return;
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

std::string AggrFuncExpression::get_func_name() const
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
AttrType AggrFuncExpression::get_return_type() const
{
  switch (type_) {
    case AggrFuncType::MAX:
    case AggrFuncType::MIN:
    case AggrFuncType::SUM:
      return field_->attr_type();
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
void AggrFuncExpression::to_string(std::ostream &os) const
{
  // TODO(wbj) if value_ != nullptr
  if (with_brace()) {
    os << '(';
  }
  os << get_func_name();
  os << '(';
  os << field_->table_name();
  os << '.';
  os << field_->field_name();
  os << ')';
  if (with_brace()) {
    os << ')';
  }
}
RC AggrFuncExpression::get_value(const Tuple &tuple, TupleCell &cell) const
{
  // when project tuple call this function, need to pack aggr_func_type in field
  // the field with aggr_func_type will be used in GroupTuple.find_cell
  Field tmp_field(field_->field());
  tmp_field.set_aggr(type_);
  return tuple.find_cell(tmp_field, cell);
}
void AggrFuncExpression::get_aggrfuncexprs(const Expression *expr, std::vector<AggrFuncExpression *> &aggrfunc_exprs)
{
  switch (expr->type()) {
    case ExprType::AGGRFUNCTION: {
      const AggrFuncExpression *afexp = (const AggrFuncExpression *)expr;
      aggrfunc_exprs.emplace_back(const_cast<AggrFuncExpression *>(afexp));
      break;
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

RC Expression::create_expression(const Expr *expr, const std::unordered_map<std::string, Table *> &table_map,
    const std::vector<Table *> &tables, Expression *&res_expr)
{
  bool with_brace = expr->with_brace;
  if (expr->type == UNARY) {
    UnaryExpr *uexpr = expr->uexp;
    if (uexpr->is_attr) {
      const char *table_name = uexpr->attr.relation_name;
      const char *field_name = uexpr->attr.attribute_name;
      if (common::is_blank(table_name)) {
        if (tables.size() != 1) {
          LOG_WARN("invalid. I do not know the attr's table. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        Table *table = tables[0];
        const FieldMeta *field_meta = table->table_meta().field(field_name);
        if (nullptr == field_meta) {
          LOG_WARN("no such field. field=%s.%s", table->name(), field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        res_expr = new FieldExpr(table, field_meta, with_brace);
        return RC::SUCCESS;
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        const FieldMeta *field_meta = table->table_meta().field(field_name);
        if (nullptr == field_meta) {
          LOG_WARN("no such field. field=%s.%s", table->name(), field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        res_expr = new FieldExpr(table, field_meta, with_brace);
        return RC::SUCCESS;
      }
    } else {
      res_expr = new ValueExpr(uexpr->value, with_brace);
      return RC::SUCCESS;
    }
  } else if (expr->type == BINARY) {
    Expression *left_expr;
    Expression *right_expr;
    RC rc = create_expression(expr->bexp->left, table_map, tables, left_expr);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    rc = create_expression(expr->bexp->right, table_map, tables, right_expr);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    res_expr = new BinaryExpression(expr->bexp->op, left_expr, right_expr, with_brace, expr->bexp->minus);
    return RC::SUCCESS;
  } else if (expr->type == FUNC) {
    Expression *param_expr1;
    Expression *param_expr2;
    switch (expr->fexp->type) {
      case FUNC_LENGTH: {
        RC rc = create_expression(expr->fexp->params[0], table_map, tables, param_expr1);
        if (rc != RC::SUCCESS) {
          return rc;
        }
        // res_expr = new FuncExpression(expr->fexp->type, expr->fexp->param_size, param_expr1, param_expr2,
        // with_brace);
        break;
      }
      case FUNC_ROUND: {
        RC rc = create_expression(expr->fexp->params[0], table_map, tables, param_expr1);
        if (rc != RC::SUCCESS) {
          return rc;
        }
        if (expr->fexp->param_size == 2) {
          rc = create_expression(expr->fexp->params[1], table_map, tables, param_expr2);
          if (rc != RC::SUCCESS) {
            return rc;
          }
        }
        // res_expr = new FuncExpression(expr->fexp->type, expr->fexp->param_size, param_expr1, param_expr2,
        // with_brace);
        break;
      }
      case FUNC_DATE_FORMAT: {
        RC rc = create_expression(expr->fexp->params[0], table_map, tables, param_expr1);
        if (rc != RC::SUCCESS) {
          return rc;
        }
        rc = create_expression(expr->fexp->params[1], table_map, tables, param_expr2);
        if (rc != RC::SUCCESS) {
          return rc;
        }
        // res_expr = new FuncExpression(expr->fexp->type, expr->fexp->param_size, param_expr1, param_expr2,
        // with_brace);
        break;
      }
      default:
        break;
    }
  } else if (AGGRFUNC == expr->type) {
    // TODO(wbj)
    if (UNARY == expr->afexp->param->type && 0 == expr->afexp->param->uexp->is_attr) {
      // count(*) count(1) count(Value)
      assert(AggrFuncType::COUNT == expr->afexp->type);
      // substitue * or 1 with some field
      Expression *tmp_value_exp = nullptr;
      RC rc = create_expression(expr->afexp->param, table_map, tables, tmp_value_exp);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      assert(ExprType::VALUE == tmp_value_exp->type());
      auto aggr_func_expr = new AggrFuncExpression(
          AggrFuncType::COUNT, new FieldExpr(tables[0], tables[0]->table_meta().field(1)), with_brace);
      aggr_func_expr->set_param_value((ValueExpr *)tmp_value_exp);
      res_expr = aggr_func_expr;
      return RC::SUCCESS;
    }
    Expression *param = nullptr;
    RC rc = create_expression(expr->afexp->param, table_map, tables, param);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    assert(nullptr != param && ExprType::FIELD == param->type());
    res_expr = new AggrFuncExpression(expr->afexp->type, (FieldExpr *)param, with_brace);
    return RC::SUCCESS;
  }
  return RC::SUCCESS;
}
