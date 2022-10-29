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
// Created by Meiyi
//

#include "sql/parser/parse.h"
#include "net/connection_context.h"
#include "rc.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"

RC parse(char *st, Query *sqln);

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

void attr_print(RelAttr *attr, int indent)
{
  for (int i = 0; i < indent; i++) {
    printf("\t");
  }
  if (NULL != attr->relation_name) {
    printf("%s ", attr->relation_name);
  }
  printf("%s\n", attr->attribute_name);
}

void value_print(Value *value, int indent)
{
  for (int i = 0; i < indent; i++) {
    printf("\t");
  }
  switch (value->type) {
    case INTS:
      printf("%d ", *(int *)(value->data));
      break;
    case FLOATS:
      printf("%f ", *(float *)(value->data));
      break;
    case CHARS:
      printf("%s ", (char *)value->data);
      break;
    default:
      break;
  }
  printf("\n");
}

void relation_from_destory(Relation *relation)
{
  if (relation->alias != NULL) {
    free(relation->alias);
  }
  free(relation->relation_name);
}

void relation_from_init(Relation *relation, const char *relation_name, const char *alias_name)
{
  relation->relation_name = strdup(relation_name);
  if (alias_name != NULL) {
    relation->alias = strdup(alias_name);
  } else {
    relation->alias = NULL;
  }
}

void unary_expr_print(UnaryExpr *expr, int indent)
{
  if (expr->is_attr) {
    attr_print(&(expr->attr), indent);
  } else {
    value_print(&(expr->value), indent);
  }
}

void projectcol_init_star(ProjectCol *projectcol, const char *relation_name)
{
  projectcol->is_star = 1;
  if (relation_name != nullptr) {
    projectcol->relation_name = strdup(relation_name);
  } else {
    projectcol->relation_name = nullptr;
  }
}

void projectcol_init_expr(ProjectCol *projectcol, Expr *expr)
{
  projectcol->is_star = 0;
  projectcol->relation_name = nullptr;
  projectcol->expr = expr;
}

void projectcol_destroy(ProjectCol *projectcol)
{
  if (nullptr != projectcol->relation_name)
    free(projectcol->relation_name);
  projectcol->relation_name = nullptr;
}

void aggr_func_expr_init(AggrFuncExpr *func_expr, AggrFuncType type, Expr *param)
{
  func_expr->is_star = 0;
  func_expr->type = type;
  func_expr->param = param;
}
void aggr_func_expr_init_star(AggrFuncExpr *func_expr, AggrFuncType type)
{
  func_expr->is_star = 1;
  func_expr->type = type;
  func_expr->param = NULL;
}
void aggr_func_expr_destory(AggrFuncExpr *expr)
{
  expr_destroy(expr->param);
  expr->param = NULL;
}

void func_expr_init_type(FuncExpr *func_expr, FuncType type)
{
  func_expr->type = type;
  func_expr->param_size = 0;
}

void func_expr_init_params(FuncExpr *func_expr, Expr *expr1, Expr *expr2)
{
  if (expr1 != nullptr) {
    func_expr->params[func_expr->param_size++] = expr1;
  }
  if (expr2 != nullptr) {
    func_expr->params[func_expr->param_size++] = expr2;
  }
}

void func_expr_destory(FuncExpr *expr)
{
  expr_destroy(expr->params[0]);
  if (expr->param_size == 2) {
    expr_destroy(expr->params[1]);
  }
  expr->param_size = 0;
}

void unary_expr_init_value(UnaryExpr *expr, Value *value)
{
  expr->is_attr = 0;
  expr->value = *value;
}
void unary_expr_init_attr(UnaryExpr *expr, RelAttr *relation_attr)
{
  expr->is_attr = 1;
  expr->attr = *relation_attr;
}
void unary_expr_destroy(UnaryExpr *expr)
{
  return;
}

