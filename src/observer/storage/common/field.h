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
// Created by Wangyunlai on 2022/07/05.
//

#pragma once

#include "sql/parser/parse_defs.h"
#include "storage/common/table.h"
#include "storage/common/field_meta.h"
#include <cassert>

class Field {
public:
  Field() = default;
  Field(const Table *table, const FieldMeta *field) : table_(table), field_(field)
  {}

  const Table *table() const
  {
    return table_;
  }
  const FieldMeta *meta() const
  {
    return field_;
  }
  AttrType attr_type() const
  {
    return field_->type();
  }
  const char *table_name() const
  {
    return table_->name();
  }
  const char *field_name() const
  {
    return field_->name();
  }

  bool with_aggr() const
  {
    return aggr_type_ >= 0 && aggr_type_ < AggrFuncType::AGGR_FUNC_TYPE_NUM;
  }
  AggrFuncType get_aggr_type() const
  {
    assert(with_aggr());
    return aggr_type_;
  }

  void set_table(const Table *table)
  {
    this->table_ = table;
  }
  void set_field(const FieldMeta *field)
  {
    this->field_ = field;
  }
  void set_aggr(AggrFuncType type)
  {
    assert(type >= 0 && type < AggrFuncType::AGGR_FUNC_TYPE_NUM);
    this->aggr_type_ = type;
  }

  bool equal(const Field &other) const
  {
    return table_ == other.table_ && field_->equal(*other.field_);
  }
  bool equal_with_aggr_type(const Field &other) const
  {
    return equal(other) && aggr_type_ == other.aggr_type_;
  }

private:
  const Table *table_ = nullptr;
  const FieldMeta *field_ = nullptr;
  AggrFuncType aggr_type_ = AggrFuncType::AGGR_FUNC_TYPE_NUM;
};
