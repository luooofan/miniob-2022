
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

typedef struct ParserContext {
  Query * ssql;
  size_t value_length;
  Value values[MAX_NUM];
  size_t condition_length;
  Condition conditions[MAX_NUM];
  size_t having_length;
  Condition havings[MAX_NUM];
  size_t orderby_length;
  OrderBy orderbys[MAX_NUM];
  size_t groupby_length;
  GroupBy groupbys[MAX_NUM];
  size_t from_length;
  Relation froms[MAX_NUM];
  size_t project_length;
  ProjectCol projects[MAX_NUM];
  CompOp comp;
	char id[MAX_NUM];
  AggrFuncType aggrfunctype;
} ParserContext;

typedef struct _FromInfo {
  int from_len;
  int inner_join_conditions_len;
} FromInfo;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

//从字符串指定位置开始，查找指定字符第一次出现的位置
int find(const char *s, int b, const char *t)
{
  int i;
  for (i = b; i < strlen(s); i++) {
		if (s[i] == *t)	return i;
  }
  return -1;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->orderby_length = 0;
  context->from_length = 0;
  context->value_length = 0;
  context->having_length = 0;
  context->groupby_length = 0;
  context->project_length = 0;
  context->ssql->sstr.insertion.value_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        INNER
        JOIN
        SELECT
        DESC
        ASC
        AS
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
				DATE_T
        FLOAT_T
        ORDER
        GROUP
        BY
        IN
        EXISTS
        HAVING
        AGGR_MAX
        AGGR_MIN
        AGGR_SUM
        AGGR_AVG
        AGGR_COUNT
        HELP
        TEXT
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        OR
        SET
        ON
        LOAD
        DATA
        INFILE
        NOT
        LIKE
				UNIQUE
        ADD
        SUB
        MUL
        DIV
        IS
        NULL_VALUE
        NULLABLE
        EQ
        LT
        GT
        LE
        GE
        NE
        LENGTH
        ROUND
        DATE_FORMAT

%union {
  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  struct _UnaryExpr* uexp1;
  struct _Expr* exp1;
  struct _Expr* exp2;
  struct _Expr* exp3;
  struct _Expr* exp4;
  struct _Expr* exp5;
  struct _Expr* exp6;
  struct _Expr* exp7;
  struct _Expr* exp8;
  struct _FromInfo* from_info;
  char *string;
  int number;
  float floats;
	char *position;
  int cur_len;
  int comp_op;
}

%token <number> NUMBER
%token <floats> FLOAT 
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> STAR
%token <string> STRING_V
%token <string> DATE_STR
//非终结符

%type <number> type;
%type <value1> value;
%type <number> number;
%type <exp1> unary_expr;
%type <exp2> mul_expr;
%type <exp3> add_expr;
%type <exp4> func_expr;
%type <exp5> aggr_func_expr;
%type <exp6> sub_select;
%type <exp7> sub_select_list;
%type <cur_len> select_attr;
%type <cur_len> attr_list;
%type <from_info> from;
%type <from_info> rel_list;
%type <cur_len> inner_join_conditions;
%type <cur_len> where;
%type <cur_len> condition_list;
%type <cur_len> opt_group_by;
%type <cur_len> groupby_list;
%type <cur_len> opt_having;
%type <cur_len> having_condition_list;
%type <cur_len> opt_order_by;
%type <cur_len> sort_list;
%type <cur_len> value_list;
%type <comp_op> comOp;
%type <exp8> select_where;
%type <exp8> condition_and;
%type <exp8> condition_or;

%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  select  
	| insert
	| update
	| delete
	| create_table
	| drop_table
	| show_tables
	| desc_table
	| show_index
	| create_index	
	| drop_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
    ;

exit:			
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

show_index:
		SHOW INDEX FROM ID SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			desc_table_init(&CONTEXT->ssql->sstr.desc_table, $4);
		}
		;

