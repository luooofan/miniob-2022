//create by yangjk b [select tables]
#include "sql/operator/join_operator.h"
#include "storage/common/table.h"
#include "rc.h"

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
  Tuple * left_tuple = left_->current_tuple();
  Tuple * right_tuple = right_->current_tuple();
  tuple_.init(left_tuple, right_tuple);
  assert(RC::SUCCESS == left_->next());
  return rc;
}

RC JoinOperator::next()
{
  RC rc = right_->next();
  if (RC::SUCCESS == rc) {
    return rc;
  }
  if (RC::RECORD_EOF != rc) {
    // LOG_ERROR
    return rc;
  }
  rc = left_->next();
  if (RC::SUCCESS == rc) {
    assert(RC::SUCCESS == right_->close());
    assert(RC::SUCCESS == right_->open());
    assert(RC::SUCCESS == right_->next());
    return rc;
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

Tuple * JoinOperator::current_tuple()
{
  return &tuple_;
}
