#pragma once

#include "sql/expr/expression.h"
#include "sql/operator/operator.h"
#include "sql/expr/tuple.h"
#include "sql/stmt/groupby_stmt.h"

class GroupByOperator : public Operator {
public:
  GroupByOperator(GroupByStmt *groupby_stmt, const std::vector<AggrFuncExpression *> &aggr_exprs,
      const std::vector<FieldExpr *> &field_exprs)
      : groupby_stmt_(groupby_stmt)
  {
    tuple_.init(aggr_exprs, field_exprs);
  }

  virtual ~GroupByOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

  void print_info();

  void set_groupby_stmt(GroupByStmt *groupby_stmt)
  {
    groupby_stmt_ = groupby_stmt;
  }

private:
  bool is_first_ = true;
  bool is_new_group_ = true;
  bool is_record_eof_ = false;

  // not own this
  GroupByStmt *groupby_stmt_ = nullptr;

  std::vector<TupleCell> pre_values_;  // its size equal to groupby_units.size
  GroupTuple tuple_;
};
