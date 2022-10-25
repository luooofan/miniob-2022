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
  struct _FromInfo* from_info;
  char *string;
  int number;
  float floats;
	char *position;
  int cur_len;
  int comp_op;

#line 313 "yacc_sql.tab.c"

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
#define YYLAST   379
=======
#define YYLAST   382
>>>>>>> subquery resolve

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
<<<<<<< HEAD
#define YYNRULES  146
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  304
=======
#define YYNRULES  148
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  310
>>>>>>> subquery resolve

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
<<<<<<< HEAD
       0,   224,   224,   226,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   251,   256,   261,   267,   273,   279,   285,   291,
     297,   304,   312,   317,   324,   326,   332,   339,   346,   355,
     357,   361,   372,   379,   390,   397,   404,   411,   420,   423,
     424,   425,   426,   429,   438,   444,   446,   450,   460,   462,
     468,   471,   486,   493,   503,   504,   511,   521,   527,   541,
     555,   563,   571,   578,   587,   596,   600,   603,   606,   612,
     615,   618,   621,   624,   630,   638,   660,   670,   680,   690,
     702,   736,   739,   742,   745,   748,   752,   762,   768,   778,
     788,   820,   827,   834,   842,   846,   853,   860,   869,   877,
     883,   888,   896,   899,   904,   907,   913,   916,   922,   925,
     930,   933,   940,   941,   942,   943,   944,   945,   946,   947,
     950,   959,   968,   977,   986,   995,  1005,  1009,  1015,  1018,
    1025,  1032,  1041,  1045,  1051,  1054,  1061
=======
       0,   225,   225,   227,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   252,   257,   262,   268,   274,   280,   286,   292,
     298,   305,   313,   318,   325,   327,   333,   340,   347,   356,
     358,   362,   373,   384,   391,   398,   405,   414,   417,   418,
     419,   420,   423,   432,   438,   440,   444,   454,   456,   462,
     465,   480,   487,   497,   498,   505,   515,   521,   535,   549,
     555,   561,   567,   576,   584,   591,   600,   609,   613,   616,
     619,   625,   628,   631,   634,   637,   643,   651,   673,   683,
     693,   703,   715,   757,   760,   763,   766,   769,   773,   783,
     789,   799,   809,   841,   848,   855,   863,   867,   874,   881,
     890,   898,   904,   909,   917,   920,   925,   928,   934,   937,
     943,   946,   951,   954,   961,   962,   963,   964,   965,   966,
     967,   968,   971,   980,   989,   998,  1007,  1016,  1026,  1030,
    1036,  1039,  1046,  1053,  1062,  1066,  1072,  1075,  1082
>>>>>>> subquery resolve
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
  "FLOAT_T", "ORDER", "GROUP", "BY", "IN", "EXISTS", "HAVING", "AGGR_MAX",
  "AGGR_MIN", "AGGR_SUM", "AGGR_AVG", "AGGR_COUNT", "HELP", "TEXT", "EXIT",
  "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON", "LOAD",
  "DATA", "INFILE", "NOT", "LIKE", "UNIQUE", "ADD", "SUB", "MUL", "DIV",
  "IS", "NULL_VALUE", "NULLABLE", "EQ", "LT", "GT", "LE", "GE", "NE",
  "LENGTH", "ROUND", "DATE_FORMAT", "NUMBER", "FLOAT", "ID", "PATH", "SSS",
  "STAR", "STRING_V", "DATE_STR", "$accept", "commands", "command", "exit",
  "help", "sync", "begin", "commit", "rollback", "drop_table",
  "show_tables", "desc_table", "show_index", "create_index", "id_list",
  "id", "drop_index", "create_table", "attr_def_list", "attr_def",
  "number", "type", "ID_get", "insert", "row_value_list", "row_value",
  "value_list", "mul_expr", "add_expr", "condition", "having_condition",
  "unary_expr", "aggr_func_type", "aggr_func_expr", "func_expr",
  "sub_select", "value", "delete", "update", "select", "select_attr",
  "attr_list", "from", "rel_list", "inner_join_conditions", "where",
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
     335
};
# endif

#define YYPACT_NINF (-233)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
<<<<<<< HEAD
    -233,   295,  -233,     4,    47,    39,   -39,    86,    13,    -4,
      -3,   -23,    58,    88,    95,    97,   125,    78,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,    61,    68,   149,
      90,   100,    -8,  -233,  -233,  -233,  -233,  -233,   143,  -233,
     142,   153,   158,  -233,  -233,   144,  -233,   164,  -233,   -45,
      38,  -233,   167,  -233,  -233,  -233,  -233,   145,   185,   189,
     147,  -233,   119,   127,   151,  -233,  -233,  -233,  -233,  -233,
     150,   193,   154,   146,   219,   221,    39,   182,    27,    34,
    -233,  -233,  -233,   171,   171,   171,   -53,    67,  -233,   217,
     217,   171,   171,  -233,    96,   152,  -233,  -233,   155,   181,
     184,   157,   161,   159,   160,   178,  -233,  -233,   194,   172,
    -233,  -233,  -233,    98,    25,    66,  -233,   164,   196,   164,
      38,  -233,  -233,   -45,   -45,   229,   102,     0,   184,   247,
     238,   171,   255,   200,   234,  -233,   260,   170,   263,   209,
     152,  -233,  -233,   171,   171,  -233,   -37,  -233,  -233,  -233,
    -233,   275,   211,  -233,   266,  -233,   203,   272,   205,   250,
    -233,   203,   296,   159,   281,  -233,  -233,  -233,  -233,  -233,
     -12,   228,   285,   184,   106,   126,   164,   230,     0,   277,
     280,   294,   238,   313,   171,   265,  -233,   -28,  -233,  -233,
    -233,  -233,  -233,  -233,   171,   171,  -233,   184,   246,   260,
     319,   251,   261,  -233,  -233,   304,   228,   266,  -233,  -233,
    -233,   276,  -233,   252,   171,   301,   203,   314,   272,  -233,
      63,  -233,   271,  -233,    63,   250,   333,   341,  -233,  -233,
    -233,   325,  -233,   228,   327,   304,   280,   171,     0,   305,
     328,  -233,   274,   302,   320,   349,   294,  -233,  -233,  -233,
    -233,  -233,  -233,   -40,   304,   350,   334,   301,   250,  -233,
     282,   252,   171,   171,  -233,   283,  -233,  -233,   293,  -233,
    -233,  -233,   353,   339,  -233,  -233,  -233,    63,   302,     5,
     340,  -233,  -233,  -233,  -233,  -233,  -233,  -233,   287,   283,
     138,  -233,  -233,  -233
=======
    -228,   318,  -228,     0,    28,    66,    -7,    86,    79,    26,
      39,    17,    97,   106,   110,   138,   141,    55,  -228,  -228,
    -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,  -228,  -228,  -228,   105,   108,   143,
     128,   140,     4,  -228,  -228,  -228,  -228,  -228,   168,  -228,
     152,   182,   198,  -228,  -228,   115,  -228,   203,  -228,   -32,
      77,  -228,   207,  -228,  -228,  -228,  -228,   189,   227,   232,
     191,  -228,   169,   171,   200,  -228,  -228,  -228,  -228,  -228,
     194,   235,   206,   183,   253,   255,    66,   217,    -6,    83,
    -228,  -228,  -228,   214,   214,   214,   -56,    93,  -228,   241,
     241,   214,   214,  -228,   139,   187,  -228,  -228,   188,   219,
     218,   192,   193,   196,   208,   216,  -228,  -228,   222,   215,
    -228,  -228,  -228,     2,    -8,   103,  -228,   203,   226,   203,
      77,  -228,  -228,   -32,   -32,   252,     6,     8,   218,   278,
     272,   214,   289,   231,   254,  -228,   274,   195,   277,   225,
     187,  -228,  -228,   214,   214,  -228,   -44,  -228,  -228,  -228,
    -228,   290,   229,  -228,   271,  -228,   -41,   283,    54,   258,
    -228,   -41,   300,   196,   287,  -228,  -228,  -228,  -228,    -9,
     234,   297,   218,    40,    59,   203,   245,     8,   293,   275,
     304,   272,   323,   214,   214,   114,  -228,   100,  -228,  -228,
    -228,  -228,  -228,  -228,   214,   214,  -228,   218,   247,   274,
     324,   256,   270,  -228,  -228,   316,   234,   271,  -228,  -228,
    -228,   294,  -228,   264,   214,   310,   -41,   325,   283,  -228,
     129,   129,   214,   214,  -228,   285,  -228,   129,   258,   341,
     344,  -228,  -228,  -228,   328,  -228,   234,   329,   316,   275,
     214,     8,   308,   330,  -228,   127,   305,   322,   351,   304,
    -228,  -228,   129,   129,  -228,  -228,  -228,  -228,   -34,   316,
     352,   336,   310,   258,  -228,   286,   264,   303,   214,   214,
    -228,   288,  -228,  -228,   302,  -228,  -228,  -228,   358,   345,
    -228,  -228,  -228,   129,   305,    12,   343,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,   292,   288,   185,  -228,  -228,  -228
