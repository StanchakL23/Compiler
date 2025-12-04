/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "symbtab.h"

//current environment pointer (for scope)
Env *current_env = NULL;
IntermediateCode *global_code = NULL;

// Temporary storage for building type records during parsing
static BaseType current_base_type;
static int dimension_stack[10];  // fixed size for simplicity
static int dimension_count = 0;

extern FILE *yyin;
//Declaration for error handling
void yyerror(const char *s);
int yylex(void);

#line 93 "/home/lstanchak/Assignment2/build/parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_WHILE_ = 3,                     /* WHILE_  */
  YYSYMBOL_IF_ = 4,                        /* IF_  */
  YYSYMBOL_ELSE_ = 5,                      /* ELSE_  */
  YYSYMBOL_RETURN_ = 6,                    /* RETURN_  */
  YYSYMBOL_BREAK_ = 7,                     /* BREAK_  */
  YYSYMBOL_DO = 8,                         /* DO  */
  YYSYMBOL_LEFTBRACE = 9,                  /* LEFTBRACE  */
  YYSYMBOL_RIGHTBRACE = 10,                /* RIGHTBRACE  */
  YYSYMBOL_SEMIC = 11,                     /* SEMIC  */
  YYSYMBOL_EQUALS = 12,                    /* EQUALS  */
  YYSYMBOL_PLUS = 13,                      /* PLUS  */
  YYSYMBOL_MINUS = 14,                     /* MINUS  */
  YYSYMBOL_LEFTPARAN = 15,                 /* LEFTPARAN  */
  YYSYMBOL_RIGHTPARAN = 16,                /* RIGHTPARAN  */
  YYSYMBOL_LT = 17,                        /* LT  */
  YYSYMBOL_GT = 18,                        /* GT  */
  YYSYMBOL_LE = 19,                        /* LE  */
  YYSYMBOL_GE = 20,                        /* GE  */
  YYSYMBOL_LEFTBRACK = 21,                 /* LEFTBRACK  */
  YYSYMBOL_RIGHTBRACK = 22,                /* RIGHTBRACK  */
  YYSYMBOL_AND = 23,                       /* AND  */
  YYSYMBOL_OR = 24,                        /* OR  */
  YYSYMBOL_NE = 25,                        /* NE  */
  YYSYMBOL_ASSIGN = 26,                    /* ASSIGN  */
  YYSYMBOL_NOT = 27,                       /* NOT  */
  YYSYMBOL_MULTIPLY = 28,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 29,                    /* DIVIDE  */
  YYSYMBOL_ID = 30,                        /* ID  */
  YYSYMBOL_BASIC = 31,                     /* BASIC  */
  YYSYMBOL_NUM = 32,                       /* NUM  */
  YYSYMBOL_REAL = 33,                      /* REAL  */
  YYSYMBOL_BOOLCONST = 34,                 /* BOOLCONST  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_program = 36,                   /* program  */
  YYSYMBOL_block = 37,                     /* block  */
  YYSYMBOL_38_1 = 38,                      /* $@1  */
  YYSYMBOL_decls = 39,                     /* decls  */
  YYSYMBOL_decl = 40,                      /* decl  */
  YYSYMBOL_base_type_spec = 41,            /* base_type_spec  */
  YYSYMBOL_dims = 42,                      /* dims  */
  YYSYMBOL_stmts = 43,                     /* stmts  */
  YYSYMBOL_stmt = 44,                      /* stmt  */
  YYSYMBOL_loc = 45,                       /* loc  */
  YYSYMBOL_bool = 46,                      /* bool  */
  YYSYMBOL_join = 47,                      /* join  */
  YYSYMBOL_equality = 48,                  /* equality  */
  YYSYMBOL_rel = 49,                       /* rel  */
  YYSYMBOL_expr = 50,                      /* expr  */
  YYSYMBOL_term = 51,                      /* term  */
  YYSYMBOL_unary = 52,                     /* unary  */
  YYSYMBOL_factor = 53                     /* factor  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   118

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  50
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  101

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    50,    50,    57,    57,    67,    68,    73,    84,    94,
     100,   104,   107,   111,   131,   133,   135,   137,   139,   141,
     143,   145,   147,   152,   190,   205,   207,   212,   214,   219,
     221,   223,   228,   230,   232,   234,   236,   241,   260,   279,
     287,   306,   325,   333,   335,   337,   342,   347,   368,   373,
     378
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "WHILE_", "IF_",
  "ELSE_", "RETURN_", "BREAK_", "DO", "LEFTBRACE", "RIGHTBRACE", "SEMIC",
  "EQUALS", "PLUS", "MINUS", "LEFTPARAN", "RIGHTPARAN", "LT", "GT", "LE",
  "GE", "LEFTBRACK", "RIGHTBRACK", "AND", "OR", "NE", "ASSIGN", "NOT",
  "MULTIPLY", "DIVIDE", "ID", "BASIC", "NUM", "REAL", "BOOLCONST",
  "$accept", "program", "block", "$@1", "decls", "decl", "base_type_spec",
  "dims", "stmts", "stmt", "loc", "bool", "join", "equality", "rel",
  "expr", "term", "unary", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-23)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-13)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       1,   -23,     6,    13,   -23,    45,    25,    52,    71,    35,
      72,   -23,   -23,   -23,   -23,   -23,   -23,    47,    44,     8,
     -23,   -23,    71,    71,    71,    71,    71,   -23,   -23,   -23,
      49,    -6,    54,     0,   -23,    93,    31,   -23,   -23,   -23,
      68,   -23,     3,   -23,   -23,    71,    71,    11,    12,   -23,
      14,   -23,   -23,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    69,    13,    57,    80,    15,
       2,    72,    72,   -23,    54,     0,   -23,   -23,    31,    31,
      48,    48,    48,    48,   -23,   -23,    71,    82,    73,   -23,
     -23,   -23,   -23,    88,    42,   -23,   -23,    72,    85,   -23,
     -23
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     5,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     3,    24,     8,    20,     6,    10,     0,     0,     0,
      22,    21,     0,     0,     0,     0,     0,    48,    49,    50,
      47,     0,    26,    28,    31,    36,    39,    42,    45,    18,
       0,     5,     0,     2,    11,     0,     0,     0,     0,    44,
       0,    43,    19,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    46,    25,    27,    29,    30,    37,    38,
      32,    34,    33,    35,    40,    41,     0,     0,     0,     7,
      23,    13,    16,    14,     0,     4,     9,     0,     0,    15,
      17
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -23,   -23,   -23,   -23,    56,   -23,   -23,   -23,   -17,    -7,
      -3,   -14,    46,    64,    27,    55,    30,   -22,   -23
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,    14,    41,     3,    15,    16,    42,    17,    18,
      30,    31,    32,    33,    34,    35,    36,    37,    38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      19,    44,    49,    40,    51,    52,     4,    19,    47,    48,
       1,    50,    55,    91,     5,    19,     6,     7,    53,     8,
       9,    10,    11,   -12,    67,    56,    53,    71,    72,    45,
      73,    69,    70,    68,    46,    53,    53,    90,    53,    53,
      22,    84,    85,    12,    13,     5,    39,     6,     7,    87,
       8,     9,    10,    11,   -12,    20,    21,    43,    98,    63,
      64,    57,    58,    19,    92,    93,    53,    23,    19,    19,
      45,    65,    94,     5,    12,     6,     7,    54,     8,     9,
      10,    11,    76,    77,    86,    24,    25,    78,    79,    88,
      99,    89,    95,    97,    19,    96,   100,    66,    26,    74,
       0,    12,    12,    27,    28,    29,    57,    58,     0,     0,
      59,    60,    61,    62,    80,    81,    82,    83,    75
};

static const yytype_int8 yycheck[] =
{
       3,    18,    24,    10,    26,    11,     0,    10,    22,    23,
       9,    25,    12,    11,     1,    18,     3,     4,    24,     6,
       7,     8,     9,    10,    21,    25,    24,    16,    16,    21,
      16,    45,    46,    30,    26,    24,    24,    22,    24,    24,
      15,    63,    64,    30,    31,     1,    11,     3,     4,    66,
       6,     7,     8,     9,    10,    10,    11,    10,    16,    28,
      29,    13,    14,    66,    71,    72,    24,    15,    71,    72,
      21,     3,    86,     1,    30,     3,     4,    23,     6,     7,
       8,     9,    55,    56,    15,    14,    15,    57,    58,    32,
      97,    11,    10,     5,    97,    22,    11,    41,    27,    53,
      -1,    30,    30,    32,    33,    34,    13,    14,    -1,    -1,
      17,    18,    19,    20,    59,    60,    61,    62,    54
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    36,    39,     0,     1,     3,     4,     6,     7,
       8,     9,    30,    31,    37,    40,    41,    43,    44,    45,
      10,    11,    15,    15,    14,    15,    27,    32,    33,    34,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    11,
      44,    38,    42,    10,    43,    21,    26,    46,    46,    52,
      46,    52,    11,    24,    23,    12,    25,    13,    14,    17,
      18,    19,    20,    28,    29,     3,    39,    21,    30,    46,
      46,    16,    16,    16,    47,    48,    49,    49,    51,    51,
      50,    50,    50,    50,    52,    52,    15,    43,    32,    11,
      22,    11,    44,    44,    46,    10,    22,     5,    16,    44,
      11
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    38,    37,    39,    39,    40,    41,    42,
      42,    43,    43,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    45,    45,    46,    46,    47,    47,    48,
      48,    48,    49,    49,    49,    49,    49,    50,    50,    50,
      51,    51,    51,    52,    52,    52,    53,    53,    53,    53,
      53
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     0,     5,     0,     2,     4,     1,     4,
       0,     2,     0,     4,     5,     7,     5,     7,     2,     3,
       1,     2,     2,     4,     1,     3,     1,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     1,     2,     2,     1,     3,     1,     1,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* program: LEFTBRACE decls stmts RIGHTBRACE  */
