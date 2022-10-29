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


#line 157 "yacc_sql.tab.c"

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
    OR = 305,
    SET = 306,
    ON = 307,
    LOAD = 308,
    DATA = 309,
    INFILE = 310,
    NOT = 311,
    LIKE = 312,
    UNIQUE = 313,
    ADD = 314,
    SUB = 315,
    MUL = 316,
    DIV = 317,
    IS = 318,
    NULL_VALUE = 319,
    NULLABLE = 320,
    EQ = 321,
    LT = 322,
    GT = 323,
    LE = 324,
    GE = 325,
    NE = 326,
    LENGTH = 327,
    ROUND = 328,
    DATE_FORMAT = 329,
    NUMBER = 330,
    FLOAT = 331,
    ID = 332,
    PATH = 333,
    SSS = 334,
    STAR = 335,
    STRING_V = 336,
    DATE_STR = 337
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 167 "yacc_sql.y"

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

#line 314 "yacc_sql.tab.c"

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
#define YYLAST   465

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  83
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  170
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  352

#define YYUNDEFTOK  2
#define YYMAXUTOK   337


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
      75,    76,    77,    78,    79,    80,    81,    82
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   230,   230,   232,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   257,   262,   267,   273,   279,   285,   291,   297,
     303,   310,   318,   323,   330,   332,   338,   345,   352,   361,
     363,   367,   378,   385,   396,   403,   410,   417,   426,   429,
     430,   431,   432,   435,   444,   450,   452,   456,   467,   479,
     482,   489,   492,   507,   514,   524,   525,   532,   542,   548,
     562,   576,   582,   588,   601,   617,   625,   632,   641,   650,
     654,   657,   660,   663,   668,   671,   674,   677,   680,   686,
     694,   716,   726,   736,   746,   758,   801,   804,   807,   810,
     813,   817,   827,   833,   844,   851,   853,   857,   869,   878,
     883,   915,   922,   929,   936,   944,   953,   957,   964,   971,
     978,   986,   996,  1003,  1010,  1020,  1026,  1033,  1040,  1047,
    1057,  1060,  1065,  1068,  1074,  1077,  1083,  1086,  1097,  1104,
    1120,  1123,  1129,  1132,  1137,  1140,  1147,  1148,  1149,  1150,
    1151,  1152,  1153,  1154,  1157,  1166,  1175,  1184,  1193,  1202,
    1212,  1216,  1222,  1225,  1232,  1239,  1248,  1252,  1258,  1261,
    1268
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "TABLE",
  "TABLES", "INDEX", "INNER", "JOIN", "SELECT", "DESC", "ASC", "AS",
  "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE",
  "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "DATE_T", "FLOAT_T", "ORDER", "GROUP", "BY", "IN", "EXISTS", "HAVING",
  "AGGR_MAX", "AGGR_MIN", "AGGR_SUM", "AGGR_AVG", "AGGR_COUNT", "HELP",
  "TEXT", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "OR",
  "SET", "ON", "LOAD", "DATA", "INFILE", "NOT", "LIKE", "UNIQUE", "ADD",
  "SUB", "MUL", "DIV", "IS", "NULL_VALUE", "NULLABLE", "EQ", "LT", "GT",
  "LE", "GE", "NE", "LENGTH", "ROUND", "DATE_FORMAT", "NUMBER", "FLOAT",
  "ID", "PATH", "SSS", "STAR", "STRING_V", "DATE_STR", "$accept",
  "commands", "command", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "desc_table", "show_index",
  "create_index", "id_list", "id", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "insert",
  "row_value_list", "row_value", "sub_select_list", "value_list",
  "mul_expr", "add_expr", "condition", "having_condition", "unary_expr",
  "aggr_func_type", "aggr_func_expr", "func_expr", "sub_select", "value",
  "delete", "update", "update_options", "update_option", "select",
  "select_attr", "attr_list", "from", "rel_list", "inner_join_conditions",
  "where", "select_where", "condition_or", "condition_and",
  "condition_list", "opt_having", "having_condition_list", "comOp",
  "sort_unit", "sort_list", "opt_order_by", "groupby_unit", "groupby_list",
  "opt_group_by", "load_data", YY_NULLPTR
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
     335,   336,   337
};
# endif

