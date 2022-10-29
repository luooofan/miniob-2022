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
// Created by Wangyunlai on 2022/07/08.
//

#include "sql/operator/index_scan_operator.h"
#include "storage/index/index.h"

IndexScanOperator::IndexScanOperator(const Table *table, Index *index, const TupleCell *left_cell, bool left_inclusive,
    const TupleCell *right_cell, bool right_inclusive)
    : table_(table), index_(index), left_inclusive_(left_inclusive), right_inclusive_(right_inclusive)
{
  if (left_cell) {
    left_cell_ = *left_cell;
  }
  if (right_cell) {
    right_cell_ = *right_cell;
  }
}

RC IndexScanOperator::open()
{
  if (nullptr == table_ || nullptr == index_) {
    return RC::INTERNAL;
  }

  const char *left;
  const char *right;
  int left_len = 0;
  int right_len = 0;
  int value_len = 0;
  int map_len = table_->table_meta().null_bitmap_field()->len();
  for (int i = 0; i < index_->index_meta().field_count(); i++) {
    const char *field_name = index_->index_meta().field()->at(i).c_str();
    value_len += table_->table_meta().field(field_name)->len();
  }

  char *left_with_bitmap = new char[map_len + value_len];
  char *right_with_bitmap = new char[map_len + value_len];
  if (nullptr != left_cell_.data()) {
    memset(left_with_bitmap, 0, map_len + value_len);
    common::Bitmap left_map(left_with_bitmap, map_len);
    if (left_cell_.attr_type() == AttrType::NULLS) {
      const char *field_name = index_->index_meta().field()->at(0).c_str();
      int field_id = table_->table_meta().field(field_name)->id();
      left_map.set_bit(field_id);
    }
    memcpy(left_with_bitmap + map_len, left_cell_.data(), value_len);
    left = left_with_bitmap;
    left_len = map_len + value_len;
  } else {
    left = nullptr;
    left_len = left_cell_.length();
  }

  if (nullptr != right_cell_.data()) {
    memset(left_with_bitmap, 0, map_len + value_len);
    common::Bitmap right_map(right_with_bitmap, map_len);
    if (right_cell_.attr_type() == AttrType::NULLS) {
      const char *field_name = index_->index_meta().field()->at(0).c_str();
      int field_id = table_->table_meta().field(field_name)->id();
      right_map.set_bit(field_id);
    }
    memcpy(right_with_bitmap + map_len, right_cell_.data(), value_len);
    right = right_with_bitmap;
    right_len = map_len + value_len;
  } else {
    right = nullptr;
    right_len = right_cell_.length();
  }

  IndexScanner *index_scanner =
      index_->create_scanner(left, left_len, left_inclusive_, right, right_len, right_inclusive_);
  delete[] left_with_bitmap;
  delete[] right_with_bitmap;

  if (nullptr == index_scanner) {
    LOG_WARN("failed to create index scanner");
    return RC::INTERNAL;
  }

  record_handler_ = table_->record_handler();
  if (nullptr == record_handler_) {
    LOG_WARN("invalid record handler");
    index_scanner->destroy();
    return RC::INTERNAL;
  }
  index_scanner_ = index_scanner;

  tuple_.set_schema(table_, table_->table_meta().field_metas());

  return RC::SUCCESS;
}

RC IndexScanOperator::next()
{
  RID rid;
  RC rc = index_scanner_->next_entry(&rid);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return record_handler_->get_record(&rid, &current_record_);
}

RC IndexScanOperator::close()
{
  index_scanner_->destroy();
  index_scanner_ = nullptr;
  return RC::SUCCESS;
}

Tuple *IndexScanOperator::current_tuple()
{
  tuple_.set_record(&current_record_);
  return &tuple_;
}
