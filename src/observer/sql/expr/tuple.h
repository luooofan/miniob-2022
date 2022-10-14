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
// Created by Wangyunlai on 2021/5/14.
//

#pragma once

#include <memory>
#include <vector>

#include "common/log/log.h"
#include "sql/parser/parse.h"
#include "sql/expr/tuple_cell.h"
#include "sql/expr/expression.h"
#include "storage/record/record.h"

class Table;

class TupleCellSpec {
public:
  TupleCellSpec() = default;
  TupleCellSpec(Expression *expr) : expression_(expr)
  {}

  ~TupleCellSpec()
  {
    if (expression_) {
      delete expression_;
      expression_ = nullptr;
    }
  }

  void set_alias(const char *alias)
  {
    // this->alias_ = alias;
    alias_ = std::shared_ptr<std::string>(new std::string(alias));
  }
  void set_alias(std::shared_ptr<std::string> ptr)
  {
    alias_ = ptr;
  }

  std::shared_ptr<std::string> get_alias_ptr()
  {
    return alias_;
  }

  const char *alias() const
  {
    return alias_.get()->c_str();
  }

  Expression *expression() const
  {
    return expression_;
  }

private:
  // const char *alias_ = nullptr;
  // const std::string* alias_ = nullptr;
  std::shared_ptr<std::string> alias_ = nullptr;
  Expression *expression_ = nullptr;
};

class Tuple {
public:
  Tuple() = default;
  virtual ~Tuple() = default;

  virtual int cell_num() const = 0;
  virtual RC cell_at(int index, TupleCell &cell) const = 0;
  virtual RC find_cell(const Field &field, TupleCell &cell) const = 0;

  virtual RC cell_spec_at(int index, const TupleCellSpec *&spec) const = 0;

  virtual void get_record(CompoundRecord &record) const = 0;
};

class RowTuple : public Tuple {
public:
  RowTuple() = default;
  virtual ~RowTuple()
  {
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_record(Record *record)
  {
    this->record_ = record;
  }

  void set_schema(const Table *table, const std::vector<FieldMeta> *fields)
  {
    table_ = table;
    this->speces_.reserve(fields->size());
    for (const FieldMeta &field : *fields) {
      speces_.push_back(new TupleCellSpec(new FieldExpr(table, &field)));
    }
  }

  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    const TupleCellSpec *spec = speces_[index];
    FieldExpr *field_expr = (FieldExpr *)spec->expression();
    const FieldMeta *field_meta = field_expr->field().meta();
    cell.set_type(field_meta->type());
    cell.set_data(this->record_->data() + field_meta->offset());
    cell.set_length(field_meta->len());
    return RC::SUCCESS;
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    const char *table_name = field.table_name();
    if (0 != strcmp(table_name, table_->name())) {
      return RC::NOTFOUND;
    }

    const char *field_name = field.field_name();
    for (size_t i = 0; i < speces_.size(); ++i) {
      const FieldExpr *field_expr = (const FieldExpr *)speces_[i]->expression();
      const Field &field = field_expr->field();
      if (0 == strcmp(field_name, field.field_name())) {
        return cell_at(i, cell);
      }
    }
    return RC::NOTFOUND;
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }

  Record &record()
  {
    return *record_;
  }

  const Record &record() const
  {
    return *record_;
  }

  void get_record(CompoundRecord &record) const override
  {
    record.emplace_back(record_);
  }

private:
  Record *record_ = nullptr;
  const Table *table_ = nullptr;
  std::vector<TupleCellSpec *> speces_;
};

/*
class CompositeTuple : public Tuple
{
public:
  int cell_num() const override;
  RC  cell_at(int index, TupleCell &cell) const = 0;
private:
  int cell_num_ = 0;
  std::vector<Tuple *> tuples_;
};
*/