void binary_expr_print(BinaryExpr *expr, int indent)
{
  for (int i = 0; i < indent; i++) {
    printf("\t");
  }
  printf("%d\n", expr->op);
  expr_print(expr->left, indent + 1);
  expr_print(expr->right, indent + 1);
}
void binary_expr_init(BinaryExpr *expr, ExpOp op, Expr *left_expr, Expr *right_expr)
{
  expr->left = left_expr;
  expr->right = right_expr;
  expr->op = op;
  expr->minus = 0;
}
void binary_expr_set_minus(BinaryExpr *expr)
{
  expr->minus = 1;
}
void binary_expr_destroy(BinaryExpr *expr)
{
  expr_destroy(expr->left);
  expr_destroy(expr->right);
}

void condition_print(Condition *condition, int indent)
{
  for (int i = 0; i < indent; i++) {
    printf("\t");
  }
  printf("%d\n", condition->comp);
  expr_print(condition->left, indent + 1);
  expr_print(condition->right, indent + 1);
}
void condition_init(Condition *condition, CompOp op, Expr *left_expr, Expr *right_expr)
{
  condition->left = left_expr;
  condition->right = right_expr;
  condition->comp = op;
}
void condition_destroy(Condition *condition)
{
  if (NULL != condition->left) {
    expr_destroy(condition->left);
  }
  if (NULL != condition->right) {
    expr_destroy(condition->right);
  }
}

void list_expr_init(ListExpr *expr, Value values[], size_t value_num)
{
  for (size_t i = 0; i < value_num; i++) {
    expr->list[i] = values[i];
  }
  expr->list_length = value_num;
}

void list_expr_destory(ListExpr *expr)
{
  for (size_t i = 0; i < expr->list_length; i++) {
    value_destroy(&expr->list[i]);
  }
  expr->list_length = 0;
}

void sub_query_expr_init(SubQueryExpr *s_expr, Selects *sub_select)
{
  s_expr->sub_select = sub_select;
}

void sub_query_expr_destory(SubQueryExpr *s_expr)
{
  selects_destroy(s_expr->sub_select);
}

void expr_print(Expr *expr, int indent)
{
  switch (expr->type) {
    case ExpType::UNARY:
      unary_expr_print(expr->uexp, indent);
      break;
    case ExpType::BINARY:
      binary_expr_print(expr->bexp, indent);
      break;
    default:
      break;
  }
}

void expr_init_alias(Expr *expr, const char *alias_name)
{
  if (alias_name != nullptr) {
    expr->alias = strdup(alias_name);
  }
}

void expr_init(Expr *expr)
{
  expr->type = ExpType::EXP_TYPE_NUM;
  expr->lexp = NULL;
  expr->sexp = NULL;
  expr->afexp = NULL;
  expr->fexp = NULL;
  expr->bexp = NULL;
  expr->uexp = NULL;
  expr->alias = NULL;
  expr->cexp = NULL;
  expr->with_brace = 0;
}

