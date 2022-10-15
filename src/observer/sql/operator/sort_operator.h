/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include <vector>
#include "sql/parser/parse.h"
#include "sql/operator/operator.h"
#include "rc.h"

class OrderByStmt;

// TODO fixme
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
  RC fetch_table();
  RC sort_table();
  bool CmpAsc(CompoundRecord a, CompoundRecord b);
  bool CmpDesc(CompoundRecord a, CompoundRecord b);

private:
  bool is_first_ = true;
  // std::vector<CompoundRecord>::iterator st_it_;  // sort table stmt
  std::vector<CompoundRecord> st_;  // sort table
  OrderByStmt *orderby_stmt_ = nullptr;
  std::vector<int> ordered_idx_;
  std::vector<int>::iterator it_;
};
