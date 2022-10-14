#include "sql/operator/join_operator.h"

RC JoinOperator::open()
{
  RC rc = RC::SUCCESS;
  if (RC::SUCCESS != (rc = left_->open())) {
    rc = RC::INTERNAL;
    LOG_WARN("JoinOperater child left open failed!");
  }
  if (RC::SUCCESS != (rc = right_->open())) {
    rc = RC::INTERNAL;
    LOG_WARN("JoinOperater child right open failed!");
  }
  Tuple *left_tuple = left_->current_tuple();
  Tuple *right_tuple = right_->current_tuple();
  tuple_.init(left_tuple, right_tuple);
  // assert(RC::SUCCESS == left_->next());
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
  rht_it_ = rht_.begin();
  print_info();

  if (RC::RECORD_EOF == rc) {
    return RC::SUCCESS;
  }
  return rc;
}

void JoinOperator::print_info()
{
  std::cout << "right table info: " << std::endl;
  // for (auto& cpd_rcd : rht_) {
  // }
  std::cout << "current right table iter: " << std::endl;
  std::cout << rht_it_ - rht_.begin() << std::endl;
  std::cout << "current tuple: " << std::endl;
  //
}

RC JoinOperator::next()
{
  RC rc = RC::SUCCESS;
  if (is_first_) {
    rc = left_->next();
    is_first_ = false;
    if (RC::SUCCESS != rc) {
      return rc;
    }
    rc = fetch_right_table();
    if (RC::SUCCESS != rc) {
      return rc;
    }
    assert(rht_.begin() == rht_it_);
  }
  if (rht_.end() != rht_it_) {
    CompoundRecord temp(*rht_it_);
    tuple_.set_right_record(temp);
    rht_it_++;
    return RC::SUCCESS;
  }
  rc = left_->next();
  if (RC::SUCCESS == rc) {
    rht_it_ = rht_.begin();
    return next();
  }
  // LOG_ERROR
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