void expr_init_condition(Expr *expr, Condition *c_expr)
{
  expr_init(expr);
  expr->type = ExpType::COND;
  expr->cexp = c_expr;
}
void expr_init_list(Expr *expr, ListExpr *l_expr)
{
  expr_init(expr);
  expr->type = ExpType::SUBLIST;
  expr->lexp = l_expr;
}
void expr_init_sub_query(Expr *expr, SubQueryExpr *s_expr)
{
  expr_init(expr);
  expr->type = ExpType::SUBQUERY;
  expr->sexp = s_expr;
}
void expr_init_aggr_func(Expr *expr, AggrFuncExpr *f_expr)
{
  expr_init(expr);
  expr->type = ExpType::AGGRFUNC;
  expr->afexp = f_expr;
}
void expr_init_func(Expr *expr, FuncExpr *f_expr)
{
  expr_init(expr);
  expr->type = ExpType::FUNC;
  expr->fexp = f_expr;
}
void expr_init_unary(Expr *expr, UnaryExpr *u_expr)
{
  expr_init(expr);
  expr->type = ExpType::UNARY;
  expr->uexp = u_expr;
}
void expr_init_binary(Expr *expr, BinaryExpr *b_expr)
{
  expr_init(expr);
  expr->type = ExpType::BINARY;
  expr->bexp = b_expr;
}
void expr_set_with_brace(Expr *expr)
{
  expr->with_brace = 1;
}
void expr_destroy(Expr *expr)
{
  switch (expr->type) {
    case ExpType::UNARY:
      unary_expr_destroy(expr->uexp);
      expr->uexp = NULL;
      break;
    case ExpType::BINARY:
      binary_expr_destroy(expr->bexp);
      expr->bexp = NULL;
      break;
    case ExpType::COND:
      condition_destroy(expr->cexp);
      break;
    case ExpType::FUNC:
      func_expr_destory(expr->fexp);
      expr->fexp = NULL;
      break;
    case ExpType::AGGRFUNC:
      aggr_func_expr_destory(expr->afexp);
      expr->afexp = NULL;
      break;
    case ExpType::SUBQUERY:
      sub_query_expr_destory(expr->sexp);
      break;
    case ExpType::SUBLIST:
      list_expr_destory(expr->lexp);
    default:
      break;
  }
  if (expr->alias != NULL) {
    free(expr->alias);
  }
  expr->with_brace = 0;
}

void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name)
{
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  relation_attr->attribute_name = strdup(attribute_name);
}

void relation_attr_destroy(RelAttr *relation_attr)
{
  free(relation_attr->relation_name);
  free(relation_attr->attribute_name);
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
}

void value_init_null(Value *value)
{
  value->type = NULLS;
  value->data = nullptr;
}

