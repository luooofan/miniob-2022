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

#ifndef __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
#define __OBSERVER_SQL_PARSER_PARSE_DEFS_H__

#include <stddef.h>
#include <stdbool.h>

#define MAX_NUM 20
#define MAX_REL_NAME 20
#define MAX_ATTR_NAME 20
#define MAX_ERROR_MESSAGE 20
#define MAX_DATA 50

// 属性结构体
typedef struct {
  char *relation_name;   // relation name (may be NULL) 表名
  char *attribute_name;  // attribute name              属性名
} RelAttr;

typedef enum {
  EQUAL_TO,     //"="            0
  LESS_EQUAL,   //"<="           1
  NOT_EQUAL,    //"<>"           2
  LESS_THAN,    //"<"            3
  GREAT_EQUAL,  //">="           4
  GREAT_THAN,   //">"            5
  LIKE_OP,      //"like"         6
  NOT_LIKE_OP,  //"not like"     7
  IS_NULL,      //"is null"      8
  IS_NOT_NULL,  //"is not null"  9
  IN_OP,        // sub_query IN      10
  NOT_IN,       // sub_query NOT IN  11
  EXISTS_OP,    // sub_query EXISTS  12
  NOT_EXISTS,   // sub_query NOT EXISTS  13
  AND_OP,       // condition and condition 14
  OR_OP,        // condition or condition 15
  NO_OP
} CompOp;

typedef enum { ADD_OP, SUB_OP, MUL_OP, DIV_OP, EXP_OP_NUM } ExpOp;
typedef enum { MAX, MIN, SUM, AVG, COUNT, AGGR_FUNC_TYPE_NUM } AggrFuncType;
typedef enum { UNARY, BINARY, COND, FUNC, AGGRFUNC, SUBQUERY, SUBLIST, EXP_TYPE_NUM } ExpType;
typedef enum { FUNC_LENGTH, FUNC_ROUND, FUNC_DATE_FORMAT, FUNC_TYPE_NUM } FuncType;
typedef enum { SUB_IN, SUB_NOT_IN, SUB_EXISTS, SUB_NOT_EXISTS, SUB_NORMAL, SUB_TYPE_NUM } SubQueryType;

typedef enum { UNDEFINED, CHARS, INTS, DATES, NULLS, FLOATS } AttrType;

// 属性值
typedef struct _Value {
  AttrType type;  // type of value
  void *data;     // value
} Value;

typedef struct _UnaryExpr {
  int is_attr;  // TRUE if is an attribute
  Value value;
  RelAttr attr;
} UnaryExpr;

typedef struct _BinaryExpr BinaryExpr;
typedef struct _FuncExpr FuncExpr;
typedef struct _AggrFuncExpr AggrFuncExpr;
typedef struct _SubQueryExpr SubQueryExpr;
typedef struct _ListExpr ListExpr;
typedef struct _Condition Condition;

typedef struct _Expr {
  ExpType type;
  UnaryExpr *uexp;
  BinaryExpr *bexp;
  FuncExpr *fexp;
  AggrFuncExpr *afexp;
  SubQueryExpr *sexp;
  ListExpr *lexp;
  Condition *cexp;
  int with_brace;
  char *alias;
} Expr;

typedef struct _AggrFuncExpr {
  int is_star;
  AggrFuncType type;
  Expr *param;
} AggrFuncExpr;

typedef struct _FuncExpr {
  FuncType type;
  Expr *params[MAX_NUM];
  int param_size;
} FuncExpr;

typedef struct _BinaryExpr {
  ExpOp op;
  Expr *left;
  Expr *right;
  int minus;
} BinaryExpr;

typedef struct _Condition {
  CompOp comp;
  Expr *left;
  Expr *right;
} Condition;

typedef struct _ProjectCol {
  int is_star;  // 0 is not star, 1 is star
  char *relation_name;
  Expr *expr;
} ProjectCol;

typedef struct _OrderBy {
  RelAttr sort_attr;  // order by attribute
  int is_asc;         // sort type:asc or desc ,asc is true, desc is false
} OrderBy;

typedef RelAttr GroupBy;
typedef struct _Relation {
  char *relation_name;
  char *alias;
} Relation;

