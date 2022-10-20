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
// Created by WangYunlai on 2022/07/05.
//

#include "sql/expr/tuple_cell.h"
#include "common/lang/defer.h"
#include "storage/common/field.h"
#include "common/log/log.h"
#include "util/comparator.h"
#include "util/typecast.h"
#include "util/util.h"

void TupleCell::to_string(std::ostream &os) const
{
  switch (attr_type_) {
    case INTS: {
      os << *(int *)data_;
    } break;
    case FLOATS: {
      float v = *(float *)data_;
      os << double2string(v);
    } break;
    case CHARS: {
      for (int i = 0; i < length_; i++) {
        if (data_[i] == '\0') {
          break;
        }
        os << data_[i];
      }
    } break;
    case DATES: {
      int y, m, d;
      y = *(int *)data_ / 10000;
      m = (*(int *)data_ - y * 10000) / 100;
      d = *(int *)data_ - y * 10000 - m * 100;
      os << y << "-" << (m < 10 ? "0" : "") << m << "-" << (d < 10 ? "0" : "") << d;
    } break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
}

int TupleCell::compare(const TupleCell &other) const
{
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case INTS:
      case DATES:
        return compare_int(this->data_, other.data_);
      case FLOATS:
        return compare_float(this->data_, other.data_);
      case CHARS:
        return compare_string(this->data_, this->length_, other.data_, other.length_);
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = *(int *)data_;
    return compare_float(&this_data, other.data_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = *(int *)other.data_;
    return compare_float(data_, &other_data);
  }
  // for compare.
  float *tmp_left_float = nullptr;
  float *tmp_right_float = nullptr;
  DEFER([&]() {
    if (tmp_left_float)
      delete tmp_left_float;
    if (tmp_right_float)
      delete tmp_right_float;
  });
  tmp_left_float = (float *)cast_to[this->attr_type_][FLOATS](this->data_);
  assert(nullptr != tmp_left_float);
  std::cout << *tmp_left_float << std::endl;
  tmp_right_float = (float *)cast_to[other.attr_type_][FLOATS](other.data_);
  assert(nullptr != tmp_right_float);
  std::cout << *tmp_right_float << std::endl;
  return compare_float(tmp_left_float, tmp_right_float);

  LOG_WARN("not supported");
  return -1;  // TODO return rc?
}