create_index:		/*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE id id_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;			//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, false, $3, $5);
		}
		|CREATE UNIQUE INDEX ID ON ID LBRACE id id_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;			//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, true, $4, $6);
		}
    ;

id_list:
		/* EMPTY */
		|COMMA id id_list 
		{
			/* Do Nothing */
		}
		;
id:
	ID 
	{
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, $1);
	}
	;

drop_index:			/*drop index 语句的语法解析树*/
    DROP INDEX ID  SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
		}
    ;
create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;
    
attr_def:
    ID_get type LBRACE number RBRACE 
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $4, FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
    | ID_get TEXT
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, CHARS, 4096, FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
    |ID_get type
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
    |ID_get type LBRACE number RBRACE NOT NULL_VALUE
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $4, FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
    |ID_get type LBRACE number RBRACE NULLABLE
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $4, TRUE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
    |ID_get type NOT NULL_VALUE
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
    |ID_get type NULLABLE
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, TRUE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
    ;
number:
		NUMBER {$$ = $1;}
		;
type:
	INT_T { $$=INTS; }
       | STRING_T { $$=CHARS; }
       | FLOAT_T { $$=FLOATS; }
			 | DATE_T { $$=DATES; }
       ;
ID_get:
	ID 
	{
		char *temp=$1; 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
	;

	
insert:				/*insert   语句的语法解析树*/
    INSERT INTO ID VALUES row_value row_value_list SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_INSERT;		//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, $3);
    }

row_value_list:
		/* EMPTY */
		| COMMA row_value row_value_list {
			// Do Nothing
		}
row_value:
		LBRACE value value_list RBRACE
		{
			if (0 != inserts_append_data(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length)) {
				return -1;
			}
			//临时变量清零
			memset(CONTEXT->values, 0, sizeof(CONTEXT->values));
      CONTEXT->value_length=0;
		}

sub_select_list:
    LBRACE value value_list RBRACE
    {
      Expr * expr = malloc(sizeof(Expr));
      ListExpr * lexp = malloc(sizeof(ListExpr));
      int v_length = $3 + 1;
      list_expr_init(lexp, &CONTEXT->values[CONTEXT->value_length - v_length], v_length);
      expr_init_list(expr, lexp);
      $$ = expr;
    }
    ;

value_list:
    /* empty */{
        $$ = 0;
    }
    | COMMA value value_list  { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
        $$ = $3 + 1;
	  }
    ;

mul_expr:
    unary_expr {
      $$ = $1;
    }
    | SUB unary_expr {
      Value * tmp_val = malloc(sizeof(Value));
      value_init_integer(tmp_val, -1);
      UnaryExpr * tmp_uexpr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(tmp_uexpr, tmp_val);
      Expr * tmp_expr = malloc(sizeof(Expr));
      expr_init_unary(tmp_expr, tmp_uexpr);

      Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, MUL_OP, tmp_expr, $2);
      binary_expr_set_minus(b_expr);
      expr_init_binary(expr, b_expr);
      $$ = expr;
    }
    | mul_expr STAR unary_expr {
      Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, MUL_OP, $1, $3);
      expr_init_binary(expr, b_expr);
      $$ = expr;
    }
    | mul_expr DIV unary_expr {
    	Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, DIV_OP, $1, $3);
      expr_init_binary(expr, b_expr);
      $$ = expr;
    }
    ;

add_expr:
    mul_expr { $$ = $1; }
    | add_expr ADD mul_expr {
    	Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, ADD_OP, $1, $3);
      expr_init_binary(expr, b_expr);
      $$ = expr;
    }
    | add_expr SUB mul_expr {
    	Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, SUB_OP, $1, $3);
      expr_init_binary(expr, b_expr);
      $$ = expr;
    }
    ;

