/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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
  size_t select_length;
  size_t condition_length;
  size_t having_length;
  size_t orderby_length;
  size_t groupby_length;
  size_t aggrfunc_length;
  size_t from_length;
  size_t value_length;
  size_t project_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  Condition havings[MAX_NUM];
  OrderBy orderbys[MAX_NUM];
  GroupBy groupbys[MAX_NUM];
  Relation froms[MAX_NUM];
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
  context->select_length = 0;
  context->value_length = 0;
  context->having_length = 0;
  context->groupby_length = 0;
  context->aggrfunc_length = 0;
  context->project_length = 0;
  context->ssql->sstr.insertion.value_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 161 "yacc_sql.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 169 "yacc_sql.y"

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
  struct _FromInfo* from_info;
  char *string;
  int number;
  float floats;
	char *position;
  int cur_len;
  int comp_op;

#line 315 "yacc_sql.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
<<<<<<< HEAD
#define YYLAST   405
=======
#define YYLAST   427
>>>>>>> alias finish v1

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
<<<<<<< HEAD
#define YYNRULES  151
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  316
=======
#define YYNRULES  156
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  331
>>>>>>> alias finish v1

#define YYUNDEFTOK  2
#define YYMAXUTOK   335


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   229,   229,   231,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   256,   261,   266,   272,   278,   284,   290,   296,
     302,   309,   317,   322,   329,   331,   337,   344,   351,   360,
<<<<<<< HEAD
     362,   366,   377,   384,   395,   402,   409,   416,   425,   428,
     429,   430,   431,   434,   443,   449,   451,   455,   466,   478,
     481,   488,   491,   506,   513,   523,   524,   531,   541,   547,
     561,   575,   581,   587,   600,   616,   624,   631,   640,   649,
     653,   656,   659,   662,   667,   670,   673,   676,   679,   685,
     693,   715,   725,   735,   745,   757,   799,   802,   805,   808,
     811,   815,   825,   831,   841,   851,   883,   890,   897,   905,
     909,   916,   923,   932,   940,   946,   951,   959,   962,   967,
     970,   976,   979,   985,   988,   993,   996,  1003,  1004,  1005,
    1006,  1007,  1008,  1009,  1010,  1013,  1022,  1031,  1040,  1049,
    1058,  1068,  1072,  1078,  1081,  1088,  1095,  1104,  1108,  1114,
    1117,  1124
=======
     362,   366,   377,   388,   395,   402,   409,   418,   421,   422,
     423,   424,   427,   436,   442,   444,   448,   459,   471,   474,
     481,   484,   499,   506,   516,   517,   524,   534,   540,   554,
     568,   574,   580,   593,   609,   617,   624,   633,   642,   646,
     649,   652,   655,   660,   663,   666,   669,   672,   678,   686,
     708,   718,   728,   738,   750,   792,   795,   798,   801,   804,
     808,   818,   824,   834,   844,   876,   883,   890,   897,   906,
     910,   917,   924,   931,   941,   948,   955,   965,   971,   978,
     985,   992,  1002,  1005,  1010,  1013,  1019,  1022,  1028,  1031,
    1036,  1039,  1046,  1047,  1048,  1049,  1050,  1051,  1052,  1053,
    1056,  1065,  1074,  1083,  1092,  1101,  1111,  1115,  1121,  1124,
    1131,  1138,  1147,  1151,  1157,  1160,  1167
>>>>>>> alias finish v1
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "TABLE",
<<<<<<< HEAD
  "TABLES", "INDEX", "INNER", "JOIN", "SELECT", "DESC", "ASC", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA",
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "DATE_T",
  "FLOAT_T", "ORDER", "GROUP", "BY", "IN", "EXISTS", "HAVING", "AGGR_MAX",
  "AGGR_MIN", "AGGR_SUM", "AGGR_AVG", "AGGR_COUNT", "HELP", "TEXT", "EXIT",
  "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON", "LOAD",
  "DATA", "INFILE", "NOT", "LIKE", "UNIQUE", "ADD", "SUB", "MUL", "DIV",
  "IS", "NULL_VALUE", "NULLABLE", "EQ", "LT", "GT", "LE", "GE", "NE",
  "LENGTH", "ROUND", "DATE_FORMAT", "NUMBER", "FLOAT", "ID", "PATH", "SSS",
  "STAR", "STRING_V", "DATE_STR", "$accept", "commands", "command", "exit",
  "help", "sync", "begin", "commit", "rollback", "drop_table",
=======
  "TABLES", "INDEX", "INNER", "JOIN", "SELECT", "DESC", "ASC", "AS",
  "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE",
  "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "DATE_T", "FLOAT_T", "ORDER", "GROUP", "BY", "IN", "EXISTS", "HAVING",
  "AGGR_MAX", "AGGR_MIN", "AGGR_SUM", "AGGR_AVG", "AGGR_COUNT", "HELP",
  "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON",
  "LOAD", "DATA", "INFILE", "NOT", "LIKE", "UNIQUE", "ADD", "SUB", "MUL",
  "DIV", "IS", "NULL_VALUE", "NULLABLE", "EQ", "LT", "GT", "LE", "GE",
  "NE", "LENGTH", "ROUND", "DATE_FORMAT", "NUMBER", "FLOAT", "ID", "PATH",
  "SSS", "STAR", "STRING_V", "DATE_STR", "$accept", "commands", "command",
  "exit", "help", "sync", "begin", "commit", "rollback", "drop_table",
>>>>>>> alias finish v1
  "show_tables", "desc_table", "show_index", "create_index", "id_list",
  "id", "drop_index", "create_table", "attr_def_list", "attr_def",
  "number", "type", "ID_get", "insert", "row_value_list", "row_value",
  "sub_select_list", "value_list", "mul_expr", "add_expr", "condition",
  "having_condition", "unary_expr", "aggr_func_type", "aggr_func_expr",
  "func_expr", "sub_select", "value", "delete", "update", "select",
  "select_attr", "attr_list", "from", "rel_list", "inner_join_conditions",
  "where", "condition_list", "opt_having", "having_condition_list",
  "comOp", "sort_unit", "sort_list", "opt_order_by", "groupby_unit",
  "groupby_list", "opt_group_by", "load_data", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335
};
# endif

#define YYPACT_NINF (-234)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-60)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
<<<<<<< HEAD
    -234,     6,  -234,     7,   110,   154,   -56,    27,    46,    22,
      16,    14,    92,    97,   103,   107,   114,    73,  -234,  -234,
    -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,
    -234,  -234,  -234,  -234,  -234,  -234,  -234,    61,    63,   134,
      77,    85,    49,  -234,  -234,  -234,  -234,  -234,   256,  -234,
     129,   142,   144,  -234,  -234,   124,  -234,   151,  -234,  -234,
     -51,    51,  -234,   157,  -234,  -234,  -234,  -234,   131,   181,
     183,   141,  -234,   121,   127,   162,  -234,  -234,  -234,  -234,
    -234,   150,   194,   164,   147,   212,   220,   154,   190,    18,
     130,    57,  -234,  -234,  -234,   285,   285,   285,   -39,   182,
    -234,   313,   313,   285,   285,  -234,   228,   160,  -234,  -234,
     161,   193,   192,   166,   165,   168,   170,   196,  -234,  -234,
     202,   174,  -234,    91,   230,  -234,  -234,    20,    12,    76,
    -234,   151,   208,   151,    51,  -234,  -234,   -51,   -51,   238,
      23,    84,   192,   258,   249,   108,   266,   206,   227,  -234,
     251,    87,   254,   199,   160,   255,  -234,  -234,  -234,   285,
     285,  -234,    62,  -234,  -234,  -234,  -234,   267,   203,  -234,
     252,  -234,    91,   262,   285,   246,   312,   236,  -234,    91,
     279,   168,   268,  -234,  -234,  -234,  -234,  -234,   -12,   214,
     277,   192,  -234,    41,    45,   151,   222,    84,   276,   253,
     255,   249,   306,    99,   285,   285,    -1,  -234,    42,  -234,
    -234,  -234,  -234,  -234,  -234,   285,   108,  -234,   192,   235,
     251,   308,   239,   257,  -234,  -234,   292,   214,   252,  -234,
    -234,  -234,   265,  -234,   241,   285,   288,   305,   262,  -234,
      99,    99,   285,  -234,   272,  -234,    99,   236,   332,   334,
    -234,  -234,  -234,   318,  -234,   214,   319,   292,   253,   108,
      84,   297,   320,  -234,   140,   294,   314,   343,  -234,  -234,
      99,  -234,  -234,  -234,  -234,   -13,   292,   350,   341,   288,
     236,  -234,   289,   241,   299,   285,   285,  -234,   293,  -234,
     301,  -234,  -234,  -234,   369,   354,  -234,  -234,  -234,    99,
     294,    13,   361,  -234,  -234,  -234,  -234,  -234,  -234,  -234,
     316,   293,   146,  -234,  -234,  -234
=======
    -242,   375,  -242,     7,    95,   123,   -34,    97,    41,    33,
      35,    54,   130,   132,   142,   167,   171,   102,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,  -242,   101,   103,   169,
     104,   108,    -6,  -242,  -242,  -242,  -242,  -242,   241,  -242,
     160,   162,   164,  -242,  -242,   143,  -242,   170,  -242,  -242,
     -31,     4,  -242,   182,  -242,  -242,  -242,  -242,   153,   201,
     202,   165,  -242,   131,   135,   163,  -242,  -242,  -242,  -242,
    -242,   161,   195,   177,   144,   214,   217,   123,   187,   -12,
     105,    65,  -242,  -242,  -242,   268,   268,   268,   -54,   151,
    -242,   297,   297,   168,   268,   268,  -242,   196,   172,  -242,
    -242,   173,   193,   192,   175,   174,   180,   185,   190,  -242,
    -242,   198,   188,  -242,   179,   224,  -242,  -242,    39,    67,
      73,  -242,   170,   203,   170,    29,  -242,  -242,   170,   -31,
     -31,   236,    49,    -3,   192,   259,   244,    78,   262,   208,
     231,  -242,   260,    94,   263,   209,   172,   264,  -242,  -242,
    -242,   268,   268,  -242,   -40,  -242,   210,  -242,  -242,  -242,
    -242,   277,   215,   216,    91,  -242,   258,  -242,   179,   270,
     268,   266,   296,   245,  -242,   179,   288,   180,   276,  -242,
    -242,  -242,  -242,    30,   223,   281,   192,  -242,    89,   107,
     170,   170,   227,    91,     3,  -242,   278,   274,   264,   244,
     316,   109,   268,   268,   -13,  -242,    57,  -242,  -242,  -242,
    -242,  -242,  -242,   268,    78,  -242,   192,   247,   260,   317,
     250,   265,  -242,  -242,   302,   223,   258,  -242,  -242,  -242,
    -242,   275,  -242,   253,    91,  -242,   256,   268,   314,   311,
     270,  -242,   109,   109,   268,  -242,   284,  -242,   109,   245,
     344,   346,  -242,  -242,  -242,   331,  -242,   223,   335,   302,
     274,    78,    91,    91,  -242,   315,   351,  -242,   354,   318,
     349,   373,  -242,  -242,   109,  -242,  -242,  -242,  -242,   -27,
     302,   379,   357,   314,   245,  -242,  -242,   308,   256,   329,
     268,   268,  -242,   310,  -242,   326,  -242,  -242,  -242,   386,
     374,  -242,  -242,  -242,   109,   318,    10,   380,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,   321,   310,   156,  -242,  -242,
    -242