// struct of select
typedef struct {
  size_t attr_num;                // Length of attrs in Select clause
  RelAttr attributes[MAX_NUM];    // attrs in Select clause
  size_t relation_num;            // Length of relations in Fro clause
  Relation relations[MAX_NUM];    // relations in From clause
  size_t condition_num;           // Length of conditions in inner join on clause
  Condition conditions[MAX_NUM];  // conditions in inner join on clause
  int has_where;                  // whether has where clause or not
  Condition where_condition;      // conditions in Where clause
  size_t project_num;             // Length of select clauses
  ProjectCol projects[MAX_NUM];   // project_col in select clause
  size_t orderby_num;             // Length of orderby
  OrderBy orderbys[MAX_NUM];      // order by
  size_t groupby_num;             // Length of groupby
  GroupBy groupbys[MAX_NUM];      // group by
  size_t having_num;              // Length of conditions in Having clause
  Condition havings[MAX_NUM];     // conditions in Having clause
} Selects;

// struct of sub_select
typedef struct _SubQueryExpr {
  Selects *sub_select;
} SubQueryExpr;

// sub_select list
typedef struct _ListExpr {
  size_t list_length;
  Value list[MAX_NUM];
} ListExpr;

// struct of insert
typedef struct {
  const Value *values;
} Row;

typedef struct {
  char *name;     // Attribute name
  AttrType type;  // Type of attribute
  size_t length;  // Length of attribute
  char nullable;  // Nullable
} AttrInfo;

typedef struct {
  char *relation_name;             // Relation to insert into
  size_t row_num;                  // Row size
  size_t value_num;                // Length of values
  Value values[MAX_NUM][MAX_NUM];  // values to insert
} Inserts;

// struct of delete
typedef struct {
  char *relation_name;            // Relation to delete from
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Deletes;

// struct of update
typedef struct {
  char *relation_name;                // Relation to update
  size_t attribute_num;               // Attribute nums
  AttrInfo attribute_names[MAX_NUM];  // Attributes to update
  Value values[MAX_NUM];              // update values
  Expr exprs[MAX_NUM];                // update values
  size_t condition_num;               // Length of conditions in Where clause
  Condition conditions[MAX_NUM];      // conditions in Where clause
} Updates;

// struct of craete_table
typedef struct {
  char *relation_name;           // Relation name
  size_t attribute_count;        // Length of attribute
  AttrInfo attributes[MAX_NUM];  // attributes
} CreateTable;

// struct of drop_table
typedef struct {
  char *relation_name;  // Relation name
} DropTable;

// struct of create_index
typedef struct {
  bool unique;                       // wether unique index
  char *index_name;                  // Index name
  char *relation_name;               // Relation name
  int attribute_count;               // Attribute count
  AttrInfo attribute_name[MAX_NUM];  // Attribute name
} CreateIndex;

// struct of  drop_index
typedef struct {
  const char *index_name;  // Index name
} DropIndex;

typedef struct {
  const char *relation_name;
} DescTable;

typedef struct {
  const char *relation_name;
  const char *file_name;
} LoadData;

union Queries {
  Selects selection;
  Inserts insertion;
  Deletes deletion;
  Updates update;
  CreateTable create_table;
  DropTable drop_table;
  CreateIndex create_index;
  DropIndex drop_index;
  DescTable desc_table;
  LoadData load_data;
  char *errors;
};

// 修改yacc中相关数字编码为宏定义
enum SqlCommandFlag {
  SCF_ERROR = 0,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_DROP_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_SHOW_INDEX,
  SCF_BEGIN,
  SCF_COMMIT,
  SCF_CLOG_SYNC,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT
};
// struct of flag and sql_struct
typedef struct Query {
  enum SqlCommandFlag flag;
  union Queries sstr;
} Query;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

void attr_print(RelAttr *attr, int indent);
void value_print(Value *value, int indent);

void list_expr_init(ListExpr *expr, Value values[], size_t value_num);
void list_expr_destory(ListExpr *expr);

void sub_query_expr_init(SubQueryExpr *expr, Selects *sub_select);
void sub_query_expr_destory(SubQueryExpr *expr);

void aggr_func_expr_init(AggrFuncExpr *func_expr, AggrFuncType type, Expr *param);
void aggr_func_expr_init_star(AggrFuncExpr *func_expr, AggrFuncType type);
void aggr_func_expr_destory(AggrFuncExpr *expr);

void func_expr_init_type(FuncExpr *func_expr, FuncType type);
void func_expr_init_params(FuncExpr *func_expr, Expr *expr1, Expr *expr2);
void func_expr_destory(FuncExpr *expr);

void unary_expr_print(UnaryExpr *expr, int indent);
void unary_expr_init_attr(UnaryExpr *expr, RelAttr *relation_attr);
void unary_expr_init_value(UnaryExpr *expr, Value *value);
void unary_expr_destroy(UnaryExpr *expr);

void binary_expr_print(BinaryExpr *expr, int indent);
void binary_expr_init(BinaryExpr *expr, ExpOp op, Expr *left_expr, Expr *right_expr);
void binary_expr_set_minus(BinaryExpr *expr);
void binary_expr_destroy(BinaryExpr *expr);

void expr_print(Expr *expr, int indent);
void expr_init_alias(Expr *expr, const char *alias_name);
void expr_init_list(Expr *expr, ListExpr *l_expr);
void expr_init_sub_query(Expr *expr, SubQueryExpr *s_expr);
void expr_init_aggr_func(Expr *expr, AggrFuncExpr *f_expr);
void expr_init_func(Expr *expr, FuncExpr *f_expr);
void expr_init_unary(Expr *expr, UnaryExpr *u_expr);
void expr_init_binary(Expr *expr, BinaryExpr *b_expr);
void expr_init_condition(Expr *expr, Condition *c_expr);
void expr_set_with_brace(Expr *expr);
void expr_destroy(Expr *expr);

void condition_print(Condition *condition, int indent);
void condition_init(Condition *condition, CompOp op, Expr *left_expr, Expr *right_expr);
void condition_destroy(Condition *condition);

void projectcol_init_star(ProjectCol *projectcol, const char *relation_name);
void projectcol_init_expr(ProjectCol *projectcol, Expr *expr);
void projectcol_destroy(ProjectCol *projectcol);

void relation_from_init(Relation *relation, const char *relation_name, const char *alias_name);
void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name);
void relation_attr_destroy(RelAttr *relation_attr);

