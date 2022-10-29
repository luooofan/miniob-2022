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
// Created by Meiyi & Longda on 2021/4/13.
//

#include <memory>
#include <string>
#include <sstream>
#include <vector>

#include "common/defs.h"
#include "execute_stage.h"

#include "common/io/io.h"
#include "common/log/log.h"
#include "common/lang/defer.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/operator/dual_table_scan_operator.h"
#include "sql/operator/groupby_operator.h"
#include "sql/operator/operator.h"
#include "sql/operator/table_scan_operator.h"
#include "sql/operator/index_scan_operator.h"
#include "sql/operator/predicate_operator.h"
#include "sql/operator/insert_operator.h"
#include "sql/operator/update_operator.h"
#include "sql/operator/delete_operator.h"
#include "sql/operator/project_operator.h"
#include "sql/operator/join_operator.h"
#include "sql/operator/sort_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/groupby_stmt.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/table.h"
#include "storage/common/field.h"
#include "storage/index/index.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"
#include "storage/clog/clog.h"

using namespace common;

typedef std::vector<FilterUnit *> FilterUnits;

// RC create_selection_executor(
//   Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node);

//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag)
{}

//! Destructor
ExecuteStage::~ExecuteStage()
{}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag)
{
  ExecuteStage *stage = new (std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties()
{
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize()
{
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup()
{
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event)
{
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context)
{
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::handle_request(common::StageEvent *event)
{
  SQLStageEvent *sql_event = static_cast<SQLStageEvent *>(event);
  SessionEvent *session_event = sql_event->session_event();
  Stmt *stmt = sql_event->stmt();
  Session *session = session_event->session();
  Query *sql = sql_event->query();

  if (stmt != nullptr) {
    switch (stmt->type()) {
      case StmtType::SELECT: {
        do_select(sql_event);
      } break;
      case StmtType::INSERT: {
        do_insert(sql_event);
      } break;
      case StmtType::UPDATE: {
        do_update(sql_event);
      } break;
      case StmtType::DELETE: {
        do_delete(sql_event);
      } break;
      default: {
        LOG_WARN("should not happen. please implenment");
      } break;
    }
  } else {
    switch (sql->flag) {
      case SCF_HELP: {
        do_help(sql_event);
      } break;
      case SCF_CREATE_TABLE: {
        do_create_table(sql_event);
      } break;
      case SCF_CREATE_INDEX: {
        do_create_index(sql_event);
      } break;
      case SCF_SHOW_TABLES: {
        do_show_tables(sql_event);
      } break;
      case SCF_DESC_TABLE: {
        do_desc_table(sql_event);
      } break;
      case SCF_SHOW_INDEX: {
        do_show_index(sql_event);
      } break;
      case SCF_DROP_TABLE: {
        do_drop_table(sql_event);
      } break;
      case SCF_DROP_INDEX:
      case SCF_LOAD_DATA: {
        default_storage_stage_->handle_event(event);
      } break;
      case SCF_SYNC: {
        /*
        RC rc = DefaultHandler::get_default().sync();
        session_event->set_response(strrc(rc));
        */
      } break;
      case SCF_BEGIN: {
        do_begin(sql_event);
        /*
        session_event->set_response("SUCCESS\n");
        */
      } break;
      case SCF_COMMIT: {
        do_commit(sql_event);
        /*
        Trx *trx = session->current_trx();
        RC rc = trx->commit();
        session->set_trx_multi_operation_mode(false);
        session_event->set_response(strrc(rc));
        */
      } break;
      case SCF_CLOG_SYNC: {
        do_clog_sync(sql_event);
      }
      case SCF_ROLLBACK: {
        Trx *trx = session_event->get_client()->session->current_trx();
        RC rc = trx->rollback();
        session->set_trx_multi_operation_mode(false);
        session_event->set_response(strrc(rc));
      } break;
      case SCF_EXIT: {
        // do nothing
        const char *response = "Unsupported\n";
        session_event->set_response(response);
      } break;
      default: {
        LOG_ERROR("Unsupported command=%d\n", sql->flag);
      }
    }
  }
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right)
{
  if (!session->is_trx_multi_operation_mode()) {
    if (all_right) {
      trx->commit();
    } else {
      trx->rollback();
    }
  }
}

void print_tuple_header(std::ostream &os, const ProjectOperator &oper)
{
  const int cell_num = oper.tuple_cell_num();
  const TupleCellSpec *cell_spec = nullptr;
  for (int i = 0; i < cell_num; i++) {
    oper.tuple_cell_spec_at(i, cell_spec);
    if (i != 0) {
      os << " | ";
    }

    if (cell_spec->alias()) {
      os << cell_spec->alias();
    }
  }

  if (cell_num > 0) {
    os << '\n';
  }
}
RC tuple_to_string(std::ostream &os, const Tuple &tuple)
{
  TupleCell cell;
  RC rc = RC::SUCCESS;
  bool first_field = true;
  for (int i = 0; i < tuple.cell_num(); i++) {
    rc = tuple.cell_at(i, cell);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to fetch field of cell. index=%d, rc=%s", i, strrc(rc));
      break;
    }

    if (!first_field) {
      os << " | ";
    } else {
      first_field = false;
    }
    cell.to_string(os);
  }
  return rc;
}

IndexScanOperator *try_to_create_index_scan_operator(const FilterUnits &filter_units)
{
  if (filter_units.empty()) {
    return nullptr;
  }

  // 在所有过滤条件中，找到字段与值做比较的条件，然后判断字段是否可以使用索引
  // 如果是多列索引，这里的处理需要更复杂。
  // 这里的查找规则是比较简单的，就是尽量找到使用相等比较的索引
  // 如果没有就找范围比较的，但是直接排除不等比较的索引查询. (你知道为什么?)
  const FilterUnit *better_filter = nullptr;
  for (const FilterUnit *filter_unit : filter_units) {
    if (filter_unit->comp() == NOT_EQUAL) {
      continue;
    }

    if (AND_OP == filter_unit->comp() || OR_OP == filter_unit->comp()) {
      continue;
    }

    Expression *left = filter_unit->left();
    Expression *right = filter_unit->right();
    if (left->type() == ExprType::FIELD && right->type() == ExprType::VALUE) {
    } else if (left->type() == ExprType::VALUE && right->type() == ExprType::FIELD) {
      std::swap(left, right);
    } else {
      continue;
    }
    FieldExpr &left_field_expr = *(FieldExpr *)left;
    const Field &field = left_field_expr.field();
    const Table *table = field.table();
    Index *index = table->find_index_by_field(field.field_name());
    if (index != nullptr) {
      if (better_filter == nullptr) {
        better_filter = filter_unit;
      } else if (filter_unit->comp() == EQUAL_TO) {
        better_filter = filter_unit;
        break;
      }
    }
  }

  if (better_filter == nullptr) {
    return nullptr;
  }

  Expression *left = better_filter->left();
  Expression *right = better_filter->right();
  CompOp comp = better_filter->comp();
  if (left->type() == ExprType::VALUE && right->type() == ExprType::FIELD) {
    std::swap(left, right);
    switch (comp) {
      case EQUAL_TO: {
        comp = EQUAL_TO;
      } break;
      case LESS_EQUAL: {
        comp = GREAT_THAN;
      } break;
      case NOT_EQUAL: {
        comp = NOT_EQUAL;
      } break;
      case LESS_THAN: {
        comp = GREAT_EQUAL;
      } break;
      case GREAT_EQUAL: {
        comp = LESS_THAN;
      } break;
      case GREAT_THAN: {
        comp = LESS_EQUAL;
      } break;
      default: {
        LOG_WARN("should not happen");
      }
    }
  }

  FieldExpr &left_field_expr = *(FieldExpr *)left;
  const Field &field = left_field_expr.field();
  const Table *table = field.table();
  Index *index = table->find_index_by_field(field.field_name());
  assert(index != nullptr);

  ValueExpr &right_value_expr = *(ValueExpr *)right;
  TupleCell value;
  right_value_expr.get_tuple_cell(value);

  // left是field, right是value
  const TupleCell *left_cell = nullptr;
  const TupleCell *right_cell = nullptr;
  bool left_inclusive = false;
  bool right_inclusive = false;

  switch (comp) {
    case EQUAL_TO: {
      left_cell = &value;
      right_cell = &value;
      left_inclusive = true;
      right_inclusive = true;
    } break;

    case LESS_EQUAL: {
      left_cell = nullptr;
      left_inclusive = false;
      right_cell = &value;
      right_inclusive = true;
    } break;

    case LESS_THAN: {
      left_cell = nullptr;
      left_inclusive = false;
      right_cell = &value;
      right_inclusive = false;
    } break;

    case GREAT_EQUAL: {
      left_cell = &value;
      left_inclusive = true;
      right_cell = nullptr;
      right_inclusive = false;
    } break;

    case GREAT_THAN: {
      left_cell = &value;
      left_inclusive = false;
      right_cell = nullptr;
      right_inclusive = false;
    } break;

    default: {
      LOG_WARN("should not happen. comp=%d", comp);
    } break;
  }

  IndexScanOperator *oper = new IndexScanOperator(table, index, left_cell, left_inclusive, right_cell, right_inclusive);

  LOG_INFO("use index for scan: %s in table %s", index->index_meta().name(), table->name());
  return oper;
}

// TODO(wbj) have to reconsider this function
std::unordered_map<Table *, std::unique_ptr<FilterUnits>> split_filters(
    const std::vector<Table *> &tables, FilterStmt *filter_stmt)
{
  std::unordered_map<Table *, std::unique_ptr<FilterUnits>> res;
  for (auto table : tables) {
    res[table] = std::make_unique<FilterUnits>();
  }
  if (nullptr == filter_stmt) {
    return res;
  }
  for (auto filter : filter_stmt->filter_units()) {
    // TODO(wbj)
    if (CompOp::AND_OP == filter->comp() || CompOp::OR_OP == filter->comp()) {
      continue;
    }
    Expression *left = filter->left();
    Expression *right = filter->right();
    if (ExprType::FIELD == left->type() && ExprType::VALUE == right->type()) {
    } else if (ExprType::FIELD == right->type() && ExprType::VALUE == left->type()) {
      std::swap(left, right);
    } else {
      continue;
    }
    // TODO: NEED TO CONSIDER SUB_QUERY
    // only support FILED comp VALUE or VALUE comp FILED now
    assert(ExprType::FIELD == left->type() && ExprType::VALUE == right->type());
    auto &left_filed_expr = *static_cast<FieldExpr *>(left);
    const Field &field = left_filed_expr.field();
    res[const_cast<Table *>(field.table())]->emplace_back(filter);
  }
  return res;
}

RC ExecuteStage::gen_join_operator(
    const SelectStmt *select_stmt, Operator *&result_op, std::vector<Operator *> &delete_opers)
{
  std::list<Operator *> oper_store;
  std::list<Table *> table_list;
  {
    const auto &tables = select_stmt->tables();
    FilterStmt *filter_stmt = select_stmt->filter_stmt();  // maybe null
    auto table_filters_ht = split_filters(tables, filter_stmt);
    for (std::vector<Table *>::size_type i = 0; i < tables.size(); i++) {
      Operator *scan_oper = try_to_create_index_scan_operator(*table_filters_ht[tables[i]]);
      if (nullptr == scan_oper) {
        scan_oper = new TableScanOperator(tables[i]);
      }
      oper_store.push_front(scan_oper);
      table_list.push_front(tables[i]);
      delete_opers.push_back(scan_oper);
    }
  }

  std::unordered_set<const Table *> table_set;
  table_set.insert(table_list.front());
  table_list.pop_front();
  std::vector<FilterUnit *> filter_units;  // push down inner join on filter. cond and cond and ...
  if (nullptr != select_stmt->inner_join_filter_stmt()) {
    filter_units = select_stmt->inner_join_filter_stmt()->filter_units();
  }

  while (oper_store.size() > 1) {
    JoinOperator *join_oper = NULL;
    Operator *left_oper = NULL;
    Operator *right_oper = NULL;

    left_oper = oper_store.front();
    oper_store.pop_front();
    right_oper = oper_store.front();
    oper_store.pop_front();

    table_set.insert(table_list.front());
    table_list.pop_front();

    join_oper = new JoinOperator(left_oper, right_oper);
    oper_store.push_front(join_oper);
    delete_opers.push_back(join_oper);

    // get proper filter unit. then add to join_oper
    for (auto it = filter_units.begin(); it != filter_units.end();) {
      auto unit = *it;
      bool addable = true;
      assert(CompOp::AND_OP != unit->comp() && CompOp::OR_OP != unit->comp());
      Expression *left_expr = unit->left();
      if (ExprType::FIELD == left_expr->type()) {
        if (0 == table_set.count(((FieldExpr *)left_expr)->table())) {
          addable = false;
        }
      }
      Expression *right_expr = unit->right();
      if (ExprType::FIELD == right_expr->type()) {
        if (0 == table_set.count(((FieldExpr *)right_expr)->table())) {
          addable = false;
        }
      }
      if (addable) {
        join_oper->add_filter_unit(unit);
        it = filter_units.erase(it);
      } else {
        it++;
      }
    }
  }

  result_op = oper_store.front();
  return RC::SUCCESS;
}

RC ExecuteStage::gen_physical_plan_for_subquery(const FilterUnit *filter, std::vector<Operator *> &delete_opers)
{
  RC rc = RC::SUCCESS;
  // process sub query
  auto process_sub_query_expr = [&](Expression *expr) {
    if (ExprType::SUBQUERYTYPE == expr->type()) {
      auto sub_query_expr = (SubQueryExpression *)expr;
      const SelectStmt *sub_select = sub_query_expr->get_sub_query_stmt();
      ProjectOperator *sub_project = nullptr;
      if (RC::SUCCESS != (rc = gen_physical_plan(sub_select, sub_project, delete_opers))) {
        return rc;
      }
      assert(nullptr != sub_project);
      sub_query_expr->set_sub_query_top_oper(sub_project);
    }
    return RC::SUCCESS;
  };

  if (CompOp::AND_OP == filter->comp() || CompOp::OR_OP == filter->comp()) {
    if (RC::SUCCESS != (rc = gen_physical_plan_for_subquery(filter->left_unit(), delete_opers))) {
      return rc;
    }
    return gen_physical_plan_for_subquery(filter->right_unit(), delete_opers);
  }

  if (RC::SUCCESS != (rc = process_sub_query_expr(filter->left()))) {
    return rc;
  }
  return process_sub_query_expr(filter->right());
}
// remember to delete these operators
RC ExecuteStage::gen_physical_plan(
    const SelectStmt *select_stmt, ProjectOperator *&op, std::vector<Operator *> &delete_opers)
{
  RC rc = RC::SUCCESS;
  bool is_single_table = true;
  Operator *scan_oper = nullptr;
  if (select_stmt->tables().size() > 1) {
    rc = gen_join_operator(select_stmt, scan_oper, delete_opers);
    if (RC::SUCCESS != rc) {
      return rc;
    }
    is_single_table = false;
  } else if (select_stmt->tables().size() == 1) {
    if (nullptr != select_stmt->filter_stmt()) {
      scan_oper = try_to_create_index_scan_operator(select_stmt->filter_stmt()->filter_units());
    }
    if (nullptr == scan_oper) {
      scan_oper = new TableScanOperator(select_stmt->tables()[0]);
    }
    delete_opers.push_back(scan_oper);
  } else {
    scan_oper = new DualTableScanOperator();
    delete_opers.push_back(scan_oper);
  }

  assert(nullptr != scan_oper);
  Operator *top_op = scan_oper;

  // 1. process where clause
  PredicateOperator *pred_oper = nullptr;
  if (nullptr != select_stmt->filter_stmt()) {
    pred_oper = new PredicateOperator(select_stmt->filter_stmt());
    pred_oper->add_child(top_op);
    top_op = pred_oper;
    delete_opers.emplace_back(pred_oper);

    for (auto unit : select_stmt->filter_stmt()->filter_units()) {
      if (RC::SUCCESS != (rc = gen_physical_plan_for_subquery(unit, delete_opers))) {
        return rc;
      }
    }
  }

  // 2 process groupby clause and aggrfunc fileds
  // 2.1 gen sort oper for groupby
  SortOperator *sort_oper_for_groupby = nullptr;
  if (nullptr != select_stmt->orderby_stmt_for_groupby()) {
    sort_oper_for_groupby = new SortOperator(select_stmt->orderby_stmt_for_groupby());
    sort_oper_for_groupby->add_child(top_op);
    top_op = sort_oper_for_groupby;
    delete_opers.emplace_back(sort_oper_for_groupby);
  }

  // 2.2 get aggrfunc_exprs from projects
  std::vector<AggrFuncExpression *> aggr_exprs;
  for (auto project : select_stmt->projects()) {
    AggrFuncExpression::get_aggrfuncexprs(project, aggr_exprs);
  }

  // 2.3 get normal field_exprs from projects
  std::vector<FieldExpr *> field_exprs;
  for (auto project : select_stmt->projects()) {
    FieldExpr::get_fieldexprs_without_aggrfunc(project, field_exprs);
  }

  // 2.4 get aggrfunc_exprs field_exprs from havings
  HavingStmt *having_stmt = select_stmt->having_stmt();
  if (nullptr != having_stmt) {
    // TODO(wbj) unique
    for (auto hf : having_stmt->filter_units()) {
      AggrFuncExpression::get_aggrfuncexprs(hf->left(), aggr_exprs);
      AggrFuncExpression::get_aggrfuncexprs(hf->right(), aggr_exprs);
      FieldExpr::get_fieldexprs_without_aggrfunc(hf->left(), field_exprs);
      FieldExpr::get_fieldexprs_without_aggrfunc(hf->right(), field_exprs);
    }
  }

  GroupByStmt *groupby_stmt = select_stmt->groupby_stmt();
  // 2.5 do check (we should do this check earlier actually)
  if (!aggr_exprs.empty() && !field_exprs.empty()) {
    if (nullptr == groupby_stmt) {
      return RC::SQL_SYNTAX;
    }
    for (auto field_expr : field_exprs) {
      bool in_groupby = false;
      for (auto groupby_unit : groupby_stmt->groupby_units()) {
        if (field_expr->in_expression(groupby_unit->expr())) {
          in_groupby = true;
          break;
        }
      }
      if (!in_groupby) {
        return RC::SQL_SYNTAX;
      }
    }
  }

  // 2.6 gen groupby oper
  GroupByStmt *empty_groupby_stmt = nullptr;  // new a empty groupby stmt for no groupby fields
  GroupByOperator *group_oper = nullptr;
  if (0 != aggr_exprs.size()) {
    group_oper = new GroupByOperator(groupby_stmt, aggr_exprs, field_exprs);
    if (nullptr == select_stmt->groupby_stmt()) {
      empty_groupby_stmt = new GroupByStmt();
      group_oper->set_groupby_stmt(empty_groupby_stmt);
    }
    group_oper->add_child(top_op);
    top_op = group_oper;
    delete_opers.emplace_back(group_oper);
  }

  // 3 process having clause
  HavingOperator *having_oper = nullptr;
  if (nullptr != having_stmt) {
    having_oper = new HavingOperator(having_stmt);
    having_oper->add_child(top_op);
    top_op = having_oper;
    delete_opers.emplace_back(having_oper);
  }

  // 4. process orderby clause
  SortOperator *sort_oper = nullptr;
  if (nullptr != select_stmt->orderby_stmt()) {
    sort_oper = new SortOperator(select_stmt->orderby_stmt());
    sort_oper->add_child(top_op);
    top_op = sort_oper;
    delete_opers.emplace_back(sort_oper);
  }

  // 5. process select clause
  ProjectOperator *project_oper = new ProjectOperator();
  project_oper->add_child(top_op);
  // top_op = project_oper;
  auto &projects = select_stmt->projects();
  for (auto it = projects.begin(); it != projects.end(); it++) {
    project_oper->add_projection(*it, is_single_table);
  }

  op = project_oper;
  return RC::SUCCESS;
}

RC ExecuteStage::do_select(SQLStageEvent *sql_event)
{
  SelectStmt *select_stmt = (SelectStmt *)(sql_event->stmt());
  SessionEvent *session_event = sql_event->session_event();

  std::vector<Operator *> delete_opers;
  DEFER([&]() {
    for (auto oper : delete_opers) {
      delete oper;
    }
  });

  ProjectOperator *project_oper = nullptr;
  RC rc = gen_physical_plan(select_stmt, project_oper, delete_opers);
  if (RC::SUCCESS != rc) {
    if (RC::SQL_SYNTAX == rc) {
      session_event->set_response("FAILURE\n");
    }
    return rc;
  }

  assert(nullptr != project_oper);

  rc = project_oper->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open operator");
    session_event->set_response("FAILURE\n");
    return rc;
  }

  std::stringstream ss;
  print_tuple_header(ss, *project_oper);
  while ((rc = project_oper->next()) == RC::SUCCESS) {
    // get current record
    // write to response
    Tuple *tuple = project_oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get current record. rc=%s", strrc(rc));
      break;
    }

    rc = tuple_to_string(ss, *tuple);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("tuple to string failed:%d, %s", rc, strrc(rc));
      break;
    }
    ss << std::endl;
  }

  if (rc != RC::RECORD_EOF) {
    LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
    session_event->set_response("FAILURE\n");
    project_oper->close();
    return rc;
  } else {
    rc = project_oper->close();
  }
  session_event->set_response(ss.str());
  return rc;
}

RC ExecuteStage::do_help(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  const char *response = "show tables;\n"
                         "desc `table name`;\n"
                         "create table `table name` (`column name` `column type`, ...);\n"
                         "create index `index name` on `table` (`column`);\n"
                         "insert into `table` values(`value1`,`value2`);\n"
                         "update `table` set column=value [where `column`=`value`];\n"
                         "delete from `table` [where `column`=`value`];\n"
                         "select [ * | `columns` ] from `table`;\n";
  session_event->set_response(response);
  return RC::SUCCESS;
}

RC ExecuteStage::do_create_table(SQLStageEvent *sql_event)
{
  const CreateTable &create_table = sql_event->query()->sstr.create_table;
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  RC rc = db->create_table(create_table.relation_name, create_table.attribute_count, create_table.attributes);
  if (rc == RC::SUCCESS) {
    session_event->set_response("SUCCESS\n");
  } else {
    session_event->set_response("FAILURE\n");
  }
  return rc;
}

RC ExecuteStage::do_drop_table(SQLStageEvent *sql_event)
{
  const DropTable &drop_table = sql_event->query()->sstr.drop_table;
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();

  Trx *trx = session->current_trx();
  // handle trx here or passed in db->drop_table
  Table *table = db->find_table(drop_table.relation_name);
  if (nullptr != trx) {
    trx->delete_table(table);
  }

  RC rc = db->drop_table(drop_table.relation_name);
  if (rc == RC::SUCCESS) {
    session_event->set_response("SUCCESS\n");
  } else {
    session_event->set_response("FAILURE\n");
  }
  return rc;
}

RC ExecuteStage::do_create_index(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  const CreateIndex &create_index = sql_event->query()->sstr.create_index;
  Table *table = db->find_table(create_index.relation_name);
  if (nullptr == table) {
    session_event->set_response("FAILURE\n");
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  RC rc = table->create_index(
      nullptr, create_index.unique, create_index.index_name, create_index.attribute_count, create_index.attribute_name);

  sql_event->session_event()->set_response(rc == RC::SUCCESS ? "SUCCESS\n" : "FAILURE\n");
  return rc;
}

RC ExecuteStage::do_show_tables(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  std::vector<std::string> all_tables;
  db->all_tables(all_tables);
  if (all_tables.empty()) {
    session_event->set_response("No table\n");
  } else {
    std::stringstream ss;
    for (const auto &table : all_tables) {
      ss << table << std::endl;
    }
    session_event->set_response(ss.str().c_str());
  }
  return RC::SUCCESS;
}

RC ExecuteStage::do_desc_table(SQLStageEvent *sql_event)
{
  Query *query = sql_event->query();
  Db *db = sql_event->session_event()->session()->get_current_db();
  const char *table_name = query->sstr.desc_table.relation_name;
  Table *table = db->find_table(table_name);
  std::stringstream ss;
  if (table != nullptr) {
    table->table_meta().desc(ss);
  } else {
    ss << "No such table: " << table_name << std::endl;
  }
  sql_event->session_event()->set_response(ss.str().c_str());
  return RC::SUCCESS;
}

RC ExecuteStage::do_show_index(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  Query *query = sql_event->query();
  Db *db = sql_event->session_event()->session()->get_current_db();
  const char *table_name = query->sstr.desc_table.relation_name;
  Table *table = db->find_table(table_name);
  std::stringstream ss;
  if (table != nullptr) {
    table->table_meta().show_index(ss);
  } else {
    ss << "FAILURE" << std::endl;
  }
  sql_event->session_event()->set_response(ss.str().c_str());
  return rc;
}

RC ExecuteStage::do_insert(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  Stmt *stmt = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  if (stmt == nullptr) {
    LOG_WARN("cannot find statement");
    return RC::GENERIC_ERROR;
  }

  InsertStmt *insert_stmt = (InsertStmt *)stmt;
  InsertOperator insert_oper(insert_stmt, trx);

  rc = insert_oper.open();
  if (rc == RC::SUCCESS) {
    if (!session->is_trx_multi_operation_mode()) {
      CLogRecord *clog_record = nullptr;
      rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
      if (rc != RC::SUCCESS || clog_record == nullptr) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      rc = clog_manager->clog_append_record(clog_record);
      if (rc != RC::SUCCESS) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      trx->next_current_id();
      session_event->set_response("SUCCESS\n");
    } else {
      session_event->set_response("SUCCESS\n");
    }
  } else {
    session_event->set_response("FAILURE\n");
  }
  return rc;
}

RC ExecuteStage::do_update(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  Stmt *stmt = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  if (stmt == nullptr) {
    LOG_WARN("cannot find statement");
    return RC::GENERIC_ERROR;
  }

  UpdateStmt *update_stmt = (UpdateStmt *)stmt;
  TableScanOperator scan_oper(update_stmt->table());
  PredicateOperator pred_oper(update_stmt->filter_stmt());
  pred_oper.add_child(&scan_oper);
  UpdateOperator update_oper(update_stmt, trx);
  update_oper.add_child(&pred_oper);

  rc = update_oper.open();
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    if (!session->is_trx_multi_operation_mode()) {
      CLogRecord *clog_record = nullptr;
      rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
      if (rc != RC::SUCCESS || clog_record == nullptr) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      rc = clog_manager->clog_append_record(clog_record);
      if (rc != RC::SUCCESS) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      trx->next_current_id();
      session_event->set_response("SUCCESS\n");
    } else {
      session_event->set_response("SUCCESS\n");
    }
  }

  return rc;
}

RC ExecuteStage::do_delete(SQLStageEvent *sql_event)
{
  Stmt *stmt = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  if (stmt == nullptr) {
    LOG_WARN("cannot find statement");
    return RC::GENERIC_ERROR;
  }

  DeleteStmt *delete_stmt = (DeleteStmt *)stmt;
  TableScanOperator scan_oper(delete_stmt->table());
  PredicateOperator pred_oper(delete_stmt->filter_stmt());
  pred_oper.add_child(&scan_oper);
  DeleteOperator delete_oper(delete_stmt, trx);
  delete_oper.add_child(&pred_oper);

  RC rc = delete_oper.open();
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
    if (!session->is_trx_multi_operation_mode()) {
      CLogRecord *clog_record = nullptr;
      rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
      if (rc != RC::SUCCESS || clog_record == nullptr) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      rc = clog_manager->clog_append_record(clog_record);
      if (rc != RC::SUCCESS) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      trx->next_current_id();
      session_event->set_response("SUCCESS\n");
    }
  }
  return rc;
}

RC ExecuteStage::do_begin(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  session->set_trx_multi_operation_mode(true);

  CLogRecord *clog_record = nullptr;
  rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_BEGIN, trx->get_current_id(), clog_record);
  if (rc != RC::SUCCESS || clog_record == nullptr) {
    session_event->set_response("FAILURE\n");
    return rc;
  }

  rc = clog_manager->clog_append_record(clog_record);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  return rc;
}

RC ExecuteStage::do_commit(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  session->set_trx_multi_operation_mode(false);

  CLogRecord *clog_record = nullptr;
  rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
  if (rc != RC::SUCCESS || clog_record == nullptr) {
    session_event->set_response("FAILURE\n");
    return rc;
  }

  rc = clog_manager->clog_append_record(clog_record);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  trx->next_current_id();

  return rc;
}

RC ExecuteStage::do_clog_sync(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  CLogManager *clog_manager = db->get_clog_manager();

  rc = clog_manager->clog_sync();
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  return rc;
}