void value_init_integer(Value *value, int v)
{
  value->type = INTS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_float(Value *value, float v)
{
  value->type = FLOATS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_string(Value *value, const char *v)
{
  value->type = CHARS;
  value->data = strdup(v);
}
int check_date(int year, int month, int day)
{
  static int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  bool leap = (year % 400 == 0 || (year % 100 && year % 4 == 0));
  if (year > 0 && (month > 0) && (month <= 12) && (day > 0) && (day <= ((month == 2 && leap) ? 1 : 0) + mon[month]))
    return 0;
  else
    return -1;
}
int value_init_date(Value *value, const char *year, const char *month, const char *day)
{
  value->type = DATES;
  int y, m, d;
  sscanf(year, "%d", &y);  // not check return value eq 3, lex guarantee
  sscanf(month, "%d", &m);
  sscanf(day, "%d", &d);

  if (0 != check_date(y, m, d)) {
    LOG_WARN("Error date: %d-%d-%d", y, m, d);
    return -1;
  }

  int dv = y * 10000 + m * 100 + d;
  value->data = malloc(sizeof(dv));  // TODO:check malloc failure
  memcpy(value->data, &dv, sizeof(dv));
  return 0;
}
void value_destroy(Value *value)
{
  value->type = UNDEFINED;
  if (nullptr != value->data) {
    free(value->data);
    value->data = nullptr;
  }
}

void orderby_destroy(OrderBy *orderby)
{
  relation_attr_destroy(&orderby->sort_attr);
}

void orderby_init(OrderBy *orderby, int is_asc, RelAttr *attr)
{
  orderby->sort_attr = *attr;
  orderby->is_asc = is_asc;
}

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length, char nullable)
{
  attr_info->name = strdup(name);
  attr_info->type = type;
  attr_info->length = length;
  attr_info->nullable = nullable;
}
void attr_info_destroy(AttrInfo *attr_info)
{
  free(attr_info->name);
  attr_info->name = nullptr;
}

void selects_init(Selects *selects, ...);

void selects_append_project(Selects *selects, ProjectCol *project_col)
{
  selects->projects[selects->project_num++] = *project_col;
}

void selects_append_projects(Selects *selects, ProjectCol project_col[], size_t project_num)
{
  assert(project_num <= sizeof(selects->projects) / sizeof(selects->projects[0]));
  for (size_t i = 0; i < project_num; i++) {
    selects->projects[i] = project_col[i];
  }
  selects->project_num = project_num;
}
void selects_append_attribute(Selects *selects, RelAttr *rel_attr)
{
  selects->attributes[selects->attr_num++] = *rel_attr;
}

void selects_append_froms(Selects *selects, Relation froms[], size_t from_num)
{
  assert(from_num <= sizeof(selects->relations) / sizeof(selects->relations[0]));
  for (size_t i = 0; i < from_num; i++) {
    selects->relations[i] = froms[i];
  }
  selects->relation_num = from_num;
}

void selects_set_where_condition(Selects *selects, Expr *expr)
{
  if (NULL != expr) {
    selects->has_where = 1;
    assert(COND == expr->type && NULL != expr->cexp);
    selects->where_condition = *expr->cexp;
  } else {
    selects->has_where = 0;
  }
}
void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num)
{
  assert(condition_num <= sizeof(selects->conditions) / sizeof(selects->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    selects->conditions[i] = conditions[i];
  }

  selects->condition_num = condition_num;
}

void selects_append_groupbys(Selects *selects, GroupBy groupbys[], size_t groupby_num)
{
  assert(groupby_num <= sizeof(selects->groupbys) / sizeof(selects->groupbys[0]));
  for (size_t i = 0; i < groupby_num; i++) {
    selects->groupbys[i] = groupbys[i];
  }
  selects->groupby_num = groupby_num;
}

void selects_append_havings(Selects *selects, Condition conditions[], size_t condition_num)
{
  assert(condition_num <= sizeof(selects->havings) / sizeof(selects->havings[0]));
  for (size_t i = 0; i < condition_num; i++) {
    selects->havings[i] = conditions[i];
  }

  selects->having_num = condition_num;
}

void selects_append_orderbys(Selects *selects, OrderBy orderbys[], size_t orderby_num)
{
  assert(orderby_num <= sizeof(selects->orderbys) / sizeof(selects->orderbys[0]));
  for (size_t i = 0; i < orderby_num; i++) {
    selects->orderbys[i] = orderbys[i];
  }
  selects->orderby_num = orderby_num;
}

void selects_destroy(Selects *selects)
{
  for (size_t i = 0; i < selects->attr_num; i++) {
    relation_attr_destroy(&selects->attributes[i]);
  }
  selects->attr_num = 0;

  for (size_t i = 0; i < selects->relation_num; i++) {
    relation_from_destory(&selects->relations[i]);
  }
  selects->relation_num = 0;

  for (size_t i = 0; i < selects->condition_num; i++) {
    condition_destroy(&selects->conditions[i]);
  }
  selects->condition_num = 0;

  if (selects->has_where) {
    condition_destroy(&selects->where_condition);
  }
  selects->has_where = 0;

  for (size_t i = 0; i < selects->project_num; i++) {
    projectcol_destroy(&selects->projects[i]);
  }
  selects->project_num = 0;

  for (size_t i = 0; i < selects->orderby_num; i++) {
    orderby_destroy(&selects->orderbys[i]);
  }
  selects->orderby_num = 0;

  for (size_t i = 0; i < selects->groupby_num; i++) {
    relation_attr_destroy(&selects->groupbys[i]);
  }
  selects->groupby_num = 0;

  for (size_t i = 0; i < selects->having_num; i++) {
    condition_destroy(&selects->havings[i]);
  }
  selects->having_num = 0;
}

void inserts_init(Inserts *inserts, const char *relation_name)
{
  inserts->relation_name = strdup(relation_name);
}

int inserts_append_data(Inserts *inserts, Value values[], size_t value_num)
{
  assert(value_num <= sizeof(inserts->values[0]) / sizeof(inserts->values[0][0]));
  if (inserts->value_num == 0) {
    inserts->value_num = value_num;
  } else if (inserts->value_num != value_num) {
    return -1;
  }

  for (size_t i = 0; i < value_num; i++) {
    inserts->values[inserts->row_num][i] = values[i];
  }
  inserts->row_num++;
  return 0;
}
void inserts_destroy(Inserts *inserts)
{
  free(inserts->relation_name);
  inserts->relation_name = nullptr;

  for (size_t i = 0; i < inserts->row_num; i++) {
    for (size_t j = 0; j < inserts->value_num; j++) {
      value_destroy(&inserts->values[i][j]);
    }
  }
  inserts->value_num = 0;
}

void deletes_init_relation(Deletes *deletes, const char *relation_name)
{
  deletes->relation_name = strdup(relation_name);
}

void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num)
{
  assert(condition_num <= sizeof(deletes->conditions) / sizeof(deletes->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    deletes->conditions[i] = conditions[i];
  }
  deletes->condition_num = condition_num;
}
void deletes_destroy(Deletes *deletes)
{
  for (size_t i = 0; i < deletes->condition_num; i++) {
    condition_destroy(&deletes->conditions[i]);
  }
  deletes->condition_num = 0;
  free(deletes->relation_name);
  deletes->relation_name = nullptr;
}

void updates_init(Updates *updates, const char *relation_name, Condition conditions[], size_t condition_num)
{
  updates->relation_name = strdup(relation_name);

  assert(condition_num <= sizeof(updates->conditions) / sizeof(updates->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    updates->conditions[i] = conditions[i];
  }
  updates->condition_num = condition_num;
}
void updates_append_attribute(Updates *updates, const char *attribute_name, Expr *expr)
{
  updates->attribute_names[updates->attribute_num].name = strdup(attribute_name);
  updates->exprs[updates->attribute_num] = *expr;
  updates->attribute_num++;
}
void updates_destroy(Updates *updates)
{
  free(updates->relation_name);
  updates->relation_name = nullptr;

  for (size_t i = 0; i < updates->attribute_num; i++) {
    attr_info_destroy(&updates->attribute_names[i]);
    value_destroy(&updates->values[i]);
  }
  for (size_t i = 0; i < updates->condition_num; i++) {
    condition_destroy(&updates->conditions[i]);
  }
  updates->condition_num = 0;
  updates->attribute_num = 0;
}

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info)
{
  create_table->attributes[create_table->attribute_count++] = *attr_info;
}

void create_table_init_name(CreateTable *create_table, const char *relation_name)
{
  create_table->relation_name = strdup(relation_name);
}

void create_table_destroy(CreateTable *create_table)
{
  for (size_t i = 0; i < create_table->attribute_count; i++) {
    attr_info_destroy(&create_table->attributes[i]);
  }
  create_table->attribute_count = 0;
  free(create_table->relation_name);
  create_table->relation_name = nullptr;
}

void drop_table_init(DropTable *drop_table, const char *relation_name)
{
  drop_table->relation_name = strdup(relation_name);
}

void drop_table_destroy(DropTable *drop_table)
{
  free(drop_table->relation_name);
  drop_table->relation_name = nullptr;
}

void create_index_init(CreateIndex *create_index, bool unique, const char *index_name, const char *relation_name)
{
  create_index->index_name = strdup(index_name);
  create_index->relation_name = strdup(relation_name);
  create_index->unique = unique;
}

void create_index_append_attribute(CreateIndex *create_index, const char *attr_name)
{
  int num = create_index->attribute_count;
  create_index->attribute_name[num].name = strdup(attr_name);
  create_index->attribute_count++;
}

void create_index_destroy(CreateIndex *create_index)
{
  free(create_index->index_name);
  free(create_index->relation_name);

  create_index->index_name = nullptr;
  create_index->relation_name = nullptr;
  for (int i = 0; i < create_index->attribute_count; i++) {
    attr_info_destroy(&create_index->attribute_name[i]);
  }
  create_index->attribute_count = 0;
  create_index->unique = false;
}

void drop_index_init(DropIndex *drop_index, const char *index_name)
{
  drop_index->index_name = strdup(index_name);
}

void drop_index_destroy(DropIndex *drop_index)
{
  free((char *)drop_index->index_name);
  drop_index->index_name = nullptr;
}

void desc_table_init(DescTable *desc_table, const char *relation_name)
{
  desc_table->relation_name = strdup(relation_name);
}

void desc_table_destroy(DescTable *desc_table)
{
  free((char *)desc_table->relation_name);
  desc_table->relation_name = nullptr;
}

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name)
{
  load_data->relation_name = strdup(relation_name);

  if (file_name[0] == '\'' || file_name[0] == '\"') {
    file_name++;
  }
  char *dup_file_name = strdup(file_name);
  int len = strlen(dup_file_name);
  if (dup_file_name[len - 1] == '\'' || dup_file_name[len - 1] == '\"') {
    dup_file_name[len - 1] = 0;
  }
  load_data->file_name = dup_file_name;
}

