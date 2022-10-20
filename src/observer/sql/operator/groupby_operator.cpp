#include "sql/operator/groupby_operator.h"
#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "sql/stmt/groupby_stmt.h"
#include <algorithm>

RC GroupByOperator::open()
{
  RC rc = RC::SUCCESS;
  if (RC::SUCCESS != (rc = children_[0]->open())) {
    rc = RC::INTERNAL;
    LOG_WARN("SortOperater child open failed!");
  }
  tuple_.set_tuple(children_[0]->current_tuple());
  return rc;
}

void GroupByOperator::print_info()
{}

RC GroupByOperator::next()
{
  RC rc = RC::SUCCESS;
  auto &units = groupby_stmt_->groupby_units();

  if (is_first) {
    rc = children_[0]->next();
    is_first = false;
    is_new_group = true;
    if (RC::SUCCESS != rc) {
      return rc;
    }
    // set initial value of pre_values_
    for (auto unit : units) {
      pre_values_.emplace_back(TupleCell());
      unit->expr()->get_value(*children_[0]->current_tuple(), pre_values_.back());
    }
    assert(pre_values_.size() == units.size());
  }

  while (true) {
    // 0. if the last row is new group, do aggregate first
    if (is_new_group) {
      tuple_.do_aggregate();
      is_new_group = false;
    }
    if (RC::SUCCESS != (rc = children_[0]->next())) {
      break;
    }
    // 1. adjust whether current tuple is new group or not
    for (size_t i = 0; i < units.size(); ++i) {
      const GroupByUnit *unit = units[i];
      Expression *expr = unit->expr();
      TupleCell cell;
      expr->get_value(*children_[0]->current_tuple(), cell);
      if (cell != pre_values_[i]) {
        // 2. update pre_values_ and set new group
        pre_values_[i] = cell;
        is_new_group = true;
      }
    }
    // 3. if new group, should return a row, update tuple_
    if (is_new_group) {
      tuple_.do_aggregate_done();
      return rc;
    }
    // 4. if not new group, execute aggregate function and update result
    tuple_.do_aggregate();
  }

  return rc;
}

RC GroupByOperator::close()
{
  RC rc = RC::SUCCESS;
  children_[0]->close();
  return rc;
}

Tuple *GroupByOperator::current_tuple()
{
  return &tuple_;
}