condition:
    add_expr comOp add_expr{
      Condition expr;
      condition_init(&expr, $2, $1, $3);
      // condition_print(&expr, 0);
      CONTEXT->conditions[CONTEXT->condition_length++] = expr;
    }
    | add_expr IS NULL_VALUE {
      Value value;
      value_init_null(&value);

      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(u_expr, &value);

    	Expr *expr = malloc(sizeof(Expr));
      expr_init_unary(expr, u_expr);

      Condition cond;
      condition_init(&cond, IS_NULL, $1, expr);
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
    | add_expr IS NOT NULL_VALUE {
      Value value;
      value_init_null(&value);

      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(u_expr, &value);

    	Expr *expr = malloc(sizeof(Expr));
      expr_init_unary(expr, u_expr);

      Condition cond;
      condition_init(&cond, IS_NOT_NULL, $1, expr);
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
    | add_expr IN add_expr {
      // TODO
      Condition cond;
      condition_init(&cond, IN_OP, $1, $3);
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
    | add_expr NOT IN add_expr {
      // TODO
      Condition cond;
      condition_init(&cond, NOT_IN, $1, $4);
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
    | EXISTS add_expr {
      // TODO
      Value * tmp_val = malloc(sizeof(Value));
      value_init_integer(tmp_val, 1);
      UnaryExpr * tmp_uexpr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(tmp_uexpr, tmp_val);
      Expr * tmp_expr = malloc(sizeof(Expr));
      expr_init_unary(tmp_expr, tmp_uexpr);

      Condition cond;
      condition_init(&cond, EXISTS_OP, tmp_expr, $2);
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
    | NOT EXISTS add_expr {
      // TODO
      Value * tmp_val = malloc(sizeof(Value));
      value_init_integer(tmp_val, 1);
      UnaryExpr * tmp_uexpr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(tmp_uexpr, tmp_val);
      Expr * tmp_expr = malloc(sizeof(Expr));
      expr_init_unary(tmp_expr, tmp_uexpr);

      Condition cond;
      condition_init(&cond, NOT_EXISTS, tmp_expr, $3);
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
    ;

having_condition:
    add_expr comOp add_expr{
      Condition expr;
      condition_init(&expr, $2, $1, $3);
      CONTEXT->havings[CONTEXT->having_length++] = expr;
    }
    ;

unary_expr:
    value {
    	Expr *expr = malloc(sizeof(Expr));
      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(u_expr, &CONTEXT->values[CONTEXT->value_length-1]);
      expr_init_unary(expr, u_expr);
      $$ = expr;
    }
    | ID {
    	Expr *expr = malloc(sizeof(Expr));
      RelAttr attr;
      relation_attr_init(&attr, NULL, $1);
      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_attr(u_expr, &attr);
      expr_init_unary(expr, u_expr);
      $$ = expr;
    }
    | ID DOT ID {
    	Expr *expr = malloc(sizeof(Expr));
      RelAttr attr;
      relation_attr_init(&attr, $1, $3);
      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_attr(u_expr, &attr);
      expr_init_unary(expr, u_expr);
      $$ = expr;
    }
    | LBRACE add_expr RBRACE {
      expr_set_with_brace($2);
      $$ = $2;
    }
    | func_expr {
      $$ = $1;
    }
    | aggr_func_expr {
      $$ = $1;
    }
    | sub_select {
       $$ = $1;
    }
    | sub_select_list{
      $$ = $1;
    }
    ;
aggr_func_type:
    AGGR_MAX {
      CONTEXT->aggrfunctype = MAX;
    }
    | AGGR_MIN {
      CONTEXT->aggrfunctype = MIN;
    }
    | AGGR_SUM {
      CONTEXT->aggrfunctype = SUM;
    }
    | AGGR_AVG {
      CONTEXT->aggrfunctype = AVG;
    }
    | AGGR_COUNT {
      CONTEXT->aggrfunctype = COUNT;
    }
    ;

aggr_func_expr:
    aggr_func_type LBRACE add_expr RBRACE
    {
      AggrFuncExpr* afexpr = malloc(sizeof(AggrFuncExpr));
      aggr_func_expr_init(afexpr, CONTEXT->aggrfunctype, $3);
      Expr* expr = malloc(sizeof(Expr));
      expr_init_aggr_func(expr, afexpr);
      $$ = expr;
    }
    | aggr_func_type LBRACE STAR RBRACE
    {
      if (CONTEXT->aggrfunctype != COUNT) {
        return -1;
      }
      // regard as a string value
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], "*");

    	Expr *param = malloc(sizeof(Expr));
      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(u_expr, &CONTEXT->values[CONTEXT->value_length-1]);
      expr_init_unary(param, u_expr);

      AggrFuncExpr* afexpr = malloc(sizeof(AggrFuncExpr));
      aggr_func_expr_init(afexpr, COUNT, param);
      Expr* expr = malloc(sizeof(Expr));
      expr_init_aggr_func(expr, afexpr);
      $$ = expr;
    }
    ;

func_expr:
    LENGTH LBRACE add_expr RBRACE
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 0);
      func_expr_init_params(fexpr, $3, NULL);
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      $$ = expr;
    }
    |
    ROUND LBRACE add_expr RBRACE
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 1);
      func_expr_init_params(fexpr, $3, NULL);
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      $$ = expr;
    }
    |
    ROUND LBRACE add_expr COMMA add_expr RBRACE
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 1);
      func_expr_init_params(fexpr, $3, $5);
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      $$ = expr;
    }
    |
    DATE_FORMAT LBRACE add_expr COMMA add_expr RBRACE
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 2);
      func_expr_init_params(fexpr, $3, $5);
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      $$ = expr;
    }
    ;

