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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/lang/defer.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/groupby_stmt.h"
#include "sql/stmt/orderby_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/common/db.h"
#include "storage/common/table.h"

#define DEFER_WHEN_NOT_NULL(ptr) \
  DEFER([ptr]() {                \
    if (nullptr != (ptr)) {      \
      delete (ptr);              \
    }                            \
  });

SelectStmt::~SelectStmt()
{
  if (nullptr != inner_join_filter_stmt_) {
    delete inner_join_filter_stmt_;
    inner_join_filter_stmt_ = nullptr;
  }

  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }

  if (nullptr != having_stmt_) {
    delete having_stmt_;
    having_stmt_ = nullptr;
  }

  for (auto expr : projects_) {
    delete expr;
  }
  projects_.clear();

  if (nullptr != orderby_stmt_) {
    delete orderby_stmt_;
    orderby_stmt_ = nullptr;
  }

  if (nullptr != orderby_stmt_for_groupby_) {
    delete orderby_stmt_for_groupby_;
    orderby_stmt_for_groupby_ = nullptr;
  }

  if (nullptr != groupby_stmt_) {
    delete groupby_stmt_;
    groupby_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Expression *> &projects)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num() - table_meta.extra_filed_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    if (table_meta.field(i)->visible()) {
      projects.emplace_back(new FieldExpr(table, table_meta.field(i)));
    }
  }
}