#line 51 "parser.y"
        { 
            printf("program -> { decls stmts }\n"); 
        }
#line 1199 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 3: /* $@1: %empty  */
#line 57 "parser.y"
                { current_env = env_create(current_env); }
#line 1205 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 4: /* block: LEFTBRACE $@1 decls stmts RIGHTBRACE  */
#line 58 "parser.y"
        { 
            printf("block -> decls stmts\n");
            env_print_scope(current_env);
            current_env = current_env->prev; 
        }
#line 1215 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 5: /* decls: %empty  */
#line 67 "parser.y"
        { printf("decls -> e\n"); }
#line 1221 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 6: /* decls: decls decl  */
#line 69 "parser.y"
        { printf("decls -> decl decls\n"); }
#line 1227 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 7: /* decl: base_type_spec dims ID SEMIC  */
#line 74 "parser.y"
        {
            printf("decl -> base_type_spec dims ID SEMIC\n");  
            TypeRecord *type = type_record_create(current_base_type, dimension_stack, dimension_count);
            env_put(current_env, (yyvsp[-1].str), type, false);
            dimension_count = 0;
            free((yyvsp[-1].str));
        }
#line 1239 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 8: /* base_type_spec: BASIC  */
#line 85 "parser.y"
        {
            dimension_count = 0;  // reset dimensions
            if (strcmp((yyvsp[0].str), "int") == 0) current_base_type = INT;
            else if (strcmp((yyvsp[0].str), "float") == 0) current_base_type = FLOAT;
            else if (strcmp((yyvsp[0].str), "bool") == 0) current_base_type = BOOL;
            free((yyvsp[0].str));
        }