>>>>>>> subquery resolve
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
       0,     0,     0,    79,    80,    81,    82,    83,     0,    97,
       0,     0,     0,    91,    93,    73,    95,   104,    96,    64,
     104,    60,     0,    77,    76,    78,    72,     0,     0,     0,
       0,    24,     0,     0,     0,    25,    26,    27,    23,    22,
       0,     0,     0,     0,     0,     0,     0,    73,     0,     0,
      91,    93,    61,     0,     0,     0,     0,     0,   101,     0,
       0,     0,     0,   103,     0,     0,    30,    29,     0,     0,
     114,     0,     0,     0,     0,     0,    28,    37,     0,     0,
      75,    92,    94,     0,     0,     0,    74,   104,    73,   104,
     104,    63,    62,    65,    66,     0,     0,   109,   114,     0,
       0,     0,     0,     0,     0,    53,    39,     0,     0,     0,
       0,    86,    87,     0,     0,   102,     0,   105,   107,    85,
      84,     0,     0,   108,   144,    31,     0,    55,     0,   116,
      98,     0,     0,     0,     0,    49,    50,    52,    51,    42,
      43,     0,     0,   114,     0,     0,   104,     0,   109,     0,
     118,    58,     0,     0,     0,     0,   128,     0,   122,   123,
     124,   125,   126,   127,     0,     0,   115,   114,     0,    39,
       0,     0,     0,    47,    36,    34,     0,   144,    88,    89,
     106,   112,   110,     0,     0,   138,     0,     0,    55,    54,
      70,   129,     0,    68,    67,   116,     0,     0,    40,    38,
      48,     0,    46,     0,     0,    34,   118,     0,   109,   140,
     143,   145,     0,   120,     0,     0,    58,    57,    56,    69,
     117,    99,   146,    41,    34,     0,     0,   138,   116,   111,
       0,     0,     0,     0,   119,     0,   100,    59,     0,    45,
      35,    32,     0,     0,   113,   141,   142,    71,   120,   130,
     137,   139,    44,    33,    90,   121,   132,   133,     0,     0,
     131,   136,   134,   135
=======
       0,     0,     0,    81,    82,    83,    84,    85,     0,    99,
       0,     0,     0,    93,    95,    75,    97,   106,    98,    63,
     106,    59,     0,    79,    78,    80,    74,     0,     0,     0,
       0,    24,     0,     0,     0,    25,    26,    27,    23,    22,
       0,     0,     0,     0,     0,     0,     0,    75,     0,     0,
      93,    95,    60,     0,     0,     0,     0,     0,   103,     0,
       0,     0,     0,   105,     0,     0,    30,    29,     0,     0,
     116,     0,     0,     0,     0,     0,    28,    37,     0,     0,
      77,    94,    96,     0,     0,     0,    76,   106,    75,   106,
     106,    62,    61,    64,    65,     0,     0,   111,   116,     0,
       0,     0,     0,     0,     0,    52,    39,     0,     0,     0,
       0,    88,    89,     0,     0,   104,     0,   107,   109,    87,
      86,     0,     0,   110,   146,    31,     0,    54,     0,   118,
     100,     0,     0,     0,     0,    48,    49,    51,    50,    42,
       0,     0,   116,     0,     0,   106,     0,   111,     0,   120,
      57,     0,     0,     0,     0,     0,   130,     0,   124,   125,
     126,   127,   128,   129,     0,     0,   117,   116,     0,    39,
       0,     0,     0,    46,    36,    34,     0,   146,    90,    91,
     108,   114,   112,     0,     0,   140,     0,     0,    54,    53,
      69,    71,     0,     0,   131,     0,    67,    66,   118,     0,
       0,    40,    38,    47,     0,    45,     0,     0,    34,   120,
       0,   111,   142,   145,   147,     0,   122,     0,     0,    57,
      56,    55,    70,    72,    68,   119,   101,   148,    41,    34,
       0,     0,   140,   118,   113,     0,     0,     0,     0,     0,
     121,     0,   102,    58,     0,    44,    35,    32,     0,     0,
     115,   143,   144,    73,   122,   132,   139,   141,    43,    33,
      92,   123,   134,   135,     0,     0,   133,   138,   136,   137
>>>>>>> subquery resolve
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
<<<<<<< HEAD
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -232,  -208,  -233,  -233,   156,   187,
    -233,  -233,  -233,  -233,   135,   174,   108,    51,    -5,  -203,
      94,   -43,  -233,  -233,  -233,  -233,  -147,  -233,  -233,  -233,
     284,   -59,   218,  -168,  -233,  -134,  -229,   123,    83,   120,
    -233,    74,   107,  -233,   104,   162,  -233
=======
    -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,   -96,  -121,  -228,  -228,   158,   197,
    -228,  -228,  -228,  -228,   144,   178,   112,   130,    -5,  -198,
      94,   -43,  -228,  -228,  -228,  -228,  -162,  -228,  -228,  -228,
     291,   -59,   224,  -185,  -228,  -135,  -227,   126,    82,   123,
    -228,    74,   109,  -228,   104,   165,  -228
>>>>>>> subquery resolve
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
<<<<<<< HEAD
      26,    27,    28,    29,   244,   215,    30,    31,   174,   146,
     241,   180,   147,    32,   193,   167,   227,    59,   168,   169,
     253,    61,    62,    63,    64,    65,    66,    33,    34,    35,
      67,    98,   138,   163,   248,   142,   206,   225,   274,   204,
     290,   291,   255,   250,   251,   190,    36
=======
      26,    27,    28,    29,   247,   215,    30,    31,   174,   146,
     244,   179,   147,    32,   192,   167,   227,    59,   168,   169,
     256,    61,    62,    63,    64,    65,    66,    33,    34,    35,
      67,    98,   138,   163,   251,   142,   206,   225,   280,   204,
     296,   297,   258,   253,   254,   189,    36
>>>>>>> subquery resolve
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
<<<<<<< HEAD
      60,   103,   235,    86,   164,    92,   260,   211,   245,   161,
      37,    42,    38,   266,   278,    99,    71,   296,   297,   191,
     222,   162,   126,   279,   207,   127,   232,    43,    44,    45,
      46,    47,   280,   100,   233,   264,    68,    88,   126,   284,
      72,   186,   212,    73,   268,   152,   153,   120,   298,   217,
      48,   213,    74,    40,    49,    41,   131,   132,    42,    97,
      39,    75,    50,    51,    52,    53,    54,    87,   155,    56,
     157,   158,    58,   236,    43,    44,    45,    46,    47,   256,
     269,    60,   101,   102,   101,   102,    42,   154,   123,   124,
     125,    76,   130,    69,    70,   101,   102,    48,    77,   136,
      78,    49,    43,    44,    45,    46,    47,   121,   122,    50,
      51,    52,    53,    54,    55,    42,    56,    57,   151,    58,
     101,   102,   160,   101,   102,    48,   218,   220,    79,    49,
      80,    43,    44,    45,    46,    47,    81,    50,    51,    52,
      53,    54,   128,    82,    56,   129,   219,    58,   184,   185,
     302,   303,   133,   134,    48,   101,   102,    83,    49,   101,
     102,    93,    42,   101,   102,    84,    50,    51,    52,    53,
      54,    87,    94,    56,   135,    85,    58,    95,    43,    44,
      45,    46,    47,   101,   102,    97,   104,    96,   106,   230,
      42,   105,   107,   108,   109,   175,   176,   177,   178,   234,
     111,    89,   110,   112,   114,    49,    43,    44,    45,    46,
      47,   179,   113,    50,    51,    52,    90,    91,    87,   252,
      56,   115,   116,    58,   117,   119,   140,   137,   149,    48,
     139,   141,   143,    49,   145,   148,    42,   194,   144,   156,
     150,    50,    51,    52,    53,    54,    87,   126,    56,   159,
     165,    58,    43,    44,    45,    46,    47,   166,   170,   195,
     196,    89,   101,   102,   171,    49,   197,   287,   252,   198,
     199,   200,   201,   202,   203,    89,    53,    54,   172,    49,
      56,   173,   181,    58,   182,   187,   188,    50,    51,    52,
      53,    54,    87,   192,    56,     2,   189,    58,   205,     3,
       4,   210,   208,   214,   216,   221,     5,     6,   223,     7,
       8,     9,    10,    11,   224,   226,   229,    12,    13,    14,
     231,   237,   239,   242,   240,   243,   247,   249,   195,   196,
     254,   101,   102,   259,   257,    15,   261,    16,   198,   199,
     200,   201,   202,   203,   262,   263,    17,   265,   270,   271,
     273,   275,   276,   281,   282,   292,   293,   285,   289,   294,
     209,   299,   300,   258,   277,   238,   228,   288,   183,   267,
     118,   295,   272,   301,   283,   286,     0,     0,     0,   246