RC SelectStmt::create(Db *db, const Selects &select_sql, const std::vector<Table *> &parent_tables,
    const std::unordered_map<std::string, Table *> &parent_table_map, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  std::unordered_map<Table *, std::string> alias_map;
  for (size_t i = 0; i < select_sql.relation_num; i++) {
    const char *table_name = select_sql.relations[i].relation_name;
    const char *alias_name = select_sql.relations[i].alias;
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    // duplicate alias
    if (nullptr != alias_name) {
      if (0 != table_map.count(std::string(alias_name))) {
        return RC::SQL_SYNTAX;
      }
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
    if (alias_name != nullptr) {
      table_map.insert(std::pair<std::string, Table *>(alias_name, table));
      alias_map.insert(std::pair<Table *, std::string>(table, alias_name));
    }
  }

  // collect query fields in `select` statement
  // TODO(wbj) check aggrfunc fields
  std::vector<Expression *> projects;
  for (int i = (int)select_sql.project_num - 1; i >= 0; i--) {
    const ProjectCol &project_col = select_sql.projects[i];
    // only *
    if (common::is_blank(project_col.relation_name) && project_col.is_star) {

      for (auto it = tables.rbegin(); it != tables.rend(); it++) {
        //     wildcard_fields(*it, projects);
        auto it2 = alias_map.find(*it);
        std::string table_name((*it)->name());
        if (it2 != alias_map.end()) {
          table_name = it2->second;
        }
        Table *table = *it;
        const TableMeta &table_meta = table->table_meta();
        const int field_num = table_meta.field_num() - table_meta.extra_filed_num();
        for (int i = table_meta.sys_field_num(); i < field_num; i++) {
          if (table_meta.field(i)->visible()) {
            FieldExpr *tmp_field = new FieldExpr(table, table_meta.field(i));
            std::string alias;
            if (tables.size() == 1) {
              alias = std::string(table_meta.field(i)->name());
            } else {
              alias = std::string(table_name) + '.' + std::string(table_meta.field(i)->name());
            }
            tmp_field->set_alias(alias);
            projects.emplace_back(tmp_field);
          }
        }
      }
    } else if (!common::is_blank(project_col.relation_name) && project_col.is_star)  // table_id.*
    {
      const char *table_name = project_col.relation_name;
      if (0 == strcmp(table_name, "*")) {
        for (Table *table : tables) {
          wildcard_fields(table, projects);
        }
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        Table *table = iter->second;
        const TableMeta &table_meta = table->table_meta();
        const int field_num = table_meta.field_num() - table_meta.extra_filed_num();
        for (int i = table_meta.sys_field_num(); i < field_num; i++) {
          if (table_meta.field(i)->visible()) {
            FieldExpr *tmp_field = new FieldExpr(table, table_meta.field(i));
            std::string alias;
            if (tables.size() == 1) {
              alias = std::string(table_meta.field(i)->name());
            } else {
              alias = std::string(table_name) + '.' + std::string(table_meta.field(i)->name());
            }
            tmp_field->set_alias(alias);
            projects.emplace_back(tmp_field);
          }
        }
      }
    } else  // expression
    {
      Expression *res_project;
      RC rc = Expression::create_expression(project_col.expr, table_map, tables, res_project);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      if (project_col.expr->alias != nullptr) {
        std::string alias = std::string(project_col.expr->alias);
        res_project->set_alias(alias);
      }
      projects.emplace_back(res_project);
    }
  }

  LOG_INFO("got %d tables in from stmt and %d projects in query stmt", tables.size(), projects.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  RC rc = RC::SUCCESS;
  std::unordered_map<std::string, Table *> temp_table_map = table_map;
  temp_table_map.insert(parent_table_map.begin(), parent_table_map.end());

  // create filter statement in `inner join on` statement
  FilterStmt *inner_join_filter_stmt = nullptr;
  DEFER_WHEN_NOT_NULL(inner_join_filter_stmt);
  if (0 != select_sql.condition_num) {
    rc = FilterStmt::create(
        db, default_table, &temp_table_map, select_sql.conditions, select_sql.condition_num, inner_join_filter_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct inner join filter stmt");
      return rc;
    }
  }

  FilterStmt *filter_stmt = nullptr;
  DEFER_WHEN_NOT_NULL(filter_stmt);
  if (0 != select_sql.has_where) {
    rc = FilterStmt::create(db, default_table, &temp_table_map, &select_sql.where_condition, 1, filter_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct filter stmt");
      return rc;
    }
  }

  OrderByStmt *orderby_stmt = nullptr;
  DEFER_WHEN_NOT_NULL(orderby_stmt);
  if (0 != select_sql.orderby_num) {
    rc = OrderByStmt::create(db, default_table, &table_map, select_sql.orderbys, select_sql.orderby_num, orderby_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct order by stmt");
      return rc;
    }
  }

  OrderByStmt *orderby_stmt_for_groupby = nullptr;
  GroupByStmt *groupby_stmt = nullptr;
  DEFER_WHEN_NOT_NULL(orderby_stmt_for_groupby);
  DEFER_WHEN_NOT_NULL(groupby_stmt);
  if (0 != select_sql.groupby_num) {
    rc = OrderByStmt::create(
        db, default_table, &table_map, select_sql.groupbys, select_sql.groupby_num, orderby_stmt_for_groupby);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct order by stmt for groupby");
      return rc;
    }
    rc = GroupByStmt::create(db, default_table, &table_map, select_sql.groupbys, select_sql.groupby_num, groupby_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct group by stmt");
      return rc;
    }
  }

  // create having filter statement in `having` clause
  HavingStmt *having_stmt = nullptr;
  DEFER_WHEN_NOT_NULL(having_stmt);
  if (0 != select_sql.having_num) {
    rc = FilterStmt::create(db, default_table, &table_map, select_sql.havings, select_sql.having_num, having_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct having filter stmt");
      return rc;
    }
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  select_stmt->tables_.swap(tables);
  select_stmt->projects_.swap(projects);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->inner_join_filter_stmt_ = inner_join_filter_stmt;
  select_stmt->having_stmt_ = having_stmt;
  select_stmt->orderby_stmt_ = orderby_stmt;
  select_stmt->orderby_stmt_for_groupby_ = orderby_stmt_for_groupby;
  select_stmt->groupby_stmt_ = groupby_stmt;
  stmt = select_stmt;
  return RC::SUCCESS;
}
