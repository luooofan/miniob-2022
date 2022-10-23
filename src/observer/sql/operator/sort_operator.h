#pragma once

#include <vector>
#include "sql/parser/parse.h"
#include "sql/operator/operator.h"
#include "rc.h"

class OrderByStmt;

class SortOperator : public Operator {
public:
  SortOperator(OrderByStmt *orderby_stmt) : orderby_stmt_(orderby_stmt)
  {}

  virtual ~SortOperator()
  {
    for (auto &cpd_rcd : st_) {
      for (auto rcd : cpd_rcd) {
        delete rcd;
      }
    }
  }

  RC open() override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

  void print_info();

private:
  RC fetch_and_sort_table();

private:
  OrderByStmt *orderby_stmt_ = nullptr;
  bool is_first_ = true;

  std::vector<CompoundRecord> st_;  // sort table
  std::vector<int> ordered_idx_;
  std::vector<int>::iterator it_;
};