#line 1251 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 9: /* dims: dims LEFTBRACK NUM RIGHTBRACK  */
#line 95 "parser.y"
        {
            printf("dims -> dims [ NUM ]\n");
            dimension_stack[dimension_count++] = (yyvsp[-1].num);
        }
#line 1260 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 10: /* dims: %empty  */
#line 100 "parser.y"
        { printf("dims -> e\n"); }
#line 1266 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 11: /* stmts: stmt stmts  */
#line 105 "parser.y"
        { printf("stmts -> stmt stmts\n"); }
#line 1272 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 12: /* stmts: %empty  */
#line 107 "parser.y"
        { printf("stmts -> e\n"); }
#line 1278 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 13: /* stmt: loc ASSIGN bool SEMIC  */
#line 112 "parser.y"
        { 
            printf("stmt -> loc = bool ;\n"); 
            
            Address *destination_addr = (yyvsp[-3].addr); 
            Address *source_addr = (yyvsp[-1].addr);      
            OpCode op;
            
            // Check if destination is a temporary variable (like t12)
            // If it's a temporary, it means it holds the calculated address of an array element.
            if (destination_addr && destination_addr->type == ADDR_VARIABLE && destination_addr->data.variable.name[0] == 't') {
                op = OP_STORE; // Use STORE for array element assignment: STORE $3 into address $1
            } else {
                op = OP_ASSIGN; // Use ASSIGN for simple variable assignment: $1 = $3
            }
            
            // Note: src2 is NULL for both
            Instruction *instr = instruction_create(op, source_addr, NULL, destination_addr, current_env);
            intermediate_code_append(global_code, instr);
        }
