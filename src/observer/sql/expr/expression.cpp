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

#include <cmath>
#include <iomanip>
#include "sql/expr/expression.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/stmt/select_stmt.h"
#include "sql/operator/project_operator.h"

RC FuncExpression::get_func_length_value(const Tuple &tuple, TupleCell &final_cell) const
{
  Expression *param_expr = *params_expr_.begin();
  TupleCell param_cell;
  param_expr->get_value(tuple, param_cell);
  // unsupported not chars
  if (param_cell.attr_type() != CHARS) {
    return RC::INTERNAL;
  }
  const char *param_char = param_cell.data();
  int *result_length = new int(strlen(param_char));
  final_cell.set_type(INTS);
  final_cell.set_length(sizeof(int));
  final_cell.set_data((char *)(result_length));
  return RC::SUCCESS;
}

RC FuncExpression::get_func_round_value(const Tuple &tuple, TupleCell &final_cell) const
{
  if (param_size_ > 1) {
    Expression *param_expr = *params_expr_.begin();
    Expression *param_expr_precision = params_expr_[1];
    TupleCell param_expr_cell;
    TupleCell param_expr_precision_cell;
    param_expr->get_value(tuple, param_expr_cell);
    param_expr_precision->get_value(tuple, param_expr_precision_cell);
    if (param_expr_cell.attr_type() != FLOATS) {
      return RC::INTERNAL;
    }
    if (param_expr_precision_cell.attr_type() != INTS) {
      return RC::INTERNAL;
    }
    float cell_float = *(float *)(param_expr_cell.data());
    int cell_precision = *(int *)(param_expr_precision_cell.data());
    auto inner_round = [](float f, int precision) {
      // std::cout << "Before: " << std::setprecision(12) << f << std::endl;
      std::stringstream ss;
      ss << std::fixed << std::setprecision(precision) << f;
      ss >> f;
      // std::cout << "After: " << std::setprecision(12) << f << std::endl;
      return f;
    };
    *(uint32_t *)&cell_float += 1;
    cell_float = inner_round(cell_float, cell_precision);
    // std::cout << cell_float << std::endl;
    float *result_float = new float(cell_float);
    final_cell.set_type(FLOATS);
    final_cell.set_data((char *)(result_float));
  } else {
    Expression *param_expr = *params_expr_.begin();
    TupleCell param_expr_cell;
    param_expr->get_value(tuple, param_expr_cell);
    if (param_expr_cell.attr_type() != FLOATS) {
      return RC::INTERNAL;
    }
    float cell_float = *(float *)(param_expr_cell.data());
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << cell_float;
    ss >> cell_float;
    float *result_float = new float(cell_float);
    final_cell.set_type(FLOATS);
    final_cell.set_data((char *)(result_float));
  }
  return RC::SUCCESS;
}

