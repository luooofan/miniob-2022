#pragma once

#include "sql/operator/operator.h"
#include "storage/record/record_manager.h"
#include "rc.h"

class DualTableScanOperator : public Operator {
public:
  DualTableScanOperator() = default;

  virtual ~DualTableScanOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;

  // NOTE: DO NOT USE THE TUPLE
  Tuple *current_tuple() override;

private:
  RowTuple tuple_;
  bool is_first_ = true;
};