void load_data_destroy(LoadData *load_data)
{
  free((char *)load_data->relation_name);
  free((char *)load_data->file_name);
  load_data->relation_name = nullptr;
  load_data->file_name = nullptr;
}

void query_init(Query *query)
{
  query->flag = SCF_ERROR;
  memset(&query->sstr, 0, sizeof(query->sstr));
}

Query *query_create()
{
  Query *query = (Query *)malloc(sizeof(Query));
  if (nullptr == query) {
    LOG_ERROR("Failed to alloc memroy for query. size=%ld", sizeof(Query));
    return nullptr;
  }

  query_init(query);
  return query;
}

void query_reset(Query *query)
{
  switch (query->flag) {
    case SCF_SELECT: {
      selects_destroy(&query->sstr.selection);
    } break;
    case SCF_INSERT: {
      inserts_destroy(&query->sstr.insertion);
    } break;
    case SCF_DELETE: {
      deletes_destroy(&query->sstr.deletion);
    } break;
    case SCF_UPDATE: {
      updates_destroy(&query->sstr.update);
    } break;
    case SCF_CREATE_TABLE: {
      create_table_destroy(&query->sstr.create_table);
    } break;
    case SCF_DROP_TABLE: {
      drop_table_destroy(&query->sstr.drop_table);
    } break;
    case SCF_CREATE_INDEX: {
      create_index_destroy(&query->sstr.create_index);
    } break;
    case SCF_DROP_INDEX: {
      drop_index_destroy(&query->sstr.drop_index);
    } break;
    case SCF_SYNC: {

    } break;
    case SCF_SHOW_TABLES:
      break;
    case SCF_DESC_TABLE:
    case SCF_SHOW_INDEX: {
      desc_table_destroy(&query->sstr.desc_table);
    } break;

    case SCF_LOAD_DATA: {
      load_data_destroy(&query->sstr.load_data);
    } break;
    case SCF_CLOG_SYNC:
    case SCF_BEGIN:
    case SCF_COMMIT:
    case SCF_ROLLBACK:
    case SCF_HELP:
    case SCF_EXIT:
    case SCF_ERROR:
      break;
  }
}

void query_destroy(Query *query)
{
  query_reset(query);
  free(query);
}
#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////

extern "C" int sql_parse(const char *st, Query *sqls);

RC parse(const char *st, Query *sqln)
{
  sql_parse(st, sqln);

  if (sqln->flag == SCF_ERROR) {
    printf("sql parse error");
    return SQL_SYNTAX;
  }

  else
    return SUCCESS;
}