RC FuncExpression::get_func_data_format_value(const Tuple &tuple, TupleCell &final_cell) const
{
  Expression *date_expr = params_expr_[0];
  Expression *format_expr = params_expr_[1];
  TupleCell date_expr_cell;
  TupleCell format_expr_cell;
  date_expr->get_value(tuple, date_expr_cell);
  format_expr->get_value(tuple, format_expr_cell);
  if (date_expr_cell.attr_type() != DATES) {
    return RC::INTERNAL;
  }
  if (format_expr_cell.attr_type() != CHARS) {
    return RC::INTERNAL;
  }
  int cell_date = *(int *)(date_expr_cell.data());
  char *cell_format_chars = (char *)(format_expr_cell.data());
  std::string result_date_str;
  int year = cell_date / 10000;
  int month = (cell_date / 100) % 100;
  int day = cell_date % 100;
  for (size_t i = 0; i < strlen(cell_format_chars); i++) {
    // A ~ z
    if (65 <= cell_format_chars[i] && cell_format_chars[i] <= 122) {
      switch (cell_format_chars[i]) {
        case 'Y': {
          char tmp[5];
          sprintf(tmp, "%d", year);
          result_date_str += tmp;
          break;
        }
        case 'y': {
          char tmp[5];
          sprintf(tmp, "%d", year % 100);
          if (0 <= (year % 100) && (year % 100) <= 9) {
            result_date_str += "0";
          }
          result_date_str += tmp;
          break;
        }
        case 'M': {
          switch (month) {
            case 1: {
              result_date_str += "January";
              break;
            }
            case 2: {
              result_date_str += "February";
              break;
            }
            case 3: {
              result_date_str += "March";
              break;
            }
            case 4: {
              result_date_str += "April";
              break;
            }
            case 5: {
              result_date_str += "May";
              break;
            }
            case 6: {
              result_date_str += "June";
              break;
            }
            case 7: {
              result_date_str += "July";
              break;
            }
            case 8: {
              result_date_str += "August";
              break;
            }
            case 9: {
              result_date_str += "September";
              break;
            }
            case 10: {
              result_date_str += "October";
              break;
            }
            case 11: {
              result_date_str += "November";
              break;
            }
            case 12: {
              result_date_str += "December";
              break;
            }
            default: {
              return RC::INTERNAL;
              break;
            }
          }
          break;
        }
        case 'm': {
          char tmp[3];
          sprintf(tmp, "%d", month);
          if (0 <= month && month <= 9) {
            result_date_str += "0";
          }
          result_date_str += tmp;
          break;
        }
        case 'D': {
          char tmp[3];
          sprintf(tmp, "%d", day);
          if (10 <= day && day <= 20) {
            result_date_str += tmp;
            result_date_str += "th";
          } else {
            switch (day % 10) {
              case 1: {
                result_date_str += tmp;
                result_date_str += "st";
                break;
              }
              case 2: {
                result_date_str += tmp;
                result_date_str += "nd";
                break;
              }
              case 3: {
                result_date_str += tmp;
                result_date_str += "rd";
                break;
              }
              default: {
                result_date_str += tmp;
                result_date_str += "th";
                break;
              }
            }
          }
          break;
        }
        case 'd': {
          char tmp[3];
          sprintf(tmp, "%d", day);
          if (0 <= day && day <= 9) {
            result_date_str += "0";
          }
          result_date_str += tmp;
          break;
        }
        default: {
          result_date_str += cell_format_chars[i];
          break;
        }
      }
    } else if (cell_format_chars[i] != '%') {
      result_date_str += cell_format_chars[i];
    }
  }
  // std::cout << result_date_str << std::endl;
  final_cell.set_data(strdup(result_date_str.c_str()));
  final_cell.set_type(CHARS);
  final_cell.set_length(strlen(result_date_str.c_str()));
  return RC::SUCCESS;
}

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
  if (RC::SUCCESS != rc) {
    LOG_ERROR("BinaryExpression Get Left Value Failed. RC = %d:%s", rc, strrc(rc));
    return rc;
  }
  rc = right_expr_->get_value(tuple, right_cell);
  if (RC::SUCCESS != rc) {
    LOG_ERROR("BinaryExpression Get Right Value Failed. RC = %d:%s", rc, strrc(rc));
    return rc;
  }
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

RC SubQueryExpression::open_sub_query() const
{
  assert(nullptr != sub_top_oper_);
  return sub_top_oper_->open();
}
RC SubQueryExpression::close_sub_query() const
{
  assert(nullptr != sub_top_oper_);
  return sub_top_oper_->close();
}
RC SubQueryExpression::get_value(TupleCell &final_cell) const
{
  RC rc = sub_top_oper_->next();
  if (RC::RECORD_EOF == rc) {
    final_cell.set_null();
  }
  if (RC::SUCCESS != rc) {
    return rc;
  }
  Tuple *child_tuple = sub_top_oper_->current_tuple();
  if (nullptr == child_tuple) {
    LOG_WARN("failed to get current record. rc=%s", strrc(rc));
    return RC::INTERNAL;
  }
  rc = child_tuple->cell_at(0, final_cell);  // only need the first cell
  return rc;
}
RC SubQueryExpression::get_value(const Tuple &tuple, TupleCell &final_cell) const
{
  assert(nullptr != sub_top_oper_);
  sub_top_oper_->set_parent_tuple(&tuple);  // set parent tuple
  return get_value(final_cell);
}