>>>>>>> alias finish v1
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,    19,     0,     0,     0,
<<<<<<< HEAD
       0,     0,     0,    84,    85,    86,    87,    88,     0,   102,
       0,     0,     0,    96,    98,    77,   100,   109,   101,    83,
      65,   109,    61,     0,    81,    80,    82,    76,     0,     0,
       0,     0,    24,     0,     0,     0,    25,    26,    27,    23,
      22,     0,     0,     0,     0,     0,     0,     0,    77,     0,
      76,     0,    96,    98,    62,     0,     0,     0,     0,     0,
     106,     0,     0,     0,     0,   108,     0,     0,    30,    29,
       0,     0,   119,     0,     0,     0,     0,     0,    28,    37,
       0,     0,    79,     0,     0,    97,    99,     0,     0,     0,
      78,   109,    77,   109,   109,    64,    63,    66,    67,     0,
       0,   114,   119,     0,     0,     0,     0,     0,     0,    53,
      39,     0,     0,     0,     0,    59,    58,    91,    92,     0,
       0,   107,     0,   110,   112,    90,    89,     0,     0,   113,
     149,    31,     0,    55,     0,     0,     0,   121,   103,     0,
       0,     0,     0,    49,    50,    52,    51,    42,    43,     0,
       0,   119,    60,     0,     0,   109,     0,   114,     0,   123,
      59,     0,     0,    73,     0,     0,     0,   133,     0,   127,
     128,   129,   130,   131,   132,     0,     0,   120,   119,     0,
      39,     0,     0,     0,    47,    36,    34,     0,   149,    93,
      94,   111,   117,   115,     0,     0,   143,     0,    55,    54,
      74,    71,     0,   134,     0,    69,    68,   121,     0,     0,
      40,    38,    48,     0,    46,     0,     0,    34,   123,     0,
     114,   145,   148,   150,     0,   125,     0,     0,    57,    56,
      72,    70,   122,   104,   151,    41,    34,     0,     0,   143,
     121,   116,     0,     0,     0,     0,     0,   124,     0,   105,
       0,    45,    35,    32,     0,     0,   118,   146,   147,    75,
     125,   135,   142,   144,    44,    33,    95,   126,   137,   138,
       0,     0,   136,   141,   139,   140
=======
       0,     0,     0,    83,    84,    85,    86,    87,     0,   101,
       0,     0,     0,    95,    97,    76,    99,   109,   100,    82,
      64,   109,    60,     0,    80,    79,    81,    75,     0,     0,
       0,     0,    24,     0,     0,     0,    25,    26,    27,    23,
      22,     0,     0,     0,     0,     0,     0,     0,    76,     0,
      75,     0,    95,    97,    61,     0,     0,     0,     0,     0,
     105,     0,     0,     0,     0,     0,   107,     0,     0,    30,
      29,     0,     0,   124,     0,     0,     0,     0,     0,    28,
      37,     0,     0,    78,     0,     0,    96,    98,     0,     0,
       0,    77,   109,    76,   109,   109,    63,    62,   109,    65,
      66,     0,     0,   117,   124,     0,     0,     0,     0,     0,
       0,    52,    39,     0,     0,     0,     0,    58,    57,    90,
      91,     0,     0,   106,     0,   110,     0,   112,   108,    89,
      88,     0,     0,     0,   117,   114,   154,    31,     0,    54,
       0,     0,     0,   126,   102,     0,     0,     0,     0,    48,
      49,    51,    50,    42,     0,     0,   124,    59,     0,     0,
     109,   109,     0,   117,   117,   115,     0,   128,    58,     0,
       0,    72,     0,     0,     0,   138,     0,   132,   133,   134,
     135,   136,   137,     0,     0,   125,   124,     0,    39,     0,
       0,     0,    46,    36,    34,     0,   154,    92,    93,   111,
     113,   122,   116,     0,   117,   118,     0,     0,   148,     0,
      54,    53,    73,    70,     0,   139,     0,    68,    67,   126,
       0,     0,    40,    38,    47,     0,    45,     0,     0,    34,
     128,     0,   117,   117,   119,   150,   153,   155,     0,   130,
       0,     0,    56,    55,    71,    69,   127,   103,   156,    41,
      34,     0,     0,   148,   126,   121,   120,     0,     0,     0,
       0,     0,   129,     0,   104,     0,    44,    35,    32,     0,
       0,   123,   151,   152,    74,   130,   140,   147,   149,    43,
      33,    94,   131,   142,   143,     0,     0,   141,   146,   144,
     145
>>>>>>> alias finish v1
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
<<<<<<< HEAD
    -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,
    -234,  -234,  -234,  -234,  -212,  -211,  -234,  -234,   169,   211,
    -234,  -234,  -234,  -234,   156,   195,  -234,  -147,    71,    -5,
    -204,   109,   -43,  -234,  -234,  -234,  -234,   -40,  -234,  -234,
    -234,   310,   -60,   244,  -193,  -234,  -139,  -233,   143,   100,
     135,  -234,    93,   123,  -234,   120,   177,  -234
=======
    -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,  -241,  -219,  -242,  -242,   176,   218,
    -242,  -242,  -242,  -242,   147,   194,  -242,  -149,    68,    -5,
    -217,   100,   -44,  -242,  -242,  -242,  -242,   -41,  -242,  -242,
    -242,   319,   -59,   251,  -164,  -242,  -141,  -160,   140,    98,
     136,  -242,    99,   122,  -242,   126,   191,  -242
>>>>>>> alias finish v1
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
<<<<<<< HEAD
      26,    27,    28,    29,   256,   226,    30,    31,   182,   150,
     253,   188,   151,    32,   202,   173,    59,   124,    60,   176,
     177,   265,    62,    63,    64,    65,    66,    67,    33,    34,
      35,    68,   100,   142,   169,   260,   146,   217,   236,   287,
     215,   302,   303,   267,   262,   263,   199,    36
=======
      26,    27,    28,    29,   268,   234,    30,    31,   188,   152,
     265,   193,   153,    32,   210,   179,    59,   125,    60,   182,
     183,   279,    62,    63,    64,    65,    66,    67,    33,    34,
      35,    68,   100,   144,   175,   272,   148,   225,   248,   302,
     223,   317,   318,   281,   276,   277,   207,    36
>>>>>>> alias finish v1
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
<<<<<<< HEAD
      61,   105,    90,   170,   233,    94,     2,   222,   192,   101,
       3,     4,   247,    37,   272,    38,   257,     5,     6,    69,
       7,     8,     9,    10,    11,   308,   309,   102,    12,    13,
      14,   242,   158,   159,    70,    71,   130,    89,   122,   131,
     157,   290,   223,   166,   276,   278,    15,   296,    16,    72,
     291,   224,   228,   237,   243,   280,   310,    17,   135,   136,
      87,   229,    74,    39,   292,   230,    73,   281,    42,   103,
     104,   161,    99,   163,   164,   103,   104,   103,   104,   248,
     103,   104,    61,   155,    43,    44,    45,    46,    47,    75,
     127,   128,   129,   167,   134,    76,   244,   160,   103,   104,
      77,   140,   103,   104,   245,   168,    78,    48,   103,   104,
      79,    49,   183,   184,   185,   186,    40,    80,    41,    50,
      51,    52,    53,    54,    88,    81,    56,    42,   187,    58,
     125,   126,   200,   103,   104,   231,    82,   130,    83,   218,
     195,   174,    84,    43,    44,    45,    46,    47,    95,    91,
     -59,   123,    85,    49,   193,   194,   103,   104,   314,   315,
      86,    96,   175,    97,    53,    54,    48,    98,    56,   203,
      49,    58,    99,    42,   137,   138,   106,   107,    50,    51,
      52,    53,    54,    88,   108,    56,   109,   110,    58,    43,
      44,    45,    46,    47,   284,   207,   111,   103,   104,   240,
     241,    42,   112,   114,   209,   210,   211,   212,   213,   214,
     246,   113,    48,   115,   116,   118,    49,    43,    44,    45,
      46,    47,   117,   119,    50,    51,    52,    53,    54,    55,
     264,    56,    57,   121,    58,   141,   143,   270,   144,   145,
      48,   147,   148,   149,    49,   152,   153,    42,   154,   130,
     156,   162,    50,    51,    52,    53,    54,   132,   165,    56,
     133,   171,    58,    43,    44,    45,    46,    47,   172,   178,
     179,   180,   181,   189,   190,    42,   123,   196,   197,   204,
     299,   264,   198,   201,   216,   219,    48,   235,   221,   225,
      49,    43,    44,    45,    46,    47,   227,   232,    50,    51,
      52,    53,    54,    88,    42,    56,   139,   234,    58,   239,
     249,   251,   252,   255,    91,   259,   261,   266,    49,   254,
      43,    44,    45,    46,    47,   268,    50,    51,    52,    92,
      93,    88,    42,    56,   271,   273,    58,   274,   275,   277,
     282,   283,   286,    48,   205,   288,   289,    49,    43,    44,
      45,    46,    47,   293,   243,    50,    51,    52,    53,    54,
      88,   294,    56,   304,   297,    58,   206,   207,   301,   103,
     104,    91,   305,   208,   306,    49,   209,   210,   211,   212,
     213,   214,   311,    50,    51,    52,    53,    54,    88,   250,
      56,   312,   220,    58,   269,   300,   238,   120,   191,   285,
     307,   279,   295,   298,   313,   258