=======
      60,   103,   222,   164,   190,    92,    37,   238,    38,   207,
     211,   265,   152,   153,   120,    86,    89,   161,   126,   284,
      49,   127,   151,    42,   302,   303,   160,    99,   285,   162,
     126,    53,    54,   185,    40,    56,    41,    88,    58,    43,
      44,    45,    46,    47,   212,   100,   290,   217,   101,   102,
     101,   102,   273,   213,   304,    39,   131,   132,   101,   102,
     218,    48,   101,   102,   259,    49,   274,    68,   155,    72,
     157,   158,   239,    50,    51,    52,    53,    54,    87,   219,
      56,    60,    71,    58,    73,    42,   193,   194,   123,   124,
     125,    74,   130,    69,    70,   248,   101,   102,    97,   136,
      75,    43,    44,    45,    46,    47,    80,   195,   196,    76,
     101,   102,    42,    77,   197,   101,   102,   198,   199,   200,
     201,   202,   203,    48,   154,   269,   220,    49,    43,    44,
      45,    46,    47,   101,   102,    50,    51,    52,    53,    54,
      55,    78,    56,    57,    79,    58,   232,   233,   183,   184,
      48,    83,   271,   235,    49,   121,   122,    96,    42,   101,
     102,   236,    50,    51,    52,    53,    54,   128,   234,    56,
     129,    93,    58,   286,    43,    44,    45,    46,    47,    81,
     277,   196,    82,   101,   102,   101,   102,    42,   230,   231,
     198,   199,   200,   201,   202,   203,    48,   308,   309,   237,
      49,    94,    84,    43,    44,    45,    46,    47,    50,    51,
      52,    53,    54,    87,    85,    56,   135,    95,    58,   255,
     175,   176,   177,   178,    97,    89,   104,   262,   263,    49,
     106,   133,   134,    42,   105,   107,   108,    50,    51,    52,
      90,    91,    87,   109,    56,   110,   112,    58,   111,    43,
      44,    45,    46,    47,   113,   114,   116,   115,   117,   119,
      42,   137,   139,   140,   141,   149,   143,   150,   156,   144,
     145,    48,   159,   293,   255,    49,    43,    44,    45,    46,
      47,   165,   148,    50,    51,    52,    53,    54,    87,   126,
      56,   166,   170,    58,   171,   173,   180,   172,    89,   181,
     186,   188,    49,   187,   191,   205,   208,   210,   214,   224,
      50,    51,    52,    53,    54,    87,   216,    56,     2,   221,
      58,   240,     3,     4,   223,   226,   229,   242,   243,     5,
       6,   245,     7,     8,     9,    10,    11,   246,   252,   257,
      12,    13,    14,   250,   266,   260,   264,   267,   268,   270,
     275,   276,   279,   281,   282,   287,   288,   234,    15,    16,
     291,   299,   295,   298,   305,   300,   306,   241,    17,   228,
     209,   283,   261,   294,   182,   272,   301,   118,   278,   307,
     292,   289,   249
>>>>>>> subquery resolve
};