sub_select:
    LBRACE SELECT select_attr FROM from select_where opt_group_by opt_having opt_order_by RBRACE {
      // printf("THE SUBQUERY has %d projects %d froms %d inner_join_conditions %d conditions %d groupbys %d havings %d orderbys\n", $3, $5->from_len, $5->inner_join_conditions_len, $6, $7, $8, $9);

      Selects * sub_select = (Selects *)malloc(sizeof(Selects));
      memset(sub_select, 0 ,sizeof(Selects));

			selects_append_projects(sub_select,  &CONTEXT->projects[CONTEXT->project_length - $3], $3);
    
      size_t from_len = $5->from_len;
      size_t inner_join_conditions_len = $5->inner_join_conditions_len;
			selects_append_froms(sub_select,  &CONTEXT->froms[CONTEXT->from_length - from_len], from_len);

      // fill inner join conditions
			selects_append_conditions(sub_select, &CONTEXT->conditions[CONTEXT->condition_length - inner_join_conditions_len], inner_join_conditions_len);

      // fill where conditions
      selects_set_where_condition(sub_select, $6);

			selects_append_groupbys(sub_select, &CONTEXT->groupbys[CONTEXT->groupby_length - $7], $7);

			selects_append_havings(sub_select, &CONTEXT->havings[CONTEXT->having_length - $8], $8);

			selects_append_orderbys(sub_select, &CONTEXT->orderbys[CONTEXT->orderby_length - $9], $9);

			//CONTEXT->ssql->flag=SCF_SELECT;//"select";

			CONTEXT->orderby_length -= $9;
      CONTEXT->having_length -= $8;
			CONTEXT->groupby_length -= $7;
			CONTEXT->condition_length -= inner_join_conditions_len;
      CONTEXT->from_length -= from_len;
      CONTEXT->project_length -= $3;
			CONTEXT->value_length = 0;

      SubQueryExpr * s_expr = malloc(sizeof(SubQueryExpr));
      sub_query_expr_init(s_expr, sub_select);
      Expr* expr = malloc(sizeof(Expr));
      expr_init_sub_query(expr, s_expr);
      $$ = expr;
    }
    ;