=======
      61,    90,   106,   176,    94,    87,   171,   259,   197,   123,
     205,   172,   171,    37,    42,    38,   269,   243,   103,   173,
     254,   131,   323,   324,   132,   173,    99,   305,   292,   101,
      43,    44,    45,    46,    47,   131,   306,    89,   200,   242,
     245,    69,   255,   166,    72,   104,   105,   102,   290,   307,
     230,    99,    48,   325,   294,   236,    49,   136,   137,   249,
     159,   104,   105,    39,    50,    51,    52,    53,    54,    88,
     170,    56,   174,   163,    58,   165,   167,    73,   244,   168,
     274,    74,    61,   157,   231,   260,   104,   105,   160,   161,
     128,   129,   130,   232,   135,   162,   104,   105,    42,   286,
     171,    40,   142,    41,    70,    71,   104,   105,   295,   296,
     237,   256,   180,   173,    43,    44,    45,    46,    47,   257,
     189,   190,   191,   192,   104,   105,   -58,   124,   238,    75,
     104,   105,   181,    76,   311,    77,    48,   208,   126,   127,
      49,   239,   240,    42,   226,    78,   104,   105,    50,    51,
      52,    53,    54,    88,    81,    56,   198,   199,    58,    43,
      44,    45,    46,    47,   104,   105,   104,   105,   329,   330,
      79,    42,   139,   140,    80,   211,    82,    84,    83,    85,
      95,    48,    96,    86,    97,    49,    98,    43,    44,    45,
      46,    47,    99,    50,    51,    52,    53,    54,    55,   108,
      56,    57,   107,    58,   109,   110,   112,   252,   253,    48,
     113,   111,   114,    49,   115,   116,    42,   119,   258,   118,
     120,    50,    51,    52,    53,    54,   133,   117,    56,   134,
     122,    58,    43,    44,    45,    46,    47,    91,   146,   147,
     155,    49,   278,   138,   156,   158,   164,   143,   145,   284,
     149,   150,    53,    54,    48,   151,    56,   169,    49,    58,
     154,    42,   177,   131,   178,   184,    50,    51,    52,    53,
      54,    88,   185,    56,   141,   186,    58,    43,    44,    45,
      46,    47,   187,   194,   195,   201,   124,   202,    42,   206,
     203,   204,   209,   224,   227,   314,   278,   229,   233,    91,
     212,   235,   241,    49,    43,    44,    45,    46,    47,   247,
     246,    50,    51,    52,    92,    93,    88,    42,    56,   251,
     263,    58,   261,   264,   267,   271,    48,   266,   273,   213,
      49,   275,   282,    43,    44,    45,    46,    47,    50,    51,
      52,    53,    54,    88,   280,    56,   285,   287,    58,   288,
     214,   215,   289,   104,   105,    91,   291,   216,   297,    49,
     217,   218,   219,   220,   221,   222,   301,    50,    51,    52,
      53,    54,    88,   298,    56,     2,   304,    58,   309,     3,
       4,   303,   308,   312,   255,   316,     5,     6,   319,   320,
       7,     8,     9,    10,    11,   321,   327,   283,    12,    13,
      14,   315,   326,   250,   262,   228,   121,   196,   299,   215,
     293,   104,   105,   322,   300,   310,    15,    16,   217,   218,
     219,   220,   221,   222,   313,   328,    17,   270
>>>>>>> alias finish v1
};

static const yytype_int16 yycheck[] =
{
<<<<<<< HEAD
       5,    61,    42,   142,   197,    48,     0,    19,   155,    60,
       4,     5,   216,     6,   247,     8,   227,    11,    12,    75,
      14,    15,    16,    17,    18,    12,    13,    78,    22,    23,
      24,    32,    20,    21,     7,     8,    75,    42,    20,    78,
      20,    54,    54,    20,   255,   257,    40,   280,    42,     3,
      63,    63,   191,   200,    55,   259,    43,    51,   101,   102,
      11,    20,    46,    56,   276,    20,    44,   260,    19,    57,
      58,   131,    21,   133,   134,    57,    58,    57,    58,   218,
      57,    58,    87,   123,    35,    36,    37,    38,    39,    75,
      95,    96,    97,     9,    99,     3,    54,    21,    57,    58,
       3,   106,    57,    58,    62,    21,     3,    58,    57,    58,
       3,    62,    25,    26,    27,    28,     6,     3,     8,    70,
      71,    72,    73,    74,    75,    52,    77,    19,    41,    80,
      73,    74,   172,    57,    58,   195,    75,    75,    75,   179,
      78,    33,     8,    35,    36,    37,    38,    39,    19,    58,
      20,    21,    75,    62,   159,   160,    57,    58,    12,    13,
      75,    19,    54,    19,    73,    74,    58,    43,    77,   174,
      62,    80,    21,    19,   103,   104,    19,    46,    70,    71,
      72,    73,    74,    75,     3,    77,     3,    46,    80,    35,
      36,    37,    38,    39,    54,    55,    75,    57,    58,   204,
     205,    19,    75,    53,    64,    65,    66,    67,    68,    69,
     215,    49,    58,    19,    50,     3,    62,    35,    36,    37,
      38,    39,    75,     3,    70,    71,    72,    73,    74,    75,
     235,    77,    78,    43,    80,    75,    75,   242,    45,    47,
      58,    75,    77,    75,    62,    75,    50,    19,    46,    75,
      20,    43,    70,    71,    72,    73,    74,    75,    20,    77,
      78,     3,    80,    35,    36,    37,    38,    39,    19,     3,
      64,    44,    21,    19,    75,    19,    21,    10,    75,    33,
     285,   286,    30,    21,    48,     6,    58,    34,    20,    75,
      62,    35,    36,    37,    38,    39,    19,    75,    70,    71,
      72,    73,    74,    75,    19,    77,    78,    31,    80,     3,
      75,     3,    73,    21,    58,    50,    75,    29,    62,    62,
      35,    36,    37,    38,    39,    20,    70,    71,    72,    73,
      74,    75,    19,    77,    62,     3,    80,     3,    20,    20,
      43,    21,    48,    58,    32,    31,     3,    62,    35,    36,
      37,    38,    39,     3,    55,    70,    71,    72,    73,    74,
      75,    20,    77,    62,    75,    80,    54,    55,    75,    57,
      58,    58,     3,    61,    20,    62,    64,    65,    66,    67,
      68,    69,    21,    70,    71,    72,    73,    74,    75,   220,
      77,    75,   181,    80,   238,   286,   201,    87,   154,   264,
     300,   258,   279,   283,   311,   228
=======
       5,    42,    61,   144,    48,    11,     9,   224,   157,    21,
     174,    14,     9,     6,    20,     8,   235,    14,    14,    22,
      33,    75,    12,    13,    78,    22,    22,    54,   269,    60,
      36,    37,    38,    39,    40,    75,    63,    42,    78,   203,
     204,    75,    55,    14,     3,    57,    58,    78,   267,   290,
      20,    22,    58,    43,   271,   196,    62,   101,   102,   208,
      21,    57,    58,    56,    70,    71,    72,    73,    74,    75,
      21,    77,    75,   132,    80,   134,   135,    44,    75,   138,
     244,    46,    87,   124,    54,   226,    57,    58,    21,    22,
      95,    96,    97,    63,    99,    22,    57,    58,    20,   259,
       9,     6,   107,     8,     7,     8,    57,    58,   272,   273,
      21,    54,    34,    22,    36,    37,    38,    39,    40,    62,
      26,    27,    28,    29,    57,    58,    21,    22,    21,    75,
      57,    58,    54,     3,   294,     3,    58,   178,    73,    74,
      62,   200,   201,    20,   185,     3,    57,    58,    70,    71,
      72,    73,    74,    75,    52,    77,   161,   162,    80,    36,
      37,    38,    39,    40,    57,    58,    57,    58,    12,    13,
       3,    20,   104,   105,     3,   180,    75,     8,    75,    75,
      20,    58,    20,    75,    20,    62,    43,    36,    37,    38,
      39,    40,    22,    70,    71,    72,    73,    74,    75,    46,
      77,    78,    20,    80,     3,     3,    75,   212,   213,    58,
      75,    46,    49,    62,    53,    20,    20,     3,   223,    75,
       3,    70,    71,    72,    73,    74,    75,    50,    77,    78,
      43,    80,    36,    37,    38,    39,    40,    58,    45,    47,
      50,    62,   247,    75,    46,    21,    43,    75,    75,   254,
      75,    77,    73,    74,    58,    75,    77,    21,    62,    80,
      75,    20,     3,    75,    20,     3,    70,    71,    72,    73,
      74,    75,    64,    77,    78,    44,    80,    36,    37,    38,
      39,    40,    22,    20,    75,    75,    22,    10,    20,    31,
      75,    75,    22,    48,     6,   300,   301,    21,    75,    58,
      34,    20,    75,    62,    36,    37,    38,    39,    40,    35,
      32,    70,    71,    72,    73,    74,    75,    20,    77,     3,
       3,    80,    75,    73,    22,    50,    58,    62,    75,    33,
      62,    75,    21,    36,    37,    38,    39,    40,    70,    71,
      72,    73,    74,    75,    30,    77,    62,     3,    80,     3,
      54,    55,    21,    57,    58,    58,    21,    61,    43,    62,
      64,    65,    66,    67,    68,    69,    48,    70,    71,    72,
      73,    74,    75,    22,    77,     0,     3,    80,    21,     4,
       5,    32,     3,    75,    55,    75,    11,    12,    62,     3,
      15,    16,    17,    18,    19,    21,    75,   250,    23,    24,
      25,   301,    22,   209,   228,   187,    87,   156,    54,    55,
     270,    57,    58,   315,   278,   293,    41,    42,    64,    65,
      66,    67,    68,    69,   298,   326,    51,   236
>>>>>>> alias finish v1
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
<<<<<<< HEAD
       0,    82,     0,     4,     5,    11,    12,    14,    15,    16,
      17,    18,    22,    23,    24,    40,    42,    51,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      97,    98,   104,   119,   120,   121,   138,     6,     8,    56,
       6,     8,    19,    35,    36,    37,    38,    39,    58,    62,
=======
       0,    82,     0,     4,     5,    11,    12,    15,    16,    17,
      18,    19,    23,    24,    25,    41,    42,    51,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      97,    98,   104,   119,   120,   121,   138,     6,     8,    56,
       6,     8,    20,    36,    37,    38,    39,    40,    58,    62,
>>>>>>> alias finish v1
      70,    71,    72,    73,    74,    75,    77,    78,    80,   107,
     109,   110,   113,   114,   115,   116,   117,   118,   122,    75,
       7,     8,     3,    44,    46,    75,     3,     3,     3,     3,
       3,    52,    75,    75,     8,    75,    75,    11,    75,   110,
<<<<<<< HEAD
     118,    58,    73,    74,   113,    19,    19,    19,    43,    21,
     123,    60,    78,    57,    58,   123,    19,    46,     3,     3,
      46,    75,    75,    49,    53,    19,    50,    75,     3,     3,
     122,    43,    20,    21,   108,    73,    74,   110,   110,   110,
      75,    78,    75,    78,   110,   113,   113,   109,   109,    78,
     110,    75,   124,    75,    45,    47,   127,    75,    77,    75,
     100,   103,    75,    50,    46,   118,    20,    20,    20,    21,
      21,   123,    43,   123,   123,    20,    20,     9,    21,   125,
     127,     3,    19,   106,    33,    54,   110,   111,     3,    64,
      44,    21,    99,    25,    26,    27,    28,    41,   102,    19,
      75,   124,   108,   110,   110,    78,    10,    75,    30,   137,
     118,    21,   105,   110,    33,    32,    54,    55,    61,    64,
      65,    66,    67,    68,    69,   131,    48,   128,   118,     6,
     100,    20,    19,    54,    63,    75,    96,    19,   127,    20,
      20,   123,    75,   125,    31,    34,   129,   108,   106,     3,
     110,   110,    32,    55,    54,    62,   110,   111,   127,    75,
      99,     3,    73,   101,    62,    21,    95,    96,   137,    50,
     126,    75,   135,   136,   110,   112,    29,   134,    20,   105,
     110,    62,   128,     3,     3,    20,    96,    20,    95,   129,
     111,   125,    43,    21,    54,   131,    48,   130,    31,     3,
      54,    63,    95,     3,    20,   134,   128,    75,   136,   110,
     112,    75,   132,   133,    62,     3,    20,   130,    12,    13,
      43,    21,    75,   133,    12,    13
=======
     118,    58,    73,    74,   113,    20,    20,    20,    43,    22,
     123,    60,    78,    14,    57,    58,   123,    20,    46,     3,
       3,    46,    75,    75,    49,    53,    20,    50,    75,     3,
       3,   122,    43,    21,    22,   108,    73,    74,   110,   110,
     110,    75,    78,    75,    78,   110,   113,   113,    75,   109,
     109,    78,   110,    75,   124,    75,    45,    47,   127,    75,
      77,    75,   100,   103,    75,    50,    46,   118,    21,    21,
      21,    22,    22,   123,    43,   123,    14,   123,   123,    21,
      21,     9,    14,    22,    75,   125,   127,     3,    20,   106,
      34,    54,   110,   111,     3,    64,    44,    22,    99,    26,
      27,    28,    29,   102,    20,    75,   124,   108,   110,   110,
      78,    75,    10,    75,    75,   125,    31,   137,   118,    22,
     105,   110,    34,    33,    54,    55,    61,    64,    65,    66,
      67,    68,    69,   131,    48,   128,   118,     6,   100,    21,
      20,    54,    63,    75,    96,    20,   127,    21,    21,   123,
     123,    75,   125,    14,    75,   125,    32,    35,   129,   108,
     106,     3,   110,   110,    33,    55,    54,    62,   110,   111,
     127,    75,    99,     3,    73,   101,    62,    22,    95,    96,
     137,    50,   126,    75,   125,    75,   135,   136,   110,   112,
      30,   134,    21,   105,   110,    62,   128,     3,     3,    21,
      96,    21,    95,   129,   111,   125,   125,    43,    22,    54,
     131,    48,   130,    32,     3,    54,    63,    95,     3,    21,
     134,   128,    75,   136,   110,   112,    75,   132,   133,    62,
       3,    21,   130,    12,    13,    43,    22,    75,   133,    12,
      13
>>>>>>> alias finish v1
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    82,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    94,    95,    95,    96,    97,    98,    99,
<<<<<<< HEAD
      99,   100,   100,   100,   100,   100,   100,   100,   101,   102,
     102,   102,   102,   103,   104,   105,   105,   106,   107,   108,
     108,   109,   109,   109,   109,   110,   110,   110,   111,   111,
     111,   111,   111,   111,   111,   112,   113,   113,   113,   113,
     113,   113,   113,   113,   114,   114,   114,   114,   114,   115,
     115,   116,   116,   116,   116,   117,   118,   118,   118,   118,
     118,   118,   118,   119,   120,   121,   122,   122,   122,   123,
     123,   123,   123,   124,   125,   125,   125,   126,   126,   127,
     127,   128,   128,   129,   129,   130,   130,   131,   131,   131,
     131,   131,   131,   131,   131,   132,   132,   132,   132,   132,
     132,   133,   133,   134,   134,   135,   135,   136,   136,   137,
     137,   138
=======
      99,   100,   100,   100,   100,   100,   100,   101,   102,   102,
     102,   102,   103,   104,   105,   105,   106,   107,   108,   108,
     109,   109,   109,   109,   110,   110,   110,   111,   111,   111,
     111,   111,   111,   111,   112,   113,   113,   113,   113,   113,
     113,   113,   113,   114,   114,   114,   114,   114,   115,   115,
     116,   116,   116,   116,   117,   118,   118,   118,   118,   118,
     118,   118,   119,   120,   121,   122,   122,   122,   122,   123,
     123,   123,   123,   123,   124,   124,   124,   125,   125,   125,
     125,   125,   126,   126,   127,   127,   128,   128,   129,   129,
     130,   130,   131,   131,   131,   131,   131,   131,   131,   131,
     132,   132,   132,   132,   132,   132,   133,   133,   134,   134,
     135,   135,   136,   136,   137,   137,   138
>>>>>>> alias finish v1
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       3,     5,    10,    11,     0,     3,     1,     4,     8,     0,
<<<<<<< HEAD
       3,     5,     2,     2,     7,     6,     4,     3,     1,     1,
       1,     1,     1,     1,     7,     0,     3,     4,     4,     0,
       3,     1,     2,     3,     3,     1,     3,     3,     3,     3,
       4,     3,     4,     2,     3,     3,     1,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       4,     4,     4,     6,     6,    10,     1,     2,     1,     2,
       1,     1,     1,     5,     8,     9,     2,     4,     2,     0,
       3,     5,     3,     2,     0,     3,     5,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     3,     2,     2,     4,
       4,     3,     1,     0,     3,     1,     3,     3,     1,     0,
       3,     8
=======
       3,     5,     2,     7,     6,     4,     3,     1,     1,     1,
       1,     1,     1,     7,     0,     3,     4,     4,     0,     3,
       1,     2,     3,     3,     1,     3,     3,     3,     3,     4,
       3,     4,     2,     3,     3,     1,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     4,
       4,     4,     6,     6,    10,     1,     2,     1,     2,     1,
       1,     1,     5,     8,     9,     2,     4,     2,     4,     0,
       3,     5,     3,     5,     2,     3,     4,     0,     3,     4,
       5,     5,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     3,     2,     2,     4,     4,     3,     1,     0,     3,
       1,     3,     3,     1,     0,     3,     8
>>>>>>> alias finish v1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, void *scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              , scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 22:
#line 256 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
<<<<<<< HEAD
#line 1748 "yacc_sql.tab.c"
=======
#line 1758 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 23:
#line 261 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
<<<<<<< HEAD
#line 1756 "yacc_sql.tab.c"
=======
#line 1766 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 24:
#line 266 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
<<<<<<< HEAD
#line 1764 "yacc_sql.tab.c"
=======
#line 1774 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 25:
#line 272 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
<<<<<<< HEAD
#line 1772 "yacc_sql.tab.c"
=======
#line 1782 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 26:
#line 278 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
<<<<<<< HEAD
#line 1780 "yacc_sql.tab.c"
=======
#line 1790 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 27:
#line 284 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
<<<<<<< HEAD
#line 1788 "yacc_sql.tab.c"
=======
#line 1798 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 28:
#line 290 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
<<<<<<< HEAD
#line 1797 "yacc_sql.tab.c"
=======
#line 1807 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 29:
#line 296 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
<<<<<<< HEAD
#line 1805 "yacc_sql.tab.c"
=======
#line 1815 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 30:
#line 302 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
<<<<<<< HEAD
#line 1814 "yacc_sql.tab.c"
=======
#line 1824 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 31:
#line 310 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
		}
