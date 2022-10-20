#pragma once

#include <vector>
#include "sql/expr/expression.h"
#include "sql/parser/parse.h"
#include "sql/operator/operator.h"
#include "rc.h"
#include "sql/expr/tuple.h"
#include "storage/record/record.h"

class GroupByStmt;

class GroupByOperator : public Operator {
public:
  GroupByOperator(GroupByStmt *groupby_stmt, const std::vector<AggrFuncExpr *> &aggr_expr) : groupby_stmt_(groupby_stmt)
  {
    tuple_.init(aggr_expr);
  }

  virtual ~GroupByOperator()
  {}

  RC open() override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

  void print_info();

private:
  bool is_first = true;
  bool is_new_group = true;
  GroupByStmt *groupby_stmt_ = nullptr;
  std::vector<TupleCell> pre_values_;  // its size equal to groupby_units.size
  GroupTuple tuple_;
};