#define YYPACT_NINF (-262)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-60)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -262,   412,  -262,    39,   108,   150,   -49,    34,    45,    64,
      26,    48,   114,   119,   140,   143,   152,   105,  -262,  -262,
    -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,
    -262,  -262,  -262,  -262,  -262,  -262,  -262,   100,   102,   172,
     106,   107,    -7,  -262,  -262,  -262,  -262,  -262,   274,  -262,
     165,   171,   176,  -262,  -262,   148,  -262,   173,  -262,  -262,
     -28,     4,  -262,   178,  -262,  -262,  -262,  -262,     8,   196,
     202,   159,  -262,   130,   131,   158,  -262,  -262,  -262,  -262,
    -262,   156,   192,   161,   138,   216,   225,   150,   189,    74,
      79,     9,  -262,  -262,  -262,   303,   303,   303,    28,   198,
    -262,   332,   332,   164,   303,   303,   173,  -262,   227,  -262,
     167,  -262,  -262,   168,   209,   200,   179,   180,   199,   204,
     205,  -262,  -262,   213,   206,  -262,   118,   248,  -262,  -262,
      81,    -1,   -10,  -262,   173,   235,   173,    29,  -262,  -262,
     173,   -28,   -28,  -262,   261,    94,    -6,   236,   282,   266,
      92,   285,   223,   268,   247,  -262,   271,   175,   275,   219,
     167,   276,  -262,  -262,  -262,   303,   303,  -262,    33,  -262,
     220,   173,  -262,  -262,  -262,  -262,   295,   231,   238,    13,
    -262,    92,   289,  -262,   118,   302,   303,   291,   183,   277,
    -262,    63,   179,   200,   321,   199,   314,  -262,  -262,  -262,
    -262,  -262,    42,   259,   317,   236,  -262,   103,   116,   173,
     173,  -262,   267,    13,     1,  -262,  -262,   304,   296,   323,
     322,   276,   266,   355,    76,   303,   303,   -19,  -262,    40,
    -262,  -262,  -262,  -262,  -262,  -262,   303,    92,  -262,   348,
    -262,  -262,   268,   357,   284,   271,   359,   290,   300,  -262,
    -262,   344,   259,   289,  -262,  -262,  -262,  -262,   329,  -262,
     297,    13,  -262,    92,    92,   306,   303,   343,   363,   302,
    -262,    76,    76,   303,  -262,   324,  -262,    76,   277,  -262,
    -262,   383,  -262,  -262,  -262,   366,  -262,   259,   368,   344,
     322,    92,    13,    13,  -262,   296,  -262,   346,   369,  -262,
     262,   345,   361,   392,  -262,  -262,    76,  -262,  -262,  -262,
     -29,   344,   394,   377,   343,   277,  -262,  -262,   325,   306,
     342,   303,   303,  -262,   326,  -262,   336,  -262,  -262,  -262,
     398,   389,  -262,  -262,  -262,    76,   345,    12,   391,  -262,
    -262,  -262,  -262,  -262,  -262,  -262,   338,   326,   145,  -262,
    -262,  -262
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
       0,     0,     0,    84,    85,    86,    87,    88,     0,   102,
       0,     0,     0,    96,    98,    77,   100,   116,   101,    83,
      65,   116,    61,     0,    81,    80,    82,    76,     0,     0,
       0,     0,    24,     0,     0,     0,    25,    26,    27,    23,
      22,     0,     0,     0,     0,     0,     0,     0,    77,     0,
      76,     0,    96,    98,    62,     0,     0,     0,     0,     0,
     111,     0,     0,     0,     0,     0,   116,   113,     0,   109,
       0,    30,    29,     0,     0,   132,     0,     0,     0,     0,
       0,    28,    37,     0,     0,    79,     0,     0,    97,    99,
       0,     0,     0,    78,   116,    77,   116,   116,    64,    63,
     116,    66,    67,   115,     0,     0,   125,   134,     0,     0,
       0,     0,     0,   105,     0,    53,    39,     0,     0,     0,
       0,    59,    58,    91,    92,     0,     0,   112,     0,   117,
       0,   116,   119,   114,    90,    89,     0,     0,     0,   125,
     122,     0,   168,    31,     0,    55,     0,     0,     0,   140,
     103,     0,     0,   132,     0,     0,     0,    49,    50,    52,
      51,    42,    43,     0,     0,   134,    60,     0,     0,   116,
     116,   121,     0,   125,   125,   123,   138,   135,   136,     0,
     142,    59,     0,     0,    73,     0,     0,     0,   152,     0,
     146,   147,   148,   149,   150,   151,     0,     0,   133,     0,
     108,   107,   105,     0,     0,    39,     0,     0,     0,    47,
      36,    34,     0,   168,    93,    94,   118,   120,   130,   124,
       0,   125,   126,     0,     0,     0,     0,   162,     0,    55,
      54,    74,    71,     0,   153,     0,    69,    68,   140,   106,
     104,     0,    40,    38,    48,     0,    46,     0,     0,    34,
     142,     0,   125,   125,   127,   137,   139,   164,   167,   169,
       0,   144,     0,     0,    57,    56,    72,    70,   141,   170,
      41,    34,     0,     0,   162,   140,   129,   128,     0,     0,
       0,     0,     0,   143,     0,   110,     0,    45,    35,    32,
       0,     0,   131,   165,   166,    75,   144,   154,   161,   163,
      44,    33,    95,   145,   156,   157,     0,     0,   155,   160,
     158,   159
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,
    -262,  -262,  -262,  -262,  -190,  -243,  -262,  -262,   174,   226,
    -262,  -262,  -262,  -262,   149,   203,  -262,  -142,    68,    -5,
    -144,    98,   -41,  -262,  -262,  -262,   241,   -40,  -262,  -262,
     184,   230,  -262,   347,   -60,   273,  -174,  -262,   245,   234,
    -262,   177,  -261,   151,   109,   142,  -262,    96,   132,  -262,
     125,   194,  -262
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,   288,   251,    30,    31,   196,   156,
     285,   202,   157,    32,   223,   185,    59,   127,    60,   188,
     216,   301,    62,    63,    64,    65,    66,    67,    33,    34,
     193,   153,    35,    68,   100,   147,   180,   292,   151,   182,
     217,   218,   238,   267,   323,   236,   338,   339,   303,   298,
     299,   220,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,   107,    90,   176,    87,   215,   189,    94,   177,   289,
     176,   109,   166,    42,   273,   260,   178,   308,   103,   206,
     164,   165,   176,   178,   344,   345,    99,   326,    69,    43,
      44,    45,    46,    47,   101,   178,   327,    89,   274,   259,
     262,    70,    71,   170,   311,    37,   143,    38,    72,   104,
     105,    99,   102,    48,   332,   110,   346,    49,   104,   105,
     138,   139,   247,   104,   105,    50,    51,    52,    53,    54,
      88,   179,    56,    74,   167,    58,   169,   172,   261,   268,
     173,   106,    61,   239,   128,   129,   161,   294,   104,   105,
     130,   131,   132,   278,   137,   125,   275,    39,   248,   313,
     -59,   126,   163,   145,   276,   133,   171,   249,   134,    73,
     133,   211,    42,   209,    40,   175,    41,    76,   316,   317,
     296,   328,    77,    91,   254,    75,   186,    49,    43,    44,
      45,    46,    47,   104,   105,   104,   105,   255,    53,    54,
     104,   105,    56,    78,   221,    58,    79,   315,   187,   256,
     257,   241,    48,   104,   105,    80,    49,   350,   351,    81,
     207,   208,   104,   105,    50,    51,    52,    53,    54,    88,
      42,    56,   141,   142,    58,   104,   105,    82,    91,    83,
      84,   224,    49,    85,    86,    95,    43,    44,    45,    46,
      47,    96,    98,    53,    54,    99,    97,    56,   108,   111,
      58,   197,   198,   199,   200,   112,   113,   114,   115,   116,
      48,   117,   118,   119,    49,   120,   226,   201,    42,   121,
     271,   272,    50,    51,    52,    53,    54,    55,   122,    56,
      57,   277,    58,   124,    43,    44,    45,    46,    47,   227,
     228,   140,   104,   105,   146,   148,   229,    42,   150,   230,
     231,   232,   233,   234,   235,   149,   152,   159,    48,   154,
     160,   300,    49,    43,    44,    45,    46,    47,   306,   162,
      50,    51,    52,    53,    54,   135,   155,    56,   136,   168,
      58,   158,   174,   133,   181,   183,   184,    48,   190,   191,
     192,    49,   194,   195,    42,   203,   204,   210,   126,    50,
      51,    52,    53,    54,    88,   212,    56,   144,   213,    58,
      43,    44,    45,    46,    47,   214,   335,   300,   320,   228,
     219,   104,   105,    42,   222,   225,   237,   244,   230,   231,
     232,   233,   234,   235,    91,   246,   250,   252,    49,    43,
      44,    45,    46,    47,   258,   264,    50,    51,    52,    92,
      93,    88,    42,    56,   263,   265,    58,   266,   270,    87,
     280,   281,   283,    48,   286,   284,   287,    49,    43,    44,
      45,    46,    47,   302,   293,    50,    51,    52,    53,    54,
      88,   291,    56,   297,   304,    58,   309,   310,   307,   312,
     318,   319,    91,   324,   322,   325,    49,   329,   330,   274,
     340,   341,   333,   337,    50,    51,    52,    53,    54,    88,
     342,    56,     2,   347,    58,   348,     3,     4,   305,   282,
     336,   245,   242,     5,     6,   269,   279,     7,     8,     9,
      10,    11,   240,   205,   123,    12,    13,    14,   243,   253,
     295,   314,   321,   349,   334,   343,   331,   290,     0,     0,
       0,     0,     0,    15,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17
};

