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
  HAVING = 287,
  AGGR_MAX = 288,
  AGGR_MIN = 289,
  AGGR_SUM = 290,
  AGGR_AVG = 291,
  AGGR_COUNT = 292,
  HELP = 293,
  EXIT = 294,
  DOT = 295,
  INTO = 296,
  VALUES = 297,
  FROM = 298,
  WHERE = 299,
  AND = 300,
  SET = 301,
  ON = 302,
  LOAD = 303,
  DATA = 304,
  INFILE = 305,
  NOT = 306,
  LIKE = 307,
  UNIQUE = 308,
  ADD = 309,
  SUB = 310,
  MUL = 311,
  DIV = 312,
  EQ = 313,
  LT = 314,
  GT = 315,
  LE = 316,
  GE = 317,
  NE = 318,
  LENGTH = 319,
  ROUND = 320,
  DATE_FORMAT = 321,
  NUMBER = 322,
  FLOAT = 323,
  ID = 324,
  PATH = 325,
  SSS = 326,
  STAR = 327,
  STRING_V = 328,
  DATE_STR = 329
};
#endif

/* Value type.  */
#if !defined YYSTYPE && !defined YYSTYPE_IS_DECLARED
union YYSTYPE {
#line 154 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Condition *having1;
  struct _Value *value1;
  struct _UnaryExpr *uexp1;
  struct _Expr *exp1;
  struct _Expr *exp2;
  struct _Expr *exp3;
  struct _Expr *exp4;
  struct _Expr *exp5;
  char *string;
  int number;
  float floats;
  char *position;

#line 149 "yacc_sql.tab.h"
};
typedef union YYSTYPE YYSTYPE;
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1
#endif

int yyparse(void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