static const yytype_int16 yycheck[] =
{
<<<<<<< HEAD
       5,    60,   205,    11,   138,    48,   235,    19,   216,     9,
       6,    19,     8,   245,    54,    60,     3,    12,    13,   166,
     188,    21,    75,    63,   171,    78,    54,    35,    36,    37,
      38,    39,   264,    78,    62,   243,    75,    42,    75,   268,
      44,    78,    54,    46,   247,    20,    21,    20,    43,   183,
      58,    63,    75,     6,    62,     8,    99,   100,    19,    21,
      56,     3,    70,    71,    72,    73,    74,    75,   127,    77,
     129,   130,    80,   207,    35,    36,    37,    38,    39,   226,
     248,    86,    57,    58,    57,    58,    19,    21,    93,    94,
      95,     3,    97,     7,     8,    57,    58,    58,     3,   104,
       3,    62,    35,    36,    37,    38,    39,    73,    74,    70,
      71,    72,    73,    74,    75,    19,    77,    78,    20,    80,
      57,    58,    20,    57,    58,    58,    20,   186,     3,    62,
      52,    35,    36,    37,    38,    39,    75,    70,    71,    72,
      73,    74,    75,    75,    77,    78,    20,    80,   153,   154,
      12,    13,   101,   102,    58,    57,    58,     8,    62,    57,
      58,    19,    19,    57,    58,    75,    70,    71,    72,    73,
      74,    75,    19,    77,    78,    75,    80,    19,    35,    36,
      37,    38,    39,    57,    58,    21,    19,    43,     3,   194,
      19,    46,     3,    46,    75,    25,    26,    27,    28,   204,
      49,    58,    75,    53,    50,    62,    35,    36,    37,    38,
      39,    41,    19,    70,    71,    72,    73,    74,    75,   224,
      77,    75,     3,    80,     3,    43,    45,    75,    50,    58,
      75,    47,    75,    62,    75,    75,    19,    32,    77,    43,
      46,    70,    71,    72,    73,    74,    75,    75,    77,    20,
       3,    80,    35,    36,    37,    38,    39,    19,     3,    54,
      55,    58,    57,    58,    64,    62,    61,   272,   273,    64,
      65,    66,    67,    68,    69,    58,    73,    74,    44,    62,
      77,    21,    19,    80,    75,    10,    75,    70,    71,    72,
      73,    74,    75,    21,    77,     0,    30,    80,    48,     4,
       5,    20,     6,    75,    19,    75,    11,    12,    31,    14,
      15,    16,    17,    18,    34,    21,     3,    22,    23,    24,
      55,    75,     3,    62,    73,    21,    50,    75,    54,    55,
      29,    57,    58,    62,    20,    40,     3,    42,    64,    65,
      66,    67,    68,    69,     3,    20,    51,    20,    43,    21,
      48,    31,     3,     3,    20,    62,     3,    75,    75,    20,
     173,    21,    75,   228,   256,   209,   192,   273,   150,   246,
      86,   288,   252,   299,   267,   271,    -1,    -1,    -1,   217
=======
       5,    60,   187,   138,   166,    48,     6,   205,     8,   171,
      19,   238,    20,    21,    20,    11,    57,     9,    74,    53,
      61,    77,    20,    19,    12,    13,    20,    59,    62,    21,
      74,    72,    73,    77,     6,    76,     8,    42,    79,    35,
      36,    37,    38,    39,    53,    77,   273,   182,    56,    57,
      56,    57,   250,    62,    42,    55,    99,   100,    56,    57,
      20,    57,    56,    57,   226,    61,   251,    74,   127,    43,
     129,   130,   207,    69,    70,    71,    72,    73,    74,    20,
      76,    86,     3,    79,    45,    19,    32,    33,    93,    94,
      95,    74,    97,     7,     8,   216,    56,    57,    21,   104,
       3,    35,    36,    37,    38,    39,    51,    53,    54,     3,
      56,    57,    19,     3,    60,    56,    57,    63,    64,    65,
      66,    67,    68,    57,    21,   246,   185,    61,    35,    36,
      37,    38,    39,    56,    57,    69,    70,    71,    72,    73,
      74,     3,    76,    77,     3,    79,    32,    33,   153,   154,
      57,     8,   248,    53,    61,    72,    73,    42,    19,    56,
      57,    61,    69,    70,    71,    72,    73,    74,    54,    76,
      77,    19,    79,   269,    35,    36,    37,    38,    39,    74,
      53,    54,    74,    56,    57,    56,    57,    19,   193,   194,
      63,    64,    65,    66,    67,    68,    57,    12,    13,   204,
      61,    19,    74,    35,    36,    37,    38,    39,    69,    70,
      71,    72,    73,    74,    74,    76,    77,    19,    79,   224,
      25,    26,    27,    28,    21,    57,    19,   232,   233,    61,
       3,   101,   102,    19,    45,     3,    45,    69,    70,    71,
      72,    73,    74,    74,    76,    74,    52,    79,    48,    35,
      36,    37,    38,    39,    19,    49,     3,    74,     3,    42,
      19,    74,    74,    44,    46,    49,    74,    45,    42,    76,
      74,    57,    20,   278,   279,    61,    35,    36,    37,    38,
      39,     3,    74,    69,    70,    71,    72,    73,    74,    74,
      76,    19,     3,    79,    63,    21,    19,    43,    57,    74,
      10,    30,    61,    74,    21,    47,     6,    20,    74,    34,
      69,    70,    71,    72,    73,    74,    19,    76,     0,    74,
      79,    74,     4,     5,    31,    21,     3,     3,    72,    11,
      12,    61,    14,    15,    16,    17,    18,    21,    74,    29,
      22,    23,    24,    49,     3,    20,    61,     3,    20,    20,
      42,    21,    47,    31,     3,     3,    20,    54,    40,    41,
      74,     3,    74,    61,    21,    20,    74,   209,    50,   191,
     173,   259,   228,   279,   150,   249,   294,    86,   255,   305,
     276,   272,   217
>>>>>>> subquery resolve
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
<<<<<<< HEAD
       0,    82,     0,     4,     5,    11,    12,    14,    15,    16,
      17,    18,    22,    23,    24,    40,    42,    51,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      97,    98,   104,   118,   119,   120,   137,     6,     8,    56,
       6,     8,    19,    35,    36,    37,    38,    39,    58,    62,
      70,    71,    72,    73,    74,    75,    77,    78,    80,   108,
     109,   112,   113,   114,   115,   116,   117,   121,    75,     7,
       8,     3,    44,    46,    75,     3,     3,     3,     3,     3,
      52,    75,    75,     8,    75,    75,    11,    75,   109,    58,
      73,    74,   112,    19,    19,    19,    43,    21,   122,    60,
      78,    57,    58,   122,    19,    46,     3,     3,    46,    75,
      75,    49,    53,    19,    50,    75,     3,     3,   121,    43,
      20,    73,    74,   109,   109,   109,    75,    78,    75,    78,
     109,   112,   112,   108,   108,    78,   109,    75,   123,    75,
      45,    47,   126,    75,    77,    75,   100,   103,    75,    50,
      46,    20,    20,    21,    21,   122,    43,   122,   122,    20,
      20,     9,    21,   124,   126,     3,    19,   106,   109,   110,
       3,    64,    44,    21,    99,    25,    26,    27,    28,    41,
     102,    19,    75,   123,   109,   109,    78,    10,    75,    30,
     136,   117,    21,   105,    32,    54,    55,    61,    64,    65,
      66,    67,    68,    69,   130,    48,   127,   117,     6,   100,
      20,    19,    54,    63,    75,    96,    19,   126,    20,    20,
     122,    75,   124,    31,    34,   128,    21,   107,   106,     3,
     109,    55,    54,    62,   109,   110,   126,    75,    99,     3,
      73,   101,    62,    21,    95,    96,   136,    50,   125,    75,
     134,   135,   109,   111,    29,   133,   117,    20,   105,    62,
     127,     3,     3,    20,    96,    20,    95,   128,   110,   124,
      43,    21,   130,    48,   129,    31,     3,   107,    54,    63,
      95,     3,    20,   133,   127,    75,   135,   109,   111,    75,
     131,   132,    62,     3,    20,   129,    12,    13,    43,    21,
      75,   132,    12,    13
=======
       0,    81,     0,     4,     5,    11,    12,    14,    15,    16,
      17,    18,    22,    23,    24,    40,    41,    50,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      96,    97,   103,   117,   118,   119,   136,     6,     8,    55,
       6,     8,    19,    35,    36,    37,    38,    39,    57,    61,
      69,    70,    71,    72,    73,    74,    76,    77,    79,   107,
     108,   111,   112,   113,   114,   115,   116,   120,    74,     7,
       8,     3,    43,    45,    74,     3,     3,     3,     3,     3,
      51,    74,    74,     8,    74,    74,    11,    74,   108,    57,
      72,    73,   111,    19,    19,    19,    42,    21,   121,    59,
      77,    56,    57,   121,    19,    45,     3,     3,    45,    74,
      74,    48,    52,    19,    49,    74,     3,     3,   120,    42,
      20,    72,    73,   108,   108,   108,    74,    77,    74,    77,
     108,   111,   111,   107,   107,    77,   108,    74,   122,    74,
      44,    46,   125,    74,    76,    74,    99,   102,    74,    49,
      45,    20,    20,    21,    21,   121,    42,   121,   121,    20,
      20,     9,    21,   123,   125,     3,    19,   105,   108,   109,
       3,    63,    43,    21,    98,    25,    26,    27,    28,   101,
      19,    74,   122,   108,   108,    77,    10,    74,    30,   135,
     116,    21,   104,    32,    33,    53,    54,    60,    63,    64,
      65,    66,    67,    68,   129,    47,   126,   116,     6,    99,
      20,    19,    53,    62,    74,    95,    19,   125,    20,    20,
     121,    74,   123,    31,    34,   127,    21,   106,   105,     3,
     108,   108,    32,    33,    54,    53,    61,   108,   109,   125,
      74,    98,     3,    72,   100,    61,    21,    94,    95,   135,
      49,   124,    74,   133,   134,   108,   110,    29,   132,   116,
      20,   104,   108,   108,    61,   126,     3,     3,    20,    95,
      20,    94,   127,   109,   123,    42,    21,    53,   129,    47,
     128,    31,     3,   106,    53,    62,    94,     3,    20,   132,
     126,    74,   134,   108,   110,    74,   130,   131,    61,     3,
      20,   128,    12,    13,    42,    21,    74,   131,    12,    13
>>>>>>> subquery resolve
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
<<<<<<< HEAD
       0,    81,    82,    82,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    94,    95,    95,    96,    97,    98,    99,
      99,   100,   100,   100,   100,   100,   100,   100,   101,   102,
     102,   102,   102,   103,   104,   105,   105,   106,   107,   107,
     108,   108,   108,   108,   109,   109,   109,   110,   110,   110,
     110,   111,   112,   112,   112,   112,   112,   112,   112,   113,
     113,   113,   113,   113,   114,   114,   115,   115,   115,   115,
     116,   117,   117,   117,   117,   117,   117,   117,   118,   119,
     120,   121,   121,   121,   122,   122,   122,   122,   123,   124,
     124,   124,   125,   125,   126,   126,   127,   127,   128,   128,
     129,   129,   130,   130,   130,   130,   130,   130,   130,   130,
     131,   131,   131,   131,   131,   131,   132,   132,   133,   133,
     134,   134,   135,   135,   136,   136,   137
=======
       0,    80,    81,    81,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    93,    94,    94,    95,    96,    97,    98,
      98,    99,    99,    99,    99,    99,    99,   100,   101,   101,
     101,   101,   102,   103,   104,   104,   105,   106,   106,   107,
     107,   107,   107,   108,   108,   108,   109,   109,   109,   109,
     109,   109,   109,   110,   111,   111,   111,   111,   111,   111,
     111,   112,   112,   112,   112,   112,   113,   113,   114,   114,
     114,   114,   115,   116,   116,   116,   116,   116,   116,   116,
     117,   118,   119,   120,   120,   120,   121,   121,   121,   121,
     122,   123,   123,   123,   124,   124,   125,   125,   126,   126,
     127,   127,   128,   128,   129,   129,   129,   129,   129,   129,
     129,   129,   130,   130,   130,   130,   130,   130,   131,   131,
     132,   132,   133,   133,   134,   134,   135,   135,   136
>>>>>>> subquery resolve
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
       1,     1,     1,     1,     7,     0,     3,     4,     0,     3,
       1,     2,     3,     3,     1,     3,     3,     3,     3,     4,
       3,     3,     1,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     4,     4,     4,     6,     6,
      10,     1,     2,     1,     2,     1,     1,     1,     5,     8,
       9,     2,     4,     2,     0,     3,     5,     3,     2,     0,
       3,     5,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     3,     2,     2,     4,     4,     3,     1,     0,     3,
       1,     3,     3,     1,     0,     3,     8
=======
       3,     5,     2,     7,     6,     4,     3,     1,     1,     1,
       1,     1,     1,     7,     0,     3,     4,     0,     3,     1,
       2,     3,     3,     1,     3,     3,     3,     3,     4,     3,
       4,     3,     4,     3,     1,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     4,     4,     4,
       6,     6,    10,     1,     2,     1,     2,     1,     1,     1,
       5,     8,     9,     2,     4,     2,     0,     3,     5,     3,
       2,     0,     3,     5,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     3,     2,     2,     4,     4,     3,     1,
       0,     3,     1,     3,     3,     1,     0,     3,     8
>>>>>>> subquery resolve
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
<<<<<<< HEAD
#line 251 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1734 "yacc_sql.tab.c"
    break;

  case 23:
#line 256 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1742 "yacc_sql.tab.c"
    break;

  case 24:
#line 261 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1750 "yacc_sql.tab.c"
    break;

  case 25:
#line 267 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1758 "yacc_sql.tab.c"
    break;

  case 26:
#line 273 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1766 "yacc_sql.tab.c"
    break;

  case 27:
#line 279 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1774 "yacc_sql.tab.c"
    break;

  case 28:
#line 285 "yacc_sql.y"
=======
#line 252 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1735 "yacc_sql.tab.c"
    break;

  case 23:
#line 257 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1743 "yacc_sql.tab.c"
    break;

  case 24:
#line 262 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1751 "yacc_sql.tab.c"
    break;

  case 25:
#line 268 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1759 "yacc_sql.tab.c"
    break;

  case 26:
#line 274 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1767 "yacc_sql.tab.c"
    break;

  case 27:
#line 280 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1775 "yacc_sql.tab.c"
    break;

  case 28:
#line 286 "yacc_sql.y"
>>>>>>> subquery resolve
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
<<<<<<< HEAD
#line 1783 "yacc_sql.tab.c"
    break;

  case 29:
#line 291 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1791 "yacc_sql.tab.c"
    break;

  case 30:
#line 297 "yacc_sql.y"
=======
#line 1784 "yacc_sql.tab.c"
    break;

  case 29:
#line 292 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1792 "yacc_sql.tab.c"
    break;

  case 30:
#line 298 "yacc_sql.y"
>>>>>>> subquery resolve
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
<<<<<<< HEAD
#line 1800 "yacc_sql.tab.c"
    break;

  case 31:
#line 305 "yacc_sql.y"
=======
#line 1801 "yacc_sql.tab.c"
    break;

  case 31:
#line 306 "yacc_sql.y"
>>>>>>> subquery resolve
                {
			CONTEXT->ssql->flag = SCF_SHOW_INDEX;
			desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
		}
<<<<<<< HEAD
#line 1809 "yacc_sql.tab.c"
    break;

  case 32:
#line 313 "yacc_sql.y"
=======
#line 1810 "yacc_sql.tab.c"
    break;

  case 32:
#line 314 "yacc_sql.y"
>>>>>>> subquery resolve
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;			//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, false, (yyvsp[-7].string), (yyvsp[-5].string));
		}
<<<<<<< HEAD
#line 1818 "yacc_sql.tab.c"
    break;

  case 33:
#line 318 "yacc_sql.y"
=======
#line 1819 "yacc_sql.tab.c"
    break;

  case 33:
#line 319 "yacc_sql.y"
>>>>>>> subquery resolve
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;			//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, true, (yyvsp[-7].string), (yyvsp[-5].string));
		}
<<<<<<< HEAD
#line 1827 "yacc_sql.tab.c"
    break;

  case 35:
#line 327 "yacc_sql.y"
                {
			/* Do Nothing */
		}
#line 1835 "yacc_sql.tab.c"
    break;

  case 36:
#line 333 "yacc_sql.y"
        {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	}
#line 1843 "yacc_sql.tab.c"
    break;

  case 37:
#line 340 "yacc_sql.y"
=======
#line 1828 "yacc_sql.tab.c"
    break;

  case 35:
#line 328 "yacc_sql.y"
                {
			/* Do Nothing */
		}
#line 1836 "yacc_sql.tab.c"
    break;

  case 36:
#line 334 "yacc_sql.y"
        {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	}
#line 1844 "yacc_sql.tab.c"
    break;

  case 37:
#line 341 "yacc_sql.y"
>>>>>>> subquery resolve
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
<<<<<<< HEAD
#line 1852 "yacc_sql.tab.c"
    break;

  case 38:
#line 347 "yacc_sql.y"
=======
#line 1853 "yacc_sql.tab.c"
    break;

  case 38:
#line 348 "yacc_sql.y"
>>>>>>> subquery resolve
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
<<<<<<< HEAD
#line 1864 "yacc_sql.tab.c"
    break;

  case 40:
#line 357 "yacc_sql.y"
                                   {    }
#line 1870 "yacc_sql.tab.c"
    break;

  case 41:
#line 362 "yacc_sql.y"
=======
#line 1865 "yacc_sql.tab.c"
    break;

  case 40:
#line 358 "yacc_sql.y"
                                   {    }
#line 1871 "yacc_sql.tab.c"
    break;

  case 41:
#line 363 "yacc_sql.y"
>>>>>>> subquery resolve
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
#line 1885 "yacc_sql.tab.c"
    break;

  case 42:
#line 373 "yacc_sql.y"
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, CHARS, 4096, FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1896 "yacc_sql.tab.c"
    break;

  case 43:
#line 380 "yacc_sql.y"
=======
#line 1886 "yacc_sql.tab.c"
    break;

  case 42:
#line 374 "yacc_sql.y"
>>>>>>> subquery resolve
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
#line 1911 "yacc_sql.tab.c"
    break;

  case 44:
#line 391 "yacc_sql.y"
=======
#line 1901 "yacc_sql.tab.c"
    break;

  case 43:
#line 385 "yacc_sql.y"
>>>>>>> subquery resolve
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-5].number), (yyvsp[-3].number), FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
#line 1922 "yacc_sql.tab.c"
    break;

  case 45:
#line 398 "yacc_sql.y"
=======
#line 1912 "yacc_sql.tab.c"
    break;

  case 44:
#line 392 "yacc_sql.y"
>>>>>>> subquery resolve
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number), TRUE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
#line 1933 "yacc_sql.tab.c"
    break;

  case 46:
#line 405 "yacc_sql.y"
=======
#line 1923 "yacc_sql.tab.c"
    break;

  case 45:
#line 399 "yacc_sql.y"
>>>>>>> subquery resolve
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-2].number), 4, FALSE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
#line 1944 "yacc_sql.tab.c"
    break;

  case 47:
#line 412 "yacc_sql.y"
=======
#line 1934 "yacc_sql.tab.c"
    break;

  case 46:
#line 406 "yacc_sql.y"
>>>>>>> subquery resolve
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, TRUE);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
#line 1955 "yacc_sql.tab.c"
    break;

  case 48:
#line 420 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1961 "yacc_sql.tab.c"
    break;

  case 49:
#line 423 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1967 "yacc_sql.tab.c"
    break;

  case 50:
#line 424 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1973 "yacc_sql.tab.c"
    break;

  case 51:
#line 425 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1979 "yacc_sql.tab.c"
    break;

  case 52:
#line 426 "yacc_sql.y"
                                  { (yyval.number)=DATES; }
#line 1985 "yacc_sql.tab.c"
    break;

  case 53:
#line 430 "yacc_sql.y"
=======
#line 1945 "yacc_sql.tab.c"
    break;

  case 47:
#line 414 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1951 "yacc_sql.tab.c"
    break;

  case 48:
#line 417 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1957 "yacc_sql.tab.c"
    break;

  case 49:
#line 418 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1963 "yacc_sql.tab.c"
    break;

  case 50:
#line 419 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1969 "yacc_sql.tab.c"
    break;

  case 51:
#line 420 "yacc_sql.y"
                                  { (yyval.number)=DATES; }
#line 1975 "yacc_sql.tab.c"
    break;

  case 52:
#line 424 "yacc_sql.y"
>>>>>>> subquery resolve
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
<<<<<<< HEAD
#line 1994 "yacc_sql.tab.c"
    break;

  case 54:
#line 439 "yacc_sql.y"
=======
#line 1984 "yacc_sql.tab.c"
    break;

  case 53:
#line 433 "yacc_sql.y"
>>>>>>> subquery resolve
                {
			CONTEXT->ssql->flag=SCF_INSERT;		//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
    }
<<<<<<< HEAD
#line 2003 "yacc_sql.tab.c"
    break;

  case 56:
#line 446 "yacc_sql.y"
                                                 {
			// Do Nothing
		}
#line 2011 "yacc_sql.tab.c"
    break;

  case 57:
#line 451 "yacc_sql.y"
=======
#line 1993 "yacc_sql.tab.c"
    break;

  case 55:
#line 440 "yacc_sql.y"
                                                 {
			// Do Nothing
		}
#line 2001 "yacc_sql.tab.c"
    break;

  case 56:
#line 445 "yacc_sql.y"
>>>>>>> subquery resolve
                {
			if (0 != inserts_append_data(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length)) {
				return -1;
			}
			//临时变量清零
			memset(CONTEXT->values, 0, sizeof(CONTEXT->values));
      CONTEXT->value_length=0;
		}
<<<<<<< HEAD
#line 2024 "yacc_sql.tab.c"
    break;

  case 59:
#line 462 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 2032 "yacc_sql.tab.c"
    break;

  case 60:
#line 468 "yacc_sql.y"
               {
      (yyval.exp2) = (yyvsp[0].exp1);
    }
#line 2040 "yacc_sql.tab.c"
    break;

  case 61:
#line 471 "yacc_sql.y"
=======
#line 2014 "yacc_sql.tab.c"
    break;

  case 58:
#line 456 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 2022 "yacc_sql.tab.c"
    break;

  case 59:
#line 462 "yacc_sql.y"
               {
      (yyval.exp2) = (yyvsp[0].exp1);
    }
#line 2030 "yacc_sql.tab.c"
    break;

  case 60:
#line 465 "yacc_sql.y"
>>>>>>> subquery resolve
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
#line 2060 "yacc_sql.tab.c"
    break;

  case 62:
#line 486 "yacc_sql.y"
=======
#line 2050 "yacc_sql.tab.c"
    break;

  case 61:
#line 480 "yacc_sql.y"
>>>>>>> subquery resolve
                               {
      Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, MUL_OP, (yyvsp[-2].exp2), (yyvsp[0].exp1));
      expr_init_binary(expr, b_expr);
      (yyval.exp2) = expr;
    }
<<<<<<< HEAD
#line 2072 "yacc_sql.tab.c"
    break;

  case 63:
#line 493 "yacc_sql.y"
=======
#line 2062 "yacc_sql.tab.c"
    break;

  case 62:
#line 487 "yacc_sql.y"
>>>>>>> subquery resolve
                              {
    	Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, DIV_OP, (yyvsp[-2].exp2), (yyvsp[0].exp1));
      expr_init_binary(expr, b_expr);
      (yyval.exp2) = expr;
    }
<<<<<<< HEAD
#line 2084 "yacc_sql.tab.c"
    break;

  case 64:
#line 503 "yacc_sql.y"
             { (yyval.exp3) = (yyvsp[0].exp2); }
#line 2090 "yacc_sql.tab.c"
    break;

  case 65:
#line 504 "yacc_sql.y"
=======
#line 2074 "yacc_sql.tab.c"
    break;

  case 63:
#line 497 "yacc_sql.y"
             { (yyval.exp3) = (yyvsp[0].exp2); }
#line 2080 "yacc_sql.tab.c"
    break;

  case 64:
#line 498 "yacc_sql.y"
>>>>>>> subquery resolve
                            {
    	Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, ADD_OP, (yyvsp[-2].exp3), (yyvsp[0].exp2));
      expr_init_binary(expr, b_expr);
      (yyval.exp3) = expr;
    }
<<<<<<< HEAD
#line 2102 "yacc_sql.tab.c"
    break;

  case 66:
#line 511 "yacc_sql.y"
=======
#line 2092 "yacc_sql.tab.c"
    break;

  case 65:
#line 505 "yacc_sql.y"
>>>>>>> subquery resolve
                            {
    	Expr * expr = malloc(sizeof(Expr));
      BinaryExpr * b_expr = malloc(sizeof(BinaryExpr));
      binary_expr_init(b_expr, SUB_OP, (yyvsp[-2].exp3), (yyvsp[0].exp2));
      expr_init_binary(expr, b_expr);
      (yyval.exp3) = expr;
    }
<<<<<<< HEAD
#line 2114 "yacc_sql.tab.c"
    break;

  case 67:
#line 521 "yacc_sql.y"
=======
#line 2104 "yacc_sql.tab.c"
    break;

  case 66:
#line 515 "yacc_sql.y"
>>>>>>> subquery resolve
                           {
      Condition expr;
      condition_init(&expr, (yyvsp[-1].comp_op), (yyvsp[-2].exp3), (yyvsp[0].exp3));
      // condition_print(&expr, 0);
      CONTEXT->conditions[CONTEXT->condition_length++] = expr;
    }
<<<<<<< HEAD
#line 2125 "yacc_sql.tab.c"
    break;

  case 68:
#line 527 "yacc_sql.y"
=======
#line 2115 "yacc_sql.tab.c"
    break;

  case 67:
#line 521 "yacc_sql.y"
>>>>>>> subquery resolve
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
#line 2144 "yacc_sql.tab.c"
    break;

  case 69:
#line 541 "yacc_sql.y"
=======
#line 2134 "yacc_sql.tab.c"
    break;

  case 68:
#line 535 "yacc_sql.y"
>>>>>>> subquery resolve
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
#line 2163 "yacc_sql.tab.c"
    break;

  case 70:
#line 555 "yacc_sql.y"
=======
#line 2153 "yacc_sql.tab.c"
    break;

  case 69:
#line 549 "yacc_sql.y"
>>>>>>> subquery resolve
                           {
      // TODO
      Condition cond;
      condition_init(&cond, IN_OP, (yyvsp[-2].exp3), (yyvsp[0].exp3));
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
<<<<<<< HEAD
#line 2173 "yacc_sql.tab.c"
    break;

  case 71:
#line 563 "yacc_sql.y"
=======
#line 2164 "yacc_sql.tab.c"
    break;

  case 70:
#line 555 "yacc_sql.y"
                               {
      // TODO
      Condition cond;
      condition_init(&cond, NOT_IN, (yyvsp[-3].exp3), (yyvsp[0].exp3));
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
#line 2175 "yacc_sql.tab.c"
    break;

  case 71:
#line 561 "yacc_sql.y"
                               {
      // TODO
      Condition cond;
      condition_init(&cond, EXISTS_OP, (yyvsp[-2].exp3), (yyvsp[0].exp3));
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
#line 2186 "yacc_sql.tab.c"
    break;

  case 72:
#line 567 "yacc_sql.y"
                                   {
      // TODO
      Condition cond;
      condition_init(&cond, NOT_EXISTS, (yyvsp[-3].exp3), (yyvsp[0].exp3));
      CONTEXT->conditions[CONTEXT->condition_length++] = cond;
    }
#line 2197 "yacc_sql.tab.c"
    break;

  case 73:
#line 576 "yacc_sql.y"
>>>>>>> subquery resolve
                           {
      Condition expr;
      condition_init(&expr, (yyvsp[-1].comp_op), (yyvsp[-2].exp3), (yyvsp[0].exp3));
      CONTEXT->havings[CONTEXT->having_length++] = expr;
    }
<<<<<<< HEAD
#line 2183 "yacc_sql.tab.c"
    break;

  case 72:
#line 571 "yacc_sql.y"
=======
#line 2207 "yacc_sql.tab.c"
    break;

  case 74:
#line 584 "yacc_sql.y"
>>>>>>> subquery resolve
          {
    	Expr *expr = malloc(sizeof(Expr));
      UnaryExpr* u_expr = malloc(sizeof(UnaryExpr));
      unary_expr_init_value(u_expr, &CONTEXT->values[CONTEXT->value_length-1]);
      expr_init_unary(expr, u_expr);
      (yyval.exp1) = expr;
    }
<<<<<<< HEAD
#line 2195 "yacc_sql.tab.c"
    break;

  case 73:
#line 578 "yacc_sql.y"
=======
#line 2219 "yacc_sql.tab.c"
    break;

  case 75:
#line 591 "yacc_sql.y"
>>>>>>> subquery resolve
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
#line 2209 "yacc_sql.tab.c"
    break;

  case 74:
#line 587 "yacc_sql.y"
=======
#line 2233 "yacc_sql.tab.c"
    break;

  case 76:
#line 600 "yacc_sql.y"
>>>>>>> subquery resolve
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
#line 2223 "yacc_sql.tab.c"
    break;

  case 75:
#line 596 "yacc_sql.y"
=======
#line 2247 "yacc_sql.tab.c"
    break;

  case 77:
#line 609 "yacc_sql.y"
>>>>>>> subquery resolve
                             {
      expr_set_with_brace((yyvsp[-1].exp3));
      (yyval.exp1) = (yyvsp[-1].exp3);
    }
<<<<<<< HEAD
#line 2232 "yacc_sql.tab.c"
    break;

  case 76:
#line 600 "yacc_sql.y"
                {
      (yyval.exp1) = (yyvsp[0].exp4);
    }
#line 2240 "yacc_sql.tab.c"
    break;

  case 77:
#line 603 "yacc_sql.y"
                     {
      (yyval.exp1) = (yyvsp[0].exp5);
    }
#line 2248 "yacc_sql.tab.c"
    break;

  case 78:
#line 606 "yacc_sql.y"
=======
#line 2256 "yacc_sql.tab.c"
    break;

  case 78:
#line 613 "yacc_sql.y"
                {
      (yyval.exp1) = (yyvsp[0].exp4);
    }
#line 2264 "yacc_sql.tab.c"
    break;

  case 79:
#line 616 "yacc_sql.y"
                     {
      (yyval.exp1) = (yyvsp[0].exp5);
    }
#line 2272 "yacc_sql.tab.c"
    break;

  case 80:
#line 619 "yacc_sql.y"
>>>>>>> subquery resolve
                 {
       (yyval.exp1) = (yyvsp[0].exp6);
    }
<<<<<<< HEAD
#line 2256 "yacc_sql.tab.c"
    break;

  case 79:
#line 612 "yacc_sql.y"
             {
      CONTEXT->aggrfunctype = MAX;
    }
#line 2264 "yacc_sql.tab.c"
    break;

  case 80:
#line 615 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = MIN;
    }
#line 2272 "yacc_sql.tab.c"
    break;

  case 81:
#line 618 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = SUM;
    }
#line 2280 "yacc_sql.tab.c"
    break;

  case 82:
#line 621 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = AVG;
    }
#line 2288 "yacc_sql.tab.c"
    break;

  case 83:
#line 624 "yacc_sql.y"
                 {
      CONTEXT->aggrfunctype = COUNT;
    }
#line 2296 "yacc_sql.tab.c"
    break;

  case 84:
#line 631 "yacc_sql.y"
=======
#line 2280 "yacc_sql.tab.c"
    break;

  case 81:
#line 625 "yacc_sql.y"
             {
      CONTEXT->aggrfunctype = MAX;
    }
#line 2288 "yacc_sql.tab.c"
    break;

  case 82:
#line 628 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = MIN;
    }
#line 2296 "yacc_sql.tab.c"
    break;

  case 83:
#line 631 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = SUM;
    }
#line 2304 "yacc_sql.tab.c"
    break;

  case 84:
#line 634 "yacc_sql.y"
               {
      CONTEXT->aggrfunctype = AVG;
    }
#line 2312 "yacc_sql.tab.c"
    break;

  case 85:
#line 637 "yacc_sql.y"
                 {
      CONTEXT->aggrfunctype = COUNT;
    }
#line 2320 "yacc_sql.tab.c"
    break;

  case 86:
#line 644 "yacc_sql.y"
>>>>>>> subquery resolve
    {
      AggrFuncExpr* afexpr = malloc(sizeof(AggrFuncExpr));
      aggr_func_expr_init(afexpr, CONTEXT->aggrfunctype, (yyvsp[-1].exp3));
      Expr* expr = malloc(sizeof(Expr));
      expr_init_aggr_func(expr, afexpr);
      (yyval.exp5) = expr;
    }
<<<<<<< HEAD
#line 2308 "yacc_sql.tab.c"
    break;

  case 85:
#line 639 "yacc_sql.y"
=======
#line 2332 "yacc_sql.tab.c"
    break;

  case 87:
#line 652 "yacc_sql.y"
>>>>>>> subquery resolve
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
#line 2331 "yacc_sql.tab.c"
    break;

  case 86:
#line 661 "yacc_sql.y"
=======
#line 2355 "yacc_sql.tab.c"
    break;

  case 88:
#line 674 "yacc_sql.y"
>>>>>>> subquery resolve
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 0);
      func_expr_init_params(fexpr, (yyvsp[-1].exp3), NULL);
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      (yyval.exp4) = expr;
    }
<<<<<<< HEAD
#line 2344 "yacc_sql.tab.c"
    break;

  case 87:
#line 671 "yacc_sql.y"
=======
#line 2368 "yacc_sql.tab.c"
    break;

  case 89:
#line 684 "yacc_sql.y"
>>>>>>> subquery resolve
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 1);
      func_expr_init_params(fexpr, (yyvsp[-1].exp3), NULL);
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      (yyval.exp4) = expr;
    }
<<<<<<< HEAD
#line 2357 "yacc_sql.tab.c"
    break;

  case 88:
#line 681 "yacc_sql.y"
=======
#line 2381 "yacc_sql.tab.c"
    break;

  case 90:
#line 694 "yacc_sql.y"
>>>>>>> subquery resolve
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 1);
      func_expr_init_params(fexpr, (yyvsp[-3].exp3), (yyvsp[-1].exp3));
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      (yyval.exp4) = expr;
    }
<<<<<<< HEAD
#line 2370 "yacc_sql.tab.c"
    break;

  case 89:
#line 691 "yacc_sql.y"
=======
#line 2394 "yacc_sql.tab.c"
    break;

  case 91:
#line 704 "yacc_sql.y"
>>>>>>> subquery resolve
    {
      FuncExpr* fexpr = malloc(sizeof(FuncExpr));
      func_expr_init_type(fexpr, 2);
      func_expr_init_params(fexpr, (yyvsp[-3].exp3), (yyvsp[-1].exp3));
      Expr* expr = malloc(sizeof(Expr));
      expr_init_func(expr, fexpr);
      (yyval.exp4) = expr;
    }
<<<<<<< HEAD
#line 2383 "yacc_sql.tab.c"
    break;

  case 90:
#line 702 "yacc_sql.y"
=======
#line 2407 "yacc_sql.tab.c"
    break;

  case 92:
#line 715 "yacc_sql.y"
>>>>>>> subquery resolve
                                                                                          {
      //printf("THE SUBQUERY has %d projects %d froms %d inner_join_conditions %d conditions %d groupbys %d havings %d orderbys\n", $3, $5->from_len, $5->inner_join_conditions_len, $6, $7, $8, $9);

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
#line 2419 "yacc_sql.tab.c"
    break;

  case 91:
#line 736 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 2427 "yacc_sql.tab.c"
    break;

  case 92:
#line 739 "yacc_sql.y"
               {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], -((yyvsp[0].number)));
		}