static const yytype_int16 yycheck[] =
{
       5,    61,    42,     9,    11,   179,   150,    48,    14,   252,
       9,     3,    22,    20,    33,    14,    22,   278,    14,   161,
      21,    22,     9,    22,    12,    13,    22,    56,    77,    36,
      37,    38,    39,    40,    62,    22,    65,    42,    57,   213,
     214,     7,     8,    14,   287,     6,   106,     8,     3,    59,
      60,    22,    80,    60,   315,    47,    44,    64,    59,    60,
     101,   102,    20,    59,    60,    72,    73,    74,    75,    76,
      77,    77,    79,    47,   134,    82,   136,   137,    77,   221,
     140,    77,    87,    20,    75,    76,   126,   261,    59,    60,
      95,    96,    97,   237,    99,    21,    56,    58,    56,   289,
      21,    22,    21,   108,    64,    77,    77,    65,    80,    45,
      77,   171,    20,    80,     6,    21,     8,     3,   292,   293,
     264,   311,     3,    60,    21,    77,    34,    64,    36,    37,
      38,    39,    40,    59,    60,    59,    60,    21,    75,    76,
      59,    60,    79,     3,   184,    82,     3,   291,    56,   209,
     210,   191,    60,    59,    60,     3,    64,    12,    13,    54,
     165,   166,    59,    60,    72,    73,    74,    75,    76,    77,
      20,    79,   104,   105,    82,    59,    60,    77,    60,    77,
       8,   186,    64,    77,    77,    20,    36,    37,    38,    39,
      40,    20,    44,    75,    76,    22,    20,    79,    20,     3,
      82,    26,    27,    28,    29,     3,    47,    77,    77,    51,
      60,    55,    20,    52,    64,    77,    33,    42,    20,     3,
     225,   226,    72,    73,    74,    75,    76,    77,     3,    79,
      80,   236,    82,    44,    36,    37,    38,    39,    40,    56,
      57,    77,    59,    60,    77,    77,    63,    20,    48,    66,
      67,    68,    69,    70,    71,    46,    77,    52,    60,    79,
      47,   266,    64,    36,    37,    38,    39,    40,   273,    21,
      72,    73,    74,    75,    76,    77,    77,    79,    80,    44,
      82,    77,    21,    77,    48,     3,    20,    60,     3,    66,
      22,    64,    45,    22,    20,    20,    77,    77,    22,    72,
      73,    74,    75,    76,    77,    10,    79,    80,    77,    82,
      36,    37,    38,    39,    40,    77,   321,   322,    56,    57,
      31,    59,    60,    20,    22,    34,    49,     6,    66,    67,
      68,    69,    70,    71,    60,    21,    77,    20,    64,    36,
      37,    38,    39,    40,    77,    49,    72,    73,    74,    75,
      76,    77,    20,    79,    50,    32,    82,    35,     3,    11,
       3,    77,     3,    60,    64,    75,    22,    64,    36,    37,
      38,    39,    40,    30,    77,    72,    73,    74,    75,    76,
      77,    52,    79,    77,    21,    82,     3,    21,    64,    21,
      44,    22,    60,    32,    49,     3,    64,     3,    21,    57,
      64,     3,    77,    77,    72,    73,    74,    75,    76,    77,
      21,    79,     0,    22,    82,    77,     4,     5,   269,   245,
     322,   195,   192,    11,    12,   222,   242,    15,    16,    17,
      18,    19,   191,   160,    87,    23,    24,    25,   193,   205,
     263,   290,   300,   347,   319,   336,   314,   253,    -1,    -1,
      -1,    -1,    -1,    41,    -1,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    84,     0,     4,     5,    11,    12,    15,    16,    17,
      18,    19,    23,    24,    25,    41,    43,    53,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      99,   100,   106,   121,   122,   125,   145,     6,     8,    58,
       6,     8,    20,    36,    37,    38,    39,    40,    60,    64,
      72,    73,    74,    75,    76,    77,    79,    80,    82,   109,
     111,   112,   115,   116,   117,   118,   119,   120,   126,    77,
       7,     8,     3,    45,    47,    77,     3,     3,     3,     3,
       3,    54,    77,    77,     8,    77,    77,    11,    77,   112,
     120,    60,    75,    76,   115,    20,    20,    20,    44,    22,
     127,    62,    80,    14,    59,    60,    77,   127,    20,     3,
      47,     3,     3,    47,    77,    77,    51,    55,    20,    52,
      77,     3,     3,   126,    44,    21,    22,   110,    75,    76,
     112,   112,   112,    77,    80,    77,    80,   112,   115,   115,
      77,   111,   111,   127,    80,   112,    77,   128,    77,    46,
      48,   131,    77,   124,    79,    77,   102,   105,    77,    52,
      47,   120,    21,    21,    21,    22,    22,   127,    44,   127,
      14,    77,   127,   127,    21,    21,     9,    14,    22,    77,
     129,    48,   132,     3,    20,   108,    34,    56,   112,   113,
       3,    66,    22,   123,    45,    22,   101,    26,    27,    28,
      29,    42,   104,    20,    77,   128,   110,   112,   112,    80,
      77,   127,    10,    77,    77,   129,   113,   133,   134,    31,
     144,   120,    22,   107,   112,    34,    33,    56,    57,    63,
      66,    67,    68,    69,    70,    71,   138,    49,   135,    20,
     119,   120,   124,   131,     6,   102,    21,    20,    56,    65,
      77,    98,    20,   132,    21,    21,   127,   127,    77,   129,
      14,    77,   129,    50,    49,    32,    35,   136,   110,   108,
       3,   112,   112,    33,    57,    56,    64,   112,   113,   123,
       3,    77,   101,     3,    75,   103,    64,    22,    97,    98,
     144,    52,   130,    77,   129,   134,   113,    77,   142,   143,
     112,   114,    30,   141,    21,   107,   112,    64,   135,     3,
      21,    98,    21,    97,   136,   113,   129,   129,    44,    22,
      56,   138,    49,   137,    32,     3,    56,    65,    97,     3,
      21,   141,   135,    77,   143,   112,   114,    77,   139,   140,
      64,     3,    21,   137,    12,    13,    44,    22,    77,   140,
      12,    13
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    83,    84,    84,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    96,    97,    97,    98,    99,   100,   101,
     101,   102,   102,   102,   102,   102,   102,   102,   103,   104,
     104,   104,   104,   105,   106,   107,   107,   108,   109,   110,
     110,   111,   111,   111,   111,   112,   112,   112,   113,   113,
     113,   113,   113,   113,   113,   114,   115,   115,   115,   115,
     115,   115,   115,   115,   116,   116,   116,   116,   116,   117,
     117,   118,   118,   118,   118,   119,   120,   120,   120,   120,
     120,   120,   120,   121,   122,   123,   123,   124,   124,   125,
     125,   126,   126,   126,   126,   126,   127,   127,   127,   127,
     127,   127,   128,   128,   128,   129,   129,   129,   129,   129,
     130,   130,   131,   131,   132,   132,   133,   133,   134,   134,
     135,   135,   136,   136,   137,   137,   138,   138,   138,   138,
     138,   138,   138,   138,   139,   139,   139,   139,   139,   139,
     140,   140,   141,   141,   142,   142,   143,   143,   144,   144,
     145
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       3,     5,    10,    11,     0,     3,     1,     4,     8,     0,
       3,     5,     2,     2,     7,     6,     4,     3,     1,     1,
       1,     1,     1,     1,     7,     0,     3,     4,     4,     0,
       3,     1,     2,     3,     3,     1,     3,     3,     3,     3,
       4,     3,     4,     2,     3,     3,     1,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       4,     4,     4,     6,     6,    10,     1,     2,     1,     2,
       1,     1,     1,     5,     7,     0,     3,     3,     3,     3,
       9,     2,     4,     2,     4,     3,     0,     3,     5,     3,
       5,     4,     2,     3,     4,     0,     3,     4,     5,     5,
       0,     3,     0,     3,     0,     2,     1,     3,     1,     3,
       0,     3,     0,     3,     0,     3,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     3,     2,     2,     4,     4,
       3,     1,     0,     3,     1,     3,     3,     1,     0,     3,
       8
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
#line 257 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1781 "yacc_sql.tab.c"
    break;

  case 23:
#line 262 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1789 "yacc_sql.tab.c"
    break;

  case 24:
#line 267 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1797 "yacc_sql.tab.c"
    break;

  case 25:
#line 273 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1805 "yacc_sql.tab.c"
    break;

  case 26:
#line 279 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1813 "yacc_sql.tab.c"
    break;

  case 27:
#line 285 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1821 "yacc_sql.tab.c"
    break;

  case 28:
#line 291 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1830 "yacc_sql.tab.c"
    break;

  case 29:
#line 297 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1838 "yacc_sql.tab.c"
    break;

  case 30:
#line 303 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1847 "yacc_sql.tab.c"
    break;

  case 31:
#line 311 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
		}
