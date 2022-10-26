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
<<<<<<< HEAD
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
  TEXT = 296,
=======
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
>>>>>>> alias finish v1
  EXIT = 297,
  DOT = 298,
  INTO = 299,
  VALUES = 300,
  FROM = 301,
  WHERE = 302,
  AND = 303,
  SET = 304,
  ON = 305,
  LOAD = 306,
  DATA = 307,
  INFILE = 308,
  NOT = 309,
  LIKE = 310,
  UNIQUE = 311,
  ADD = 312,
  SUB = 313,
  MUL = 314,
  DIV = 315,
  IS = 316,
  NULL_VALUE = 317,
  NULLABLE = 318,
  EQ = 319,
  LT = 320,
  GT = 321,
  LE = 322,
  GE = 323,
  NE = 324,
  LENGTH = 325,
  ROUND = 326,
  DATE_FORMAT = 327,
  NUMBER = 328,
  FLOAT = 329,
  ID = 330,
  PATH = 331,
  SSS = 332,
  STAR = 333,
  STRING_V = 334,
  DATE_STR = 335
};
#endif

/* Value type.  */
#if !defined YYSTYPE && !defined YYSTYPE_IS_DECLARED
union YYSTYPE {
#line 169 "yacc_sql.y"

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

#line 159 "yacc_sql.tab.h"
};
typedef union YYSTYPE YYSTYPE;
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1
#endif

int yyparse(void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
