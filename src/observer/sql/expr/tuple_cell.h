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
// Created by WangYunlai on 2022/6/7.
//

#pragma once

#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>
#include "sql/parser/parse_defs.h"
#include "storage/common/table.h"
#include "storage/common/field_meta.h"

class TupleCell {
public:
  TupleCell() = default;

  TupleCell(FieldMeta *meta, char *data) : TupleCell(meta->type(), data)
  {}
  TupleCell(AttrType attr_type, char *data) : attr_type_(attr_type), data_(data)
  {}

  static const TupleCell add(const TupleCell &left, const TupleCell &right);
  static const TupleCell sub(const TupleCell &left, const TupleCell &right);
  static const TupleCell mul(const TupleCell &left, const TupleCell &right);
  static const TupleCell div(const TupleCell &left, const TupleCell &right);

  void set_null()
  {
    this->attr_type_ = AttrType::NULLS;
  }
  void set_type(AttrType type)
  {
    this->attr_type_ = type;
  }
  void set_length(int length)
  {
    this->length_ = length;
  }
  void set_data(char *data)
  {
    this->data_ = data;
  }
  void set_data(const char *data)
  {
    this->set_data(const_cast<char *>(data));
  }
  void modify_data(char *data)
  {
    if (nullptr == data_) {
      return;
    }
    switch (attr_type_) {
      case AttrType::DATES:
      case AttrType::INTS:
        memcpy(data_, data, sizeof(int));
        break;
      case AttrType::FLOATS:
        memcpy(data_, data, sizeof(float));
        break;
      case AttrType::CHARS:
        // TODO(wbj) note memcpy len
        memcpy(data_, data, length_);
        break;
      default:
        break;
    }
    return;
  }

  void to_string(std::ostream &os) const;

  int compare(const TupleCell &other) const;

  const char *data() const
  {
    return data_;
  }

  int length() const
  {
    return length_;
  }

  AttrType attr_type() const
  {
    return attr_type_;
  }

  bool operator==(const TupleCell &other) const
  {
    return 0 == compare(other);
  }

  bool operator!=(const TupleCell &other) const
  {
    return 0 != compare(other);
  }

  bool operator<(const TupleCell &other) const
  {
    return 0 > compare(other);
  }

  bool operator<=(const TupleCell &other) const
  {
    return 0 >= compare(other);
  }

  bool operator>(const TupleCell &other) const
  {
    return 0 < compare(other);
  }

  bool operator>=(const TupleCell &other) const
  {
    return 0 <= compare(other);
  }

  static const TupleCell &min(const TupleCell &a, const TupleCell &b)
  {
    if (a.is_null()) {
      return b;  // even if b is also null
    }
    return a <= b ? a : b;
  }

  static const TupleCell &max(const TupleCell &a, const TupleCell &b)
  {
    if (a.is_null()) {
      return b;  // even if b is also null
    }
    return a >= b ? a : b;
  }

  bool is_null() const
  {
    return AttrType::NULLS == attr_type_;
  }

  // consider null: null is euqal to null
  bool equal_to(const TupleCell &other) const
  {
    if (is_null()) {
      return other.is_null();
    }
    if (other.is_null()) {
      return false;
    }
    return 0 == compare(other);
  }

  bool in_cells(const std::vector<TupleCell> &cells) const
  {
    for (auto &cell : cells) {
      if (equal_to(cell)) {
        return true;
      }
    }
    return false;
  }

  // return false if is_null and null in cells
  bool not_in_cells(const std::vector<TupleCell> &cells) const
  {
    for (auto &cell : cells) {
      if (equal_to(cell)) {
        return false;
      }
    }
    return true;
  }

private:
  AttrType attr_type_ = UNDEFINED;
  int length_ = -1;
  char *data_ = nullptr;  // real data. no need to move to field_meta.offset
};
