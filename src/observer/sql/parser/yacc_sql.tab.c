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
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  Condition havings[MAX_NUM];
  OrderBy orderbys[MAX_NUM];
  GroupBy groupbys[MAX_NUM];
  CompOp comp;
	char id[MAX_NUM];
  AggrFuncType aggrfunctype;
} ParserContext;

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
  context->ssql->sstr.insertion.value_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 152 "yacc_sql.tab.c"

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
    TEXT = 294,
    EXIT = 295,
    DOT = 296,
    INTO = 297,
    VALUES = 298,
    FROM = 299,
    WHERE = 300,
    AND = 301,
    SET = 302,
    ON = 303,
    LOAD = 304,
    DATA = 305,
    INFILE = 306,
    NOT = 307,
    LIKE = 308,
    UNIQUE = 309,
    ADD = 310,
    SUB = 311,
    MUL = 312,
    DIV = 313,
    IS = 314,
    NULL_VALUE = 315,
    NULLABLE = 316,
    EQ = 317,
    LT = 318,
    GT = 319,
    LE = 320,
    GE = 321,
    NE = 322,
    LENGTH = 323,
    ROUND = 324,
    DATE_FORMAT = 325,
    NUMBER = 326,
    FLOAT = 327,
    ID = 328,
    PATH = 329,
    SSS = 330,
    STAR = 331,
    STRING_V = 332,
    DATE_STR = 333
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 158 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Condition *having1;
  struct _Value *value1;
  struct _UnaryExpr* uexp1;
  struct _Expr* exp1;
  struct _Expr* exp2;
  struct _Expr* exp3;
  struct _Expr* exp4;
  struct _Expr* exp5;
  char *string;
  int number;
  float floats;
	char *position;

#line 300 "yacc_sql.tab.c"

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
#define YYLAST   348

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  142
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  291

#define YYUNDEFTOK  2
#define YYMAXUTOK   333


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
      75,    76,    77,    78
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   198,   198,   200,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   225,   230,   235,   241,   247,   253,   259,   265,
     271,   278,   286,   291,   298,   300,   306,   313,   320,   329,
     331,   335,   346,   353,   364,   371,   378,   385,   394,   397,
     398,   399,   400,   403,   412,   418,   420,   424,   434,   436,
     442,   445,   460,   467,   477,   478,   485,   495,   501,   515,
     532,   540,   547,   556,   565,   569,   572,   578,   581,   584,
     587,   590,   596,   604,   626,   636,   646,   656,   668,   671,
     674,   677,   680,   684,   694,   700,   710,   720,   748,   754,
     760,   766,   769,   775,   781,   788,   790,   793,   797,   799,
     803,   805,   809,   811,   816,   819,   822,   824,   830,   831,
     832,   833,   834,   835,   836,   837,   840,   849,   858,   867,
     876,   885,   895,   899,   904,   906,   913,   920,   929,   933,
     938,   940,   947
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "TABLE",
  "TABLES", "INDEX", "INNER", "JOIN", "SELECT", "DESC", "ASC", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA",
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "DATE_T",
  "FLOAT_T", "ORDER", "GROUP", "BY", "HAVING", "AGGR_MAX", "AGGR_MIN",
  "AGGR_SUM", "AGGR_AVG", "AGGR_COUNT", "HELP", "TEXT", "EXIT", "DOT",
  "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON", "LOAD", "DATA",
  "INFILE", "NOT", "LIKE", "UNIQUE", "ADD", "SUB", "MUL", "DIV", "IS",
  "NULL_VALUE", "NULLABLE", "EQ", "LT", "GT", "LE", "GE", "NE", "LENGTH",
  "ROUND", "DATE_FORMAT", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR",
  "STRING_V", "DATE_STR", "$accept", "commands", "command", "exit", "help",
  "sync", "begin", "commit", "rollback", "drop_table", "show_tables",
  "desc_table", "show_index", "create_index", "id_list", "id",
  "drop_index", "create_table", "attr_def_list", "attr_def", "number",
  "type", "ID_get", "insert", "row_value_list", "row_value", "value_list",
  "mul_expr", "add_expr", "condition", "having_condition", "unary_expr",
  "aggr_func_type", "aggr_func_expr", "func_expr", "value", "delete",
  "update", "select", "select_attr", "attr_list", "rel_list",
  "inner_join_conditions", "where", "condition_list", "having",
  "having_condition_list", "comOp", "sort_unit", "sort_list",
  "opt_order_by", "groupby_unit", "groupby_list", "opt_group_by",
  "load_data", YY_NULLPTR
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
     325,   326,   327,   328,   329,   330,   331,   332,   333
};
# endif