<<<<<<< HEAD
#line 1823 "yacc_sql.tab.c"
=======
#line 1833 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 32:
#line 318 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;			//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, false, (yyvsp[-7].string), (yyvsp[-5].string));
		}
<<<<<<< HEAD
#line 1832 "yacc_sql.tab.c"
=======
#line 1842 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 33:
#line 323 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;			//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, true, (yyvsp[-7].string), (yyvsp[-5].string));
		}
<<<<<<< HEAD
#line 1841 "yacc_sql.tab.c"
=======
#line 1851 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 35:
#line 332 "yacc_sql.y"
                {
			/* Do Nothing */
		}
<<<<<<< HEAD
#line 1849 "yacc_sql.tab.c"
=======
#line 1859 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 36:
#line 338 "yacc_sql.y"
        {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	}
<<<<<<< HEAD
#line 1857 "yacc_sql.tab.c"
=======
#line 1867 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 37:
#line 345 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
<<<<<<< HEAD
#line 1866 "yacc_sql.tab.c"
=======
#line 1876 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 38:
#line 352 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
<<<<<<< HEAD
#line 1878 "yacc_sql.tab.c"
=======
#line 1888 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 40:
#line 362 "yacc_sql.y"
                                   {    }
<<<<<<< HEAD
#line 1884 "yacc_sql.tab.c"
=======
#line 1894 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 41:
#line 367 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number), FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
#line 1899 "yacc_sql.tab.c"
=======
#line 1909 "yacc_sql.tab.c"
>>>>>>> alias finish v1
    break;

  case 42:
#line 378 "yacc_sql.y"
<<<<<<< HEAD
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, CHARS, 4096, FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1910 "yacc_sql.tab.c"
    break;

  case 43:
#line 385 "yacc_sql.y"
=======
>>>>>>> alias finish v1
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4, FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
#line 1925 "yacc_sql.tab.c"
    break;

  case 44:
#line 396 "yacc_sql.y"
=======
#line 1924 "yacc_sql.tab.c"
    break;

  case 43:
#line 389 "yacc_sql.y"
>>>>>>> alias finish v1
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-5].number), (yyvsp[-3].number), FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
#line 1936 "yacc_sql.tab.c"
    break;

  case 45:
#line 403 "yacc_sql.y"
=======
#line 1935 "yacc_sql.tab.c"
    break;

  case 44:
#line 396 "yacc_sql.y"
>>>>>>> alias finish v1
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number), TRUE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
#line 1947 "yacc_sql.tab.c"
    break;

  case 46:
#line 410 "yacc_sql.y"
=======
#line 1946 "yacc_sql.tab.c"
    break;

  case 45:
#line 403 "yacc_sql.y"
>>>>>>> alias finish v1
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-2].number), 4, FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
#line 1958 "yacc_sql.tab.c"
    break;

  case 47:
#line 417 "yacc_sql.y"
=======
#line 1957 "yacc_sql.tab.c"
    break;

  case 46:
#line 410 "yacc_sql.y"
>>>>>>> alias finish v1
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, TRUE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
#line 1969 "yacc_sql.tab.c"
    break;

  case 48:
#line 425 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1975 "yacc_sql.tab.c"
    break;

  case 49:
#line 428 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1981 "yacc_sql.tab.c"
    break;

  case 50:
#line 429 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1987 "yacc_sql.tab.c"
    break;

  case 51:
#line 430 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1993 "yacc_sql.tab.c"
    break;

  case 52:
#line 431 "yacc_sql.y"
                                  { (yyval.number)=DATES; }
#line 1999 "yacc_sql.tab.c"
    break;

  case 53:
#line 435 "yacc_sql.y"
=======
#line 1968 "yacc_sql.tab.c"
    break;

  case 47:
#line 418 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1974 "yacc_sql.tab.c"
    break;

  case 48:
#line 421 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1980 "yacc_sql.tab.c"
    break;

  case 49:
#line 422 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1986 "yacc_sql.tab.c"
    break;

  case 50:
#line 423 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1992 "yacc_sql.tab.c"
    break;

  case 51:
#line 424 "yacc_sql.y"
                                  { (yyval.number)=DATES; }
#line 1998 "yacc_sql.tab.c"
    break;

  case 52:
#line 428 "yacc_sql.y"
>>>>>>> alias finish v1
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
<<<<<<< HEAD
#line 2008 "yacc_sql.tab.c"
    break;

  case 54:
#line 444 "yacc_sql.y"
=======
#line 2007 "yacc_sql.tab.c"
    break;

  case 53:
#line 437 "yacc_sql.y"
>>>>>>> alias finish v1
                {
			CONTEXT->ssql->flag=SCF_INSERT;		//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
    }
<<<<<<< HEAD
#line 2017 "yacc_sql.tab.c"
    break;

  case 56:
#line 451 "yacc_sql.y"
                                                 {
			// Do Nothing
		}
#line 2025 "yacc_sql.tab.c"
    break;

  case 57:
#line 456 "yacc_sql.y"
=======
#line 2016 "yacc_sql.tab.c"
    break;

  case 55:
#line 444 "yacc_sql.y"
                                                 {
			// Do Nothing
		}
#line 2024 "yacc_sql.tab.c"
    break;

  case 56:
#line 449 "yacc_sql.y"
>>>>>>> alias finish v1
                {
			if (0 != inserts_append_data(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length)) {
				return -1;
			}
			//临时变量清零
			memset(CONTEXT->values, 0, sizeof(CONTEXT->values));
      CONTEXT->value_length=0;
		}
<<<<<<< HEAD
#line 2038 "yacc_sql.tab.c"
    break;

  case 58:
#line 467 "yacc_sql.y"
=======
#line 2037 "yacc_sql.tab.c"
    break;

  case 57:
#line 460 "yacc_sql.y"
>>>>>>> alias finish v1
    {
      Expr * expr = malloc(sizeof(Expr));
      ListExpr * lexp = malloc(sizeof(ListExpr));
      int v_length = (yyvsp[-1].cur_len) + 1;
      list_expr_init(lexp, &CONTEXT->values[CONTEXT->value_length - v_length], v_length);
      expr_init_list(expr, lexp);
      (yyval.exp7) = expr;
    }
<<<<<<< HEAD
#line 2051 "yacc_sql.tab.c"
    break;

  case 59:
#line 478 "yacc_sql.y"
               {
        (yyval.cur_len) = 0;
    }
#line 2059 "yacc_sql.tab.c"
    break;

  case 60:
#line 481 "yacc_sql.y"
=======
#line 2050 "yacc_sql.tab.c"
    break;

  case 58:
#line 471 "yacc_sql.y"
               {
        (yyval.cur_len) = 0;
    }
#line 2058 "yacc_sql.tab.c"
    break;

  case 59:
#line 474 "yacc_sql.y"
>>>>>>> alias finish v1
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	  }
<<<<<<< HEAD
#line 2068 "yacc_sql.tab.c"
    break;

  case 61:
#line 488 "yacc_sql.y"
               {
      (yyval.exp2) = (yyvsp[0].exp1);
    }
#line 2076 "yacc_sql.tab.c"
    break;

  case 62:
#line 491 "yacc_sql.y"
=======
#line 2067 "yacc_sql.tab.c"
    break;

  case 60:
#line 481 "yacc_sql.y"
               {
      (yyval.exp2) = (yyvsp[0].exp1);
    }
#line 2075 "yacc_sql.tab.c"
    break;

  case 61:
#line 484 "yacc_sql.y"
>>>>>>> alias finish v1
                     {
      Value * tmp_val = malloc(sizeof(Value));
      value_init_integer(tmp_val, -1);
      UnaryExpr * tmp_uexpr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(tmp_uexpr, tmp_val);
      Expr * tmp_expr = malloc(sizeof(Expr));
      expr_init_unary(tmp_expr, tmp_uexpr);

      Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, MUL_OP, tmp_expr, (yyvsp[0].exp1));
      binary_expr_set_minus(b_expr);
      expr_init_binary(expr, b_expr);
      (yyval.exp2) = expr;
    }
<<<<<<< HEAD
#line 2096 "yacc_sql.tab.c"
    break;

  case 63:
#line 506 "yacc_sql.y"
=======
#line 2095 "yacc_sql.tab.c"
    break;

  case 62:
#line 499 "yacc_sql.y"
>>>>>>> alias finish v1
                               {
      Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, MUL_OP, (yyvsp[-2].exp2), (yyvsp[0].exp1));
      expr_init_binary(expr, b_expr);
      (yyval.exp2) = expr;
    }
<<<<<<< HEAD
#line 2108 "yacc_sql.tab.c"
    break;

  case 64:
#line 513 "yacc_sql.y"
=======
#line 2107 "yacc_sql.tab.c"
    break;

  case 63:
#line 506 "yacc_sql.y"
>>>>>>> alias finish v1
                              {
    	Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, DIV_OP, (yyvsp[-2].exp2), (yyvsp[0].exp1));
      expr_init_binary(expr, b_expr);
      (yyval.exp2) = expr;
    }
<<<<<<< HEAD
#line 2120 "yacc_sql.tab.c"
    break;

  case 65:
#line 523 "yacc_sql.y"
             { (yyval.exp3) = (yyvsp[0].exp2); }
#line 2126 "yacc_sql.tab.c"
    break;

  case 66:
#line 524 "yacc_sql.y"
=======
#line 2119 "yacc_sql.tab.c"
    break;

  case 64:
#line 516 "yacc_sql.y"
             { (yyval.exp3) = (yyvsp[0].exp2); }
#line 2125 "yacc_sql.tab.c"
    break;

  case 65:
#line 517 "yacc_sql.y"
>>>>>>> alias finish v1
                            {
    	Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, ADD_OP, (yyvsp[-2].exp3), (yyvsp[0].exp2));
      expr_init_binary(expr, b_expr);
      (yyval.exp3) = expr;
    }
<<<<<<< HEAD
#line 2138 "yacc_sql.tab.c"
    break;

  case 67:
#line 531 "yacc_sql.y"
=======
#line 2137 "yacc_sql.tab.c"
    break;

  case 66:
#line 524 "yacc_sql.y"
>>>>>>> alias finish v1
                            {
    	Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, SUB_OP, (yyvsp[-2].exp3), (yyvsp[0].exp2));
      expr_init_binary(expr, b_expr);
      (yyval.exp3) = expr;
    }
<<<<<<< HEAD
#line 2150 "yacc_sql.tab.c"
    break;

  case 68:
#line 541 "yacc_sql.y"
=======
#line 2149 "yacc_sql.tab.c"
    break;

  case 67:
#line 534 "yacc_sql.y"
>>>>>>> alias finish v1
                           {
      Condition expr;
      condition_init(&expr, (yyvsp[-1].comp_op), (yyvsp[-2].exp3), (yyvsp[0].exp3));
      // condition_print(&expr, 0);
      CONTEXT->conditions[CONTEXT->condition_length++] = expr;
    }
<<<<<<< HEAD
#line 2161 "yacc_sql.tab.c"
    break;

  case 69:
#line 547 "yacc_sql.y"
=======
#line 2160 "yacc_sql.tab.c"
    break;

  case 68:
#line 540 "yacc_sql.y"
>>>>>>> alias finish v1
                             {
      Value value;
      value_init_null(&value);

      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(u_expr, &value);

    	Expr *expr = malloc(sizeof(Expr));
      expr_init_unary(expr, u_expr);

      Condition cond;
      condition_init(&cond, IS_NULL, (yyvsp[-2].exp3), expr);
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
<<<<<<< HEAD
#line 2180 "yacc_sql.tab.c"
    break;

  case 70:
#line 561 "yacc_sql.y"
=======
#line 2179 "yacc_sql.tab.c"
    break;

  case 69:
#line 554 "yacc_sql.y"
>>>>>>> alias finish v1
                                 {
      Value value;
      value_init_null(&value);

      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(u_expr, &value);

    	Expr *expr = malloc(sizeof(Expr));
      expr_init_unary(expr, u_expr);

      Condition cond;
      condition_init(&cond, IS_NOT_NULL, (yyvsp[-3].exp3), expr);
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
<<<<<<< HEAD
#line 2199 "yacc_sql.tab.c"
    break;

  case 71:
#line 575 "yacc_sql.y"
=======
#line 2198 "yacc_sql.tab.c"
    break;

  case 70:
#line 568 "yacc_sql.y"
>>>>>>> alias finish v1
                           {
      // TODO
      Condition cond;
      condition_init(&cond, IN_OP, (yyvsp[-2].exp3), (yyvsp[0].exp3));
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
<<<<<<< HEAD
#line 2210 "yacc_sql.tab.c"
    break;

  case 72:
#line 581 "yacc_sql.y"
=======
#line 2209 "yacc_sql.tab.c"
    break;

  case 71:
#line 574 "yacc_sql.y"
>>>>>>> alias finish v1
                               {
      // TODO
      Condition cond;
      condition_init(&cond, NOT_IN, (yyvsp[-3].exp3), (yyvsp[0].exp3));
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
<<<<<<< HEAD
#line 2221 "yacc_sql.tab.c"
    break;

  case 73:
#line 587 "yacc_sql.y"
=======
#line 2220 "yacc_sql.tab.c"
    break;

  case 72:
#line 580 "yacc_sql.y"
>>>>>>> alias finish v1
                      {
      // TODO
      Value * tmp_val = malloc(sizeof(Value));
      value_init_integer(tmp_val, 1);
      UnaryExpr * tmp_uexpr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(tmp_uexpr, tmp_val);
      Expr * tmp_expr = malloc(sizeof(Expr));
      expr_init_unary(tmp_expr, tmp_uexpr);

      Condition cond;
      condition_init(&cond, EXISTS_OP, tmp_expr, (yyvsp[0].exp3));
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
<<<<<<< HEAD
#line 2239 "yacc_sql.tab.c"
    break;

  case 74:
#line 600 "yacc_sql.y"
=======
#line 2238 "yacc_sql.tab.c"
    break;

  case 73:
#line 593 "yacc_sql.y"
>>>>>>> alias finish v1
                          {
      // TODO
      Value * tmp_val = malloc(sizeof(Value));
      value_init_integer(tmp_val, 1);
      UnaryExpr * tmp_uexpr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(tmp_uexpr, tmp_val);
      Expr * tmp_expr = malloc(sizeof(Expr));
      expr_init_unary(tmp_expr, tmp_uexpr);

      Condition cond;
      condition_init(&cond, NOT_EXISTS, tmp_expr, (yyvsp[0].exp3));
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
<<<<<<< HEAD
#line 2257 "yacc_sql.tab.c"
    break;

  case 75:
#line 616 "yacc_sql.y"
=======
#line 2256 "yacc_sql.tab.c"
    break;

  case 74:
#line 609 "yacc_sql.y"
>>>>>>> alias finish v1
                           {
      Condition expr;
      condition_init(&expr, (yyvsp[-1].comp_op), (yyvsp[-2].exp3), (yyvsp[0].exp3));
      CONTEXT->havings[CONTEXT->having_length++] = expr;
    }
<<<<<<< HEAD
#line 2267 "yacc_sql.tab.c"
    break;

  case 76:
#line 624 "yacc_sql.y"
=======
#line 2266 "yacc_sql.tab.c"
    break;

  case 75:
#line 617 "yacc_sql.y"
>>>>>>> alias finish v1
          {
    	Expr *expr = malloc(sizeof(Expr));
      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(u_expr, &CONTEXT->values[CONTEXT->value_length-1]);
      expr_init_unary(expr, u_expr);
      (yyval.exp1) = expr;
    }
<<<<<<< HEAD
#line 2279 "yacc_sql.tab.c"
    break;

  case 77:
#line 631 "yacc_sql.y"
=======
#line 2278 "yacc_sql.tab.c"
    break;

  case 76:
#line 624 "yacc_sql.y"
>>>>>>> alias finish v1
         {
    	Expr *expr = malloc(sizeof(Expr));
      RelAttr attr;
      relation_attr_init(&attr, NULL, (yyvsp[0].string));
      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_attr(u_expr, &attr);
      expr_init_unary(expr, u_expr);
      (yyval.exp1) = expr;
    }
<<<<<<< HEAD
#line 2293 "yacc_sql.tab.c"
    break;

  case 78:
#line 640 "yacc_sql.y"
=======
#line 2292 "yacc_sql.tab.c"
    break;

  case 77:
#line 633 "yacc_sql.y"
>>>>>>> alias finish v1
                {
    	Expr *expr = malloc(sizeof(Expr));
      RelAttr attr;
      relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_attr(u_expr, &attr);
      expr_init_unary(expr, u_expr);
      (yyval.exp1) = expr;
    }
<<<<<<< HEAD
#line 2307 "yacc_sql.tab.c"
    break;

  case 79:
#line 649 "yacc_sql.y"
=======
#line 2306 "yacc_sql.tab.c"
    break;

  case 78:
#line 642 "yacc_sql.y"
>>>>>>> alias finish v1
                             {
      expr_set_with_brace((yyvsp[-1].exp3));
      (yyval.exp1) = (yyvsp[-1].exp3);
    }
<<<<<<< HEAD
#line 2316 "yacc_sql.tab.c"
    break;

  case 80:
#line 653 "yacc_sql.y"
                {
      (yyval.exp1) = (yyvsp[0].exp4);
    }
#line 2324 "yacc_sql.tab.c"
    break;

  case 81:
#line 656 "yacc_sql.y"
                     {
      (yyval.exp1) = (yyvsp[0].exp5);
    }
#line 2332 "yacc_sql.tab.c"
    break;

  case 82:
#line 659 "yacc_sql.y"
                 {
       (yyval.exp1) = (yyvsp[0].exp6);
    }
#line 2340 "yacc_sql.tab.c"
    break;

  case 83:
#line 662 "yacc_sql.y"
                     {
      (yyval.exp1) = (yyvsp[0].exp7);
    }
#line 2348 "yacc_sql.tab.c"
    break;

  case 84:
#line 667 "yacc_sql.y"
             {
      CONTEXT->aggrfunctype = MAX;
    }
#line 2356 "yacc_sql.tab.c"
    break;

  case 85:
#line 670 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = MIN;
    }
#line 2364 "yacc_sql.tab.c"
    break;

  case 86:
#line 673 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = SUM;
    }
#line 2372 "yacc_sql.tab.c"
    break;

  case 87:
#line 676 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = AVG;
    }
#line 2380 "yacc_sql.tab.c"
    break;

  case 88:
#line 679 "yacc_sql.y"
                 {
      CONTEXT->aggrfunctype = COUNT;
    }
#line 2388 "yacc_sql.tab.c"
    break;

  case 89:
#line 686 "yacc_sql.y"
=======
#line 2315 "yacc_sql.tab.c"
    break;

  case 79:
#line 646 "yacc_sql.y"
                {
      (yyval.exp1) = (yyvsp[0].exp4);
    }
#line 2323 "yacc_sql.tab.c"
    break;

  case 80:
#line 649 "yacc_sql.y"
                     {
      (yyval.exp1) = (yyvsp[0].exp5);
    }
#line 2331 "yacc_sql.tab.c"
    break;

  case 81:
#line 652 "yacc_sql.y"
                 {
       (yyval.exp1) = (yyvsp[0].exp6);
    }
#line 2339 "yacc_sql.tab.c"
    break;

  case 82:
#line 655 "yacc_sql.y"
                     {
      (yyval.exp1) = (yyvsp[0].exp7);
    }
#line 2347 "yacc_sql.tab.c"
    break;

  case 83:
#line 660 "yacc_sql.y"
             {
      CONTEXT->aggrfunctype = MAX;
    }
#line 2355 "yacc_sql.tab.c"
    break;

  case 84:
#line 663 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = MIN;
    }
#line 2363 "yacc_sql.tab.c"
    break;

  case 85:
#line 666 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = SUM;
    }
#line 2371 "yacc_sql.tab.c"
    break;

  case 86:
#line 669 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = AVG;
    }
#line 2379 "yacc_sql.tab.c"
    break;

  case 87:
#line 672 "yacc_sql.y"
                 {
      CONTEXT->aggrfunctype = COUNT;
    }
#line 2387 "yacc_sql.tab.c"
    break;

  case 88:
#line 679 "yacc_sql.y"
>>>>>>> alias finish v1
    {
      AggrFuncExpr* afexpr = malloc(sizeof(AggrFuncExpr));
      aggr_func_expr_init(afexpr, CONTEXT->aggrfunctype, (yyvsp[-1].exp3));
      Expr* expr = malloc(sizeof(Expr));
      expr_init_aggr_func(expr, afexpr);
      (yyval.exp5) = expr;
    }
<<<<<<< HEAD
#line 2400 "yacc_sql.tab.c"
    break;

  case 90:
#line 694 "yacc_sql.y"
=======
#line 2399 "yacc_sql.tab.c"
    break;

  case 89:
#line 687 "yacc_sql.y"
>>>>>>> alias finish v1
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
      (yyval.exp5) = expr;
    }
<<<<<<< HEAD
#line 2423 "yacc_sql.tab.c"
    break;

  case 91:
#line 716 "yacc_sql.y"
=======
#line 2422 "yacc_sql.tab.c"
    break;

  case 90:
#line 709 "yacc_sql.y"
>>>>>>> alias finish v1
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 0);
      func_expr_init_params(fexpr, (yyvsp[-1].exp3), NULL);
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      (yyval.exp4) = expr;
    }
<<<<<<< HEAD
#line 2436 "yacc_sql.tab.c"
    break;

  case 92:
#line 726 "yacc_sql.y"
=======
#line 2435 "yacc_sql.tab.c"
    break;

  case 91:
#line 719 "yacc_sql.y"
>>>>>>> alias finish v1
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 1);
      func_expr_init_params(fexpr, (yyvsp[-1].exp3), NULL);
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      (yyval.exp4) = expr;
    }
<<<<<<< HEAD
#line 2449 "yacc_sql.tab.c"
    break;

  case 93:
#line 736 "yacc_sql.y"
=======
#line 2448 "yacc_sql.tab.c"
    break;

  case 92:
#line 729 "yacc_sql.y"
>>>>>>> alias finish v1
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 1);
      func_expr_init_params(fexpr, (yyvsp[-3].exp3), (yyvsp[-1].exp3));
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      (yyval.exp4) = expr;
    }
<<<<<<< HEAD
#line 2462 "yacc_sql.tab.c"
    break;

  case 94:
#line 746 "yacc_sql.y"
=======
#line 2461 "yacc_sql.tab.c"
    break;

  case 93:
#line 739 "yacc_sql.y"
>>>>>>> alias finish v1
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 2);
      func_expr_init_params(fexpr, (yyvsp[-3].exp3), (yyvsp[-1].exp3));
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      (yyval.exp4) = expr;
    }
<<<<<<< HEAD
#line 2475 "yacc_sql.tab.c"
    break;

  case 95:
#line 757 "yacc_sql.y"
=======
#line 2474 "yacc_sql.tab.c"
    break;

  case 94:
#line 750 "yacc_sql.y"
>>>>>>> alias finish v1
                                                                                          {
      // printf("THE SUBQUERY has %d projects %d froms %d inner_join_conditions %d conditions %d groupbys %d havings %d orderbys\n", $3, $5->from_len, $5->inner_join_conditions_len, $6, $7, $8, $9);

      Selects * sub_select = (Selects *)malloc(sizeof(Selects));
      memset(sub_select, 0 ,sizeof(Selects));

			selects_append_projects(sub_select,  &CONTEXT->projects[CONTEXT->project_length - (yyvsp[-7].cur_len)], (yyvsp[-7].cur_len));
    
      size_t from_len = (yyvsp[-5].from_info)->from_len;
      size_t inner_join_conditions_len = (yyvsp[-5].from_info)->inner_join_conditions_len;
			selects_append_froms(sub_select,  &CONTEXT->froms[CONTEXT->from_length - from_len], from_len);

      size_t all_condition_len = (yyvsp[-4].cur_len) + inner_join_conditions_len;
			selects_append_conditions(sub_select, &CONTEXT->conditions[CONTEXT->condition_length - all_condition_len], all_condition_len);

			selects_append_groupbys(sub_select, &CONTEXT->groupbys[CONTEXT->groupby_length - (yyvsp[-3].cur_len)], (yyvsp[-3].cur_len));

			selects_append_havings(sub_select, &CONTEXT->havings[CONTEXT->having_length - (yyvsp[-2].cur_len)], (yyvsp[-2].cur_len));

			selects_append_orderbys(sub_select, &CONTEXT->orderbys[CONTEXT->orderby_length - (yyvsp[-1].cur_len)], (yyvsp[-1].cur_len));

			//CONTEXT->ssql->flag=SCF_SELECT;//"select";

			CONTEXT->orderby_length -= (yyvsp[-1].cur_len);
      CONTEXT->having_length -= (yyvsp[-2].cur_len);
			CONTEXT->groupby_length -= (yyvsp[-3].cur_len);
			CONTEXT->condition_length -= all_condition_len;
      CONTEXT->from_length -= from_len;
      CONTEXT->project_length -= (yyvsp[-7].cur_len);
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;

      // TODO cons expr
      SubQueryExpr * s_expr = malloc(sizeof(SubQueryExpr));
      sub_query_expr_init(s_expr, sub_select);
      Expr* expr = malloc(sizeof(Expr));
      expr_init_sub_query(expr, s_expr);
      (yyval.exp6) = expr;
    }
<<<<<<< HEAD
#line 2519 "yacc_sql.tab.c"
    break;

  case 96:
#line 799 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 2527 "yacc_sql.tab.c"
    break;

  case 97:
#line 802 "yacc_sql.y"
               {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], -((yyvsp[0].number)));
		}
#line 2535 "yacc_sql.tab.c"
    break;

  case 98:
#line 805 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 2543 "yacc_sql.tab.c"
    break;

  case 99:
#line 808 "yacc_sql.y"
              {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], -((yyvsp[0].floats)));
		}
#line 2551 "yacc_sql.tab.c"
    break;

  case 100:
#line 811 "yacc_sql.y"
=======
#line 2518 "yacc_sql.tab.c"
    break;

  case 95:
#line 792 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 2526 "yacc_sql.tab.c"
    break;

  case 96:
#line 795 "yacc_sql.y"
               {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], -((yyvsp[0].number)));
		}