RC Expression::create_expression(const Expr *expr, const std::unordered_map<std::string, Table *> &table_map,
    const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp, Db *db)
{
  if (expr->type == UNARY) {
    UnaryExpr *uexpr = expr->uexp;
    if (uexpr->is_attr) {
      return FieldExpr::create_expression(expr, table_map, tables, res_expr);
    } else {
      return ValueExpr::create_expression(expr, table_map, tables, res_expr);
    }
  } else if (expr->type == BINARY) {
    return BinaryExpression::create_expression(expr, table_map, tables, res_expr);
  } else if (expr->type == FUNC) {
    return FuncExpression::create_expression(expr, table_map, tables, res_expr);
  } else if (AGGRFUNC == expr->type) {
    return AggrFuncExpression::create_expression(expr, table_map, tables, res_expr);
  } else if (SUBQUERY == expr->type) {
    return SubQueryExpression::create_expression(expr, table_map, tables, res_expr, comp, db);
  } else if (SUBLIST == expr->type) {
    return ListExpression::create_expression(expr, table_map, tables, res_expr);
  }
  return RC::UNIMPLENMENT;
}

RC FieldExpr::create_expression(const Expr *expr, const std::unordered_map<std::string, Table *> &table_map,
    const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp, Db *db)
{
  assert(UNARY == expr->type);
  UnaryExpr *uexpr = expr->uexp;
  assert(uexpr->is_attr);
  bool with_brace = expr->with_brace;
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
    if (std::string(table_name) != std::string(table->name())) {
      if (tables.size() != 1) {
        res_expr->set_alias(std::string(table_name) + "." + std::string(field_name));
      }
    }

    return RC::SUCCESS;
  }
}

RC ValueExpr::create_expression(const Expr *expr, const std::unordered_map<std::string, Table *> &table_map,
    const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp, Db *db)
{
  assert(UNARY == expr->type);
  UnaryExpr *uexpr = expr->uexp;
  assert(uexpr->is_attr == 0);
  bool with_brace = expr->with_brace;
  res_expr = new ValueExpr(uexpr->value, with_brace);
  return RC::SUCCESS;
}

RC BinaryExpression::create_expression(const Expr *expr, const std::unordered_map<std::string, Table *> &table_map,
    const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp, Db *db)
{
  assert(BINARY == expr->type);
  bool with_brace = expr->with_brace;
  Expression *left_expr;
  Expression *right_expr;
  RC rc = Expression::create_expression(expr->bexp->left, table_map, tables, left_expr);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("BinaryExpression Create Left Expression Failed. RC = %d:%s", rc, strrc(rc));
    return rc;
  }
  rc = Expression::create_expression(expr->bexp->right, table_map, tables, right_expr);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("BinaryExpression Create Right Expression Failed. RC = %d:%s", rc, strrc(rc));
    delete left_expr;
    return rc;
  }
  res_expr = new BinaryExpression(expr->bexp->op, left_expr, right_expr, with_brace, expr->bexp->minus);
  return RC::SUCCESS;
}

RC AggrFuncExpression::create_expression(const Expr *expr, const std::unordered_map<std::string, Table *> &table_map,
    const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp, Db *db)
{
  assert(AGGRFUNC == expr->type);
  bool with_brace = expr->with_brace;
  // TODO(wbj)
  if (UNARY == expr->afexp->param->type && 0 == expr->afexp->param->uexp->is_attr) {
    // count(*) count(1) count(Value)
    assert(AggrFuncType::COUNT == expr->afexp->type);
    // substitue * or 1 with some field
    Expression *tmp_value_exp = nullptr;
    RC rc = Expression::create_expression(expr->afexp->param, table_map, tables, tmp_value_exp);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("AggrFuncExpression Create Param Expression Failed. RC = %d:%s", rc, strrc(rc));
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
  RC rc = Expression::create_expression(expr->afexp->param, table_map, tables, param);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("AggrFuncExpression Create Param Expression Failed. RC = %d:%s", rc, strrc(rc));
    return rc;
  }
  assert(nullptr != param && ExprType::FIELD == param->type());
  res_expr = new AggrFuncExpression(expr->afexp->type, (FieldExpr *)param, with_brace);
  return RC::SUCCESS;
}