#define YYPACT_NINF (-210)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -210,   274,  -210,    15,    23,   -17,   -41,    70,    90,    57,
      87,    64,   135,   137,   138,   142,   143,    97,  -210,  -210,
    -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,
    -210,  -210,  -210,  -210,  -210,  -210,  -210,    75,    77,   144,
      78,    81,   123,  -210,  -210,  -210,  -210,  -210,   151,  -210,
     136,   148,   153,  -210,  -210,   132,  -210,   159,  -210,   -43,
      29,  -210,   155,  -210,  -210,  -210,   156,   178,   179,   158,
    -210,   124,   126,   157,  -210,  -210,  -210,  -210,  -210,   152,
     186,   160,   133,   206,   207,   171,    -7,     8,  -210,  -210,
    -210,   123,   123,   123,   -48,    38,  -210,   197,   197,   123,
     123,  -210,    93,   140,  -210,  -210,   141,   172,   173,   154,
     162,   167,   168,   169,  -210,  -210,   170,  -210,  -210,  -210,
      26,   -14,    49,  -210,   159,   184,   159,    29,  -210,  -210,
     -43,   -43,   208,    46,    13,   241,   233,   123,   251,   193,
     214,  -210,   237,   150,   240,   187,  -210,  -210,   123,   123,
    -210,   -46,  -210,  -210,  -210,  -210,   252,   188,   173,  -210,
      61,   242,   183,   218,  -210,    61,   265,   167,   260,  -210,
    -210,  -210,  -210,  -210,   -16,   200,   262,    63,    69,   159,
     209,    13,   254,   263,   233,   284,   246,  -210,    40,  -210,
    -210,  -210,  -210,  -210,  -210,   123,   123,  -210,   173,   220,
     237,   291,   224,   243,  -210,  -210,   279,   200,  -210,  -210,
    -210,   256,  -210,   270,   272,    61,   287,   242,  -210,  -210,
     250,  -210,    67,   218,   308,   310,  -210,  -210,  -210,   301,
    -210,   200,   302,   279,   123,    13,   255,   293,   294,   263,
    -210,  -210,  -210,  -210,  -210,  -210,   -26,   279,   322,   307,
     218,  -210,    -1,   309,  -210,   258,   123,   326,  -210,   273,
    -210,  -210,  -210,   329,  -210,  -210,  -210,   261,   255,   295,
     314,  -210,   253,   292,  -210,  -210,  -210,    83,  -210,   264,
     258,   123,   123,  -210,  -210,  -210,  -210,  -210,    67,   292,
    -210
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
       0,     0,     0,    77,    78,    79,    80,    81,     0,    94,
       0,     0,     0,    88,    90,    72,    92,   101,    93,    64,
     101,    60,     0,    76,    75,    71,     0,     0,     0,     0,
      24,     0,     0,     0,    25,    26,    27,    23,    22,     0,
       0,     0,     0,     0,     0,    72,     0,     0,    88,    90,
      61,     0,     0,     0,     0,     0,    98,     0,     0,     0,
       0,   100,     0,     0,    30,    29,     0,     0,   110,     0,
       0,     0,     0,     0,    28,    37,     0,    74,    89,    91,
       0,     0,     0,    73,   101,    72,   101,   101,    63,    62,
      65,    66,     0,     0,   105,     0,     0,     0,     0,     0,
       0,    53,    39,     0,     0,     0,    84,    85,     0,     0,
      99,     0,   102,   104,    83,    82,     0,     0,   110,    31,
       0,    55,     0,   112,    95,     0,     0,     0,     0,    49,
      50,    52,    51,    42,    43,     0,     0,     0,     0,   101,
       0,   105,   134,    58,     0,     0,     0,   124,     0,   118,
     119,   120,   121,   122,   123,     0,     0,   111,   110,     0,
      39,     0,     0,     0,    47,    36,    34,     0,    86,    87,
     103,   108,   106,     0,   140,     0,     0,    55,    54,   125,
       0,    68,    67,   112,     0,     0,    40,    38,    48,     0,
      46,     0,     0,    34,     0,   105,     0,     0,   114,    58,
      57,    56,    69,   113,    96,   142,    41,    34,     0,     0,
     112,   107,   126,   133,   135,     0,     0,     0,    59,     0,
      45,    35,    32,     0,   109,   128,   129,     0,     0,   136,
     139,   141,     0,   116,    97,    44,    33,   127,   132,     0,
       0,     0,     0,   115,   130,   131,   137,   138,    70,   116,
     117
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,  -210,
    -210,  -210,  -210,  -210,  -209,  -116,  -210,  -210,   139,   174,
    -210,  -210,  -210,  -210,   125,   161,   101,    35,    -5,  -187,
      62,   -34,  -210,  -210,  -210,  -155,  -210,  -210,  -210,  -210,
     -59,  -173,  -210,  -154,  -147,  -210,    54,    74,  -210,    79,
    -210,  -210,    68,  -210,  -210
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,   232,   206,    30,    31,   168,   142,
     229,   174,   143,    32,   185,   161,   216,    59,   162,   163,
     273,    61,    62,    63,    64,    65,    33,    34,    35,    66,
      96,   158,   235,   138,   197,   257,   283,   195,   253,   254,
     214,   270,   271,   238,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      60,   101,    42,   202,   182,   183,   147,   148,   212,   223,
     198,   265,   266,   117,    90,    97,    43,    44,    45,    46,
      47,    37,   156,    38,   249,   123,   259,   123,   124,    40,
     179,    41,    67,    98,   157,   260,   203,    86,   261,    48,
     267,    99,   100,    49,   224,   204,   146,   250,    99,   100,
      95,    50,    51,    52,    53,    54,    55,    42,    56,    57,
     239,    58,   251,   128,   129,   150,   155,   152,   153,    39,
     149,    43,    44,    45,    46,    47,   243,    68,    69,   118,
     119,    99,   100,   208,    99,   100,   120,   121,   122,   209,
     127,   233,   220,    70,    48,   284,   285,   133,    49,    71,
     221,    99,   100,   264,    99,   100,    50,    51,    52,    53,
      54,   125,    42,    56,   126,   247,    58,    87,    99,   100,
     210,    49,    99,   100,    99,   100,    43,    44,    45,    46,
      47,    72,    53,    54,   130,   131,    56,    73,    74,    58,
      75,    76,    42,   177,   178,    77,    78,    79,    80,    48,
      81,    83,    82,    49,    84,    91,    43,    44,    45,    46,
      47,    50,    51,    52,    53,    54,    85,    92,    56,   132,
      42,    58,    93,    94,   102,   169,   170,   171,   172,    48,
      95,   104,   105,    49,    43,    44,    45,    46,    47,   173,
     222,    50,    51,    52,    53,    54,    85,   107,    56,   108,
     103,    58,   106,   110,   109,   111,   113,    87,   112,   114,
     115,    49,   116,   134,   135,   136,    42,   145,   137,    50,
      51,    52,    88,    89,    85,   151,    56,   139,   154,    58,
      43,    44,    45,    46,    47,   186,   187,   140,    99,   100,
     141,   144,   188,   123,   159,   189,   190,   191,   192,   193,
     194,   272,   160,    87,   164,   165,   166,    49,   167,   175,
     176,   181,   180,   184,   196,    50,    51,    52,    53,    54,
      85,   199,    56,   205,     2,    58,   288,   272,     3,     4,
     201,   207,   211,   213,   215,     5,     6,   218,     7,     8,
       9,    10,    11,   225,   227,   228,    12,    13,    14,   219,
     231,   236,   237,   230,   234,   186,   187,   240,    99,   100,
     242,   244,    15,   245,    16,   189,   190,   191,   192,   193,
     194,   246,   248,    17,   255,   262,   256,   263,   252,   274,
     268,   269,   276,   275,   277,   280,   279,   286,   282,   226,
     258,   200,   241,   290,   289,   217,   281,   278,   287
};

