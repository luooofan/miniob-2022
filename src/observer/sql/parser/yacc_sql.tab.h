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
  SHOW = 268,
  SYNC = 269,
  INSERT = 270,
  DELETE = 271,
  UPDATE = 272,
  LBRACE = 273,
  RBRACE = 274,
  COMMA = 275,
  TRX_BEGIN = 276,
  TRX_COMMIT = 277,
  TRX_ROLLBACK = 278,
  INT_T = 279,
  STRING_T = 280,
  DATE_T = 281,
  FLOAT_T = 282,
  HELP = 283,
  EXIT = 284,
  DOT = 285,
  INTO = 286,
  VALUES = 287,
  FROM = 288,
  WHERE = 289,
  AND = 290,
  SET = 291,
  ON = 292,
  LOAD = 293,
  DATA = 294,
  INFILE = 295,
  NOT = 296,
  LIKE = 297,
  EQ = 298,
  LT = 299,
  GT = 300,
  LE = 301,
  GE = 302,
  NE = 303,
  NUMBER = 304,
  FLOAT = 305,
  ID = 306,
  PATH = 307,
  SSS = 308,
  STAR = 309,
  STRING_V = 310,
  DATE_STR = 311
};
#endif

/* Value type.  */
#if !defined YYSTYPE && !defined YYSTYPE_IS_DECLARED
union YYSTYPE {
#line 121 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
  char *position;

#line 124 "yacc_sql.tab.h"
};
typedef union YYSTYPE YYSTYPE;
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1
#endif

int yyparse(void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
