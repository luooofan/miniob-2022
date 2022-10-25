/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
#define YY_YY_YACC_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
#define YYTOKENTYPE
enum yytokentype {
  SEMICOLON = 258,
  CREATE = 259,
  DROP = 260,
  TABLE = 261,
  TABLES = 262,
  INDEX = 263,
  INNER = 264,
  JOIN = 265,
  SELECT = 266,
  DESC = 267,
  ASC = 268,
  SHOW = 269,
  SYNC = 270,
  INSERT = 271,
  DELETE = 272,
  UPDATE = 273,
  LBRACE = 274,
  RBRACE = 275,
  COMMA = 276,
  TRX_BEGIN = 277,
  TRX_COMMIT = 278,
  TRX_ROLLBACK = 279,
  INT_T = 280,
  STRING_T = 281,
  DATE_T = 282,
  FLOAT_T = 283,
  ORDER = 284,
  GROUP = 285,
  BY = 286,
  IN = 287,
  EXISTS = 288,
  HAVING = 289,
  AGGR_MAX = 290,
  AGGR_MIN = 291,
  AGGR_SUM = 292,
  AGGR_AVG = 293,
  AGGR_COUNT = 294,
  HELP = 295,
  EXIT = 296,
  DOT = 297,
  INTO = 298,
  VALUES = 299,
  FROM = 300,
  WHERE = 301,
  AND = 302,
  SET = 303,
  ON = 304,
  LOAD = 305,
  DATA = 306,
  INFILE = 307,
  NOT = 308,
  LIKE = 309,
  UNIQUE = 310,
  ADD = 311,
  SUB = 312,
  MUL = 313,
  DIV = 314,
  IS = 315,
  NULL_VALUE = 316,
  NULLABLE = 317,
  EQ = 318,
  LT = 319,
  GT = 320,
  LE = 321,
  GE = 322,
  NE = 323,
  LENGTH = 324,
  ROUND = 325,
  DATE_FORMAT = 326,
  NUMBER = 327,
  FLOAT = 328,
  ID = 329,
  PATH = 330,
  SSS = 331,
  STAR = 332,
  STRING_V = 333,
  DATE_STR = 334
};
#endif

/* Value type.  */
#if !defined YYSTYPE && !defined YYSTYPE_IS_DECLARED
union YYSTYPE {
#line 168 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  struct _UnaryExpr *uexp1;
  struct _Expr *exp1;
  struct _Expr *exp2;
  struct _Expr *exp3;
  struct _Expr *exp4;
  struct _Expr *exp5;
  struct _Expr *exp6;
  struct _FromInfo *from_info;
  char *string;
  int number;
  float floats;
  char *position;
  int cur_len;
  int comp_op;

#line 157 "yacc_sql.tab.h"
};
typedef union YYSTYPE YYSTYPE;
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1
#endif

int yyparse(void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