#line 1302 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 14: /* stmt: IF_ LEFTPARAN bool RIGHTPARAN stmt  */
#line 132 "parser.y"
        { printf("stmt -> if ( bool ) stmt\n"); }
#line 1308 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 15: /* stmt: IF_ LEFTPARAN bool RIGHTPARAN stmt ELSE_ stmt  */
#line 134 "parser.y"
        { printf("stmt -> if ( bool ) stmt else stmt\n"); }
#line 1314 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 16: /* stmt: WHILE_ LEFTPARAN bool RIGHTPARAN stmt  */
#line 136 "parser.y"
        { printf("stmt -> while ( bool ) stmt\n"); }
#line 1320 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 17: /* stmt: DO stmt WHILE_ LEFTPARAN bool RIGHTPARAN SEMIC  */
#line 138 "parser.y"
        { printf("stmt -> do stmt while ( bool ) ;\n"); }
#line 1326 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 18: /* stmt: BREAK_ SEMIC  */
#line 140 "parser.y"
        { printf("stmt -> break ;\n"); }
#line 1332 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 19: /* stmt: RETURN_ bool SEMIC  */
#line 142 "parser.y"
        { printf("stmt -> return bool ;\n"); }
#line 1338 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 20: /* stmt: block  */
#line 144 "parser.y"
        { printf("stmt -> block\n"); }
#line 1344 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 21: /* stmt: error SEMIC  */
#line 146 "parser.y"
        { printf("Recovered from a bad statement (missing ';').\n"); yyerrok; }
#line 1350 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 22: /* stmt: error RIGHTBRACE  */
#line 148 "parser.y"
        { printf("Recovered from a bad block (found the closing '}' for this block).\n"); yyerrok; }
#line 1356 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 23: /* loc: loc LEFTBRACK bool RIGHTBRACK  */
#line 153 "parser.y"
        {
            printf("loc -> loc [ bool ]\n");

            Address *base_addr = (yyvsp[-3].addr);
            Address *index_addr = (yyvsp[-1].addr);
            
            // --- ERROR CHECKING ---
            if (!base_addr || base_addr->type != ADDR_VARIABLE || !base_addr->data.variable.type_record) {
                 fprintf(stderr, "Error: Cannot index non-variable or undeclared array.\n");
                 (yyval.addr) = NULL;
            } else {
                // Address is valid, proceed with array access calculation
                TypeRecord *array_type = base_addr->data.variable.type_record;
                
                size_t element_width = get_element_width(array_type); 
                
                char *temp_offset_name = create_temp(current_env, INT, NULL, 0); 
                TypeRecord *temp_offset_type = env_get(current_env, temp_offset_name);
                Address *temp_offset_addr = createVarAddr(temp_offset_name, temp_offset_type);

                Address *width_addr = createIntAddr(element_width); 

                Instruction *mul_instr = instruction_create(OP_MUL, index_addr, width_addr, temp_offset_addr, current_env);
                intermediate_code_append(global_code, mul_instr);
                
                BaseType result_basetype = array_type->base_type;
                
                char *temp_final_name = create_temp(current_env, result_basetype, NULL, 0);
                TypeRecord *temp_final_type = env_get(current_env, temp_final_name);
                Address *temp_final_addr = createVarAddr(temp_final_name, temp_final_type);

                Instruction *add_instr = instruction_create(OP_ADD, base_addr, temp_offset_addr, temp_final_addr, current_env);
                intermediate_code_append(global_code, add_instr);
                
                (yyval.addr) = temp_final_addr;
            }
        }
#line 1398 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 24: /* loc: ID  */
#line 191 "parser.y"
    { 
        printf("loc -> ID\n");
        TypeRecord *type = env_get(current_env, (yyvsp[0].str));
        if (!type) {
            fprintf(stderr, "Error: Undeclared identifier '%s'\n", (yyvsp[0].str));
            (yyval.addr) = NULL; 
        } else {
            (yyval.addr) = createVarAddr((yyvsp[0].str), type);
        }
        free((yyvsp[0].str)); 
    }
#line 1414 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 25: /* bool: bool OR join  */
#line 206 "parser.y"
        { printf("bool -> bool || join\n"); }
#line 1420 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 26: /* bool: join  */
#line 208 "parser.y"
        { printf("bool -> join\n"); }