RC FuncExpression::create_expression(const Expr *expr, const std::unordered_map<std::string, Table *> &table_map,
    const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp, Db *db)
{
  RC rc = RC::SUCCESS;
  Expression *param_expr1 = nullptr;
  Expression *param_expr2 = nullptr;
  FuncExpr *fexp = expr->fexp;
  switch (fexp->type) {
    case FUNC_LENGTH: {
      rc = Expression::create_expression(fexp->params[0], table_map, tables, param_expr1, comp, db);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("FuncExpression LENGTH Create Param[0] Failed. RC = %d:%s", rc, strrc(rc));
        return rc;
      }
      break;
    }
    case FUNC_ROUND: {
      rc = Expression::create_expression(fexp->params[0], table_map, tables, param_expr1, comp, db);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("FuncExpression ROUND Create Param[0] Failed. RC = %d:%s", rc, strrc(rc));
        return rc;
      }
      if (expr->fexp->param_size == 2) {
        rc = Expression::create_expression(fexp->params[1], table_map, tables, param_expr2, comp, db);
        if (rc != RC::SUCCESS) {
          LOG_ERROR("FuncExpression ROUND Create Param[1] Failed. RC = %d:%s", rc, strrc(rc));
          delete param_expr1;
          return rc;
        }
      }
      break;
    }
    case FUNC_DATE_FORMAT: {
      rc = Expression::create_expression(fexp->params[0], table_map, tables, param_expr1, comp, db);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("FuncExpression DATE_FORMAT Create Param[0] Failed. RC = %d:%s", rc, strrc(rc));
        return rc;
      }
      rc = Expression::create_expression(fexp->params[1], table_map, tables, param_expr2, comp, db);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("FuncExpression DATE_FORMAT Create Param[1] Failed. RC = %d:%s", rc, strrc(rc));
        delete param_expr1;
        return rc;
      }
      break;
    }
    default:
      return RC::UNIMPLENMENT;
      break;
  }

  res_expr = new FuncExpression(expr->fexp->type, expr->fexp->param_size, param_expr1, param_expr2, 0);
  return rc;
}

RC SubQueryExpression::create_expression(const Expr *expr, const std::unordered_map<std::string, Table *> &table_map,
    const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp, Db *db)
{
  assert(SUBQUERY == expr->type);
  Stmt *tmp_stmt = nullptr;
  RC rc = SelectStmt::create(db, *expr->sexp->sub_select, tables, table_map, tmp_stmt);
  if (RC::SUCCESS != rc) {
    LOG_ERROR("SubQueryExpression Create SelectStmt Failed. RC = %d:%s", rc, strrc(rc));
    return rc;
  }
  switch (comp) {
    case EXISTS_OP:
    case NOT_EXISTS:
      break;
    default: {
      if (((SelectStmt *)tmp_stmt)->projects().size() != 1) {
        return RC::SQL_SYNTAX;
      }
      break;
    }
  }
  SubQueryExpression *sub_expr = new SubQueryExpression();
  sub_expr->set_sub_query_stmt((SelectStmt *)tmp_stmt);
  res_expr = sub_expr;
  return RC::SUCCESS;
}

RC ListExpression::create_expression(const Expr *expr, const std::unordered_map<std::string, Table *> &table_map,
    const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp, Db *db)
{
  assert(SUBLIST == expr->type);
  ListExpr *lexpr = expr->lexp;
  ListExpression *list_expr = new ListExpression();
  list_expr->set_tuple_cells(lexpr->list, lexpr->list_length);
  res_expr = list_expr;
  return RC::SUCCESS;
}