static const yytype_int16 yycheck[] =
{
       5,    60,    19,    19,   158,   160,    20,    21,   181,   196,
     165,    12,    13,    20,    48,    58,    33,    34,    35,    36,
      37,     6,     9,     8,   233,    73,    52,    73,    76,     6,
      76,     8,    73,    76,    21,    61,    52,    42,   247,    56,
      41,    55,    56,    60,   198,    61,    20,   234,    55,    56,
      21,    68,    69,    70,    71,    72,    73,    19,    75,    76,
     215,    78,   235,    97,    98,   124,    20,   126,   127,    54,
      21,    33,    34,    35,    36,    37,   223,     7,     8,    71,
      72,    55,    56,    20,    55,    56,    91,    92,    93,    20,
      95,   207,    52,     3,    56,    12,    13,   102,    60,    42,
      60,    55,    56,   250,    55,    56,    68,    69,    70,    71,
      72,    73,    19,    75,    76,   231,    78,    56,    55,    56,
     179,    60,    55,    56,    55,    56,    33,    34,    35,    36,
      37,    44,    71,    72,    99,   100,    75,    73,     3,    78,
       3,     3,    19,   148,   149,     3,     3,    50,    73,    56,
      73,    73,     8,    60,    73,    19,    33,    34,    35,    36,
      37,    68,    69,    70,    71,    72,    73,    19,    75,    76,
      19,    78,    19,    41,    19,    25,    26,    27,    28,    56,
      21,     3,     3,    60,    33,    34,    35,    36,    37,    39,
     195,    68,    69,    70,    71,    72,    73,    73,    75,    73,
      44,    78,    44,    51,    47,    19,    73,    56,    48,     3,
       3,    60,    41,    73,    73,    43,    19,    48,    45,    68,
      69,    70,    71,    72,    73,    41,    75,    73,    20,    78,
      33,    34,    35,    36,    37,    52,    53,    75,    55,    56,
      73,    73,    59,    73,     3,    62,    63,    64,    65,    66,
      67,   256,    19,    56,     3,    62,    42,    60,    21,    19,
      73,    73,    10,    21,    46,    68,    69,    70,    71,    72,
      73,     6,    75,    73,     0,    78,   281,   282,     4,     5,
      20,    19,    73,    29,    21,    11,    12,     3,    14,    15,
      16,    17,    18,    73,     3,    71,    22,    23,    24,    53,
      21,    31,    30,    60,    48,    52,    53,    20,    55,    56,
      60,     3,    38,     3,    40,    62,    63,    64,    65,    66,
      67,    20,    20,    49,    31,     3,    32,    20,    73,     3,
      21,    73,     3,    60,    73,    21,    41,    73,    46,   200,
     239,   167,   217,   289,   282,   184,   272,   268,   280
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    80,     0,     4,     5,    11,    12,    14,    15,    16,
      17,    18,    22,    23,    24,    38,    40,    49,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      95,    96,   102,   115,   116,   117,   133,     6,     8,    54,
       6,     8,    19,    33,    34,    35,    36,    37,    56,    60,
      68,    69,    70,    71,    72,    73,    75,    76,    78,   106,
     107,   110,   111,   112,   113,   114,   118,    73,     7,     8,
       3,    42,    44,    73,     3,     3,     3,     3,     3,    50,
      73,    73,     8,    73,    73,    73,   107,    56,    71,    72,
     110,    19,    19,    19,    41,    21,   119,    58,    76,    55,
      56,   119,    19,    44,     3,     3,    44,    73,    73,    47,
      51,    19,    48,    73,     3,     3,    41,    20,    71,    72,
     107,   107,   107,    73,    76,    73,    76,   107,   110,   110,
     106,   106,    76,   107,    73,    73,    43,    45,   122,    73,
      75,    73,    98,   101,    73,    48,    20,    20,    21,    21,
     119,    41,   119,   119,    20,    20,     9,    21,   120,     3,
      19,   104,   107,   108,     3,    62,    42,    21,    97,    25,
      26,    27,    28,    39,   100,    19,    73,   107,   107,    76,
      10,    73,   122,   114,    21,   103,    52,    53,    59,    62,
      63,    64,    65,    66,    67,   126,    46,   123,   114,     6,
      98,    20,    19,    52,    61,    73,    94,    19,    20,    20,
     119,    73,   120,    29,   129,    21,   105,   104,     3,    53,
      52,    60,   107,   108,   122,    73,    97,     3,    71,    99,
      60,    21,    93,    94,    48,   121,    31,    30,   132,   114,
      20,   103,    60,   123,     3,     3,    20,    94,    20,    93,
     108,   120,    73,   127,   128,    31,    32,   124,   105,    52,
      61,    93,     3,    20,   123,    12,    13,    41,    21,    73,
     130,   131,   107,   109,     3,    60,     3,    73,   128,    41,
      21,   126,    46,   125,    12,    13,    73,   131,   107,   109,
     125
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    79,    80,    80,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    92,    93,    93,    94,    95,    96,    97,
      97,    98,    98,    98,    98,    98,    98,    98,    99,   100,
     100,   100,   100,   101,   102,   103,   103,   104,   105,   105,
     106,   106,   106,   106,   107,   107,   107,   108,   108,   108,
     109,   110,   110,   110,   110,   110,   110,   111,   111,   111,
     111,   111,   112,   112,   113,   113,   113,   113,   114,   114,
     114,   114,   114,   114,   114,   115,   116,   117,   118,   118,
     118,   119,   119,   119,   119,   120,   120,   120,   121,   121,
     122,   122,   123,   123,   124,   124,   125,   125,   126,   126,
     126,   126,   126,   126,   126,   126,   127,   127,   127,   127,
     127,   127,   128,   128,   129,   129,   130,   130,   131,   131,
     132,   132,   133
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       3,     5,    10,    11,     0,     3,     1,     4,     8,     0,
       3,     5,     2,     2,     7,     6,     4,     3,     1,     1,
       1,     1,     1,     1,     7,     0,     3,     4,     0,     3,
       1,     2,     3,     3,     1,     3,     3,     3,     3,     4,
       3,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     4,     4,     4,     4,     6,     6,     1,     2,
       1,     2,     1,     1,     1,     5,     8,    10,     2,     4,
       2,     0,     3,     5,     3,     0,     3,     5,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     3,     2,     2,
       4,     4,     3,     1,     0,     3,     1,     3,     3,     1,
       0,     3,     8
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
#line 225 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1711 "yacc_sql.tab.c"
    break;

  case 23:
#line 230 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1719 "yacc_sql.tab.c"
    break;

  case 24:
#line 235 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1727 "yacc_sql.tab.c"
    break;

  case 25:
#line 241 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1735 "yacc_sql.tab.c"
    break;

  case 26:
#line 247 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1743 "yacc_sql.tab.c"
    break;

  case 27:
#line 253 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1751 "yacc_sql.tab.c"
    break;

  case 28:
#line 259 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1760 "yacc_sql.tab.c"
    break;

  case 29:
#line 265 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1768 "yacc_sql.tab.c"
    break;

  case 30:
#line 271 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1777 "yacc_sql.tab.c"
    break;

  case 31:
#line 279 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
		}