#line 1426 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 27: /* join: join AND equality  */
#line 213 "parser.y"
        { printf("join -> join && equality\n"); }
#line 1432 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 28: /* join: equality  */
#line 215 "parser.y"
        { printf("join -> equality\n"); }
#line 1438 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 29: /* equality: equality EQUALS rel  */
#line 220 "parser.y"
        { printf("equality -> equality == rel\n"); }
#line 1444 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 30: /* equality: equality NE rel  */
#line 222 "parser.y"
        { printf("equality -> equality != rel\n"); }
#line 1450 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 31: /* equality: rel  */
#line 224 "parser.y"
        { printf("equality -> rel\n"); }
#line 1456 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 32: /* rel: expr LT expr  */
#line 229 "parser.y"
        { printf("rel -> expr < expr\n"); }
#line 1462 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 33: /* rel: expr LE expr  */
#line 231 "parser.y"
        { printf("rel -> expr <= expr\n"); }
#line 1468 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 34: /* rel: expr GT expr  */
#line 233 "parser.y"
        { printf("rel -> expr > expr\n"); }
#line 1474 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 35: /* rel: expr GE expr  */
#line 235 "parser.y"
        { printf("rel -> expr >= expr\n"); }
#line 1480 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 36: /* rel: expr  */
#line 237 "parser.y"
        { printf("rel -> expr\n"); }
#line 1486 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 37: /* expr: expr PLUS term  */
#line 242 "parser.y"
        { 
            printf("expr -> expr + term\n"); 
            BaseType t1 = get_address_type((yyvsp[-2].addr));
            BaseType t2 = get_address_type((yyvsp[0].addr));

            BaseType max_t = max_type(t1, t2);
            Address *src1 = widen(current_env, (yyvsp[-2].addr), t1, max_t, global_code);
            Address *src2 = widen(current_env, (yyvsp[0].addr), t2, max_t, global_code);

            char *temp_name = create_temp(current_env, max_t, NULL, 0);
            TypeRecord *temp_type = env_get(current_env, temp_name);
            Address *result = createVarAddr(temp_name, temp_type);

            Instruction *instr = instruction_create(OP_ADD, src1, src2, result, current_env);
            intermediate_code_append(global_code, instr);

            (yyval.addr) = result;
        }
#line 1509 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 38: /* expr: expr MINUS term  */
#line 261 "parser.y"
        { 
            printf("expr -> expr - term\n"); 
            BaseType t1 = get_address_type((yyvsp[-2].addr));
            BaseType t2 = get_address_type((yyvsp[0].addr));

            BaseType max_t = max_type(t1, t2);
            Address *src1 = widen(current_env, (yyvsp[-2].addr), t1, max_t, global_code);
            Address *src2 = widen(current_env, (yyvsp[0].addr), t2, max_t, global_code);

            char *temp_name = create_temp(current_env, max_t, NULL, 0);
            TypeRecord *temp_type = env_get(current_env, temp_name);
            Address *result = createVarAddr(temp_name, temp_type);

            Instruction *instr = instruction_create(OP_SUB, src1, src2, result, current_env);
            intermediate_code_append(global_code, instr);

            (yyval.addr) = result;
        }
#line 1532 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 39: /* expr: term  */
#line 280 "parser.y"
        { 
            printf("expr -> term\n"); 
            (yyval.addr) = (yyvsp[0].addr);
        }
#line 1541 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 40: /* term: term MULTIPLY unary  */
#line 288 "parser.y"
        { 
            printf("term -> term * unary\n"); 
            BaseType t1 = get_address_type((yyvsp[-2].addr));
            BaseType t2 = get_address_type((yyvsp[0].addr));

            BaseType max_t = max_type(t1, t2);
            Address *src1 = widen(current_env, (yyvsp[-2].addr), t1, max_t, global_code);
            Address *src2 = widen(current_env, (yyvsp[0].addr), t2, max_t, global_code);

            char *temp_name = create_temp(current_env, max_t, NULL, 0);
            TypeRecord *temp_type = env_get(current_env, temp_name);
            Address *result = createVarAddr(temp_name, temp_type);

            Instruction *instr = instruction_create(OP_MUL, src1, src2, result, current_env);
            intermediate_code_append(global_code, instr);

            (yyval.addr) = result;
        }