void value_init_null(Value *value);
void value_init_integer(Value *value, int v);
void value_init_float(Value *value, float v);
void value_init_string(Value *value, const char *v);
int value_init_date(Value *value, const char *year, const char *month, const char *day);
void value_destroy(Value *value);

void orderby_init(OrderBy *orderby, int is_asc, RelAttr *attr);
void orderby_destroy(OrderBy *orderby);

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length, char nullable);
void attr_info_destroy(AttrInfo *attr_info);

void selects_init(Selects *selects, ...);
void selects_append_project(Selects *selects, ProjectCol *project_col);
void selects_append_projects(Selects *selects, ProjectCol project_col[], size_t project_num);
void selects_append_attribute(Selects *selects, RelAttr *rel_attr);
void selects_append_froms(Selects *selects, Relation froms[], size_t from_num);
void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num);
void selects_append_orderbys(Selects *selects, OrderBy orderbys[], size_t orderby_num);
void selects_append_groupbys(Selects *selects, GroupBy groupbys[], size_t groupby_num);
void selects_append_havings(Selects *selects, Condition conditions[], size_t condition_num);
void selects_set_where_condition(Selects *selects, Expr *expr);
void selects_destroy(Selects *selects);

// void inserts_init(Inserts *inserts, const char *relation_name, Value values[], size_t value_num);
void inserts_init(Inserts *inserts, const char *relation_name);
int inserts_append_data(Inserts *inserts, Value values[], size_t value_num);
void inserts_destroy(Inserts *inserts);

void deletes_init_relation(Deletes *deletes, const char *relation_name);
void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num);
void deletes_destroy(Deletes *deletes);

void updates_init(Updates *updates, const char *relation_name, Condition conditions[], size_t condition_num);
void updates_append_attribute(Updates *updates, const char *attribute_name, Expr *expr);
void updates_destroy(Updates *updates);

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info);
void create_table_init_name(CreateTable *create_table, const char *relation_name);
void create_table_destroy(CreateTable *create_table);

void drop_table_init(DropTable *drop_table, const char *relation_name);
void drop_table_destroy(DropTable *drop_table);

void create_index_init(CreateIndex *create_index, bool unique, const char *index_name, const char *relation_name);
void create_index_append_attribute(CreateIndex *create_index, const char *attr_name);
void create_index_destroy(CreateIndex *create_index);

void drop_index_init(DropIndex *drop_index, const char *index_name);
void drop_index_destroy(DropIndex *drop_index);

void desc_table_init(DescTable *desc_table, const char *relation_name);
void desc_table_destroy(DescTable *desc_table);

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name);
void load_data_destroy(LoadData *load_data);

void query_init(Query *query);
Query *query_create();  // create and init
void query_reset(Query *query);
void query_destroy(Query *query);  // reset and delete

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
