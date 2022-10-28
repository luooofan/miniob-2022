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
#include <ostream>
#include <string.h>
#include <unordered_map>
#include <vector>
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "storage/common/field.h"
#include "sql/expr/tuple_cell.h"
#include "storage/common/db.h"

class Tuple;
class SelectStmt;
class ProjectOperator;
class Stmt;

enum class ExprType {
  NONE,
  FIELD,
  VALUE,
  BINARY,
  FUNC,
  AGGRFUNCTION,
  SUBQUERYTYPE,
  SUBLISTTYPE,
};

class Expression {
public:
  Expression() = default;
  virtual ~Expression() = default;

  virtual RC get_value(const Tuple &tuple, TupleCell &cell) const = 0;
  virtual ExprType type() const = 0;
  virtual void to_string(std::ostream &os) const = 0;

  static RC create_expression(const Expr *expr, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp = NO_OP, Db *db = nullptr);

  void set_with_brace()
  {
    with_brace_ = 1;
  }
  bool with_brace() const
  {
    return with_brace_;
  }

  void set_alias(const std::string &alias)
  {
    alias_ = alias;
  }

  const std::string get_alias() const
  {
    return alias_;
  }

private:
  bool with_brace_ = 0;
  std::string alias_ = "";
};

class FieldExpr : public Expression {
public:
  FieldExpr() = default;
  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field)
  {}
  FieldExpr(const Table *table, const FieldMeta *field, bool with_brace) : FieldExpr(table, field)
  {
    if (with_brace) {
      set_with_brace();
    }
  }

  virtual ~FieldExpr() = default;

  ExprType type() const override
  {
    return ExprType::FIELD;
  }

  AttrType attr_type() const
  {
    return field_.attr_type();
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

  void to_string(std::ostream &os) const override;

  bool in_expression(const Expression *expr) const;

  static void get_fieldexprs_without_aggrfunc(const Expression *expr, std::vector<FieldExpr *> &field_exprs);

  static RC create_expression(const Expr *expr, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp = NO_OP, Db *db = nullptr);

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
  ValueExpr(const Value &value, bool with_brace) : ValueExpr(value)
  {
    if (with_brace) {
      set_with_brace();
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

  void to_string(std::ostream &os) const override;

  static RC create_expression(const Expr *expr, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp = NO_OP, Db *db = nullptr);

private:
  TupleCell tuple_cell_;
};

class FuncExpression : public Expression {
public:
  FuncExpression() = default;
  FuncExpression(FuncType func_type, int param_size, Expression *param1, Expression *param2, bool with_brace)
      : func_type_(func_type), param_size_(param_size)
  {
    if (with_brace) {
      set_with_brace();
    }
    if (param1 != NULL) {
      params_expr_.emplace_back(param1);
    }
    if (param2 != NULL) {
      params_expr_.emplace_back(param2);
    }
  }
  virtual ~FuncExpression() = default;

  RC get_func_length_value(const Tuple &tuple, TupleCell &final_cell) const;

  RC get_func_round_value(const Tuple &tuple, TupleCell &final_cell) const;

  RC get_func_data_format_value(const Tuple &tuple, TupleCell &final_cell) const;

  RC get_value(const Tuple &tuple, TupleCell &final_cell) const override
  {
    RC rc = RC::SUCCESS;
    switch (func_type_) {
      case FUNC_LENGTH: {
        rc = get_func_length_value(tuple, final_cell);
        break;
      }
      case FUNC_ROUND: {
        rc = get_func_round_value(tuple, final_cell);
        break;
      }
      case FUNC_DATE_FORMAT: {
        rc = get_func_data_format_value(tuple, final_cell);
        break;
      }
      default:
        break;
    }
    return rc;
  }

  ExprType type() const override
  {
    return ExprType::FUNC;
  }

  void to_string(std::ostream &os) const override
  {}

  FuncType get_func_type()
  {
    return func_type_;
  }

  std::vector<Expression *> get_params()
  {
    return params_expr_;
  }

  int get_param_size()
  {
    return param_size_;
  }
  static RC create_expression(const Expr *expr, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp = NO_OP, Db *db = nullptr);

private:
  FuncType func_type_;
  std::vector<Expression *> params_expr_;
  int param_size_;
};

class BinaryExpression : public Expression {
public:
  BinaryExpression() = default;
  BinaryExpression(ExpOp op, Expression *left_expr, Expression *right_expr)
      : op_(op), left_expr_(left_expr), right_expr_(right_expr)
  {}
  BinaryExpression(ExpOp op, Expression *left_expr, Expression *right_expr, bool with_brace)
      : BinaryExpression(op, left_expr, right_expr)
  {
    if (with_brace) {
      set_with_brace();
    }
  }
  BinaryExpression(ExpOp op, Expression *left_expr, Expression *right_expr, bool with_brace, bool is_minus)
      : BinaryExpression(op, left_expr, right_expr, with_brace)
  {
    is_minus_ = is_minus;
  }

  bool is_minus() const
  {
    return is_minus_;
  }

  virtual ~BinaryExpression() = default;

  const char get_op_char() const;

  Expression *get_left()
  {
    return left_expr_;
  }
  const Expression *get_left() const
  {
    return left_expr_;
  }
  Expression *get_right()
  {
    return right_expr_;
  }
  const Expression *get_right() const
  {
    return right_expr_;
  }
  void set_left(Expression *expr)
  {
    left_expr_ = expr;
  }
  void set_right(Expression *expr)
  {
    right_expr_ = expr;
  }

  RC get_value(const Tuple &tuple, TupleCell &final_cell) const override;

  ExprType type() const override
  {
    return ExprType::BINARY;
  }
  void to_string(std::ostream &os) const override;

  static RC create_expression(const Expr *expr, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp = NO_OP, Db *db = nullptr);

private:
  ExpOp op_;
  Expression *left_expr_ = nullptr;
  Expression *right_expr_ = nullptr;
  TupleCell expr_result_;
  bool is_minus_ = false;  // only used for output
};

class AggrFuncExpression : public Expression {
public:
  AggrFuncExpression() = default;
  AggrFuncExpression(AggrFuncType type, const FieldExpr *field) : type_(type), field_(field)
  {}
  AggrFuncExpression(AggrFuncType type, const FieldExpr *field, bool with_brace) : AggrFuncExpression(type, field)
  {
    if (with_brace) {
      set_with_brace();
    }
  }

  virtual ~AggrFuncExpression() = default;

  void set_param_value(const ValueExpr *value)
  {
    value_ = value;
  }
  bool is_param_value() const
  {
    return nullptr != value_;
  }
  const ValueExpr *get_param_value() const
  {
    assert(nullptr != value_);
    return value_;
  }

  ExprType type() const override
  {
    return ExprType::AGGRFUNCTION;
  }

  const Field &field() const
  {
    return field_->field();
  }

  const FieldExpr &fieldexpr() const
  {
    return *field_;
  }

  const Table *table() const
  {
    return field_->table();
  }

  const char *table_name() const
  {
    return field_->table_name();
  }

  const char *field_name() const
  {
    return field_->field_name();
  }

  RC get_value(const Tuple &tuple, TupleCell &cell) const override;

  std::string get_func_name() const;

  AttrType get_return_type() const;

  AggrFuncType get_aggr_func_type() const
  {
    return type_;
  }

  void to_string(std::ostream &os) const override;

  static void get_aggrfuncexprs(const Expression *expr, std::vector<AggrFuncExpression *> &aggrfunc_exprs);

  static RC create_expression(const Expr *expr, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp = NO_OP, Db *db = nullptr);

private:
  AggrFuncType type_;
  const FieldExpr *field_ = nullptr;  // don't own this. keep const.
  const ValueExpr *value_ = nullptr;  // for count(1) count(*) count("xxx") output
};

class SubQueryExpression : public Expression {
public:
  SubQueryExpression() = default;
  virtual ~SubQueryExpression() = default;

  ExprType type() const override
  {
    return ExprType::SUBQUERYTYPE;
  }

  void to_string(std::ostream &os) const override
  {}

  RC get_value(const Tuple &tuple, TupleCell &final_cell) const override;

  RC get_value(TupleCell &final_cell) const;

  void set_sub_query_stmt(SelectStmt *sub_stmt)
  {
    sub_stmt_ = sub_stmt;
  }

  SelectStmt *get_sub_query_stmt() const
  {
    return sub_stmt_;
  }

  void set_sub_query_top_oper(ProjectOperator *oper)
  {
    sub_top_oper_ = oper;
  }

  ProjectOperator *get_sub_query_top_oper() const
  {
    return sub_top_oper_;
  }

  RC open_sub_query() const;
  RC close_sub_query() const;

  static RC create_expression(const Expr *expr, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp = NO_OP, Db *db = nullptr);

private:
  SelectStmt *sub_stmt_ = nullptr;
  ProjectOperator *sub_top_oper_ = nullptr;
};

class ListExpression : public Expression {
public:
  ListExpression() = default;

  virtual ~ListExpression() = default;

  RC get_value(const Tuple &tuple, TupleCell &cell) const override
  {
    return RC::UNIMPLENMENT;
  }

  ExprType type() const override
  {
    return ExprType::SUBLISTTYPE;
  }

  void set_tuple_cells(Value values[], int value_length)
  {
    TupleCell tuple_cell;
    for (int i = 0; i < value_length; i++) {
      tuple_cell.set_type(values[i].type);
      tuple_cell.set_length(-1);
      tuple_cell.set_data((char *)values[i].data);  // maybe null
      if (values[i].type == CHARS) {
        tuple_cell.set_length(strlen((const char *)values[i].data));
      }
      tuple_cells_.emplace_back(tuple_cell);
    }
  }

  const std::vector<TupleCell> get_tuple_cells() const
  {
    return tuple_cells_;
  }

  void to_string(std::ostream &os) const override
  {}

  static RC create_expression(const Expr *expr, const std::unordered_map<std::string, Table *> &table_map,
      const std::vector<Table *> &tables, Expression *&res_expr, CompOp comp = NO_OP, Db *db = nullptr);

private:
  std::vector<TupleCell> tuple_cells_;
};
