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
  AGGR_MAX = 287,
  AGGR_MIN = 288,
  AGGR_SUM = 289,
  AGGR_AVG = 290,
  AGGR_COUNT = 291,
  HELP = 292,
  EXIT = 293,
  DOT = 294,
  INTO = 295,
  VALUES = 296,
  FROM = 297,
  WHERE = 298,
  AND = 299,
  SET = 300,
  ON = 301,
  LOAD = 302,
  DATA = 303,
  INFILE = 304,
  NOT = 305,
  LIKE = 306,
  UNIQUE = 307,
  ADD = 308,
  SUB = 309,
  MUL = 310,
  DIV = 311,
  EQ = 312,
  LT = 313,
  GT = 314,
  LE = 315,
  GE = 316,
  NE = 317,
  NUMBER = 318,
  FLOAT = 319,
  ID = 320,
  PATH = 321,
  SSS = 322,
  STAR = 323,
  STRING_V = 324,
  DATE_STR = 325
};
#endif

/* Value type.  */
#if !defined YYSTYPE && !defined YYSTYPE_IS_DECLARED
union YYSTYPE {
#line 145 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  struct _UnaryExpr *uexp1;
  struct _Expr *exp1;
  struct _Expr *exp2;
  struct _Expr *exp3;
  char *string;
  int number;
  float floats;
  char *position;

#line 142 "yacc_sql.tab.h"
};
typedef union YYSTYPE YYSTYPE;
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1
#endif

int yyparse(void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
