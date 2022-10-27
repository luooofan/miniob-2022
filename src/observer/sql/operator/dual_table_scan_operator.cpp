#include "sql/operator/dual_table_scan_operator.h"
#include "storage/common/table.h"
#include "rc.h"

RC DualTableScanOperator::open()
{
  return RC::SUCCESS;
}

RC DualTableScanOperator::next()
{
  if (is_first_) {
    is_first_ = false;
    return RC::SUCCESS;
  }
  return RC::RECORD_EOF;
}

RC DualTableScanOperator::close()
{
  return RC::SUCCESS;
}

Tuple *DualTableScanOperator::current_tuple()
{
  return &tuple_;
}
