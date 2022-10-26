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
  AS = 269,
  SHOW = 270,
  SYNC = 271,
  INSERT = 272,
  DELETE = 273,
  UPDATE = 274,
  LBRACE = 275,
  RBRACE = 276,
  COMMA = 277,
  TRX_BEGIN = 278,
  TRX_COMMIT = 279,
  TRX_ROLLBACK = 280,
  INT_T = 281,
  STRING_T = 282,
  DATE_T = 283,
  FLOAT_T = 284,
  ORDER = 285,
  GROUP = 286,
  BY = 287,
  IN = 288,
  EXISTS = 289,
  HAVING = 290,
  AGGR_MAX = 291,
  AGGR_MIN = 292,
  AGGR_SUM = 293,
  AGGR_AVG = 294,
  AGGR_COUNT = 295,
  HELP = 296,
  TEXT = 297,
  EXIT = 298,
  DOT = 299,
  INTO = 300,
  VALUES = 301,
  FROM = 302,
  WHERE = 303,
  AND = 304,
  SET = 305,
  ON = 306,
  LOAD = 307,
  DATA = 308,
  INFILE = 309,
  NOT = 310,
  LIKE = 311,
  UNIQUE = 312,
  ADD = 313,
  SUB = 314,
  MUL = 315,
  DIV = 316,
  IS = 317,
  NULL_VALUE = 318,
  NULLABLE = 319,
  EQ = 320,
  LT = 321,
  GT = 322,
  LE = 323,
  GE = 324,
  NE = 325,
  LENGTH = 326,
  ROUND = 327,
  DATE_FORMAT = 328,
  NUMBER = 329,
  FLOAT = 330,
  ID = 331,
  PATH = 332,
  SSS = 333,
  STAR = 334,
  STRING_V = 335,
  DATE_STR = 336
};
#endif

/* Value type.  */
#if !defined YYSTYPE && !defined YYSTYPE_IS_DECLARED
union YYSTYPE {
#line 170 "yacc_sql.y"

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
  struct _Expr *exp7;
  struct _FromInfo *from_info;
  char *string;
  int number;
  float floats;
  char *position;
  int cur_len;
  int comp_op;

#line 160 "yacc_sql.tab.h"
};
typedef union YYSTYPE YYSTYPE;
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1
#endif

int yyparse(void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
