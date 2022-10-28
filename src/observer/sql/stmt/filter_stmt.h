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
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include <cassert>
#include <vector>
#include <unordered_map>
#include "rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/expr/expression.h"

class Db;
class Table;
class FieldMeta;

class FilterUnit {
public:
  FilterUnit() = default;
  ~FilterUnit()
  {
    if (left_) {
      delete left_;
      left_ = nullptr;
    }
    if (right_) {
      delete right_;
      right_ = nullptr;
    }
    if (left_unit_) {
      delete left_unit_;
      left_unit_ = nullptr;
    }
    if (right_unit_) {
      delete right_unit_;
      right_unit_ = nullptr;
    }
  }

  void set_comp(CompOp comp)
  {
    comp_ = comp;
  }

  CompOp comp() const
  {
    return comp_;
  }

  void set_left(Expression *expr)
  {
    left_ = expr;
  }
  void set_right(Expression *expr)
  {
    right_ = expr;
  }
  Expression *left() const
  {
    return left_;
  }
  Expression *right() const
  {
    return right_;
  }
  void set_left_unit(FilterUnit *unit)
  {
    assert(CompOp::AND_OP == comp_ || CompOp::OR_OP == comp_);
    left_unit_ = unit;
  }
  void set_right_unit(FilterUnit *unit)
  {
    assert(CompOp::AND_OP == comp_ || CompOp::OR_OP == comp_);
    right_unit_ = unit;
  }
  FilterUnit *left_unit() const
  {
    assert(CompOp::AND_OP == comp_ || CompOp::OR_OP == comp_);
    return left_unit_;
  }
  FilterUnit *right_unit() const
  {
    assert(CompOp::AND_OP == comp_ || CompOp::OR_OP == comp_);
    return right_unit_;
  }

private:
  CompOp comp_ = NO_OP;
  Expression *left_ = nullptr;
  Expression *right_ = nullptr;

  // if comp is and / or
  FilterUnit *left_unit_ = nullptr;
  FilterUnit *right_unit_ = nullptr;
};

class FilterStmt {
public:
  FilterStmt() = default;
  virtual ~FilterStmt();

public:
  std::vector<FilterUnit *> &filter_units()
  {
    return filter_units_;
  }
  const std::vector<FilterUnit *> &filter_units() const
  {
    return filter_units_;
  }

public:
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const Condition *conditions, int condition_num, FilterStmt *&stmt);

  static RC create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      const Condition &condition, FilterUnit *&filter_unit);

private:
  std::vector<FilterUnit *> filter_units_;  // 默认当前都是AND关系
};

typedef FilterStmt HavingStmt;

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttr &attr, Table *&table, const FieldMeta *&field);