#line 1786 "yacc_sql.tab.c"
    break;

  case 32:
#line 287 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;			//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, false, (yyvsp[-7].string), (yyvsp[-5].string));
		}
#line 1795 "yacc_sql.tab.c"
    break;

  case 33:
#line 292 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;			//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, true, (yyvsp[-7].string), (yyvsp[-5].string));
		}
#line 1804 "yacc_sql.tab.c"
    break;

  case 35:
#line 301 "yacc_sql.y"
                {
			/* Do Nothing */
		}
#line 1812 "yacc_sql.tab.c"
    break;

  case 36:
#line 307 "yacc_sql.y"
        {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	}
#line 1820 "yacc_sql.tab.c"
    break;

  case 37:
#line 314 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1829 "yacc_sql.tab.c"
    break;

  case 38:
#line 321 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1841 "yacc_sql.tab.c"
    break;

  case 40:
#line 331 "yacc_sql.y"
                                   {    }
#line 1847 "yacc_sql.tab.c"
    break;

  case 41:
#line 336 "yacc_sql.y"
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
#line 1862 "yacc_sql.tab.c"
    break;

  case 42:
#line 347 "yacc_sql.y"
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, CHARS, 4096, FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1873 "yacc_sql.tab.c"
    break;

  case 43:
#line 354 "yacc_sql.y"
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
#line 1888 "yacc_sql.tab.c"
    break;

  case 44:
#line 365 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-5].number), (yyvsp[-3].number), FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1899 "yacc_sql.tab.c"
    break;

  case 45:
#line 372 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number), TRUE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1910 "yacc_sql.tab.c"
    break;

  case 46:
#line 379 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-2].number), 4, FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1921 "yacc_sql.tab.c"
    break;

  case 47:
#line 386 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, TRUE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1932 "yacc_sql.tab.c"
    break;

  case 48:
#line 394 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1938 "yacc_sql.tab.c"
    break;

  case 49:
#line 397 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1944 "yacc_sql.tab.c"
    break;

  case 50:
#line 398 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1950 "yacc_sql.tab.c"
    break;

  case 51:
#line 399 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1956 "yacc_sql.tab.c"
    break;

  case 52:
#line 400 "yacc_sql.y"
                                  { (yyval.number)=DATES; }
#line 1962 "yacc_sql.tab.c"
    break;

  case 53:
#line 404 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1971 "yacc_sql.tab.c"
    break;

  case 54:
#line 413 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_INSERT;		//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
    }
#line 1980 "yacc_sql.tab.c"
    break;

  case 56:
#line 420 "yacc_sql.y"
                                                 {
			// Do Nothing
		}
#line 1988 "yacc_sql.tab.c"
    break;

  case 57:
#line 425 "yacc_sql.y"
                {
			if (0 != inserts_append_data(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length)) {
				return -1;
			}
			//临时变量清零
			memset(CONTEXT->values, 0, sizeof(CONTEXT->values));
      CONTEXT->value_length=0;
		}
#line 2001 "yacc_sql.tab.c"
    break;

  case 59:
#line 436 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 2009 "yacc_sql.tab.c"
    break;

  case 60:
#line 442 "yacc_sql.y"
               {
      (yyval.exp2) = (yyvsp[0].exp1);
    }
#line 2017 "yacc_sql.tab.c"
    break;

  case 61:
#line 445 "yacc_sql.y"
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
#line 2037 "yacc_sql.tab.c"
    break;

  case 62:
#line 460 "yacc_sql.y"
                               {
      Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, MUL_OP, (yyvsp[-2].exp2), (yyvsp[0].exp1));
      expr_init_binary(expr, b_expr);
      (yyval.exp2) = expr;
    }
#line 2049 "yacc_sql.tab.c"
    break;

  case 63:
#line 467 "yacc_sql.y"
                              {
    	Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, DIV_OP, (yyvsp[-2].exp2), (yyvsp[0].exp1));
      expr_init_binary(expr, b_expr);
      (yyval.exp2) = expr;
    }
#line 2061 "yacc_sql.tab.c"
    break;

  case 64:
#line 477 "yacc_sql.y"
             { (yyval.exp3) = (yyvsp[0].exp2); }
#line 2067 "yacc_sql.tab.c"
    break;

  case 65:
#line 478 "yacc_sql.y"
                            {
    	Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, ADD_OP, (yyvsp[-2].exp3), (yyvsp[0].exp2));
      expr_init_binary(expr, b_expr);
      (yyval.exp3) = expr;
    }
#line 2079 "yacc_sql.tab.c"
    break;

  case 66:
#line 485 "yacc_sql.y"
                            {
    	Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, SUB_OP, (yyvsp[-2].exp3), (yyvsp[0].exp2));
      expr_init_binary(expr, b_expr);
      (yyval.exp3) = expr;
    }
#line 2091 "yacc_sql.tab.c"
    break;

  case 67:
#line 495 "yacc_sql.y"
                           {
      Condition expr;
      condition_init(&expr, CONTEXT->comp, (yyvsp[-2].exp3), (yyvsp[0].exp3));
      // condition_print(&expr, 0);
      CONTEXT->conditions[CONTEXT->condition_length++] = expr;
    }
#line 2102 "yacc_sql.tab.c"
    break;

  case 68:
#line 501 "yacc_sql.y"
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
#line 2121 "yacc_sql.tab.c"
    break;

  case 69:
#line 515 "yacc_sql.y"
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
#line 2140 "yacc_sql.tab.c"
    break;

  case 70:
#line 532 "yacc_sql.y"
                           {
      Condition expr;
      condition_init(&expr, CONTEXT->comp, (yyvsp[-2].exp3), (yyvsp[0].exp3));
      CONTEXT->havings[CONTEXT->having_length++] = expr;
    }
#line 2150 "yacc_sql.tab.c"
    break;

  case 71:
#line 540 "yacc_sql.y"
          {
    	Expr *expr = malloc(sizeof(Expr));
      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(u_expr, &CONTEXT->values[CONTEXT->value_length-1]);
      expr_init_unary(expr, u_expr);
      (yyval.exp1) = expr;
    }
#line 2162 "yacc_sql.tab.c"
    break;

  case 72:
#line 547 "yacc_sql.y"
         {
    	Expr *expr = malloc(sizeof(Expr));
      RelAttr attr;
      relation_attr_init(&attr, NULL, (yyvsp[0].string));
      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_attr(u_expr, &attr);
      expr_init_unary(expr, u_expr);
      (yyval.exp1) = expr;
    }
#line 2176 "yacc_sql.tab.c"
    break;

  case 73:
#line 556 "yacc_sql.y"
                {
    	Expr *expr = malloc(sizeof(Expr));
      RelAttr attr;
      relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_attr(u_expr, &attr);
      expr_init_unary(expr, u_expr);
      (yyval.exp1) = expr;
    }
#line 2190 "yacc_sql.tab.c"
    break;

  case 74:
#line 565 "yacc_sql.y"
                             {
      expr_set_with_brace((yyvsp[-1].exp3));
      (yyval.exp1) = (yyvsp[-1].exp3);
    }
#line 2199 "yacc_sql.tab.c"
    break;

  case 75:
#line 569 "yacc_sql.y"
                {
      (yyval.exp1) = (yyvsp[0].exp4);
    }
#line 2207 "yacc_sql.tab.c"
    break;

  case 76:
#line 572 "yacc_sql.y"
                     {
      (yyval.exp1) = (yyvsp[0].exp5);
    }
#line 2215 "yacc_sql.tab.c"
    break;

  case 77:
#line 578 "yacc_sql.y"
             {
      CONTEXT->aggrfunctype = MAX;
    }
#line 2223 "yacc_sql.tab.c"
    break;

  case 78:
#line 581 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = MIN;
    }
#line 2231 "yacc_sql.tab.c"
    break;

  case 79:
#line 584 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = SUM;
    }
#line 2239 "yacc_sql.tab.c"
    break;

  case 80:
#line 587 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = AVG;
    }
#line 2247 "yacc_sql.tab.c"
    break;

  case 81:
#line 590 "yacc_sql.y"
                 {
      CONTEXT->aggrfunctype = COUNT;
    }
#line 2255 "yacc_sql.tab.c"
    break;

  case 82:
#line 597 "yacc_sql.y"
    {
      AggrFuncExpr* afexpr = malloc(sizeof(AggrFuncExpr));
      aggr_func_expr_init(afexpr, CONTEXT->aggrfunctype, (yyvsp[-1].exp3));
      Expr* expr = malloc(sizeof(Expr));
      expr_init_aggr_func(expr, afexpr);
      (yyval.exp5) = expr;
    }
#line 2267 "yacc_sql.tab.c"
    break;

  case 83:
#line 605 "yacc_sql.y"
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
#line 2290 "yacc_sql.tab.c"
    break;

  case 84:
#line 627 "yacc_sql.y"
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 0);
      func_expr_init_params(fexpr, (yyvsp[-1].exp3), NULL);
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      (yyval.exp4) = expr;
    }
#line 2303 "yacc_sql.tab.c"
    break;

  case 85:
#line 637 "yacc_sql.y"
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 1);
      func_expr_init_params(fexpr, (yyvsp[-1].exp3), NULL);
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      (yyval.exp4) = expr;
    }
#line 2316 "yacc_sql.tab.c"
    break;

  case 86:
#line 647 "yacc_sql.y"
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 1);
      func_expr_init_params(fexpr, (yyvsp[-3].exp3), (yyvsp[-1].exp3));
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      (yyval.exp4) = expr;
    }
#line 2329 "yacc_sql.tab.c"
    break;

  case 87:
#line 657 "yacc_sql.y"
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 2);
      func_expr_init_params(fexpr, (yyvsp[-3].exp3), (yyvsp[-1].exp3));
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      (yyval.exp4) = expr;
    }
#line 2342 "yacc_sql.tab.c"
    break;

  case 88:
#line 668 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 2350 "yacc_sql.tab.c"
    break;

  case 89:
#line 671 "yacc_sql.y"
               {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], -((yyvsp[0].number)));
		}
#line 2358 "yacc_sql.tab.c"
    break;

  case 90:
#line 674 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 2366 "yacc_sql.tab.c"
    break;

  case 91:
#line 677 "yacc_sql.y"
              {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], -((yyvsp[0].floats)));
		}
#line 2374 "yacc_sql.tab.c"
    break;

  case 92:
#line 680 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 2383 "yacc_sql.tab.c"
    break;

  case 93:
#line 684 "yacc_sql.y"
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
#line 2398 "yacc_sql.tab.c"
    break;

  case 94:
#line 694 "yacc_sql.y"
                {
      value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    }
#line 2406 "yacc_sql.tab.c"
    break;

  case 95:
#line 701 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 2418 "yacc_sql.tab.c"
    break;

  case 96:
#line 711 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 2430 "yacc_sql.tab.c"
    break;

  case 97:
#line 721 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-6].string));

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
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
#line 2459 "yacc_sql.tab.c"
    break;

  case 98:
#line 748 "yacc_sql.y"
                   {  
			ProjectCol project_col;
			projectcol_init_star(&project_col, NULL);
			selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
		}
#line 2469 "yacc_sql.tab.c"
    break;

  case 99:
#line 754 "yacc_sql.y"
                         {
      ProjectCol project_col;
			projectcol_init_star(&project_col, (yyvsp[-3].string));
			selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
    }
#line 2479 "yacc_sql.tab.c"
    break;

  case 100:
#line 760 "yacc_sql.y"
                      {
      ProjectCol project_col;
      projectcol_init_expr(&project_col, (yyvsp[-1].exp3));
      selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
    }
#line 2489 "yacc_sql.tab.c"
    break;

  case 102:
#line 769 "yacc_sql.y"
                         {  
			ProjectCol project_col;
			projectcol_init_star(&project_col, NULL);
			selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
		}
#line 2499 "yacc_sql.tab.c"
    break;

  case 103:
#line 775 "yacc_sql.y"
                               {
      ProjectCol project_col;
			projectcol_init_star(&project_col, (yyvsp[-3].string));
			selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
    }
#line 2509 "yacc_sql.tab.c"
    break;

  case 104:
#line 781 "yacc_sql.y"
                            {
      ProjectCol project_col;
      projectcol_init_expr(&project_col, (yyvsp[-1].exp3));
      selects_append_projects(&CONTEXT->ssql->sstr.selection, &project_col);
    }
#line 2519 "yacc_sql.tab.c"
    break;

  case 106:
#line 790 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2527 "yacc_sql.tab.c"
    break;

  case 107:
#line 793 "yacc_sql.y"
                                                      {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
	}
#line 2535 "yacc_sql.tab.c"
    break;

  case 109:
#line 799 "yacc_sql.y"
                                     {

	}
#line 2543 "yacc_sql.tab.c"
    break;

  case 111:
#line 805 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2551 "yacc_sql.tab.c"
    break;

  case 113:
#line 811 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2559 "yacc_sql.tab.c"
    break;

  case 114:
#line 816 "yacc_sql.y"
                 { 
      // do notion
    }
#line 2567 "yacc_sql.tab.c"
    break;

  case 115:
#line 819 "yacc_sql.y"
                                                    {	
    }
#line 2574 "yacc_sql.tab.c"
    break;

  case 117:
#line 824 "yacc_sql.y"
                                                 {
    }
#line 2581 "yacc_sql.tab.c"
    break;

  case 118:
#line 830 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2587 "yacc_sql.tab.c"
    break;

  case 119:
#line 831 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2593 "yacc_sql.tab.c"
    break;

  case 120:
#line 832 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2599 "yacc_sql.tab.c"
    break;

  case 121:
#line 833 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2605 "yacc_sql.tab.c"
    break;

  case 122:
#line 834 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2611 "yacc_sql.tab.c"
    break;

  case 123:
#line 835 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2617 "yacc_sql.tab.c"
    break;

  case 124:
#line 836 "yacc_sql.y"
           { CONTEXT->comp = LIKE_OP; }
#line 2623 "yacc_sql.tab.c"
    break;

  case 125:
#line 837 "yacc_sql.y"
               { CONTEXT->comp = NOT_LIKE_OP; }
#line 2629 "yacc_sql.tab.c"
    break;

  case 126:
#line 841 "yacc_sql.y"
        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
#line 2641 "yacc_sql.tab.c"
    break;

  case 127:
#line 850 "yacc_sql.y"
        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
#line 2653 "yacc_sql.tab.c"
    break;

  case 128:
#line 859 "yacc_sql.y"
        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		OrderBy orderby;
		orderby_init(&orderby, FALSE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
#line 2665 "yacc_sql.tab.c"
    break;

  case 129:
#line 868 "yacc_sql.y"
        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
#line 2677 "yacc_sql.tab.c"
    break;

  case 130:
#line 877 "yacc_sql.y"
        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		OrderBy orderby;
		orderby_init(&orderby, FALSE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
#line 2689 "yacc_sql.tab.c"
    break;

  case 131:
#line 886 "yacc_sql.y"
        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
#line 2701 "yacc_sql.tab.c"
    break;

  case 132:
#line 896 "yacc_sql.y"
                {
			
	}
#line 2709 "yacc_sql.tab.c"
    break;

  case 133:
#line 900 "yacc_sql.y"
                {
			
	}
#line 2717 "yacc_sql.tab.c"
    break;

  case 135:
#line 907 "yacc_sql.y"
                {

	}
#line 2725 "yacc_sql.tab.c"
    break;

  case 136:
#line 914 "yacc_sql.y"
        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		CONTEXT->groupbys[CONTEXT->groupby_length++] = attr;
	}
#line 2735 "yacc_sql.tab.c"
    break;

  case 137:
#line 921 "yacc_sql.y"
        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		CONTEXT->groupbys[CONTEXT->groupby_length++] = attr;
	}
#line 2745 "yacc_sql.tab.c"
    break;

  case 138:
#line 930 "yacc_sql.y"
                {
			
	}
#line 2753 "yacc_sql.tab.c"
    break;

  case 139:
#line 934 "yacc_sql.y"
                {
			
	}
#line 2761 "yacc_sql.tab.c"
    break;

  case 141:
#line 941 "yacc_sql.y"
                {

	}
#line 2769 "yacc_sql.tab.c"
    break;

  case 142:
#line 948 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2778 "yacc_sql.tab.c"
    break;


#line 2782 "yacc_sql.tab.c"

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
#line 953 "yacc_sql.y"

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
