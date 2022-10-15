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
  BY = 285,
  HELP = 286,
  EXIT = 287,
  DOT = 288,
  INTO = 289,
  VALUES = 290,
  FROM = 291,
  WHERE = 292,
  AND = 293,
  SET = 294,
  ON = 295,
  LOAD = 296,
  DATA = 297,
  INFILE = 298,
  NOT = 299,
  LIKE = 300,
  UNIQUE = 301,
  ADD = 302,
  SUB = 303,
  MUL = 304,
  DIV = 305,
  EQ = 306,
  LT = 307,
  GT = 308,
  LE = 309,
  GE = 310,
  NE = 311,
  NUMBER = 312,
  FLOAT = 313,
  ID = 314,
  PATH = 315,
  SSS = 316,
  STAR = 317,
  STRING_V = 318,
  DATE_STR = 319
};
#endif

/* Value type.  */
#if !defined YYSTYPE && !defined YYSTYPE_IS_DECLARED
union YYSTYPE {
#line 135 "yacc_sql.y"

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

#line 136 "yacc_sql.tab.h"
};
typedef union YYSTYPE YYSTYPE;
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1
#endif

int yyparse(void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