class ProjectTuple : public Tuple {
public:
  ProjectTuple() = default;
  virtual ~ProjectTuple()
  {
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_tuple(Tuple *tuple)
  {
    this->tuple_ = tuple;
  }

  void add_cell_spec(TupleCellSpec *spec)
  {
    speces_.push_back(spec);
  }
  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::GENERIC_ERROR;
    }
    if (tuple_ == nullptr) {
      return RC::GENERIC_ERROR;
    }

    const TupleCellSpec *spec = speces_[index];
    return spec->expression()->get_value(*tuple_, cell);
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    return tuple_->find_cell(field, cell);
  }
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::NOTFOUND;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }

  void get_record(CompoundRecord &record) const override
  {
    tuple_->get_record(record);
  }

private:
  std::vector<TupleCellSpec *> speces_;
  Tuple *tuple_ = nullptr;
};

class CompoundTuple : public Tuple {
public:
  CompoundTuple() = default;
  CompoundTuple(Tuple *left, Tuple *right)
  {
    init(left, right);
  }
  virtual ~CompoundTuple() = default;

  void init(Tuple *left, Tuple *right)
  {
    auto fill_tuples = [this](Tuple *tup) {
      RowTuple *rtup = nullptr;
      CompoundTuple *ctup = nullptr;
      if (nullptr != (rtup = dynamic_cast<RowTuple *>(tup))) {
        tuples_.push_back(rtup);
      } else if (nullptr != (ctup = dynamic_cast<CompoundTuple *>(tup))) {
        auto tups = ctup->get_tuples();
        tuples_.insert(tuples_.end(), tups.begin(), tups.end());
      }
    };
    fill_tuples(left);
    fill_tuples(right);
  }

  const std::vector<RowTuple *> &get_tuples() const
  {
    return tuples_;
  }

  void set_right_record(const CompoundRecord &record)
  {
    assert(tuples_.size() > record.size());
    auto tup_rit = tuples_.rbegin();
    auto rcd_rit = record.rbegin();
    for (; rcd_rit != record.rend(); ++tup_rit, ++rcd_rit) {
      (*tup_rit)->set_record(*rcd_rit);
    }
  }

  void set_record(const CompoundRecord &record)
  {
    assert(tuples_.size() == record.size());
    auto tup_it = tuples_.begin();
    auto rcd_it = record.begin();
    for (; tup_it != tuples_.end(); ++tup_it, ++rcd_it) {
      (*tup_it)->set_record(*rcd_it);
    }
  }

  int cell_num() const override
  {
    int num = 0;
    for (auto tup : tuples_) {
      num += tup->cell_num();
    }
    return num;
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    Tuple *tuple = nullptr;
    int real_index = -1;
    RC rc = find_tuple_and_index(index, tuple, real_index);
    if (RC::SUCCESS != rc) {
      return rc;
    }
    return tuple->cell_at(real_index, cell);
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    for (auto tup : tuples_) {
      if (RC::SUCCESS == tup->find_cell(field, cell)) {
        return RC::SUCCESS;
      }
    }
    return RC::NOTFOUND;
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    Tuple *tuple = nullptr;
    int real_index = -1;
    RC rc = find_tuple_and_index(index, tuple, real_index);
    if (RC::SUCCESS != rc) {
      return rc;
    }
    return tuple->cell_spec_at(real_index, spec);
  }

  void get_record(CompoundRecord &record) const override
  {
    for (auto tup : tuples_) {
      tup->get_record(record);
    }
  }

private:
  RC find_tuple_and_index(int index, Tuple *&tuple, int &real_index) const
  {
    if (index < 0 || index >= cell_num()) {
      return RC::INVALID_ARGUMENT;
    }
    int idx = 0;
    for (auto tup : tuples_) {
      if (idx + tup->cell_num() >= index) {
        tuple = tup;
        real_index = index - idx;
      }
      idx += tup->cell_num();
    }
    return RC::SUCCESS;
  }

private:
  std::vector<RowTuple *> tuples_;
};
