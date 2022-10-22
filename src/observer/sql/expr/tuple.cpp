#include "sql/expr/tuple.h"

void GroupTuple::do_aggregate_first()
{
  assert(aggr_results_.size() == aggr_exprs_.size());
  assert(field_results_.size() == field_results_.size());
  // first row in current group
  count_ = 1;
  for (size_t i = 0; i < aggr_exprs_.size(); ++i) {
    const AggrFuncExpression *expr = aggr_exprs_[i];
    if (AggrFuncType::COUNT != expr->get_aggr_func_type()) {
      expr->get_value(*tuple_, aggr_results_[i]);
    }
  }
  for (size_t i = 0; i < field_exprs_.size(); ++i) {
    field_exprs_[i]->get_value(*tuple_, field_results_[i]);
  }
}

void GroupTuple::do_aggregate()
{
  count_++;
  TupleCell tmp;
  for (size_t i = 0; i < aggr_exprs_.size(); ++i) {
    const AggrFuncExpression *expr = aggr_exprs_[i];
    if (AggrFuncType::COUNT == expr->get_aggr_func_type()) {
      continue;
    }
    expr->get_value(*tuple_, tmp);
    switch (expr->get_aggr_func_type()) {
      case AggrFuncType::MIN:
        aggr_results_[i] = TupleCell::min(aggr_results_[i], tmp);
        break;
      case AggrFuncType::MAX:
        aggr_results_[i] = TupleCell::max(aggr_results_[i], tmp);
        break;
      case AggrFuncType::SUM:
      case AggrFuncType::AVG:
        aggr_results_[i] = TupleCell::add(aggr_results_[i], tmp);
        break;
      default:
        LOG_ERROR("Unsupported AggrFuncType");
        break;
    }
  }
}

void GroupTuple::do_aggregate_done()
{
  for (size_t i = 0; i < aggr_exprs_.size(); ++i) {
    const AggrFuncExpression *expr = aggr_exprs_[i];
    TupleCell &res = aggr_results_[i];
    switch (expr->get_aggr_func_type()) {
      case AggrFuncType::COUNT: {
        res.set_type(AttrType::INTS);
        res.set_data((char *)(new int(count_)));
        // res.modify_data((char *)&count_);
        break;
      }
      case AggrFuncType::AVG: {
        res = TupleCell::div(res, TupleCell(AttrType::INTS, (char *)&count_));  // malloc memory in div
        break;
      }
      default:
        break;
    }
  }
  count_ = 0;  // reset for next group
}