#line 1856 "yacc_sql.tab.c"
    break;

  case 32:
#line 319 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;			//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, false, (yyvsp[-7].string), (yyvsp[-5].string));
		}
#line 1865 "yacc_sql.tab.c"
    break;

  case 33:
#line 324 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;			//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, true, (yyvsp[-7].string), (yyvsp[-5].string));
		}
#line 1874 "yacc_sql.tab.c"
    break;

  case 35:
#line 333 "yacc_sql.y"
                {
			/* Do Nothing */
		}
#line 1882 "yacc_sql.tab.c"
    break;

  case 36:
#line 339 "yacc_sql.y"
        {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	}
#line 1890 "yacc_sql.tab.c"
    break;

  case 37:
#line 346 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1899 "yacc_sql.tab.c"
    break;

  case 38:
#line 353 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1911 "yacc_sql.tab.c"
    break;

  case 40:
#line 363 "yacc_sql.y"
                                   {    }
#line 1917 "yacc_sql.tab.c"
    break;

  case 41:
#line 368 "yacc_sql.y"
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
#line 1932 "yacc_sql.tab.c"
    break;

  case 42:
#line 379 "yacc_sql.y"
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, CHARS, 4096, FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1943 "yacc_sql.tab.c"
    break;

  case 43:
#line 386 "yacc_sql.y"
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
#line 1958 "yacc_sql.tab.c"
    break;

  case 44:
#line 397 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-5].number), (yyvsp[-3].number), FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1969 "yacc_sql.tab.c"
    break;

  case 45:
#line 404 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number), TRUE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1980 "yacc_sql.tab.c"
    break;

  case 46:
#line 411 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-2].number), 4, FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1991 "yacc_sql.tab.c"
    break;

  case 47:
#line 418 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, TRUE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 2002 "yacc_sql.tab.c"
    break;

  case 48:
#line 426 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 2008 "yacc_sql.tab.c"
    break;

  case 49:
#line 429 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 2014 "yacc_sql.tab.c"
    break;

  case 50:
#line 430 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 2020 "yacc_sql.tab.c"
    break;

  case 51:
#line 431 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 2026 "yacc_sql.tab.c"
    break;

  case 52:
#line 432 "yacc_sql.y"
                                  { (yyval.number)=DATES; }
#line 2032 "yacc_sql.tab.c"
    break;

  case 53:
#line 436 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 2041 "yacc_sql.tab.c"
    break;

  case 54:
#line 445 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_INSERT;		//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
    }
#line 2050 "yacc_sql.tab.c"
    break;

  case 56:
#line 452 "yacc_sql.y"
                                                 {
			// Do Nothing
		}
#line 2058 "yacc_sql.tab.c"
    break;

  case 57:
#line 457 "yacc_sql.y"
                {
			if (0 != inserts_append_data(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length)) {
				return -1;
			}
			//临时变量清零
			memset(CONTEXT->values, 0, sizeof(CONTEXT->values));
      CONTEXT->value_length=0;
		}
#line 2071 "yacc_sql.tab.c"
    break;

  case 58:
#line 468 "yacc_sql.y"
    {
      Expr * expr = malloc(sizeof(Expr));
      ListExpr * lexp = malloc(sizeof(ListExpr));
      int v_length = (yyvsp[-1].cur_len) + 1;
      list_expr_init(lexp, &CONTEXT->values[CONTEXT->value_length - v_length], v_length);
      expr_init_list(expr, lexp);
      (yyval.exp7) = expr;
    }
#line 2084 "yacc_sql.tab.c"
    break;

  case 59:
#line 479 "yacc_sql.y"
               {
        (yyval.cur_len) = 0;
    }
#line 2092 "yacc_sql.tab.c"
    break;

  case 60:
#line 482 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	  }
#line 2101 "yacc_sql.tab.c"
    break;

  case 61:
#line 489 "yacc_sql.y"
               {
      (yyval.exp2) = (yyvsp[0].exp1);
    }
#line 2109 "yacc_sql.tab.c"
    break;

  case 62:
#line 492 "yacc_sql.y"
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
#line 2129 "yacc_sql.tab.c"
    break;

  case 63:
#line 507 "yacc_sql.y"
                               {
      Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, MUL_OP, (yyvsp[-2].exp2), (yyvsp[0].exp1));
      expr_init_binary(expr, b_expr);
      (yyval.exp2) = expr;
    }
#line 2141 "yacc_sql.tab.c"
    break;

  case 64:
#line 514 "yacc_sql.y"
                              {
    	Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, DIV_OP, (yyvsp[-2].exp2), (yyvsp[0].exp1));
      expr_init_binary(expr, b_expr);
      (yyval.exp2) = expr;
    }
#line 2153 "yacc_sql.tab.c"
    break;

  case 65:
#line 524 "yacc_sql.y"
             { (yyval.exp3) = (yyvsp[0].exp2); }
#line 2159 "yacc_sql.tab.c"
    break;

  case 66:
#line 525 "yacc_sql.y"
                            {
    	Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, ADD_OP, (yyvsp[-2].exp3), (yyvsp[0].exp2));
      expr_init_binary(expr, b_expr);
      (yyval.exp3) = expr;
    }
#line 2171 "yacc_sql.tab.c"
    break;

  case 67:
#line 532 "yacc_sql.y"
                            {
    	Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, SUB_OP, (yyvsp[-2].exp3), (yyvsp[0].exp2));
      expr_init_binary(expr, b_expr);
      (yyval.exp3) = expr;
    }
#line 2183 "yacc_sql.tab.c"
    break;

  case 68:
#line 542 "yacc_sql.y"
                           {
      Condition expr;
      condition_init(&expr, (yyvsp[-1].comp_op), (yyvsp[-2].exp3), (yyvsp[0].exp3));
      // condition_print(&expr, 0);
      CONTEXT->conditions[CONTEXT->condition_length++] = expr;
    }
#line 2194 "yacc_sql.tab.c"
    break;

  case 69:
#line 548 "yacc_sql.y"
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
#line 2213 "yacc_sql.tab.c"
    break;

  case 70:
#line 562 "yacc_sql.y"
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
#line 2232 "yacc_sql.tab.c"
    break;

  case 71:
#line 576 "yacc_sql.y"
                           {
      // TODO
      Condition cond;
      condition_init(&cond, IN_OP, (yyvsp[-2].exp3), (yyvsp[0].exp3));
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
#line 2243 "yacc_sql.tab.c"
    break;

  case 72:
#line 582 "yacc_sql.y"
                               {
      // TODO
      Condition cond;
      condition_init(&cond, NOT_IN, (yyvsp[-3].exp3), (yyvsp[0].exp3));
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
#line 2254 "yacc_sql.tab.c"
    break;

  case 73:
#line 588 "yacc_sql.y"
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
#line 2272 "yacc_sql.tab.c"
    break;

  case 74:
#line 601 "yacc_sql.y"
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
#line 2290 "yacc_sql.tab.c"
    break;

  case 75:
#line 617 "yacc_sql.y"
                           {
      Condition expr;
      condition_init(&expr, (yyvsp[-1].comp_op), (yyvsp[-2].exp3), (yyvsp[0].exp3));
      CONTEXT->havings[CONTEXT->having_length++] = expr;
    }
#line 2300 "yacc_sql.tab.c"
    break;

  case 76:
#line 625 "yacc_sql.y"
          {
    	Expr *expr = malloc(sizeof(Expr));
      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(u_expr, &CONTEXT->values[CONTEXT->value_length-1]);
      expr_init_unary(expr, u_expr);
      (yyval.exp1) = expr;
    }
#line 2312 "yacc_sql.tab.c"
    break;

  case 77:
#line 632 "yacc_sql.y"
         {
    	Expr *expr = malloc(sizeof(Expr));
      RelAttr attr;
      relation_attr_init(&attr, NULL, (yyvsp[0].string));
      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_attr(u_expr, &attr);
      expr_init_unary(expr, u_expr);
      (yyval.exp1) = expr;
    }
#line 2326 "yacc_sql.tab.c"
    break;

  case 78:
#line 641 "yacc_sql.y"
                {
    	Expr *expr = malloc(sizeof(Expr));
      RelAttr attr;
      relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_attr(u_expr, &attr);
      expr_init_unary(expr, u_expr);
      (yyval.exp1) = expr;
    }
#line 2340 "yacc_sql.tab.c"
    break;

  case 79:
#line 650 "yacc_sql.y"
                             {
      expr_set_with_brace((yyvsp[-1].exp3));
      (yyval.exp1) = (yyvsp[-1].exp3);
    }
#line 2349 "yacc_sql.tab.c"
    break;

  case 80:
#line 654 "yacc_sql.y"
                {
      (yyval.exp1) = (yyvsp[0].exp4);
    }
#line 2357 "yacc_sql.tab.c"
    break;

  case 81:
#line 657 "yacc_sql.y"
                     {
      (yyval.exp1) = (yyvsp[0].exp5);
    }
#line 2365 "yacc_sql.tab.c"
    break;

  case 82:
#line 660 "yacc_sql.y"
                 {
       (yyval.exp1) = (yyvsp[0].exp6);
    }
#line 2373 "yacc_sql.tab.c"
    break;

  case 83:
#line 663 "yacc_sql.y"
                     {
      (yyval.exp1) = (yyvsp[0].exp7);
    }
#line 2381 "yacc_sql.tab.c"
    break;

  case 84:
#line 668 "yacc_sql.y"
             {
      CONTEXT->aggrfunctype = MAX;
    }
#line 2389 "yacc_sql.tab.c"
    break;

  case 85:
#line 671 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = MIN;
    }
#line 2397 "yacc_sql.tab.c"
    break;

  case 86:
#line 674 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = SUM;
    }
#line 2405 "yacc_sql.tab.c"
    break;

  case 87:
#line 677 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = AVG;
    }
#line 2413 "yacc_sql.tab.c"
    break;

  case 88:
#line 680 "yacc_sql.y"
                 {
      CONTEXT->aggrfunctype = COUNT;
    }
#line 2421 "yacc_sql.tab.c"
    break;

  case 89:
#line 687 "yacc_sql.y"
    {
      AggrFuncExpr* afexpr = malloc(sizeof(AggrFuncExpr));
      aggr_func_expr_init(afexpr, CONTEXT->aggrfunctype, (yyvsp[-1].exp3));
      Expr* expr = malloc(sizeof(Expr));
      expr_init_aggr_func(expr, afexpr);
      (yyval.exp5) = expr;
    }
#line 2433 "yacc_sql.tab.c"
    break;

  case 90:
#line 695 "yacc_sql.y"
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
#line 2456 "yacc_sql.tab.c"
    break;

  case 91:
#line 717 "yacc_sql.y"
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 0);
      func_expr_init_params(fexpr, (yyvsp[-1].exp3), NULL);
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      (yyval.exp4) = expr;
    }