value:
    NUMBER{	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |SUB NUMBER{	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], -($2));
		}
    |FLOAT{
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |SUB FLOAT{
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], -($2));
		}
    |SSS {
			$1 = substr($1,1,strlen($1)-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
		|DATE_STR {
			int p1 = find($1,1,"-");
			int p2 = find($1,p1+1,"-");
			char *y = substr($1,1,p1-1);							// year
			char *m = substr($1,p1+1,p2-1);						// month
			char *d = substr($1,p2+1,strlen($1)-2);		// day
			if (0 != value_init_date(&CONTEXT->values[CONTEXT->value_length++], y, m, d)){
				return -1;
			}
		}
    |NULL_VALUE {
      value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    }
    ;
    
delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
    ;

update:			/*  update 语句的语法解析树*/
    UPDATE ID SET update_option update_options where SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_UPDATE;		//"update";
			updates_init(&CONTEXT->ssql->sstr.update, $2, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
update_options:
		/* EMPTY */
		|COMMA update_option update_options {
			// Do Nothing
		}
update_option:
		ID EQ value {
    	Expr *expr = malloc(sizeof(Expr));
      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(u_expr, &CONTEXT->values[0]);
      expr_init_unary(expr, u_expr);

			// Value *value = &CONTEXT->values[0];
			updates_append_attribute(&CONTEXT->ssql->sstr.update, $1, expr);
			//临时变量清零
			memset(CONTEXT->values, 0, sizeof(CONTEXT->values));
      CONTEXT->value_length=0;
		}
    | ID EQ sub_select {
			updates_append_attribute(&CONTEXT->ssql->sstr.update, $1, $3);
			//临时变量清零
			memset(CONTEXT->values, 0, sizeof(CONTEXT->values));
      CONTEXT->value_length=0;
    }
    ;

select:				/*  select 语句的语法解析树*/
    SELECT select_attr SEMICOLON {
			selects_append_projects(&CONTEXT->ssql->sstr.selection, CONTEXT->projects, CONTEXT->project_length);
			CONTEXT->ssql->flag=SCF_SELECT;//"select";
      CONTEXT->project_length=0;
    }
    | SELECT select_attr FROM from select_where opt_group_by opt_having opt_order_by SEMICOLON
		{
      // printf("THE QUERY has %d projects %d froms %d inner_join_conditions %d conditions %d groupbys %d havings %d orderbys\n\n", $2, $4->from_len, $4->inner_join_conditions_len, $5, $6, $7, $8);

			selects_append_projects(&CONTEXT->ssql->sstr.selection, CONTEXT->projects, CONTEXT->project_length);

			selects_append_froms(&CONTEXT->ssql->sstr.selection, CONTEXT->froms, CONTEXT->from_length);

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

      selects_set_where_condition(&CONTEXT->ssql->sstr.selection, $5);

			selects_append_orderbys(&CONTEXT->ssql->sstr.selection, CONTEXT->orderbys, CONTEXT->orderby_length);

			selects_append_groupbys(&CONTEXT->ssql->sstr.selection, CONTEXT->groupbys, CONTEXT->groupby_length);

			selects_append_havings(&CONTEXT->ssql->sstr.selection, CONTEXT->havings, CONTEXT->having_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";

			//临时变量清零
      CONTEXT->having_length=0;
			CONTEXT->groupby_length=0;
			CONTEXT->orderby_length=0;
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
      CONTEXT->project_length=0;
			CONTEXT->value_length=0; // ???
	}
	;

select_attr:
    STAR attr_list {  
			ProjectCol project_col;
			projectcol_init_star(&project_col, NULL);
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      $$ = $2 + 1;
		}
    |
    ID DOT STAR attr_list{
      ProjectCol project_col;
			projectcol_init_star(&project_col, $1);
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      $$ = $4 + 1;
    }
    |
    add_expr attr_list{
      ProjectCol project_col;
      projectcol_init_expr(&project_col, $1);
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      $$ = $2 + 1;
    }
    |
    add_expr AS ID attr_list{
      ProjectCol project_col;
      projectcol_init_expr(&project_col, $1);
      expr_init_alias($1, $3);
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      $$ = $4 + 1;
    }
    |
    add_expr ID attr_list{
      ProjectCol project_col;
      projectcol_init_expr(&project_col, $1);
      expr_init_alias($1, $2);
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      $$ = $3 + 1;
    }
    ;
attr_list:
    /* empty */ {
      $$ = 0;
    }
    |
    COMMA STAR attr_list {  
			ProjectCol project_col;
			projectcol_init_star(&project_col, NULL);
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      $$ = $3 + 1;
		}
    |
    COMMA ID DOT STAR attr_list{
      ProjectCol project_col;
			projectcol_init_star(&project_col, $2);
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      $$ = $5 + 1;
    }
    |
    COMMA add_expr attr_list{
      ProjectCol project_col;
      projectcol_init_expr(&project_col, $2);
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      $$ = $3 + 1;
    }
    |
    COMMA add_expr AS ID attr_list{
      ProjectCol project_col;
      projectcol_init_expr(&project_col, $2);
      expr_init_alias($2, $4);
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      $$ = $5 + 1;
    }
    |
    COMMA add_expr ID attr_list{
      ProjectCol project_col;
      projectcol_init_expr(&project_col, $2);
      expr_init_alias($2, $3);
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      $$ = $4 + 1;
    }
  	;

from:
    ID rel_list {
      Relation rel;
      relation_from_init(&rel, $1, NULL);
			CONTEXT->froms[CONTEXT->from_length++]=rel;
      $$ = $2;
      $$->from_len++;
    }
    |ID ID rel_list {
      Relation rel;
      relation_from_init(&rel, $1, $2);
			CONTEXT->froms[CONTEXT->from_length++]=rel;
      $$ = $3;
      $$->from_len++;
    }
    |ID AS ID rel_list {
      Relation rel;
      relation_from_init(&rel, $1, $3);
			CONTEXT->froms[CONTEXT->from_length++]=rel;
      $$ = $4;
      $$->from_len++;
    }
    ;

rel_list:
    /* empty */ {
      // new FromInfo
      $$ = (FromInfo*)malloc(sizeof(FromInfo));
      $$->from_len = 0;
      $$->inner_join_conditions_len = 0;
    }
    | COMMA ID rel_list {	
        Relation rel;
        relation_from_init(&rel, $2, NULL);
        CONTEXT->froms[CONTEXT->from_length++]=rel;
        $$ = $3;
        $$->from_len++;
		  }
    | COMMA ID ID rel_list{
      Relation rel;
      relation_from_init(&rel, $2, $3);
			CONTEXT->froms[CONTEXT->from_length++]=rel;
      $$ = $4;
      $$->from_len++;
    }
    | COMMA ID AS ID rel_list{
      Relation rel;
      relation_from_init(&rel, $2, $4);
			CONTEXT->froms[CONTEXT->from_length++]=rel;
      $$ = $5;
      $$->from_len++;
    }
    | INNER JOIN ID inner_join_conditions rel_list{
      Relation rel;
      relation_from_init(&rel, $3, NULL);
        CONTEXT->froms[CONTEXT->from_length++]=rel;
        $$ = $5;
        $$->from_len++;
        $$->inner_join_conditions_len += $4;
    }
    ;
inner_join_conditions:
	/* empty */ {
    $$ = 0;
  }
	| ON condition condition_list{
    $$ = $3 + 1;
	}
	;
where:
    /* empty */ {
      $$ = 0;
    }
    | WHERE condition condition_list {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
        $$ = $3 + 1;
			}
    ;
select_where:
     /* empty */ {
      $$ = NULL;
     }
     | WHERE condition_or {
      $$ = $2;
     }
     ;

condition_or:
     condition_and {
      $$ = $1;
     }
     | condition_or OR condition_and {
      Condition * c_expr = malloc(sizeof(Condition));
      condition_init(c_expr, OR_OP, $1, $3);
      Expr * expr = malloc(sizeof(Expr));
      expr_init_condition(expr, c_expr);

      $$ = expr;
     }
     ;

condition_and:
     condition {
      Expr * expr = malloc(sizeof(Expr));
      Condition * c_expr = malloc(sizeof(Condition));
      *c_expr = CONTEXT->conditions[--CONTEXT->condition_length]; // make condition in where clause would not appear in CONTEXT->condtitions
      expr_init_condition(expr, c_expr);
      $$ = expr;
     }
     | condition_and AND condition {
      Condition * rc_expr = malloc(sizeof(Condition));
      *rc_expr = CONTEXT->conditions[--CONTEXT->condition_length]; // make condition in where clause would not appear in CONTEXT->condtitions
      Expr * right_expr = malloc(sizeof(Expr));
      expr_init_condition(right_expr, rc_expr);

      Condition * c_expr = malloc(sizeof(Condition));
      condition_init(c_expr, AND_OP, $1, right_expr);
      Expr * expr = malloc(sizeof(Expr));
      expr_init_condition(expr, c_expr);

      $$ = expr;
     }
     ;

condition_list:
    /* empty */ {
      $$ = 0;
    }
    | AND condition condition_list {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
        $$ = $3 + 1;
			}
    ;
opt_having:
    /* empty */  { 
      $$ = 0;
    }
    | HAVING having_condition having_condition_list {	
        $$ = $3 + 1;
    }
    ;
having_condition_list:
    /* empty */ {
      $$ = 0;
    }
    | AND having_condition having_condition_list {
        $$ = $3 + 1;
    }
    ;


comOp:
  	  EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE { $$ = LIKE_OP; }
    | NOT LIKE { $$ = NOT_LIKE_OP; }
    ;
sort_unit:
	ID
	{
		RelAttr attr;
		relation_attr_init(&attr, NULL, $1);
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
	|
	ID DOT ID
	{
		RelAttr attr;
		relation_attr_init(&attr, $1, $3);
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
	|
	ID DESC
	{
		RelAttr attr;
		relation_attr_init(&attr, NULL, $1);
		OrderBy orderby;
		orderby_init(&orderby, FALSE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
	|
	ID ASC
	{
		RelAttr attr;
		relation_attr_init(&attr, NULL, $1);
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
	|
	ID DOT ID DESC
	{
		RelAttr attr;
		relation_attr_init(&attr, $1, $3);
		OrderBy orderby;
		orderby_init(&orderby, FALSE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
	|
	ID DOT ID ASC
	{
		RelAttr attr;
		relation_attr_init(&attr, $1, $3);
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
	;
sort_list:
	sort_unit COMMA sort_list
		{
    $$ = $3 + 1;
	}
	| sort_unit
		{
    $$ = 1;
	}
	;
opt_order_by:
	/* empty */ {
   $$ = 0;
  }
	| ORDER BY sort_list
		{
      $$ = $3;
	}
	;

groupby_unit:
	ID
	{
		RelAttr attr;
		relation_attr_init(&attr, NULL, $1);
		CONTEXT->groupbys[CONTEXT->groupby_length++] = attr;
	}
	|
	ID DOT ID
	{
		RelAttr attr;
		relation_attr_init(&attr, $1, $3);
		CONTEXT->groupbys[CONTEXT->groupby_length++] = attr;
	}
  ;

groupby_list:
	groupby_unit COMMA groupby_list
		{
    $$ = $3 + 1;
	}
	| groupby_unit
		{
    $$ = 1;
	}
	;
opt_group_by:
	/* empty */ {
    $$ = 0;
  }
	| GROUP BY groupby_list
		{
    $$ = $3 + 1;
	}
	;

load_data:
		LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
		{
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
		}
		;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
