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
    case NULLS: {
      os << "NULL";
    } break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
}

const TupleCell TupleCell::sub(const TupleCell &left, const TupleCell &right)
{
  TupleCell result_cell;
  if (left.is_null() || right.is_null()) {
    result_cell.set_null();
    return result_cell;
  }
  if (left.attr_type_ == INTS && right.attr_type_ == INTS) {
    int result = *(int *)left.data_ - *(int *)right.data_;
    int *result_data = new int(result);
    result_cell.set_data((char *)result_data);
    result_cell.set_type(INTS);
  } else {
    float *tmp_left = (float *)cast_to[left.attr_type_][FLOATS](left.data_);
    float *tmp_right = (float *)cast_to[right.attr_type_][FLOATS](right.data_);
    assert(nullptr != tmp_left);
    assert(nullptr != tmp_right);
    float *result_data = new float(*tmp_left - *tmp_right);
    result_cell.set_data((char *)result_data);
    result_cell.set_type(FLOATS);
    free(tmp_left);
    free(tmp_right);
  }
  return result_cell;
}

const TupleCell TupleCell::mul(const TupleCell &left, const TupleCell &right)
{
  TupleCell result_cell;
  if (left.is_null() || right.is_null()) {
    result_cell.set_null();
    return result_cell;
  }
  if (left.attr_type_ == INTS && right.attr_type_ == INTS) {
    int result = *(int *)left.data_ * *(int *)right.data_;
    int *result_data = new int(result);
    result_cell.set_data((char *)result_data);
    result_cell.set_type(INTS);
  } else {
    float *tmp_left = (float *)cast_to[left.attr_type_][FLOATS](left.data_);
    float *tmp_right = (float *)cast_to[right.attr_type_][FLOATS](right.data_);
    assert(nullptr != tmp_left);
    assert(nullptr != tmp_right);
    float *result_data = new float(*tmp_left * *tmp_right);
    result_cell.set_data((char *)result_data);
    result_cell.set_type(FLOATS);
    free(tmp_left);
    free(tmp_right);
  }
  return result_cell;
}

const TupleCell TupleCell::div(const TupleCell &left, const TupleCell &right)
{
  TupleCell result_cell;
  if (left.is_null() || right.is_null()) {
    result_cell.set_null();
    return result_cell;
  }
  float *tmp_left = (float *)cast_to[left.attr_type_][FLOATS](left.data_);
  float *tmp_right = (float *)cast_to[right.attr_type_][FLOATS](right.data_);
  assert(nullptr != tmp_left);
  assert(nullptr != tmp_right);
  float result = 0;
  if (0 == *tmp_right) {
    result_cell.set_type(AttrType::NULLS);
  } else {
    result = *tmp_left / *tmp_right;
    float *result_data = new float(result);
    result_cell.set_type(FLOATS);
    result_cell.set_data((char *)result_data);
  }
  free(tmp_left);
  free(tmp_right);
  return result_cell;
}

const TupleCell TupleCell::add(const TupleCell &left, const TupleCell &right)
{
  TupleCell result_cell;
  if (left.is_null() || right.is_null()) {
    result_cell.set_null();
    return result_cell;
  }
  if (left.attr_type_ == INTS && right.attr_type_ == INTS) {
    int result = *(int *)left.data_ + *(int *)right.data_;
    int *result_data = new int(result);
    result_cell.set_data((char *)result_data);
    result_cell.set_type(INTS);
  } else {
    float *tmp_left = (float *)cast_to[left.attr_type_][FLOATS](left.data_);
    float *tmp_right = (float *)cast_to[right.attr_type_][FLOATS](right.data_);
    assert(nullptr != tmp_left);
    assert(nullptr != tmp_right);
    float *result_data = new float(*tmp_left + *tmp_right);
    result_cell.set_data((char *)result_data);
    result_cell.set_type(FLOATS);
    free(tmp_left);
    free(tmp_right);
  }
  return result_cell;
}

int TupleCell::compare(const TupleCell &other) const
{
  // NULL cannot be here. It's uncomparable.
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case INTS:
      case DATES:
        return compare_int(this->data_, other.data_);
      case FLOATS:
        return compare_float(this->data_, other.data_);
      case CHARS:
        return compare_string(this->data_, this->length_, other.data_, other.length_);
      case NULLS:
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = (float)*(int *)data_;
    return compare_float(&this_data, other.data_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = (float)*(int *)other.data_;
    return compare_float(data_, &other_data);
  }
  // for compare.
  float *tmp_left_float = nullptr;
  float *tmp_right_float = nullptr;
  DEFER([&]() {
    if (tmp_left_float)
      free(tmp_left_float);
    if (tmp_right_float)
      free(tmp_right_float);
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
