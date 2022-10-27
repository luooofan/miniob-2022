/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2021/6/10.
//

#pragma once

#include <vector>
#include "sql/parser/parse.h"
#include "sql/operator/operator.h"
#include "rc.h"
#include "sql/stmt/filter_stmt.h"

class JoinOperator : public Operator {
public:
  JoinOperator(Operator *left, Operator *right) : left_(left), right_(right)
  {
    rht_it_ = filtered_rht_.end();
  }

  virtual ~JoinOperator()
  {
    for (auto &cpd_rcd : rht_) {
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

  void add_filter_unit(FilterUnit *unit)
  {
    filter_units_.emplace_back(unit);
  }

private:
  RC fetch_right_table();
  RC filter_right_table();

private:
  Operator *left_ = nullptr;
  Operator *right_ = nullptr;
  CompoundTuple tuple_;
  bool is_first_ = true;

  std::vector<size_t>::iterator rht_it_;
  std::vector<size_t> filtered_rht_;
  std::vector<CompoundRecord> rht_;  // right hand table

  std::vector<FilterUnit *> filter_units_;
};
