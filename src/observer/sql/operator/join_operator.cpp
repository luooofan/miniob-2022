#include "sql/operator/join_operator.h"
#include "common/log/log.h"
#include "sql/operator/predicate_operator.h"
#include "sql/stmt/filter_stmt.h"

RC JoinOperator::open()
{
  RC rc = RC::SUCCESS;
  if (RC::SUCCESS != (rc = left_->open())) {
    rc = RC::INTERNAL;
    LOG_WARN("JoinOperater child left open failed!");
    return rc;
  }
  if (RC::SUCCESS != (rc = right_->open())) {
    rc = RC::INTERNAL;
    LOG_WARN("JoinOperater child right open failed!");
    return rc;
  }
  tuple_.init(left_->current_tuple(), right_->current_tuple());
  LOG_INFO("Open JoinOperater SUCCESS. There are %d filter units.", filter_units_.size());
  return rc;
}

RC JoinOperator::filter_right_table()
{
  RC rc = RC::SUCCESS;
  filtered_rht_.clear();
  rht_it_ = filtered_rht_.end();
  for (size_t i = 0; i < rht_.size(); ++i) {
    CompoundRecord temp(rht_[i]);
    tuple_.set_right_record(temp);
    bool res = false;
    if (RC::SUCCESS != (rc = PredicateOperator::do_predicate(filter_units_, tuple_, res))) {
      LOG_ERROR("JoinOperater do predicate Failed. RC = %d : %s", rc, strrc(rc));
      return rc;
    }
    if (res) {
      filtered_rht_.emplace_back(i);
    }
  }
  rht_it_ = filtered_rht_.begin();
  LOG_INFO("Filter Right Table Success! There are %d rows in right table satisfy predicates.", filtered_rht_.size());
  return rc;
}

RC JoinOperator::fetch_right_table()
{
  RC rc = RC::SUCCESS;
  while (RC::SUCCESS == (rc = right_->next())) {
    // store right records
    CompoundRecord cpd_rcd;
    right_->current_tuple()->get_record(cpd_rcd);
    // need to deep copy the rcd and push back to rht
    // remember to delete them in dtor
    for (auto &rcd_ptr : cpd_rcd) {
      rcd_ptr = new Record(*rcd_ptr);
    }
    rht_.emplace_back(cpd_rcd);
  }
  LOG_INFO("Fetch Right Table Success! There are %d rows in right table.", rht_.size());

  if (RC::RECORD_EOF == rc) {
    return RC::SUCCESS;
  }
  return rc;
}

void JoinOperator::print_info()
{
  // std::cout << "right table info: " << std::endl;
  // for (auto& cpd_rcd : rht_) {
  // }
  std::cout << "current right table iter: " << std::endl;
  std::cout << rht_it_ - filtered_rht_.begin() << std::endl;
  // std::cout << "current tuple: " << std::endl;
}

RC JoinOperator::next()
{
  RC rc = RC::SUCCESS;

  if (is_first_) {
    is_first_ = false;
    rc = fetch_right_table();
    if (RC::SUCCESS != rc) {
      LOG_ERROR("Fetch Right Table Failed");
      return rc;
    }
    rht_it_ = filtered_rht_.end();
  }

  if (filtered_rht_.end() != rht_it_) {
    CompoundRecord temp(rht_[*rht_it_]);
    tuple_.set_right_record(temp);
    rht_it_++;
    return RC::SUCCESS;
  }

  rc = left_->next();
  if (RC::SUCCESS == rc) {
    rc = filter_right_table();
    if (RC::SUCCESS != rc) {
      LOG_ERROR("Filter Right Table Failed. RC = %d : %s", rc, strrc(rc));
      return rc;
    }
    return next();
  }

  if (RC::RECORD_EOF == rc) {
    LOG_INFO("Fetch Left Record EOF");
  } else {
    LOG_ERROR("Fetch Left Next Failed");
  }

  return rc;
}

RC JoinOperator::close()
{
  RC rc = RC::SUCCESS;
  left_->close();
  right_->close();
  return rc;
}

Tuple *JoinOperator::current_tuple()
{
  return &tuple_;
}