#line 2534 "yacc_sql.tab.c"
    break;

  case 97:
#line 798 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 2542 "yacc_sql.tab.c"
    break;

  case 98:
#line 801 "yacc_sql.y"
              {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], -((yyvsp[0].floats)));
		}
#line 2550 "yacc_sql.tab.c"
    break;

  case 99:
#line 804 "yacc_sql.y"
>>>>>>> alias finish v1
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
<<<<<<< HEAD
#line 2560 "yacc_sql.tab.c"
    break;

  case 101:
#line 815 "yacc_sql.y"
=======
#line 2559 "yacc_sql.tab.c"
    break;

  case 100:
#line 808 "yacc_sql.y"
>>>>>>> alias finish v1
                          {
			int p1 = find((yyvsp[0].string),1,"-");
			int p2 = find((yyvsp[0].string),p1+1,"-");
			char *y = substr((yyvsp[0].string),1,p1-1);							// year
			char *m = substr((yyvsp[0].string),p1+1,p2-1);						// month
			char *d = substr((yyvsp[0].string),p2+1,strlen((yyvsp[0].string))-2);		// day
			if (0 != value_init_date(&CONTEXT->values[CONTEXT->value_length++], y, m, d)){
				return -1;
			}
		}
<<<<<<< HEAD
#line 2575 "yacc_sql.tab.c"
    break;

  case 102:
#line 825 "yacc_sql.y"
                {
      value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    }
#line 2583 "yacc_sql.tab.c"
    break;

  case 103:
#line 832 "yacc_sql.y"
=======
#line 2574 "yacc_sql.tab.c"
    break;

  case 101:
#line 818 "yacc_sql.y"
                {
      value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    }
#line 2582 "yacc_sql.tab.c"
    break;

  case 102:
#line 825 "yacc_sql.y"
>>>>>>> alias finish v1
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
<<<<<<< HEAD
#line 2595 "yacc_sql.tab.c"
    break;

  case 104:
#line 842 "yacc_sql.y"
=======
#line 2594 "yacc_sql.tab.c"
    break;

  case 103:
#line 835 "yacc_sql.y"
>>>>>>> alias finish v1
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
<<<<<<< HEAD
#line 2607 "yacc_sql.tab.c"
    break;

  case 105:
#line 852 "yacc_sql.y"
=======
#line 2606 "yacc_sql.tab.c"
    break;

  case 104:
#line 845 "yacc_sql.y"
>>>>>>> alias finish v1
                {
      // printf("THE QUERY has %d projects %d froms %d inner_join_conditions %d conditions %d groupbys %d havings %d orderbys\n\n", $2, $4->from_len, $4->inner_join_conditions_len, $5, $6, $7, $8);

			selects_append_projects(&CONTEXT->ssql->sstr.selection, CONTEXT->projects, CONTEXT->project_length);

			selects_append_froms(&CONTEXT->ssql->sstr.selection, CONTEXT->froms, CONTEXT->from_length);

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			selects_append_orderbys(&CONTEXT->ssql->sstr.selection, CONTEXT->orderbys, CONTEXT->orderby_length);

			selects_append_groupbys(&CONTEXT->ssql->sstr.selection, CONTEXT->groupbys, CONTEXT->groupby_length);

			selects_append_havings(&CONTEXT->ssql->sstr.selection, CONTEXT->havings, CONTEXT->having_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
      CONTEXT->having_length=0;
			CONTEXT->groupby_length=0;
			CONTEXT->orderby_length=0;
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
      CONTEXT->project_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
<<<<<<< HEAD
#line 2640 "yacc_sql.tab.c"
    break;

  case 106:
#line 883 "yacc_sql.y"
=======
#line 2639 "yacc_sql.tab.c"
    break;

  case 105:
#line 876 "yacc_sql.y"
>>>>>>> alias finish v1
                   {  
			ProjectCol project_col;
			projectcol_init_star(&project_col, NULL);
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
		}
<<<<<<< HEAD
#line 2651 "yacc_sql.tab.c"
    break;

  case 107:
#line 890 "yacc_sql.y"
=======
#line 2650 "yacc_sql.tab.c"
    break;

  case 106:
#line 883 "yacc_sql.y"
>>>>>>> alias finish v1
                         {
      ProjectCol project_col;
			projectcol_init_star(&project_col, (yyvsp[-3].string));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
<<<<<<< HEAD
#line 2662 "yacc_sql.tab.c"
    break;

  case 108:
#line 897 "yacc_sql.y"
=======
#line 2661 "yacc_sql.tab.c"
    break;

  case 107:
#line 890 "yacc_sql.y"
>>>>>>> alias finish v1
                      {
      ProjectCol project_col;
      projectcol_init_expr(&project_col, (yyvsp[-1].exp3));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
<<<<<<< HEAD
#line 2673 "yacc_sql.tab.c"
    break;

  case 109:
#line 905 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2681 "yacc_sql.tab.c"
    break;

  case 110:
#line 909 "yacc_sql.y"
=======
#line 2672 "yacc_sql.tab.c"
    break;

  case 108:
#line 897 "yacc_sql.y"
                            {
      ProjectCol project_col;
      projectcol_init_expr(&project_col, (yyvsp[-3].exp3));
      expr_init_alias((yyvsp[-3].exp3), (yyvsp[-1].string));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2684 "yacc_sql.tab.c"
    break;

  case 109:
#line 906 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2692 "yacc_sql.tab.c"
    break;

  case 110:
#line 910 "yacc_sql.y"
>>>>>>> alias finish v1
                         {  
			ProjectCol project_col;
			projectcol_init_star(&project_col, NULL);
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
		}
<<<<<<< HEAD
#line 2692 "yacc_sql.tab.c"
    break;

  case 111:
#line 916 "yacc_sql.y"
=======
#line 2703 "yacc_sql.tab.c"
    break;

  case 111:
#line 917 "yacc_sql.y"
>>>>>>> alias finish v1
                               {
      ProjectCol project_col;
			projectcol_init_star(&project_col, (yyvsp[-3].string));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
<<<<<<< HEAD
#line 2703 "yacc_sql.tab.c"
    break;

  case 112:
#line 923 "yacc_sql.y"
=======
#line 2714 "yacc_sql.tab.c"
    break;

  case 112:
#line 924 "yacc_sql.y"
>>>>>>> alias finish v1
                            {
      ProjectCol project_col;
      projectcol_init_expr(&project_col, (yyvsp[-1].exp3));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
<<<<<<< HEAD
#line 2714 "yacc_sql.tab.c"
    break;

  case 113:
#line 932 "yacc_sql.y"
=======
#line 2725 "yacc_sql.tab.c"
    break;

  case 113:
#line 931 "yacc_sql.y"
                                  {
      ProjectCol project_col;
      projectcol_init_expr(&project_col, (yyvsp[-3].exp3));
      expr_init_alias((yyvsp[-3].exp3), (yyvsp[-1].string));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2737 "yacc_sql.tab.c"
    break;

  case 114:
#line 941 "yacc_sql.y"
>>>>>>> alias finish v1
                {
      Relation rel;
      relation_from_init(&rel, (yyvsp[-1].string), NULL);
			CONTEXT->froms[CONTEXT->from_length++]=rel;
      (yyval.from_info) = (yyvsp[0].from_info);
      (yyval.from_info)->from_len++;
    }
<<<<<<< HEAD
#line 2724 "yacc_sql.tab.c"
    break;

  case 114:
#line 940 "yacc_sql.y"
=======
#line 2749 "yacc_sql.tab.c"
    break;

  case 115:
#line 948 "yacc_sql.y"
                    {
      Relation rel;
      relation_from_init(&rel, (yyvsp[-2].string), (yyvsp[-1].string));
			CONTEXT->froms[CONTEXT->from_length++]=rel;
      (yyval.from_info) = (yyvsp[0].from_info);
      (yyval.from_info)->from_len++;
    }
#line 2761 "yacc_sql.tab.c"
    break;

  case 116:
#line 955 "yacc_sql.y"
                       {
      Relation rel;
      relation_from_init(&rel, (yyvsp[-3].string), (yyvsp[-1].string));
			CONTEXT->froms[CONTEXT->from_length++]=rel;
      (yyval.from_info) = (yyvsp[0].from_info);
      (yyval.from_info)->from_len++;
    }
#line 2773 "yacc_sql.tab.c"
    break;

  case 117:
#line 965 "yacc_sql.y"
>>>>>>> alias finish v1
                {
      // new FromInfo
      (yyval.from_info) = (FromInfo*)malloc(sizeof(FromInfo));
      (yyval.from_info)->from_len = 0;
      (yyval.from_info)->inner_join_conditions_len = 0;
    }
<<<<<<< HEAD
#line 2735 "yacc_sql.tab.c"
    break;

  case 115:
#line 946 "yacc_sql.y"
=======
#line 2784 "yacc_sql.tab.c"
    break;

  case 118:
#line 971 "yacc_sql.y"
>>>>>>> alias finish v1
                        {	
        Relation rel;
        relation_from_init(&rel, (yyvsp[-1].string), NULL);
        CONTEXT->froms[CONTEXT->from_length++]=rel;
        (yyval.from_info) = (yyvsp[0].from_info);
        (yyval.from_info)->from_len++;
		  }
<<<<<<< HEAD
#line 2745 "yacc_sql.tab.c"
    break;

  case 116:
#line 951 "yacc_sql.y"
=======
#line 2796 "yacc_sql.tab.c"
    break;

  case 119:
#line 978 "yacc_sql.y"
                          {
      Relation rel;
      relation_from_init(&rel, (yyvsp[-2].string), (yyvsp[-1].string));
			CONTEXT->froms[CONTEXT->from_length++]=rel;
      (yyval.from_info) = (yyvsp[0].from_info);
      (yyval.from_info)->from_len++;
    }
#line 2808 "yacc_sql.tab.c"
    break;

  case 120:
#line 985 "yacc_sql.y"
                             {
      Relation rel;
      relation_from_init(&rel, (yyvsp[-3].string), (yyvsp[-1].string));
			CONTEXT->froms[CONTEXT->from_length++]=rel;
      (yyval.from_info) = (yyvsp[0].from_info);
      (yyval.from_info)->from_len++;
    }
#line 2820 "yacc_sql.tab.c"
    break;

  case 121:
#line 992 "yacc_sql.y"
>>>>>>> alias finish v1
                                                  {
      Relation rel;
      relation_from_init(&rel, (yyvsp[-2].string), NULL);
        CONTEXT->froms[CONTEXT->from_length++]=rel;
        (yyval.from_info) = (yyvsp[0].from_info);
        (yyval.from_info)->from_len++;
        (yyval.from_info)->inner_join_conditions_len += (yyvsp[-1].cur_len);
    }
<<<<<<< HEAD
#line 2756 "yacc_sql.tab.c"
    break;

  case 117:
#line 959 "yacc_sql.y"
                    {
    (yyval.cur_len) = 0;
  }
#line 2764 "yacc_sql.tab.c"
    break;

  case 118:
#line 962 "yacc_sql.y"
                                     {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 2772 "yacc_sql.tab.c"
    break;

  case 119:
#line 967 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2780 "yacc_sql.tab.c"
    break;

  case 120:
#line 970 "yacc_sql.y"
=======
#line 2833 "yacc_sql.tab.c"
    break;

  case 122:
#line 1002 "yacc_sql.y"
                    {
    (yyval.cur_len) = 0;
  }
#line 2841 "yacc_sql.tab.c"
    break;

  case 123:
#line 1005 "yacc_sql.y"
                                     {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 2849 "yacc_sql.tab.c"
    break;

  case 124:
#line 1010 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2857 "yacc_sql.tab.c"
    break;

  case 125:
#line 1013 "yacc_sql.y"
>>>>>>> alias finish v1
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
			}
<<<<<<< HEAD
#line 2789 "yacc_sql.tab.c"
    break;

  case 121:
#line 976 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2797 "yacc_sql.tab.c"
    break;

  case 122:
#line 979 "yacc_sql.y"
=======
#line 2866 "yacc_sql.tab.c"
    break;

  case 126:
#line 1019 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2874 "yacc_sql.tab.c"
    break;

  case 127:
#line 1022 "yacc_sql.y"
>>>>>>> alias finish v1
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
			}
<<<<<<< HEAD
#line 2806 "yacc_sql.tab.c"
    break;

  case 123:
#line 985 "yacc_sql.y"
                 { 
      (yyval.cur_len) = 0;
    }
#line 2814 "yacc_sql.tab.c"
    break;

  case 124:
#line 988 "yacc_sql.y"
                                                    {	
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2822 "yacc_sql.tab.c"
    break;

  case 125:
#line 993 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2830 "yacc_sql.tab.c"
    break;

  case 126:
#line 996 "yacc_sql.y"
                                                 {
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2838 "yacc_sql.tab.c"
    break;

  case 127:
#line 1003 "yacc_sql.y"
             { (yyval.comp_op) = EQUAL_TO; }
#line 2844 "yacc_sql.tab.c"
    break;

  case 128:
#line 1004 "yacc_sql.y"
         { (yyval.comp_op) = LESS_THAN; }
#line 2850 "yacc_sql.tab.c"
    break;

  case 129:
#line 1005 "yacc_sql.y"
         { (yyval.comp_op) = GREAT_THAN; }
#line 2856 "yacc_sql.tab.c"
    break;

  case 130:
#line 1006 "yacc_sql.y"
         { (yyval.comp_op) = LESS_EQUAL; }
#line 2862 "yacc_sql.tab.c"
    break;

  case 131:
#line 1007 "yacc_sql.y"
         { (yyval.comp_op) = GREAT_EQUAL; }
#line 2868 "yacc_sql.tab.c"
    break;

  case 132:
#line 1008 "yacc_sql.y"
         { (yyval.comp_op) = NOT_EQUAL; }
#line 2874 "yacc_sql.tab.c"
    break;

  case 133:
#line 1009 "yacc_sql.y"
           { (yyval.comp_op) = LIKE_OP; }
#line 2880 "yacc_sql.tab.c"
    break;

  case 134:
#line 1010 "yacc_sql.y"
               { (yyval.comp_op) = NOT_LIKE_OP; }
#line 2886 "yacc_sql.tab.c"
    break;

  case 135:
#line 1014 "yacc_sql.y"
=======
#line 2883 "yacc_sql.tab.c"
    break;

  case 128:
#line 1028 "yacc_sql.y"
                 { 
      (yyval.cur_len) = 0;
    }
#line 2891 "yacc_sql.tab.c"
    break;

  case 129:
#line 1031 "yacc_sql.y"
                                                    {	
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2899 "yacc_sql.tab.c"
    break;

  case 130:
#line 1036 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2907 "yacc_sql.tab.c"
    break;

  case 131:
#line 1039 "yacc_sql.y"
                                                 {
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2915 "yacc_sql.tab.c"
    break;

  case 132:
#line 1046 "yacc_sql.y"
             { (yyval.comp_op) = EQUAL_TO; }
#line 2921 "yacc_sql.tab.c"
    break;

  case 133:
#line 1047 "yacc_sql.y"
         { (yyval.comp_op) = LESS_THAN; }
#line 2927 "yacc_sql.tab.c"
    break;

  case 134:
#line 1048 "yacc_sql.y"
         { (yyval.comp_op) = GREAT_THAN; }
#line 2933 "yacc_sql.tab.c"
    break;

  case 135:
#line 1049 "yacc_sql.y"
         { (yyval.comp_op) = LESS_EQUAL; }
#line 2939 "yacc_sql.tab.c"
    break;

  case 136:
#line 1050 "yacc_sql.y"
         { (yyval.comp_op) = GREAT_EQUAL; }
#line 2945 "yacc_sql.tab.c"
    break;

  case 137:
#line 1051 "yacc_sql.y"
         { (yyval.comp_op) = NOT_EQUAL; }
#line 2951 "yacc_sql.tab.c"
    break;

  case 138:
#line 1052 "yacc_sql.y"
           { (yyval.comp_op) = LIKE_OP; }
#line 2957 "yacc_sql.tab.c"
    break;

  case 139:
#line 1053 "yacc_sql.y"
               { (yyval.comp_op) = NOT_LIKE_OP; }
#line 2963 "yacc_sql.tab.c"
    break;

  case 140:
#line 1057 "yacc_sql.y"
>>>>>>> alias finish v1
        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
<<<<<<< HEAD
#line 2898 "yacc_sql.tab.c"
    break;

  case 136:
#line 1023 "yacc_sql.y"
=======
#line 2975 "yacc_sql.tab.c"
    break;

  case 141:
#line 1066 "yacc_sql.y"
>>>>>>> alias finish v1
        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
<<<<<<< HEAD
#line 2910 "yacc_sql.tab.c"
    break;

  case 137:
#line 1032 "yacc_sql.y"
=======
#line 2987 "yacc_sql.tab.c"
    break;

  case 142:
#line 1075 "yacc_sql.y"
>>>>>>> alias finish v1
        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		OrderBy orderby;
		orderby_init(&orderby, FALSE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
<<<<<<< HEAD
#line 2922 "yacc_sql.tab.c"
    break;

  case 138:
#line 1041 "yacc_sql.y"
=======
#line 2999 "yacc_sql.tab.c"
    break;

  case 143:
#line 1084 "yacc_sql.y"
>>>>>>> alias finish v1
        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
<<<<<<< HEAD
#line 2934 "yacc_sql.tab.c"
    break;

  case 139:
#line 1050 "yacc_sql.y"
=======
#line 3011 "yacc_sql.tab.c"
    break;

  case 144:
#line 1093 "yacc_sql.y"
>>>>>>> alias finish v1
        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		OrderBy orderby;
		orderby_init(&orderby, FALSE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
<<<<<<< HEAD
#line 2946 "yacc_sql.tab.c"
    break;

  case 140:
#line 1059 "yacc_sql.y"
=======
#line 3023 "yacc_sql.tab.c"
    break;

  case 145:
#line 1102 "yacc_sql.y"
>>>>>>> alias finish v1
        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
<<<<<<< HEAD
#line 2958 "yacc_sql.tab.c"
    break;

  case 141:
#line 1069 "yacc_sql.y"
                {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 2966 "yacc_sql.tab.c"
    break;

  case 142:
#line 1073 "yacc_sql.y"
                {
    (yyval.cur_len) = 1;
	}
#line 2974 "yacc_sql.tab.c"
    break;

  case 143:
#line 1078 "yacc_sql.y"
                    {
   (yyval.cur_len) = 0;
  }
#line 2982 "yacc_sql.tab.c"
    break;

  case 144:
#line 1082 "yacc_sql.y"
                {
      (yyval.cur_len) = (yyvsp[0].cur_len);
	}
#line 2990 "yacc_sql.tab.c"
    break;

  case 145:
#line 1089 "yacc_sql.y"
=======
#line 3035 "yacc_sql.tab.c"
    break;

  case 146:
#line 1112 "yacc_sql.y"
                {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 3043 "yacc_sql.tab.c"
    break;

  case 147:
#line 1116 "yacc_sql.y"
                {
    (yyval.cur_len) = 1;
	}
#line 3051 "yacc_sql.tab.c"
    break;

  case 148:
#line 1121 "yacc_sql.y"
                    {
   (yyval.cur_len) = 0;
  }
#line 3059 "yacc_sql.tab.c"
    break;

  case 149:
#line 1125 "yacc_sql.y"
                {
      (yyval.cur_len) = (yyvsp[0].cur_len);
	}
#line 3067 "yacc_sql.tab.c"
    break;

  case 150:
#line 1132 "yacc_sql.y"
>>>>>>> alias finish v1
        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		CONTEXT->groupbys[CONTEXT->groupby_length++] = attr;
	}
<<<<<<< HEAD
#line 3000 "yacc_sql.tab.c"
    break;

  case 146:
#line 1096 "yacc_sql.y"
=======
#line 3077 "yacc_sql.tab.c"
    break;

  case 151:
#line 1139 "yacc_sql.y"
>>>>>>> alias finish v1
        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		CONTEXT->groupbys[CONTEXT->groupby_length++] = attr;
	}
<<<<<<< HEAD
#line 3010 "yacc_sql.tab.c"
    break;

  case 147:
#line 1105 "yacc_sql.y"
                {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 3018 "yacc_sql.tab.c"
    break;

  case 148:
#line 1109 "yacc_sql.y"
                {
    (yyval.cur_len) = 1;
	}
#line 3026 "yacc_sql.tab.c"
    break;

  case 149:
#line 1114 "yacc_sql.y"
                    {
    (yyval.cur_len) = 0;
  }
#line 3034 "yacc_sql.tab.c"
    break;

  case 150:
#line 1118 "yacc_sql.y"
                {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 3042 "yacc_sql.tab.c"
    break;

  case 151:
#line 1125 "yacc_sql.y"
=======
#line 3087 "yacc_sql.tab.c"
    break;

  case 152:
#line 1148 "yacc_sql.y"
                {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 3095 "yacc_sql.tab.c"
    break;

  case 153:
#line 1152 "yacc_sql.y"
                {
    (yyval.cur_len) = 1;
	}
#line 3103 "yacc_sql.tab.c"
    break;

  case 154:
#line 1157 "yacc_sql.y"
                    {
    (yyval.cur_len) = 0;
  }
#line 3111 "yacc_sql.tab.c"
    break;

  case 155:
#line 1161 "yacc_sql.y"
                {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 3119 "yacc_sql.tab.c"
    break;

  case 156:
#line 1168 "yacc_sql.y"
>>>>>>> alias finish v1
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
<<<<<<< HEAD
#line 3051 "yacc_sql.tab.c"
    break;


#line 3055 "yacc_sql.tab.c"
=======
#line 3128 "yacc_sql.tab.c"
    break;


#line 3132 "yacc_sql.tab.c"
>>>>>>> alias finish v1

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
<<<<<<< HEAD
#line 1130 "yacc_sql.y"
=======
#line 1173 "yacc_sql.y"
>>>>>>> alias finish v1

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
