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
// Created by Meiyi & Wangyunlai.wyl on 2021/5/18.
//

#include "storage/common/index_meta.h"
#include "storage/common/field_meta.h"
#include "storage/common/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "rc.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString UNIQUE_OR_NOT("unique");
const static Json::StaticString FIELD_FIELD_NAME("field_name");

RC IndexMeta::init(const char *name, bool unique, std::vector<std::string> field)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  field_ = field;
  unique_ = unique;
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME] = name_;
  json_value[UNIQUE_OR_NOT] = unique_;
  for (size_t i = 0; i < field_.size(); i++) {
    int idx = i;
    json_value[FIELD_FIELD_NAME][idx] = field_[idx];
  }
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &unique_value = json_value[UNIQUE_OR_NOT];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (!unique_value.isBool()) {
    LOG_ERROR("Unique is not a boolean. json value=%s", unique_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  std::vector<std::string> fields;
  for (size_t i = 0; i < field_value.size(); i++) {
    int idx = i;
    if (!field_value[idx].isString()) {
      LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
          name_value.asCString(),
          field_value.toStyledString().c_str());
      return RC::GENERIC_ERROR;
    }

    const FieldMeta *field = table.field(field_value[idx].asCString());
    if (nullptr == field) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value.asCString());
      return RC::SCHEMA_FIELD_MISSING;
    }
    fields.push_back(field->name());
  }

  return index.init(name_value.asCString(), unique_value.asBool(), fields);
}

const char *IndexMeta::name() const
{
  return name_.c_str();
}

const bool IndexMeta::is_unique() const
{
  return unique_;
}
const int IndexMeta::field_count() const
{
  return field_.size();
}

const std::vector<std::string> *IndexMeta::field() const
{
  return &field_;
}

void IndexMeta::desc(std::ostream &os) const
{
  os << "index name=" << name_ << ", field=" << field_[0];

  for (size_t i = 1; i < field_.size(); i++) {
    os << ',' << field_[i];
  }
}

void IndexMeta::show(std::ostream &os, const char *table_name) const
{
  for (int i = 0; i < field_count(); i++) {
    os << table_name << " | " << (unique_ ? 0 : 1) << " | " << name_ << " | " << (i + 1) << " | " << field_[i]
       << std::endl;
  }
}