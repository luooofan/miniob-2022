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
// Created by WangYunlai on 2022/07/01.
//

#include <sstream>
#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "sql/operator/project_operator.h"
#include "storage/record/record.h"
#include "storage/common/table.h"

RC ProjectOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("project operator must has 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC ProjectOperator::next()
{
  return children_[0]->next();
}

RC ProjectOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}
Tuple *ProjectOperator::current_tuple()
{
  tuple_.set_tuple(children_[0]->current_tuple());
  return &tuple_;
}

void gen_project_name(const Expression *expr, bool is_single_table, std::string &result_name)
{

  if (!expr->get_alias().empty()) {
    result_name = expr->get_alias();
    return;
  }

  if (expr->with_brace()) {
    result_name += '(';
  }
  switch (expr->type()) {
    case ExprType::FIELD: {
      FieldExpr *fexpr = (FieldExpr *)expr;
      const Field &field = fexpr->field();
      if (!is_single_table) {
        result_name += std::string(field.table_name()) + '.' + std::string(field.field_name());
      } else {
        result_name += std::string(field.field_name());
      }
      break;
    }
    case ExprType::VALUE: {
      ValueExpr *vexpr = (ValueExpr *)expr;
      TupleCell cell;
      vexpr->get_tuple_cell(cell);
      std::stringstream ss;
      cell.to_string(ss);
      result_name += ss.str();
      break;
    }
    case ExprType::BINARY: {
      BinaryExpression *bexpr = (BinaryExpression *)expr;
      if (bexpr->is_minus()) {
        result_name += '-';
      } else {
        gen_project_name(bexpr->get_left(), is_single_table, result_name);
        result_name += bexpr->get_op_char();
      }
      gen_project_name(bexpr->get_right(), is_single_table, result_name);
      break;
    }
    case ExprType::AGGRFUNCTION: {
      AggrFuncExpression *afexpr = (AggrFuncExpression *)expr;
      result_name += afexpr->get_func_name();
      result_name += '(';
      if (afexpr->is_param_value()) {
        gen_project_name(afexpr->get_param_value(), is_single_table, result_name);

      } else {
        const Field &field = afexpr->field();
        if (!is_single_table) {
          result_name += std::string(field.table_name()) + '.' + std::string(field.field_name());
        } else {
          result_name += std::string(field.field_name());
        }
      }
      result_name += ')';
      break;
    }
    case ExprType::FUNC: {
      FuncExpression *fexpr = (FuncExpression *)expr;
      switch (fexpr->get_func_type()) {
        case FUNC_LENGTH: {
          result_name += "length(";
          gen_project_name(fexpr->get_params()[0], is_single_table, result_name);
          result_name += ")";
          break;
        }
        case FUNC_ROUND: {
          result_name += "round(";
          if (fexpr->get_param_size() > 1) {
            gen_project_name(fexpr->get_params()[0], is_single_table, result_name);
            result_name += ",";
            gen_project_name(fexpr->get_params()[1], is_single_table, result_name);
          } else {
            gen_project_name(fexpr->get_params()[0], is_single_table, result_name);
          }
          result_name += ")";
          break;
        }
        case FUNC_DATE_FORMAT: {
          result_name += "date_format(";
          gen_project_name(fexpr->get_params()[0], is_single_table, result_name);
          result_name += ",";
          gen_project_name(fexpr->get_params()[1], is_single_table, result_name);
          result_name += ")";
          break;
        }
        default:
          break;
      }
    }
    default:
      break;
  }
  if (expr->with_brace()) {
    result_name += ')';
  }
}

void ProjectOperator::add_projection(Expression *project, bool is_single_table)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  TupleCellSpec *spec = new TupleCellSpec(project);
  std::string alias_name;
  gen_project_name(project, is_single_table, alias_name);
  auto spec_alias = std::make_shared<std::string>(alias_name);
  spec->set_alias(spec_alias);
  tuple_.add_cell_spec(spec);
}

RC ProjectOperator::tuple_cell_spec_at(int index, const TupleCellSpec *&spec) const
{
  return tuple_.cell_spec_at(index, spec);
}