#line 2435 "yacc_sql.tab.c"
    break;

  case 93:
#line 742 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 2443 "yacc_sql.tab.c"
    break;

  case 94:
#line 745 "yacc_sql.y"
              {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], -((yyvsp[0].floats)));
		}
#line 2451 "yacc_sql.tab.c"
    break;

  case 95:
#line 748 "yacc_sql.y"
=======
#line 2451 "yacc_sql.tab.c"
    break;

  case 93:
#line 757 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 2459 "yacc_sql.tab.c"
    break;

  case 94:
#line 760 "yacc_sql.y"
               {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], -((yyvsp[0].number)));
		}
#line 2467 "yacc_sql.tab.c"
    break;

  case 95:
#line 763 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 2475 "yacc_sql.tab.c"
    break;

  case 96:
#line 766 "yacc_sql.y"
              {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], -((yyvsp[0].floats)));
		}
#line 2483 "yacc_sql.tab.c"
    break;

  case 97:
#line 769 "yacc_sql.y"
>>>>>>> subquery resolve
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
<<<<<<< HEAD
#line 2460 "yacc_sql.tab.c"
    break;

  case 96:
#line 752 "yacc_sql.y"
=======
#line 2492 "yacc_sql.tab.c"
    break;

  case 98:
#line 773 "yacc_sql.y"
>>>>>>> subquery resolve
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
#line 2475 "yacc_sql.tab.c"
    break;

  case 97:
#line 762 "yacc_sql.y"
                {
      value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    }
#line 2483 "yacc_sql.tab.c"
    break;

  case 98:
#line 769 "yacc_sql.y"
=======
#line 2507 "yacc_sql.tab.c"
    break;

  case 99:
#line 783 "yacc_sql.y"
                {
      value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    }
#line 2515 "yacc_sql.tab.c"
    break;

  case 100:
#line 790 "yacc_sql.y"
>>>>>>> subquery resolve
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
<<<<<<< HEAD
#line 2495 "yacc_sql.tab.c"
    break;

  case 99:
#line 779 "yacc_sql.y"
=======
#line 2527 "yacc_sql.tab.c"
    break;

  case 101:
#line 800 "yacc_sql.y"
>>>>>>> subquery resolve
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
<<<<<<< HEAD
#line 2507 "yacc_sql.tab.c"
    break;

  case 100:
#line 789 "yacc_sql.y"
=======
#line 2539 "yacc_sql.tab.c"
    break;

  case 102:
#line 810 "yacc_sql.y"
>>>>>>> subquery resolve
                {
      printf("THE QUERY has %d projects %d froms %d inner_join_conditions %d conditions %d groupbys %d havings %d orderbys\n\n", (yyvsp[-7].cur_len), (yyvsp[-5].from_info)->from_len, (yyvsp[-5].from_info)->inner_join_conditions_len, (yyvsp[-4].cur_len), (yyvsp[-3].cur_len), (yyvsp[-2].cur_len), (yyvsp[-1].cur_len));

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
#line 2540 "yacc_sql.tab.c"
    break;

  case 101:
#line 820 "yacc_sql.y"
=======
#line 2572 "yacc_sql.tab.c"
    break;

  case 103:
#line 841 "yacc_sql.y"
>>>>>>> subquery resolve
                   {  
			ProjectCol project_col;
			projectcol_init_star(&project_col, NULL);
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
		}
<<<<<<< HEAD
#line 2551 "yacc_sql.tab.c"
    break;

  case 102:
#line 827 "yacc_sql.y"
=======
#line 2583 "yacc_sql.tab.c"
    break;

  case 104:
#line 848 "yacc_sql.y"
>>>>>>> subquery resolve
                         {
      ProjectCol project_col;
			projectcol_init_star(&project_col, (yyvsp[-3].string));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
<<<<<<< HEAD
#line 2562 "yacc_sql.tab.c"
    break;

  case 103:
#line 834 "yacc_sql.y"
=======
#line 2594 "yacc_sql.tab.c"
    break;

  case 105:
#line 855 "yacc_sql.y"
>>>>>>> subquery resolve
                      {
      ProjectCol project_col;
      projectcol_init_expr(&project_col, (yyvsp[-1].exp3));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
<<<<<<< HEAD
#line 2573 "yacc_sql.tab.c"
    break;

  case 104:
#line 842 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2581 "yacc_sql.tab.c"
    break;

  case 105:
#line 846 "yacc_sql.y"
=======
#line 2605 "yacc_sql.tab.c"
    break;

  case 106:
#line 863 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2613 "yacc_sql.tab.c"
    break;

  case 107:
#line 867 "yacc_sql.y"
>>>>>>> subquery resolve
                         {  
			ProjectCol project_col;
			projectcol_init_star(&project_col, NULL);
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
		}
<<<<<<< HEAD
#line 2592 "yacc_sql.tab.c"
    break;

  case 106:
#line 853 "yacc_sql.y"
=======
#line 2624 "yacc_sql.tab.c"
    break;

  case 108:
#line 874 "yacc_sql.y"
>>>>>>> subquery resolve
                               {
      ProjectCol project_col;
			projectcol_init_star(&project_col, (yyvsp[-3].string));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
<<<<<<< HEAD
#line 2603 "yacc_sql.tab.c"
    break;

  case 107:
#line 860 "yacc_sql.y"
=======
#line 2635 "yacc_sql.tab.c"
    break;

  case 109:
#line 881 "yacc_sql.y"
>>>>>>> subquery resolve
                            {
      ProjectCol project_col;
      projectcol_init_expr(&project_col, (yyvsp[-1].exp3));
			CONTEXT->projects[CONTEXT->project_length++]=project_col;
      (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
<<<<<<< HEAD
#line 2614 "yacc_sql.tab.c"
    break;

  case 108:
#line 869 "yacc_sql.y"
=======
#line 2646 "yacc_sql.tab.c"
    break;

  case 110:
#line 890 "yacc_sql.y"
>>>>>>> subquery resolve
                {
			CONTEXT->froms[CONTEXT->from_length++]=(yyvsp[-1].string);
      (yyval.from_info) = (yyvsp[0].from_info);
      (yyval.from_info)->from_len++;
    }
<<<<<<< HEAD
#line 2624 "yacc_sql.tab.c"
    break;

  case 109:
#line 877 "yacc_sql.y"
=======
#line 2656 "yacc_sql.tab.c"
    break;

  case 111:
#line 898 "yacc_sql.y"
>>>>>>> subquery resolve
                {
      // new FromInfo
      (yyval.from_info) = (FromInfo*)malloc(sizeof(FromInfo));
      (yyval.from_info)->from_len = 0;
      (yyval.from_info)->inner_join_conditions_len = 0;
    }
<<<<<<< HEAD
#line 2635 "yacc_sql.tab.c"
    break;

  case 110:
#line 883 "yacc_sql.y"
=======
#line 2667 "yacc_sql.tab.c"
    break;

  case 112:
#line 904 "yacc_sql.y"
>>>>>>> subquery resolve
                        {	
        CONTEXT->froms[CONTEXT->from_length++]=(yyvsp[-1].string);
        (yyval.from_info) = (yyvsp[0].from_info);
        (yyval.from_info)->from_len++;
		  }
<<<<<<< HEAD
#line 2645 "yacc_sql.tab.c"
    break;

  case 111:
#line 888 "yacc_sql.y"
=======
#line 2677 "yacc_sql.tab.c"
    break;

  case 113:
#line 909 "yacc_sql.y"
>>>>>>> subquery resolve
                                                  {
        CONTEXT->froms[CONTEXT->from_length++]=(yyvsp[-2].string);
        (yyval.from_info) = (yyvsp[0].from_info);
        (yyval.from_info)->from_len++;
        (yyval.from_info)->inner_join_conditions_len += (yyvsp[-1].cur_len);
    }
<<<<<<< HEAD
#line 2656 "yacc_sql.tab.c"
    break;

  case 112:
#line 896 "yacc_sql.y"
                    {
    (yyval.cur_len) = 0;
  }
#line 2664 "yacc_sql.tab.c"
    break;

  case 113:
#line 899 "yacc_sql.y"
                                     {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 2672 "yacc_sql.tab.c"
    break;

  case 114:
#line 904 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2680 "yacc_sql.tab.c"
    break;

  case 115:
#line 907 "yacc_sql.y"
=======
#line 2688 "yacc_sql.tab.c"
    break;

  case 114:
#line 917 "yacc_sql.y"
                    {
    (yyval.cur_len) = 0;
  }
#line 2696 "yacc_sql.tab.c"
    break;

  case 115:
#line 920 "yacc_sql.y"
                                     {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 2704 "yacc_sql.tab.c"
    break;

  case 116:
#line 925 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2712 "yacc_sql.tab.c"
    break;

  case 117:
#line 928 "yacc_sql.y"
>>>>>>> subquery resolve
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
			}
<<<<<<< HEAD
#line 2689 "yacc_sql.tab.c"
    break;

  case 116:
#line 913 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2697 "yacc_sql.tab.c"
    break;

  case 117:
#line 916 "yacc_sql.y"
=======
#line 2721 "yacc_sql.tab.c"
    break;

  case 118:
#line 934 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2729 "yacc_sql.tab.c"
    break;

  case 119:
#line 937 "yacc_sql.y"
>>>>>>> subquery resolve
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
			}
<<<<<<< HEAD
#line 2706 "yacc_sql.tab.c"
    break;

  case 118:
#line 922 "yacc_sql.y"
                 { 
      (yyval.cur_len) = 0;
    }
#line 2714 "yacc_sql.tab.c"
    break;

  case 119:
#line 925 "yacc_sql.y"
                                                    {	
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2722 "yacc_sql.tab.c"
    break;

  case 120:
#line 930 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2730 "yacc_sql.tab.c"
    break;

  case 121:
#line 933 "yacc_sql.y"
                                                 {
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2738 "yacc_sql.tab.c"
    break;

  case 122:
#line 940 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2744 "yacc_sql.tab.c"
    break;

  case 123:
#line 941 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2750 "yacc_sql.tab.c"
    break;

  case 124:
#line 942 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2756 "yacc_sql.tab.c"
    break;

  case 125:
#line 943 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2762 "yacc_sql.tab.c"
    break;

  case 126:
#line 944 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2768 "yacc_sql.tab.c"
    break;

  case 127:
#line 945 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2774 "yacc_sql.tab.c"
    break;

  case 128:
#line 946 "yacc_sql.y"
           { CONTEXT->comp = LIKE_OP; }
#line 2780 "yacc_sql.tab.c"
    break;

  case 129:
#line 947 "yacc_sql.y"
               { CONTEXT->comp = NOT_LIKE_OP; }
#line 2786 "yacc_sql.tab.c"
    break;

  case 130:
#line 951 "yacc_sql.y"
=======
#line 2738 "yacc_sql.tab.c"
    break;

  case 120:
#line 943 "yacc_sql.y"
                 { 
      (yyval.cur_len) = 0;
    }
#line 2746 "yacc_sql.tab.c"
    break;

  case 121:
#line 946 "yacc_sql.y"
                                                    {	
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2754 "yacc_sql.tab.c"
    break;

  case 122:
#line 951 "yacc_sql.y"
                {
      (yyval.cur_len) = 0;
    }
#line 2762 "yacc_sql.tab.c"
    break;

  case 123:
#line 954 "yacc_sql.y"
                                                 {
        (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
    }
#line 2770 "yacc_sql.tab.c"
    break;

  case 124:
#line 961 "yacc_sql.y"
             { (yyval.comp_op) = EQUAL_TO; }
#line 2776 "yacc_sql.tab.c"
    break;

  case 125:
#line 962 "yacc_sql.y"
         { (yyval.comp_op) = LESS_THAN; }
#line 2782 "yacc_sql.tab.c"
    break;

  case 126:
#line 963 "yacc_sql.y"
         { (yyval.comp_op) = GREAT_THAN; }
#line 2788 "yacc_sql.tab.c"
    break;

  case 127:
#line 964 "yacc_sql.y"
         { (yyval.comp_op) = LESS_EQUAL; }
#line 2794 "yacc_sql.tab.c"
    break;

  case 128:
#line 965 "yacc_sql.y"
         { (yyval.comp_op) = GREAT_EQUAL; }
#line 2800 "yacc_sql.tab.c"
    break;

  case 129:
#line 966 "yacc_sql.y"
         { (yyval.comp_op) = NOT_EQUAL; }
#line 2806 "yacc_sql.tab.c"
    break;

  case 130:
#line 967 "yacc_sql.y"
           { (yyval.comp_op) = LIKE_OP; }
#line 2812 "yacc_sql.tab.c"
    break;

  case 131:
#line 968 "yacc_sql.y"
               { (yyval.comp_op) = NOT_LIKE_OP; }
#line 2818 "yacc_sql.tab.c"
    break;

  case 132:
#line 972 "yacc_sql.y"
>>>>>>> subquery resolve
        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
<<<<<<< HEAD
#line 2798 "yacc_sql.tab.c"
    break;

  case 131:
#line 960 "yacc_sql.y"
=======
#line 2830 "yacc_sql.tab.c"
    break;

  case 133:
#line 981 "yacc_sql.y"
>>>>>>> subquery resolve
        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
<<<<<<< HEAD
#line 2810 "yacc_sql.tab.c"
    break;

  case 132:
#line 969 "yacc_sql.y"
=======
#line 2842 "yacc_sql.tab.c"
    break;

  case 134:
#line 990 "yacc_sql.y"
>>>>>>> subquery resolve
        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		OrderBy orderby;
		orderby_init(&orderby, FALSE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
<<<<<<< HEAD
#line 2822 "yacc_sql.tab.c"
    break;

  case 133:
#line 978 "yacc_sql.y"
=======
#line 2854 "yacc_sql.tab.c"
    break;

  case 135:
#line 999 "yacc_sql.y"
>>>>>>> subquery resolve
        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
<<<<<<< HEAD
#line 2834 "yacc_sql.tab.c"
    break;

  case 134:
#line 987 "yacc_sql.y"
=======
#line 2866 "yacc_sql.tab.c"
    break;

  case 136:
#line 1008 "yacc_sql.y"
>>>>>>> subquery resolve
        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		OrderBy orderby;
		orderby_init(&orderby, FALSE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
<<<<<<< HEAD
#line 2846 "yacc_sql.tab.c"
    break;

  case 135:
#line 996 "yacc_sql.y"
=======
#line 2878 "yacc_sql.tab.c"
    break;

  case 137:
#line 1017 "yacc_sql.y"
>>>>>>> subquery resolve
        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		OrderBy orderby;
		orderby_init(&orderby, TRUE, &attr);
		CONTEXT->orderbys[CONTEXT->orderby_length++] = orderby;
	}
<<<<<<< HEAD
#line 2858 "yacc_sql.tab.c"
    break;

  case 136:
#line 1006 "yacc_sql.y"
                {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 2866 "yacc_sql.tab.c"
    break;

  case 137:
#line 1010 "yacc_sql.y"
                {
    (yyval.cur_len) = 1;
	}
#line 2874 "yacc_sql.tab.c"
    break;

  case 138:
#line 1015 "yacc_sql.y"
                    {
   (yyval.cur_len) = 0;
  }
#line 2882 "yacc_sql.tab.c"
    break;

  case 139:
#line 1019 "yacc_sql.y"
                {
      (yyval.cur_len) = (yyvsp[0].cur_len);
	}
#line 2890 "yacc_sql.tab.c"
    break;

  case 140:
#line 1026 "yacc_sql.y"
=======
#line 2890 "yacc_sql.tab.c"
    break;

  case 138:
#line 1027 "yacc_sql.y"
                {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 2898 "yacc_sql.tab.c"
    break;

  case 139:
#line 1031 "yacc_sql.y"
                {
    (yyval.cur_len) = 1;
	}
#line 2906 "yacc_sql.tab.c"
    break;

  case 140:
#line 1036 "yacc_sql.y"
                    {
   (yyval.cur_len) = 0;
  }
#line 2914 "yacc_sql.tab.c"
    break;

  case 141:
#line 1040 "yacc_sql.y"
                {
      (yyval.cur_len) = (yyvsp[0].cur_len);
	}
#line 2922 "yacc_sql.tab.c"
    break;

  case 142:
#line 1047 "yacc_sql.y"
>>>>>>> subquery resolve
        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		CONTEXT->groupbys[CONTEXT->groupby_length++] = attr;
	}
<<<<<<< HEAD
#line 2900 "yacc_sql.tab.c"
    break;

  case 141:
#line 1033 "yacc_sql.y"
=======
#line 2932 "yacc_sql.tab.c"
    break;

  case 143:
#line 1054 "yacc_sql.y"
>>>>>>> subquery resolve
        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		CONTEXT->groupbys[CONTEXT->groupby_length++] = attr;
	}
<<<<<<< HEAD
#line 2910 "yacc_sql.tab.c"
    break;

  case 142:
#line 1042 "yacc_sql.y"
                {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 2918 "yacc_sql.tab.c"
    break;

  case 143:
#line 1046 "yacc_sql.y"
                {
    (yyval.cur_len) = 1;
	}
#line 2926 "yacc_sql.tab.c"
    break;

  case 144:
#line 1051 "yacc_sql.y"
                    {
    (yyval.cur_len) = 0;
  }
#line 2934 "yacc_sql.tab.c"
    break;

  case 145:
#line 1055 "yacc_sql.y"
                {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 2942 "yacc_sql.tab.c"
    break;

  case 146:
#line 1062 "yacc_sql.y"
=======
#line 2942 "yacc_sql.tab.c"
    break;

  case 144:
#line 1063 "yacc_sql.y"
                {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 2950 "yacc_sql.tab.c"
    break;

  case 145:
#line 1067 "yacc_sql.y"
                {
    (yyval.cur_len) = 1;
	}
#line 2958 "yacc_sql.tab.c"
    break;

  case 146:
#line 1072 "yacc_sql.y"
                    {
    (yyval.cur_len) = 0;
  }
#line 2966 "yacc_sql.tab.c"
    break;

  case 147:
#line 1076 "yacc_sql.y"
                {
    (yyval.cur_len) = (yyvsp[0].cur_len) + 1;
	}
#line 2974 "yacc_sql.tab.c"
    break;

  case 148:
#line 1083 "yacc_sql.y"
>>>>>>> subquery resolve
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
<<<<<<< HEAD
#line 2951 "yacc_sql.tab.c"
    break;


#line 2955 "yacc_sql.tab.c"
=======
#line 2983 "yacc_sql.tab.c"
    break;


#line 2987 "yacc_sql.tab.c"
>>>>>>> subquery resolve

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
#line 1067 "yacc_sql.y"
=======
#line 1088 "yacc_sql.y"
>>>>>>> subquery resolve

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