#line 2469 "yacc_sql.tab.c"
    break;

  case 92:
#line 727 "yacc_sql.y"
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 1);
      func_expr_init_params(fexpr, (yyvsp[-1].exp3), NULL);
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      (yyval.exp4) = expr;
    }
#line 2482 "yacc_sql.tab.c"
    break;

  case 93:
#line 737 "yacc_sql.y"
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 1);
      func_expr_init_params(fexpr, (yyvsp[-3].exp3), (yyvsp[-1].exp3));
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      (yyval.exp4) = expr;
    }
#line 2495 "yacc_sql.tab.c"
    break;

  case 94:
#line 747 "yacc_sql.y"
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 2);
      func_expr_init_params(fexpr, (yyvsp[-3].exp3), (yyvsp[-1].exp3));
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      (yyval.exp4) = expr;
    }
#line 2508 "yacc_sql.tab.c"
    break;

  case 95:
#line 758 "yacc_sql.y"
                                                                                                 {
      // printf("THE SUBQUERY has %d projects %d froms %d inner_join_conditions %d conditions %d groupbys %d havings %d orderbys\n", $3, $5->from_len, $5->inner_join_conditions_len, $6, $7, $8, $9);

      Selects * sub_select = (Selects *)malloc(sizeof(Selects));
      memset(sub_select, 0 ,sizeof(Selects));

			selects_append_projects(sub_select,  &CONTEXT->projects[CONTEXT->project_length - (yyvsp[-7].cur_len)], (yyvsp[-7].cur_len));
    
      size_t from_len = (yyvsp[-5].from_info)->from_len;
      size_t inner_join_conditions_len = (yyvsp[-5].from_info)->inner_join_conditions_len;
			selects_append_froms(sub_select,  &CONTEXT->froms[CONTEXT->from_length - from_len], from_len);

      // fill inner join conditions
			selects_append_conditions(sub_select, &CONTEXT->conditions[CONTEXT->condition_length - inner_join_conditions_len], inner_join_conditions_len);

      // fill where conditions
      selects_set_where_condition(sub_select, (yyvsp[-4].exp8));

			selects_append_groupbys(sub_select, &CONTEXT->groupbys[CONTEXT->groupby_length - (yyvsp[-3].cur_len)], (yyvsp[-3].cur_len));

			selects_append_havings(sub_select, &CONTEXT->havings[CONTEXT->having_length - (yyvsp[-2].cur_len)], (yyvsp[-2].cur_len));

			selects_append_orderbys(sub_select, &CONTEXT->orderbys[CONTEXT->orderby_length - (yyvsp[-1].cur_len)], (yyvsp[-1].cur_len));

			//CONTEXT->ssql->flag=SCF_SELECT;//"select";

			CONTEXT->orderby_length -= (yyvsp[-1].cur_len);
      CONTEXT->having_length -= (yyvsp[-2].cur_len);
			CONTEXT->groupby_length -= (yyvsp[-3].cur_len);
			CONTEXT->condition_length -= inner_join_conditions_len;
      CONTEXT->from_length -= from_len;
      CONTEXT->project_length -= (yyvsp[-7].cur_len);
			CONTEXT->value_length = 0;

      SubQueryExpr * s_expr = malloc(sizeof(SubQueryExpr));
      sub_query_expr_init(s_expr, sub_select);
      Expr* expr = malloc(sizeof(Expr));
      expr_init_sub_query(expr, s_expr);
      (yyval.exp6) = expr;
    }
#line 2553 "yacc_sql.tab.c"
    break;

  case 96:
#line 801 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 2561 "yacc_sql.tab.c"
    break;

  case 97:
#line 804 "yacc_sql.y"
               {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], -((yyvsp[0].number)));
		}
#line 2569 "yacc_sql.tab.c"
    break;

  case 98:
#line 807 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 2577 "yacc_sql.tab.c"
    break;

  case 99:
#line 810 "yacc_sql.y"
              {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], -((yyvsp[0].floats)));
		}
#line 2585 "yacc_sql.tab.c"
    break;

  case 100:
#line 813 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 2594 "yacc_sql.tab.c"
    break;

  case 101:
#line 817 "yacc_sql.y"
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
#line 2609 "yacc_sql.tab.c"
    break;

  case 102:
#line 827 "yacc_sql.y"
                {
      value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    }
#line 2617 "yacc_sql.tab.c"
    break;

  case 103:
#line 834 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 2629 "yacc_sql.tab.c"
    break;

  case 104:
#line 845 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;		//"update";
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 2640 "yacc_sql.tab.c"
    break;

  case 106:
#line 853 "yacc_sql.y"
                                                    {
			// Do Nothing
		}
#line 2648 "yacc_sql.tab.c"
    break;

  case 107:
#line 857 "yacc_sql.y"
                            {
    	Expr *expr = malloc(sizeof(Expr));
      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(u_expr, &CONTEXT->values[0]);
      expr_init_unary(expr, u_expr);

			// Value *value = &CONTEXT->values[0];
			updates_append_attribute(&CONTEXT->ssql->sstr.update, (yyvsp[-2].string), expr);
			//临时变量清零
			memset(CONTEXT->values, 0, sizeof(CONTEXT->values));
      CONTEXT->value_length=0;
		}
#line 2665 "yacc_sql.tab.c"
    break;

  case 108:
#line 869 "yacc_sql.y"
                       {
			updates_append_attribute(&CONTEXT->ssql->sstr.update, (yyvsp[-2].string), (yyvsp[0].exp6));
			//临时变量清零
			memset(CONTEXT->values, 0, sizeof(CONTEXT->values));
      CONTEXT->value_length=0;
    }
#line 2676 "yacc_sql.tab.c"
    break;

  case 109:
#line 878 "yacc_sql.y"
                                 {
			selects_append_projects(&CONTEXT->ssql->sstr.selection, CONTEXT->projects, CONTEXT->project_length);
			CONTEXT->ssql->flag=SCF_SELECT;//"select";
      CONTEXT->project_length=0;
    }
#line 2686 "yacc_sql.tab.c"
    break;

  case 110:
#line 884 "yacc_sql.y"
                {
      // printf("THE QUERY has %d projects %d froms %d inner_join_conditions %d conditions %d groupbys %d havings %d orderbys\n\n", $2, $4->from_len, $4->inner_join_conditions_len, $5, $6, $7, $8);

			selects_append_projects(&CONTEXT->ssql->sstr.selection, CONTEXT->projects, CONTEXT->project_length);

			selects_append_froms(&CONTEXT->ssql->sstr.selection, CONTEXT->froms, CONTEXT->from_length);

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

      selects_set_where_condition(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].exp8));

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
#line 2719 "yacc_sql.tab.c"
    break;

  case 111:
#line 915 "yacc_sql.y"
                   {  
			ProjectCol project_col;
			projectcol_init_star(&project_col, NULL);
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
		}
#line 2730 "yacc_sql.tab.c"
    break;

  case 112:
#line 922 "yacc_sql.y"
                         {
      ProjectCol project_col;
			projectcol_init_star(&project_col, (yyvsp[-3].string));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2741 "yacc_sql.tab.c"
    break;

  case 113:
#line 929 "yacc_sql.y"
                      {
      ProjectCol project_col;
      projectcol_init_expr(&project_col, (yyvsp[-1].exp3));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2752 "yacc_sql.tab.c"
    break;

  case 114:
#line 936 "yacc_sql.y"
                            {
      ProjectCol project_col;
      projectcol_init_expr(&project_col, (yyvsp[-3].exp3));
      expr_init_alias((yyvsp[-3].exp3), (yyvsp[-1].string));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2764 "yacc_sql.tab.c"
    break;

  case 115:
#line 944 "yacc_sql.y"
                         {
      ProjectCol project_col;
      projectcol_init_expr(&project_col, (yyvsp[-2].exp3));
      expr_init_alias((yyvsp[-2].exp3), (yyvsp[-1].string));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2776 "yacc_sql.tab.c"
    break;

  case 116:
#line 953 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2784 "yacc_sql.tab.c"
    break;

  case 117:
#line 957 "yacc_sql.y"
                         {  
			ProjectCol project_col;
			projectcol_init_star(&project_col, NULL);
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
		}
#line 2795 "yacc_sql.tab.c"
    break;

  case 118:
#line 964 "yacc_sql.y"
                               {
      ProjectCol project_col;
			projectcol_init_star(&project_col, (yyvsp[-3].string));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2806 "yacc_sql.tab.c"
    break;

  case 119:
#line 971 "yacc_sql.y"
                            {
      ProjectCol project_col;
      projectcol_init_expr(&project_col, (yyvsp[-1].exp3));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2817 "yacc_sql.tab.c"
    break;

  case 120:
#line 978 "yacc_sql.y"
                                  {
      ProjectCol project_col;
      projectcol_init_expr(&project_col, (yyvsp[-3].exp3));
      expr_init_alias((yyvsp[-3].exp3), (yyvsp[-1].string));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2829 "yacc_sql.tab.c"
    break;

  case 121:
#line 986 "yacc_sql.y"
                               {
      ProjectCol project_col;
      projectcol_init_expr(&project_col, (yyvsp[-2].exp3));
      expr_init_alias((yyvsp[-2].exp3), (yyvsp[-1].string));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2841 "yacc_sql.tab.c"
    break;

  case 122:
#line 996 "yacc_sql.y"
                {
      Relation rel;
      relation_from_init(&rel, (yyvsp[-1].string), NULL);
			CONTEXT->froms[CONTEXT->from_length++]=rel;
      (yyval.from_info) = (yyvsp[0].from_info);
      (yyval.from_info)->from_len++;
    }
#line 2853 "yacc_sql.tab.c"
    break;

  case 123:
#line 1003 "yacc_sql.y"
                    {
      Relation rel;
      relation_from_init(&rel, (yyvsp[-2].string), (yyvsp[-1].string));
			CONTEXT->froms[CONTEXT->from_length++]=rel;
      (yyval.from_info) = (yyvsp[0].from_info);
      (yyval.from_info)->from_len++;
    }
#line 2865 "yacc_sql.tab.c"
    break;

  case 124:
#line 1010 "yacc_sql.y"
                       {
      Relation rel;
      relation_from_init(&rel, (yyvsp[-3].string), (yyvsp[-1].string));
			CONTEXT->froms[CONTEXT->from_length++]=rel;
      (yyval.from_info) = (yyvsp[0].from_info);
      (yyval.from_info)->from_len++;
    }
#line 2877 "yacc_sql.tab.c"
    break;

  case 125:
#line 1020 "yacc_sql.y"
                {
      // new FromInfo
      (yyval.from_info) = (FromInfo*)malloc(sizeof(FromInfo));
      (yyval.from_info)->from_len = 0;
      (yyval.from_info)->inner_join_conditions_len = 0;
    }
#line 2888 "yacc_sql.tab.c"
    break;

  case 126:
#line 1026 "yacc_sql.y"
                        {	
        Relation rel;
        relation_from_init(&rel, (yyvsp[-1].string), NULL);
        CONTEXT->froms[CONTEXT->from_length++]=rel;
        (yyval.from_info) = (yyvsp[0].from_info);
        (yyval.from_info)->from_len++;
		  }
#line 2900 "yacc_sql.tab.c"
    break;

  case 127:
#line 1033 "yacc_sql.y"
                          {
      Relation rel;
      relation_from_init(&rel, (yyvsp[-2].string), (yyvsp[-1].string));
			CONTEXT->froms[CONTEXT->from_length++]=rel;
      (yyval.from_info) = (yyvsp[0].from_info);
      (yyval.from_info)->from_len++;
    }
#line 2912 "yacc_sql.tab.c"
    break;

  case 128:
#line 1040 "yacc_sql.y"
                             {
      Relation rel;
      relation_from_init(&rel, (yyvsp[-3].string), (yyvsp[-1].string));
			CONTEXT->froms[CONTEXT->from_length++]=rel;
      (yyval.from_info) = (yyvsp[0].from_info);
      (yyval.from_info)->from_len++;
    }
#line 2924 "yacc_sql.tab.c"
    break;

  case 129:
#line 1047 "yacc_sql.y"
                                                  {
      Relation rel;
      relation_from_init(&rel, (yyvsp[-2].string), NULL);
        CONTEXT->froms[CONTEXT->from_length++]=rel;
        (yyval.from_info) = (yyvsp[0].from_info);
        (yyval.from_info)->from_len++;
        (yyval.from_info)->inner_join_conditions_len += (yyvsp[-1].cur_len);
    }
#line 2937 "yacc_sql.tab.c"
    break;

  case 130:
#line 1057 "yacc_sql.y"
                    {
    (yyval.cur_len) = 0;
  }
#line 2945 "yacc_sql.tab.c"
    break;

  case 131:
#line 1060 "yacc_sql.y"
                                     {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 2953 "yacc_sql.tab.c"
    break;

  case 132:
#line 1065 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2961 "yacc_sql.tab.c"
    break;

  case 133:
#line 1068 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
			}
#line 2970 "yacc_sql.tab.c"
    break;

  case 134:
#line 1074 "yacc_sql.y"
                 {
      (yyval.exp8) = NULL;
     }
#line 2978 "yacc_sql.tab.c"
    break;

  case 135:
#line 1077 "yacc_sql.y"
                          {
      (yyval.exp8) = (yyvsp[0].exp8);
     }
#line 2986 "yacc_sql.tab.c"
    break;

  case 136:
#line 1083 "yacc_sql.y"
                   {
      (yyval.exp8) = (yyvsp[0].exp8);
     }
#line 2994 "yacc_sql.tab.c"
    break;

  case 137:
#line 1086 "yacc_sql.y"
                                     {
      Condition * c_expr = malloc(sizeof(Condition));
      condition_init(c_expr, OR_OP, (yyvsp[-2].exp8), (yyvsp[0].exp8));
      Expr * expr = malloc(sizeof(Expr));
      expr_init_condition(expr, c_expr);

      (yyval.exp8) = expr;
     }
#line 3007 "yacc_sql.tab.c"
    break;

  case 138:
#line 1097 "yacc_sql.y"
               {
      Expr * expr = malloc(sizeof(Expr));
      Condition * c_expr = malloc(sizeof(Condition));
      *c_expr = CONTEXT->conditions[--CONTEXT->condition_length]; // make condition in where clause would not appear in CONTEXT->condtitions
      expr_init_condition(expr, c_expr);
      (yyval.exp8) = expr;
     }
#line 3019 "yacc_sql.tab.c"
    break;

  case 139:
#line 1104 "yacc_sql.y"
                                   {
      Condition * rc_expr = malloc(sizeof(Condition));
      *rc_expr = CONTEXT->conditions[--CONTEXT->condition_length]; // make condition in where clause would not appear in CONTEXT->condtitions
      Expr * right_expr = malloc(sizeof(Expr));
      expr_init_condition(right_expr, rc_expr);

      Condition * c_expr = malloc(sizeof(Condition));
      condition_init(c_expr, AND_OP, (yyvsp[-2].exp8), right_expr);
      Expr * expr = malloc(sizeof(Expr));
      expr_init_condition(expr, c_expr);

      (yyval.exp8) = expr;
     }
#line 3037 "yacc_sql.tab.c"
    break;

  case 140:
#line 1120 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 3045 "yacc_sql.tab.c"
    break;

  case 141:
#line 1123 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
			}
#line 3054 "yacc_sql.tab.c"
    break;

  case 142:
#line 1129 "yacc_sql.y"
                 { 
      (yyval.cur_len) = 0;
    }
#line 3062 "yacc_sql.tab.c"
    break;

  case 143:
#line 1132 "yacc_sql.y"
                                                    {	
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 3070 "yacc_sql.tab.c"
    break;

  case 144:
#line 1137 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 3078 "yacc_sql.tab.c"
    break;

  case 145:
#line 1140 "yacc_sql.y"
                                                 {
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 3086 "yacc_sql.tab.c"
    break;

  case 146:
#line 1147 "yacc_sql.y"
             { (yyval.comp_op) = EQUAL_TO; }
#line 3092 "yacc_sql.tab.c"
    break;

  case 147:
#line 1148 "yacc_sql.y"
         { (yyval.comp_op) = LESS_THAN; }
#line 3098 "yacc_sql.tab.c"
    break;

  case 148:
#line 1149 "yacc_sql.y"
         { (yyval.comp_op) = GREAT_THAN; }
#line 3104 "yacc_sql.tab.c"
    break;

  case 149:
#line 1150 "yacc_sql.y"
         { (yyval.comp_op) = LESS_EQUAL; }
#line 3110 "yacc_sql.tab.c"
    break;

  case 150:
#line 1151 "yacc_sql.y"
         { (yyval.comp_op) = GREAT_EQUAL; }
#line 3116 "yacc_sql.tab.c"
    break;

  case 151:
#line 1152 "yacc_sql.y"
         { (yyval.comp_op) = NOT_EQUAL; }
#line 3122 "yacc_sql.tab.c"
    break;

  case 152:
#line 1153 "yacc_sql.y"
           { (yyval.comp_op) = LIKE_OP; }
#line 3128 "yacc_sql.tab.c"
    break;

  case 153:
#line 1154 "yacc_sql.y"
               { (yyval.comp_op) = NOT_LIKE_OP; }
#line 3134 "yacc_sql.tab.c"
    break;

  case 154:
#line 1158 "yacc_sql.y"
        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
#line 3146 "yacc_sql.tab.c"
    break;

  case 155:
#line 1167 "yacc_sql.y"
        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
#line 3158 "yacc_sql.tab.c"
    break;

  case 156:
#line 1176 "yacc_sql.y"
        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		OrderBy orderby;
		orderby_init(&orderby, FALSE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
#line 3170 "yacc_sql.tab.c"
    break;

  case 157:
#line 1185 "yacc_sql.y"
        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
#line 3182 "yacc_sql.tab.c"
    break;

  case 158:
#line 1194 "yacc_sql.y"
        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		OrderBy orderby;
		orderby_init(&orderby, FALSE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
#line 3194 "yacc_sql.tab.c"
    break;

  case 159:
#line 1203 "yacc_sql.y"
        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
#line 3206 "yacc_sql.tab.c"
    break;

  case 160:
#line 1213 "yacc_sql.y"
                {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 3214 "yacc_sql.tab.c"
    break;

  case 161:
#line 1217 "yacc_sql.y"
                {
    (yyval.cur_len) = 1;
	}
#line 3222 "yacc_sql.tab.c"
    break;

  case 162:
#line 1222 "yacc_sql.y"
                    {
   (yyval.cur_len) = 0;
  }
#line 3230 "yacc_sql.tab.c"
    break;

  case 163:
#line 1226 "yacc_sql.y"
                {
      (yyval.cur_len) = (yyvsp[0].cur_len);
	}
#line 3238 "yacc_sql.tab.c"
    break;

  case 164:
#line 1233 "yacc_sql.y"
        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		CONTEXT->groupbys[CONTEXT->groupby_length++] = attr;
	}
#line 3248 "yacc_sql.tab.c"
    break;

  case 165:
#line 1240 "yacc_sql.y"
        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		CONTEXT->groupbys[CONTEXT->groupby_length++] = attr;
	}
#line 3258 "yacc_sql.tab.c"
    break;

  case 166:
#line 1249 "yacc_sql.y"
                {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 3266 "yacc_sql.tab.c"
    break;

  case 167:
#line 1253 "yacc_sql.y"
                {
    (yyval.cur_len) = 1;
	}
#line 3274 "yacc_sql.tab.c"
    break;

  case 168:
#line 1258 "yacc_sql.y"
                    {
    (yyval.cur_len) = 0;
  }
#line 3282 "yacc_sql.tab.c"
    break;

  case 169:
#line 1262 "yacc_sql.y"
                {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 3290 "yacc_sql.tab.c"
    break;

  case 170:
#line 1269 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 3299 "yacc_sql.tab.c"
    break;


#line 3303 "yacc_sql.tab.c"

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
#line 1274 "yacc_sql.y"

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