#line 1564 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 41: /* term: term DIVIDE unary  */
#line 307 "parser.y"
        { 
            printf("term -> term / unary\n"); 
            BaseType t1 = get_address_type((yyvsp[-2].addr));
            BaseType t2 = get_address_type((yyvsp[0].addr));

            BaseType max_t = max_type(t1, t2);
            Address *src1 = widen(current_env, (yyvsp[-2].addr), t1, max_t, global_code);
            Address *src2 = widen(current_env, (yyvsp[0].addr), t2, max_t, global_code);

            char *temp_name = create_temp(current_env, max_t, NULL, 0);
            TypeRecord *temp_type = env_get(current_env, temp_name);
            Address *result = createVarAddr(temp_name, temp_type);

            Instruction *instr = instruction_create(OP_DIV, src1, src2, result, current_env);
            intermediate_code_append(global_code, instr);

            (yyval.addr) = result;
        }
#line 1587 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 42: /* term: unary  */
#line 326 "parser.y"
        { 
            printf("term -> unary\n"); 
            (yyval.addr) = (yyvsp[0].addr);
        }
#line 1596 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 43: /* unary: NOT unary  */
#line 334 "parser.y"
        { printf("unary -> ! unary\n"); }
#line 1602 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 44: /* unary: MINUS unary  */
#line 336 "parser.y"
        { printf("unary -> - unary\n"); }
#line 1608 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 45: /* unary: factor  */
#line 338 "parser.y"
        { printf("unary -> factor\n"); }
#line 1614 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 46: /* factor: LEFTPARAN bool RIGHTPARAN  */
#line 343 "parser.y"
        { 
            printf("factor -> ( bool )\n");
            (yyval.addr) = (yyvsp[-1].addr);
        }
#line 1623 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 47: /* factor: loc  */
#line 348 "parser.y"
        { 
            printf("factor -> loc\n"); 
            Address *loc_addr = (yyvsp[0].addr);
            
            // Check if loc is a temporary address (an array element address)
            if (loc_addr && loc_addr->type == ADDR_VARIABLE && loc_addr->data.variable.name[0] == 't') {
                BaseType result_basetype = get_address_type(loc_addr);
                char *temp_load_name = create_temp(current_env, result_basetype, NULL, 0);
                TypeRecord *temp_load_type = env_get(current_env, temp_load_name);
                Address *temp_load_addr = createVarAddr(temp_load_name, temp_load_type);
                
                Instruction *instr = instruction_create(OP_LOAD, loc_addr, NULL, temp_load_addr, current_env);
                intermediate_code_append(global_code, instr);
                
                (yyval.addr) = temp_load_addr; // Return the address of the loaded value
            } else {
                // It's a simple variable (i, j, v, x), just return its address
                (yyval.addr) = loc_addr;
            }
        }
#line 1648 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 48: /* factor: NUM  */
#line 369 "parser.y"
        { 
            printf("factor -> NUM\n"); 
            (yyval.addr) = createIntAddr((yyvsp[0].num));
        }
#line 1657 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 49: /* factor: REAL  */
#line 374 "parser.y"
        { 
            printf("factor -> REAL\n"); 
            (yyval.addr) = createFloatAddr((yyvsp[0].real));
        }
#line 1666 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;

  case 50: /* factor: BOOLCONST  */
#line 379 "parser.y"
        { printf("factor -> BOOLCONST\n"); }
#line 1672 "/home/lstanchak/Assignment2/build/parser.tab.c"
    break;


#line 1676 "/home/lstanchak/Assignment2/build/parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
                      yytoken, &yylval);
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 382 "parser.y"


void yyerror(const char *s) { //Completely stops parsing if error is not recoverable.
    fprintf(stderr, "Syntax error: %s\n", s);
}

int main(int argc, char *argv[]) {
    printf("Starting parse...\n");

    if (argc != 2) {
            fprintf(stderr, "Usage: %s <input_file_path>\n", argv[0]);
            exit(1); 
        }

    // Open the specified file for reading
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        exit(1);
    }

    yyin = input_file;
    current_env = env_create_global();
    global_code = intermediate_code_create();
    int result = yyparse();

    if (result != 0) {
        printf("Unrecoverable syntax error encountered. Parsing terminated.\n");
        return 1;
    }

    printf("\nParsing complete.\n");
    printf("Applying strength reduction:\n");
    strength_reduction(global_code, current_env);
    printf("Strength reduction complete.\n");
    printf("\nFinal symbol table:\n");
    env_print_table(current_env);
    intermediate_code_print(global_code);
    fclose(input_file);
    return 0;
}
