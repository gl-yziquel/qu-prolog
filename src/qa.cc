/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 2000-2009 
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     put_x_variable = 258,
     put_y_variable = 259,
     put_x_value = 260,
     put_y_value = 261,
     put_constant = 262,
     put_integer = 263,
     put_double = 264,
     put_string = 265,
     put_list = 266,
     put_structure = 267,
     put_x_object_variable = 268,
     put_y_object_variable = 269,
     put_x_object_value = 270,
     put_y_object_value = 271,
     put_quantifier = 272,
     check_binder = 273,
     put_substitution = 274,
     put_x_term_substitution = 275,
     put_y_term_substitution = 276,
     put_initial_empty_substitution = 277,
     get_x_variable = 278,
     get_y_variable = 279,
     get_x_value = 280,
     get_y_value = 281,
     get_constant = 282,
     get_integer = 283,
     get_double = 284,
     get_string = 285,
     get_list = 286,
     get_structure = 287,
     get_structure_frame = 288,
     get_x_object_variable = 289,
     get_y_object_variable = 290,
     get_x_object_value = 291,
     get_y_object_value = 292,
     unify_x_variable = 293,
     unify_y_variable = 294,
     unify_x_value = 295,
     unify_y_value = 296,
     unify_void = 297,
     unify_constant = 298,
     unify_integer = 299,
     unify_double = 300,
     unify_string = 301,
     unify_x_ref = 302,
     unify_y_ref = 303,
     set_x_variable = 304,
     set_y_variable = 305,
     set_x_value = 306,
     set_y_value = 307,
     set_x_object_variable = 308,
     set_y_object_variable = 309,
     set_x_object_value = 310,
     set_y_object_value = 311,
     set_constant = 312,
     set_integer = 313,
     set_double = 314,
     set_string = 315,
     set_void = 316,
     set_object_void = 317,
     wam_allocate = 318,
     wam_deallocate = 319,
     call_predicate = 320,
     call_address = 321,
     call_escape = 322,
     execute_predicate = 323,
     execute_address = 324,
     execute_escape = 325,
     noop = 326,
     jump = 327,
     proceed = 328,
     wam_fail = 329,
     halt = 330,
     wam_exit = 331,
     try_me_else = 332,
     retry_me_else = 333,
     trust_me_else_fail = 334,
     wam_try = 335,
     retry = 336,
     trust = 337,
     neck_cut = 338,
     get_x_level = 339,
     get_y_level = 340,
     cut = 341,
     switch_on_term = 342,
     switch_on_constant = 343,
     switch_on_structure = 344,
     switch_on_quantifier = 345,
     pseudo_instr0 = 346,
     pseudo_instr1 = 347,
     pseudo_instr2 = 348,
     pseudo_instr3 = 349,
     pseudo_instr4 = 350,
     pseudo_instr5 = 351,
     NUMBER_TOKEN = 352,
     DOUBLE_TOKEN = 353,
     STRING_TOKEN = 354,
     ATOM_TOKEN = 355,
     LABEL_TOKEN = 356,
     END_TOKEN = 357
   };
#endif
/* Tokens.  */
#define put_x_variable 258
#define put_y_variable 259
#define put_x_value 260
#define put_y_value 261
#define put_constant 262
#define put_integer 263
#define put_double 264
#define put_string 265
#define put_list 266
#define put_structure 267
#define put_x_object_variable 268
#define put_y_object_variable 269
#define put_x_object_value 270
#define put_y_object_value 271
#define put_quantifier 272
#define check_binder 273
#define put_substitution 274
#define put_x_term_substitution 275
#define put_y_term_substitution 276
#define put_initial_empty_substitution 277
#define get_x_variable 278
#define get_y_variable 279
#define get_x_value 280
#define get_y_value 281
#define get_constant 282
#define get_integer 283
#define get_double 284
#define get_string 285
#define get_list 286
#define get_structure 287
#define get_structure_frame 288
#define get_x_object_variable 289
#define get_y_object_variable 290
#define get_x_object_value 291
#define get_y_object_value 292
#define unify_x_variable 293
#define unify_y_variable 294
#define unify_x_value 295
#define unify_y_value 296
#define unify_void 297
#define unify_constant 298
#define unify_integer 299
#define unify_double 300
#define unify_string 301
#define unify_x_ref 302
#define unify_y_ref 303
#define set_x_variable 304
#define set_y_variable 305
#define set_x_value 306
#define set_y_value 307
#define set_x_object_variable 308
#define set_y_object_variable 309
#define set_x_object_value 310
#define set_y_object_value 311
#define set_constant 312
#define set_integer 313
#define set_double 314
#define set_string 315
#define set_void 316
#define set_object_void 317
#define wam_allocate 318
#define wam_deallocate 319
#define call_predicate 320
#define call_address 321
#define call_escape 322
#define execute_predicate 323
#define execute_address 324
#define execute_escape 325
#define noop 326
#define jump 327
#define proceed 328
#define wam_fail 329
#define halt 330
#define wam_exit 331
#define try_me_else 332
#define retry_me_else 333
#define trust_me_else_fail 334
#define wam_try 335
#define retry 336
#define trust 337
#define neck_cut 338
#define get_x_level 339
#define get_y_level 340
#define cut 341
#define switch_on_term 342
#define switch_on_constant 343
#define switch_on_structure 344
#define switch_on_quantifier 345
#define pseudo_instr0 346
#define pseudo_instr1 347
#define pseudo_instr2 348
#define pseudo_instr3 349
#define pseudo_instr4 350
#define pseudo_instr5 351
#define NUMBER_TOKEN 352
#define DOUBLE_TOKEN 353
#define STRING_TOKEN 354
#define ATOM_TOKEN 355
#define LABEL_TOKEN 356
#define END_TOKEN 357




/* Copy the first part of user declarations.  */
#line 1 "qa.y"

/*
 * Copyright (C) 2000-2009 
 * Department of Computer Science and Electrical Engineering, 
 * The University of Queensland
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "asm_objects.h"
#include "asm_string_table.cc"
#include "code.h"
#include "code_block.h"
#include "errors.h"
#include "indexing.h"

const char *Program = "qa";

extern "C" int yylex();

int yyerror(const char *);

ASMStringTable *asm_string_table = NULL;

CodeBlock *query_code_block = NULL;
vector<CodeBlock *> *predicate_code_blocks = NULL;

CodeBlock *code_block = NULL;

LabelTable *labels = NULL;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 36 "qa.y"
{
  long number_value;
  double double_value;

  string *label_name;
  string *atom_name;
  string *string_value;

  ASMLoc loc;

  ASMInt<Code::InstructionSizedType> *instruction;
  ASMInt<Code::ConstantSizedType> *constant;
  ASMDouble<double> *double_num;
  ASMInt<Code::RegisterSizedType> *reg;
  ASMInt<Code::NumberSizedType> *number;
  ASMInt<Code::AddressSizedType> *address;
  ASMInt<Code::OffsetSizedType> *offset;
  ASMInt<Code::PredSizedType> *pred;
  ASMInt<Code::TableSizeSizedType> *table_size;

  vector<ConstantLabel *> *cl_list;
  ConstantLabel *cl;
  
  vector<AtomArityLabel *> *aal_list;
  AtomArityLabel *aal;
}
/* Line 193 of yacc.c.  */
#line 363 "qa.cc"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 376 "qa.cc"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   587

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  112
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  135
/* YYNRULES -- Number of states.  */
#define YYNSTATES  567

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   357

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     105,   106,     2,   110,   107,   111,     2,   103,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   104,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   108,     2,   109,     2,     2,     2,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    13,    18,    26,    27,
      30,    32,    34,    37,    44,    51,    58,    65,    72,    79,
      86,    93,    98,   105,   112,   119,   126,   133,   138,   143,
     150,   157,   164,   169,   176,   183,   190,   197,   204,   211,
     218,   225,   230,   239,   246,   253,   260,   267,   274,   279,
     284,   289,   294,   299,   304,   309,   314,   319,   324,   329,
     334,   339,   344,   349,   354,   359,   364,   369,   374,   379,
     384,   389,   394,   399,   404,   406,   415,   422,   429,   436,
     441,   446,   448,   453,   455,   457,   459,   461,   468,   473,
     475,   482,   487,   492,   494,   499,   504,   509,   526,   540,
     554,   568,   573,   580,   589,   600,   613,   628,   629,   632,
     634,   638,   642,   643,   646,   648,   652,   658,   659,   662,
     664,   668,   674,   676,   678,   680,   682,   685,   688,   690,
     693,   696,   698,   700,   702,   704
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     113,     0,    -1,   114,    -1,    -1,   114,   115,    -1,   116,
     118,   117,    -1,   137,   103,   134,   104,    -1,   102,   105,
     137,   103,   134,   106,   104,    -1,    -1,   118,   119,    -1,
     120,    -1,   121,    -1,   101,   104,    -1,     3,   105,   135,
     107,   135,   106,    -1,     4,   105,   135,   107,   135,   106,
      -1,     5,   105,   135,   107,   135,   106,    -1,     6,   105,
     135,   107,   135,   106,    -1,     7,   105,   132,   107,   135,
     106,    -1,     8,   105,   132,   107,   135,   106,    -1,     9,
     105,   133,   107,   135,   106,    -1,    10,   105,    99,   107,
     135,   106,    -1,    11,   105,   135,   106,    -1,    12,   105,
     134,   107,   135,   106,    -1,    13,   105,   135,   107,   135,
     106,    -1,    14,   105,   135,   107,   135,   106,    -1,    15,
     105,   135,   107,   135,   106,    -1,    16,   105,   135,   107,
     135,   106,    -1,    17,   105,   135,   106,    -1,    18,   105,
     135,   106,    -1,    19,   105,   134,   107,   135,   106,    -1,
      20,   105,   135,   107,   135,   106,    -1,    21,   105,   135,
     107,   135,   106,    -1,    22,   105,   135,   106,    -1,    23,
     105,   135,   107,   135,   106,    -1,    24,   105,   135,   107,
     135,   106,    -1,    25,   105,   135,   107,   135,   106,    -1,
      26,   105,   135,   107,   135,   106,    -1,    27,   105,   132,
     107,   135,   106,    -1,    28,   105,   132,   107,   135,   106,
      -1,    29,   105,   133,   107,   135,   106,    -1,    30,   105,
      99,   107,   135,   106,    -1,    31,   105,   135,   106,    -1,
      32,   105,   132,   107,   134,   107,   135,   106,    -1,    33,
     105,   134,   107,   135,   106,    -1,    34,   105,   135,   107,
     135,   106,    -1,    35,   105,   135,   107,   135,   106,    -1,
      36,   105,   135,   107,   135,   106,    -1,    37,   105,   135,
     107,   135,   106,    -1,    38,   105,   135,   106,    -1,    39,
     105,   135,   106,    -1,    40,   105,   135,   106,    -1,    41,
     105,   135,   106,    -1,    43,   105,   132,   106,    -1,    44,
     105,   132,   106,    -1,    45,   105,   133,   106,    -1,    46,
     105,    99,   106,    -1,    42,   105,   134,   106,    -1,    47,
     105,   135,   106,    -1,    48,   105,   135,   106,    -1,    49,
     105,   135,   106,    -1,    50,   105,   135,   106,    -1,    51,
     105,   135,   106,    -1,    52,   105,   135,   106,    -1,    53,
     105,   135,   106,    -1,    54,   105,   135,   106,    -1,    55,
     105,   135,   106,    -1,    56,   105,   135,   106,    -1,    57,
     105,   132,   106,    -1,    58,   105,   132,   106,    -1,    59,
     105,   133,   106,    -1,    60,   105,    99,   106,    -1,    61,
     105,   134,   106,    -1,    62,   105,   134,   106,    -1,    63,
     105,   134,   106,    -1,    64,    -1,    65,   105,   137,   107,
     134,   107,   134,   106,    -1,    66,   105,   136,   107,   134,
     106,    -1,    67,   105,   136,   107,   134,   106,    -1,    68,
     105,   137,   107,   134,   106,    -1,    69,   105,   136,   106,
      -1,    70,   105,   136,   106,    -1,    71,    -1,    72,   105,
     136,   106,    -1,    73,    -1,    74,    -1,    75,    -1,    76,
      -1,    77,   105,   134,   107,   101,   106,    -1,    78,   105,
     101,   106,    -1,    79,    -1,    80,   105,   134,   107,   101,
     106,    -1,    81,   105,   101,   106,    -1,    82,   105,   101,
     106,    -1,    83,    -1,    84,   105,   135,   106,    -1,    85,
     105,   135,   106,    -1,    86,   105,   135,   106,    -1,    87,
     105,   135,   107,   131,   107,   131,   107,   131,   107,   131,
     107,   131,   107,   131,   106,    -1,    88,   105,   135,   107,
     138,   107,   108,   100,   104,   131,   122,   109,   106,    -1,
      89,   105,   135,   107,   138,   107,   108,   100,   104,   131,
     125,   109,   106,    -1,    90,   105,   135,   107,   138,   107,
     108,   100,   104,   131,   128,   109,   106,    -1,    91,   105,
     134,   106,    -1,    92,   105,   134,   107,   135,   106,    -1,
      93,   105,   134,   107,   135,   107,   135,   106,    -1,    94,
     105,   134,   107,   135,   107,   135,   107,   135,   106,    -1,
      95,   105,   134,   107,   135,   107,   135,   107,   135,   107,
     135,   106,    -1,    96,   105,   134,   107,   135,   107,   135,
     107,   135,   107,   135,   107,   135,   106,    -1,    -1,   107,
     123,    -1,   124,    -1,   123,   107,   124,    -1,   132,   104,
     131,    -1,    -1,   107,   126,    -1,   127,    -1,   126,   107,
     127,    -1,   100,   103,   134,   104,   131,    -1,    -1,   107,
     129,    -1,   130,    -1,   129,   107,   130,    -1,   100,   103,
     134,   104,   131,    -1,   101,    -1,   100,    -1,   100,    -1,
      97,    -1,   110,    97,    -1,   111,    97,    -1,    98,    -1,
     110,    98,    -1,   111,    98,    -1,    97,    -1,    97,    -1,
      97,    -1,   100,    -1,    97,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   201,   201,   204,   205,   208,   211,   242,   268,   269,
     272,   273,   276,   282,   289,   296,   303,   310,   317,   324,
     330,   342,   348,   355,   362,   369,   376,   383,   389,   395,
     402,   409,   416,   422,   429,   436,   443,   450,   457,   465,
     472,   484,   490,   498,   505,   512,   519,   526,   533,   539,
     545,   551,   557,   563,   570,   576,   587,   593,   599,   605,
     611,   617,   623,   629,   635,   641,   647,   653,   659,   666,
     672,   683,   689,   695,   701,   706,   714,   721,   728,   735,
     741,   747,   752,   758,   763,   768,   773,   778,   790,   800,
     805,   817,   827,   837,   842,   848,   854,   860,   884,   912,
     940,   968,   974,   981,   989,   998,  1008,  1022,  1025,  1031,
    1039,  1047,  1054,  1057,  1063,  1071,  1078,  1093,  1096,  1102,
    1110,  1118,  1130,  1131,  1141,  1148,  1153,  1158,  1165,  1170,
    1175,  1181,  1190,  1197,  1204,  1212
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "put_x_variable", "put_y_variable",
  "put_x_value", "put_y_value", "put_constant", "put_integer",
  "put_double", "put_string", "put_list", "put_structure",
  "put_x_object_variable", "put_y_object_variable", "put_x_object_value",
  "put_y_object_value", "put_quantifier", "check_binder",
  "put_substitution", "put_x_term_substitution", "put_y_term_substitution",
  "put_initial_empty_substitution", "get_x_variable", "get_y_variable",
  "get_x_value", "get_y_value", "get_constant", "get_integer",
  "get_double", "get_string", "get_list", "get_structure",
  "get_structure_frame", "get_x_object_variable", "get_y_object_variable",
  "get_x_object_value", "get_y_object_value", "unify_x_variable",
  "unify_y_variable", "unify_x_value", "unify_y_value", "unify_void",
  "unify_constant", "unify_integer", "unify_double", "unify_string",
  "unify_x_ref", "unify_y_ref", "set_x_variable", "set_y_variable",
  "set_x_value", "set_y_value", "set_x_object_variable",
  "set_y_object_variable", "set_x_object_value", "set_y_object_value",
  "set_constant", "set_integer", "set_double", "set_string", "set_void",
  "set_object_void", "wam_allocate", "wam_deallocate", "call_predicate",
  "call_address", "call_escape", "execute_predicate", "execute_address",
  "execute_escape", "noop", "jump", "proceed", "wam_fail", "halt",
  "wam_exit", "try_me_else", "retry_me_else", "trust_me_else_fail",
  "wam_try", "retry", "trust", "neck_cut", "get_x_level", "get_y_level",
  "cut", "switch_on_term", "switch_on_constant", "switch_on_structure",
  "switch_on_quantifier", "pseudo_instr0", "pseudo_instr1",
  "pseudo_instr2", "pseudo_instr3", "pseudo_instr4", "pseudo_instr5",
  "NUMBER_TOKEN", "DOUBLE_TOKEN", "STRING_TOKEN", "ATOM_TOKEN",
  "LABEL_TOKEN", "END_TOKEN", "'/'", "':'", "'('", "')'", "','", "'['",
  "']'", "'+'", "'-'", "$accept", "assembler_file", "predicate_list",
  "predicate", "predicate_start", "predicate_end", "source_line_list",
  "source_line", "label_instance", "instr", "constant_labels",
  "constant_label_list", "constant_label", "atom_arity_labels",
  "atom_arity_label_list", "atom_arity_label", "quantifier_labels",
  "quantifier_label_list", "quantifier_label", "switch_label", "constant",
  "double_num", "number", "reg", "address", "atom", "table_size", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,    47,    58,    40,    41,    44,    91,    93,
      43,    45
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   112,   113,   114,   114,   115,   116,   117,   118,   118,
     119,   119,   120,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   122,   122,   123,
     123,   124,   125,   125,   126,   126,   127,   128,   128,   129,
     129,   130,   131,   131,   132,   132,   132,   132,   133,   133,
     133,   134,   135,   136,   137,   138
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     4,     7,     0,     2,
       1,     1,     2,     6,     6,     6,     6,     6,     6,     6,
       6,     4,     6,     6,     6,     6,     6,     4,     4,     6,
       6,     6,     4,     6,     6,     6,     6,     6,     6,     6,
       6,     4,     8,     6,     6,     6,     6,     6,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     1,     8,     6,     6,     6,     4,
       4,     1,     4,     1,     1,     1,     1,     6,     4,     1,
       6,     4,     4,     1,     4,     4,     4,    16,    13,    13,
      13,     4,     6,     8,    10,    12,    14,     0,     2,     1,
       3,     3,     0,     2,     1,     3,     5,     0,     2,     1,
       3,     5,     1,     1,     1,     1,     2,     2,     1,     2,
       2,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,   134,     4,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    74,     0,     0,     0,     0,     0,     0,    81,     0,
      83,    84,    85,    86,     0,     0,    89,     0,     0,     0,
      93,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     5,     9,    10,    11,
     131,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    12,     0,
       6,   132,     0,     0,     0,     0,   125,   124,     0,     0,
       0,     0,   128,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   133,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   126,   127,     0,     0,   129,   130,     0,     0,    21,
       0,     0,     0,     0,     0,    27,    28,     0,     0,     0,
      32,     0,     0,     0,     0,     0,     0,     0,     0,    41,
       0,     0,     0,     0,     0,     0,    48,    49,    50,    51,
      56,    52,    53,    54,    55,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,     0,     0,     0,     0,    79,    80,    82,     0,
      88,     0,    91,    92,    94,    95,    96,     0,     0,     0,
       0,   101,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   123,   122,     0,   135,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    13,    14,    15,
      16,    17,    18,    19,    20,    22,    23,    24,    25,    26,
      29,    30,    31,    33,    34,    35,    36,    37,    38,    39,
      40,     0,    43,    44,    45,    46,    47,     0,    76,    77,
      78,    87,    90,     0,     0,     0,     0,   102,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     7,    42,    75,     0,     0,     0,     0,
     103,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   107,   112,   117,   104,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   108,   109,
       0,     0,     0,   113,   114,     0,     0,   118,   119,     0,
     105,     0,     0,     0,     0,    98,     0,     0,    99,     0,
       0,   100,     0,     0,   110,   111,     0,   115,     0,   120,
     106,     0,     0,     0,    97,   116,   121
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,     6,   106,     8,   107,   108,   109,
     520,   528,   529,   522,   533,   534,   524,   537,   538,   426,
     530,   215,   111,   202,   272,     7,   428
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -416
static const yytype_int16 yypact[] =
{
    -416,     3,   -94,  -416,  -416,  -416,  -416,   -95,   485,   -82,
     -79,   -77,   -67,   -63,   -43,   -38,   -26,   -23,   -17,   -12,
     -11,   -10,    -6,    -5,    -4,    -3,    -2,    -1,     0,     1,
       2,     6,     8,     9,    10,    11,    12,    14,    16,    17,
      18,    19,    20,    21,    22,    23,    31,    32,    34,    35,
      36,    37,    38,    39,    40,    41,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,  -416,    59,    60,    61,    62,    63,    64,  -416,    65,
    -416,  -416,  -416,  -416,    66,    67,  -416,    68,    69,    70,
    -416,    71,    72,    73,    74,    75,    76,    77,    78,    83,
      84,    87,    88,    91,    98,   102,  -416,  -416,  -416,  -416,
    -416,    99,   119,   119,   119,   119,   -13,   -13,   -42,   118,
     119,   -82,   119,   119,   119,   119,   119,   119,   -82,   119,
     119,   119,   119,   119,   119,   119,   -13,   -13,   -42,   124,
     119,   -13,   -82,   119,   119,   119,   119,   119,   119,   119,
     119,   -82,   -13,   -13,   -42,   125,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   -13,   -13,   -42,   126,
     -82,   -82,   -82,   -94,   129,   129,   -94,   129,   129,   129,
     -82,   127,   -82,   128,   130,   119,   119,   119,   119,   119,
     119,   119,   -82,   -82,   -82,   -82,   -82,   -82,  -416,   -94,
    -416,  -416,   120,   123,   131,   132,  -416,  -416,   135,   136,
     133,   134,  -416,   137,   138,   139,   140,   142,   143,   144,
     145,   146,   147,   149,   150,   151,   152,   153,   155,   156,
     157,   158,   159,   160,   167,   168,   169,   171,   172,   173,
     174,   175,   176,   177,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,  -416,   210,   211,   212,   214,   215,   216,   217,   220,
     221,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     233,   234,   235,   236,   237,   238,   141,   119,   119,   119,
     119,  -416,  -416,   119,   119,  -416,  -416,   119,   119,  -416,
     119,   119,   119,   119,   119,  -416,  -416,   119,   119,   119,
    -416,   119,   119,   119,   119,   119,   119,   119,   119,  -416,
     -82,   119,   119,   119,   119,   119,  -416,  -416,  -416,  -416,
    -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,
    -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,
    -416,  -416,   -82,   -82,   -82,   -82,  -416,  -416,  -416,   148,
    -416,   161,  -416,  -416,  -416,  -416,  -416,   -30,   218,   218,
     218,  -416,   119,   119,   119,   119,   119,   -82,   240,   241,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   263,   264,   265,   266,
     267,   268,   269,   271,   272,   273,   274,   275,   276,   278,
     279,   280,   281,   285,  -416,  -416,   286,  -416,   287,   288,
     289,   291,   292,   293,   294,   295,   300,  -416,  -416,  -416,
    -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,
    -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,
    -416,   119,  -416,  -416,  -416,  -416,  -416,   -82,  -416,  -416,
    -416,  -416,  -416,   -30,   170,   219,   232,  -416,   119,   119,
     119,   119,   303,   302,   304,   305,   282,   298,   309,   307,
     308,   310,   311,  -416,  -416,  -416,   -30,   312,   315,   316,
    -416,   119,   119,   119,   314,   -30,   -30,   -30,   317,   318,
     319,   -30,   320,   322,   323,  -416,   119,   119,   324,   -13,
     283,   332,   313,   333,   325,   329,   330,   -30,   331,  -416,
     335,   334,   154,   336,  -416,   338,   321,   339,  -416,   341,
    -416,   119,   342,   -13,   -30,  -416,   -82,   332,  -416,   -82,
     333,  -416,   344,   -30,  -416,  -416,   337,  -416,   347,  -416,
    -416,   346,   -30,   -30,  -416,  -416,  -416
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,  -416,
    -416,  -416,  -309,  -416,  -416,  -310,  -416,  -416,  -308,  -415,
    -112,  -115,   -62,  -113,  -114,  -116,  -294
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     203,   204,   205,     3,   210,   211,     4,   217,     9,   219,
     220,   221,   222,   223,   224,   110,   226,   227,   228,   229,
     230,   231,   232,   235,   233,   234,   112,   237,   113,   238,
     240,   241,   242,   243,   244,   245,   246,   247,   114,   251,
     249,   250,   115,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   265,   263,   264,   212,   270,   485,   218,
     274,   273,   116,   275,   276,   277,   225,   117,   213,   214,
     424,   425,   283,   284,   285,   286,   287,   288,   289,   118,
     239,   504,   119,   296,   206,   429,   430,   207,   120,   248,
     512,   513,   514,   121,   122,   123,   518,   208,   209,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   267,   268,
     269,   133,   542,   134,   135,   136,   137,   138,   278,   139,
     280,   140,   141,   142,   143,   144,   145,   146,   147,   555,
     290,   291,   292,   293,   294,   295,   148,   149,   561,   150,
     151,   152,   153,   154,   155,   156,   157,   565,   566,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   388,   389,   390,   391,   193,   194,
     392,   393,   195,   196,   394,   395,   197,   396,   397,   398,
     399,   400,   198,   200,   401,   402,   403,   199,   404,   405,
     406,   407,   408,   409,   410,   411,   201,   216,   413,   414,
     415,   416,   417,   236,   252,   266,   271,   297,   279,   281,
     298,   282,   301,   302,   554,   305,   306,   557,   299,   300,
     303,   304,   559,     0,   387,     0,   307,   308,   309,   422,
     310,   311,   312,   313,   314,   315,   316,   546,   317,   318,
     319,   320,   423,   321,   322,   323,   324,   325,   412,   431,
     432,   433,   434,   435,   326,   327,   328,   329,   486,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     418,   419,   420,   421,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   427,   362,   363,   364,   365,
     366,   367,   368,     0,   369,   436,   370,   487,   371,   372,
     373,   374,   375,   376,     0,   377,   378,   379,   380,   381,
     488,   382,   383,   384,   385,   386,   437,   438,   483,   439,
     440,   441,   442,   443,   444,   445,   446,   447,   448,   449,
     450,   451,   452,   453,   454,   489,   490,   491,   492,   455,
     456,   457,   458,   459,   460,     0,   461,   462,   463,   464,
     465,   466,   497,   467,   468,   469,   470,   471,   508,   509,
     510,   472,   531,   473,   474,   475,   476,   477,   498,   478,
     479,   480,   481,   525,   526,   484,   482,   493,   494,   499,
     495,     0,   496,   500,     0,   501,   505,   502,   503,   506,
     507,   511,   535,   515,   549,   516,   517,   519,   552,   521,
     523,   527,   532,   536,   539,   540,     0,   541,   543,   544,
     545,   562,     0,   547,   548,     0,   550,   551,     0,   553,
     560,   563,   564,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   556,     0,     0,   558,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     0,     0,     0,     0,   104,   105
};

static const yytype_int16 yycheck[] =
{
     113,   114,   115,     0,   116,   117,   100,   120,   103,   122,
     123,   124,   125,   126,   127,    97,   129,   130,   131,   132,
     133,   134,   135,   138,   136,   137,   105,   140,   105,   141,
     143,   144,   145,   146,   147,   148,   149,   150,   105,   154,
     152,   153,   105,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   168,   166,   167,    98,   173,   473,   121,
     176,   175,   105,   177,   178,   179,   128,   105,   110,   111,
     100,   101,   185,   186,   187,   188,   189,   190,   191,   105,
     142,   496,   105,   199,    97,   379,   380,   100,   105,   151,
     505,   506,   507,   105,   105,   105,   511,   110,   111,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   170,   171,
     172,   105,   527,   105,   105,   105,   105,   105,   180,   105,
     182,   105,   105,   105,   105,   105,   105,   105,   105,   544,
     192,   193,   194,   195,   196,   197,   105,   105,   553,   105,
     105,   105,   105,   105,   105,   105,   105,   562,   563,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   297,   298,   299,   300,   105,   105,
     303,   304,   105,   105,   307,   308,   105,   310,   311,   312,
     313,   314,   104,   104,   317,   318,   319,   105,   321,   322,
     323,   324,   325,   326,   327,   328,    97,    99,   331,   332,
     333,   334,   335,    99,    99,    99,    97,   107,   101,   101,
     107,   101,    97,    97,   543,    98,    98,   547,   107,   107,
     107,   107,   550,    -1,   103,    -1,   107,   107,   106,   101,
     107,   107,   107,   107,   107,   106,   106,   103,   107,   107,
     107,   106,   101,   107,   107,   107,   107,   107,   330,   382,
     383,   384,   385,   386,   107,   107,   107,   106,   108,   107,
     107,   107,   107,   107,   107,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     362,   363,   364,   365,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,    97,   107,   107,   107,   107,
     106,   106,   106,    -1,   107,   387,   106,   108,   107,   106,
     106,   106,   106,   106,    -1,   107,   107,   107,   107,   106,
     108,   107,   107,   107,   107,   107,   106,   106,   461,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   478,   479,   480,   481,   106,
     106,   106,   106,   106,   106,    -1,   107,   106,   106,   106,
     106,   106,   100,   107,   106,   106,   106,   106,   501,   502,
     503,   106,   109,   107,   107,   107,   107,   106,   100,   107,
     107,   107,   107,   516,   517,   467,   106,   104,   106,   100,
     106,    -1,   107,   106,    -1,   107,   104,   107,   107,   104,
     104,   107,   109,   106,   103,   107,   107,   107,   541,   107,
     107,   107,   100,   100,   109,   106,    -1,   107,   107,   104,
     106,   104,    -1,   107,   106,    -1,   107,   106,    -1,   107,
     106,   104,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   546,    -1,    -1,   549,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    -1,    -1,    -1,    -1,   101,   102
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   113,   114,     0,   100,   115,   116,   137,   118,   103,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,   101,   102,   117,   119,   120,   121,
      97,   134,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   104,   105,
     104,    97,   135,   135,   135,   135,    97,   100,   110,   111,
     132,   132,    98,   110,   111,   133,    99,   135,   134,   135,
     135,   135,   135,   135,   135,   134,   135,   135,   135,   135,
     135,   135,   135,   132,   132,   133,    99,   135,   132,   134,
     135,   135,   135,   135,   135,   135,   135,   135,   134,   132,
     132,   133,    99,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   132,   132,   133,    99,   134,   134,   134,
     137,    97,   136,   136,   137,   136,   136,   136,   134,   101,
     134,   101,   101,   135,   135,   135,   135,   135,   135,   135,
     134,   134,   134,   134,   134,   134,   137,   107,   107,   107,
     107,    97,    97,   107,   107,    98,    98,   107,   107,   106,
     107,   107,   107,   107,   107,   106,   106,   107,   107,   107,
     106,   107,   107,   107,   107,   107,   107,   107,   107,   106,
     107,   107,   107,   107,   107,   107,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   107,   107,   107,   107,   106,   106,   106,   107,
     106,   107,   106,   106,   106,   106,   106,   107,   107,   107,
     107,   106,   107,   107,   107,   107,   107,   103,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   134,   135,   135,   135,   135,   135,   134,   134,
     134,   134,   101,   101,   100,   101,   131,    97,   138,   138,
     138,   135,   135,   135,   135,   135,   134,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   107,   106,   106,   106,   106,   106,   107,   106,   106,
     106,   106,   106,   107,   107,   107,   107,   106,   107,   107,
     107,   107,   106,   135,   134,   131,   108,   108,   108,   135,
     135,   135,   135,   104,   106,   106,   107,   100,   100,   100,
     106,   107,   107,   107,   131,   104,   104,   104,   135,   135,
     135,   107,   131,   131,   131,   106,   107,   107,   131,   107,
     122,   107,   125,   107,   128,   135,   135,   107,   123,   124,
     132,   109,   100,   126,   127,   109,   100,   129,   130,   109,
     106,   107,   131,   107,   104,   106,   103,   107,   106,   103,
     107,   106,   135,   107,   124,   131,   134,   127,   134,   130,
     106,   131,   104,   104,   106,   131,   131
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 6:
#line 212 "qa.y"
    {
		  labels = new LabelTable;

		  // Is it the query code block?
		  if ((*asm_string_table)[(yyvsp[(1) - (4)].constant)->Value()] == "$query" &&
		      (yyvsp[(3) - (4)].number)->Value() == 0)
		    {
		      if (query_code_block != NULL)
			{
			  Fatal(__FUNCTION__, 
				"more than one query code block");
			}
		      query_code_block = new CodeBlock(QUERY_BLOCK,
						       (yyvsp[(1) - (4)].constant)->Value(),
						       (yyvsp[(3) - (4)].number)->Value());

		      code_block = query_code_block;
		    }
		  else
		    {
		      code_block = new CodeBlock(PREDICATE_BLOCK,
						 (yyvsp[(1) - (4)].constant)->Value(),
						 (yyvsp[(3) - (4)].number)->Value());
		    }

		  delete (yyvsp[(1) - (4)].constant);
		  delete (yyvsp[(3) - (4)].number);
		}
    break;

  case 7:
#line 243 "qa.y"
    {
		  if ((yyvsp[(3) - (7)].constant)->Value() != code_block->Atom() ||
		      (yyvsp[(5) - (7)].number)->Value() != code_block->Arity())
		    {
		      Fatal(__FUNCTION__, 
			    "atom or arity mismatch in predicate");
		    }

		  delete (yyvsp[(3) - (7)].constant);
		  delete (yyvsp[(5) - (7)].number);

		  // Resolve all the fail label references
		  labels->ResolveFail(*code_block);

		  if (code_block->Type() == PREDICATE_BLOCK)
		    {
		      predicate_code_blocks->push_back(code_block);
		    }
		  
		  // Make it difficult to reuse the label table
		  delete labels;
		  labels = NULL;
		}
    break;

  case 12:
#line 277 "qa.y"
    {
		  labels->Resolve(*(yyvsp[(1) - (2)].label_name), *code_block);
		}
    break;

  case 13:
#line 283 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 14:
#line 290 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 15:
#line 297 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 16:
#line 304 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 17:
#line 311 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].constant)->Put(*code_block); delete (yyvsp[(3) - (6)].constant);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 18:
#line 318 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
                  ASMInt<Code::IntegerSizedType> ivalue((yyvsp[(3) - (6)].constant)->Value(), ConstEntry::INTEGER_TYPE);
		  ivalue.Put(*code_block); delete (yyvsp[(3) - (6)].constant);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 19:
#line 325 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].double_num)->Put(*code_block); delete (yyvsp[(3) - (6)].double_num);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 20:
#line 331 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		  string* buff = (yyvsp[(3) - (6)].string_value);
		  for (string::iterator iter = buff->begin();
		       iter != buff->end(); iter++)
		    code_block->Put(*iter);
		  code_block->Put('\0');
		  delete (yyvsp[(3) - (6)].string_value);
		}
    break;

  case 21:
#line 343 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
		}
    break;

  case 22:
#line 349 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].number)->Put(*code_block); delete (yyvsp[(3) - (6)].number);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 23:
#line 356 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 24:
#line 363 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 25:
#line 370 "qa.y"
    {
		   (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		   (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		   (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		 }
    break;

  case 26:
#line 377 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 27:
#line 384 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
		}
    break;

  case 28:
#line 390 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
		}
    break;

  case 29:
#line 396 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].number)->Put(*code_block); delete (yyvsp[(3) - (6)].number);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 30:
#line 403 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 31:
#line 410 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 32:
#line 417 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
		}
    break;

  case 33:
#line 423 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 34:
#line 430 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 35:
#line 437 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 36:
#line 444 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 37:
#line 451 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].constant)->Put(*code_block); delete (yyvsp[(3) - (6)].constant);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 38:
#line 458 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
                  ASMInt<Code::IntegerSizedType> ivalue((yyvsp[(3) - (6)].constant)->Value(), ConstEntry::INTEGER_TYPE);
		  ivalue.Put(*code_block); delete (yyvsp[(3) - (6)].constant);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 39:
#line 466 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].double_num)->Put(*code_block); delete (yyvsp[(3) - (6)].double_num);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 40:
#line 473 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		  string* buff = (yyvsp[(3) - (6)].string_value);
		  for (string::iterator iter = buff->begin();
		       iter != buff->end(); iter++)
		    code_block->Put(*iter);
		  code_block->Put('\0');
		  delete (yyvsp[(3) - (6)].string_value);
		}
    break;

  case 41:
#line 485 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
		}
    break;

  case 42:
#line 491 "qa.y"
    {
		  (yyvsp[(1) - (8)].instruction)->Put(*code_block); delete (yyvsp[(1) - (8)].instruction);
		  (yyvsp[(3) - (8)].constant)->Put(*code_block); delete (yyvsp[(3) - (8)].constant);
		  (yyvsp[(5) - (8)].number)->Put(*code_block); delete (yyvsp[(5) - (8)].number);
		  (yyvsp[(7) - (8)].reg)->Put(*code_block); delete (yyvsp[(7) - (8)].reg);
		}
    break;

  case 43:
#line 499 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].number)->Put(*code_block); delete (yyvsp[(3) - (6)].number);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 44:
#line 506 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 45:
#line 513 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 46:
#line 520 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 47:
#line 527 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].reg)->Put(*code_block); delete (yyvsp[(3) - (6)].reg);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 48:
#line 534 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
        	}
    break;

  case 49:
#line 540 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
        	}
    break;

  case 50:
#line 546 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
        	}
    break;

  case 51:
#line 552 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
        	}
    break;

  case 52:
#line 558 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].constant)->Put(*code_block); delete (yyvsp[(3) - (4)].constant);
		}
    break;

  case 53:
#line 564 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
                  ASMInt<Code::IntegerSizedType> ivalue((yyvsp[(3) - (4)].constant)->Value(), ConstEntry::INTEGER_TYPE);
		  ivalue.Put(*code_block); delete (yyvsp[(3) - (4)].constant);
		}
    break;

  case 54:
#line 571 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].double_num)->Put(*code_block); delete (yyvsp[(3) - (4)].double_num);
		}
    break;

  case 55:
#line 577 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  string* buff = (yyvsp[(3) - (4)].string_value);
		  for (string::iterator iter = buff->begin();
		       iter != buff->end(); iter++)
		    code_block->Put(*iter);
		  code_block->Put('\0');
		  delete (yyvsp[(3) - (4)].string_value);
		}
    break;

  case 56:
#line 588 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].number)->Put(*code_block); delete (yyvsp[(3) - (4)].number);
	        }
    break;

  case 57:
#line 594 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
        	}
    break;

  case 58:
#line 600 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
        	}
    break;

  case 59:
#line 606 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
        	}
    break;

  case 60:
#line 612 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
	        }
    break;

  case 61:
#line 618 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
        	}
    break;

  case 62:
#line 624 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
        	}
    break;

  case 63:
#line 630 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
        	}
    break;

  case 64:
#line 636 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
        	}
    break;

  case 65:
#line 642 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
        	}
    break;

  case 66:
#line 648 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
	        }
    break;

  case 67:
#line 654 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].constant)->Put(*code_block); delete (yyvsp[(3) - (4)].constant);
		}
    break;

  case 68:
#line 660 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
                  ASMInt<Code::IntegerSizedType> ivalue((yyvsp[(3) - (4)].constant)->Value(), ConstEntry::INTEGER_TYPE);
		  ivalue.Put(*code_block); delete (yyvsp[(3) - (4)].constant);
		}
    break;

  case 69:
#line 667 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].double_num)->Put(*code_block); delete (yyvsp[(3) - (4)].double_num);
		}
    break;

  case 70:
#line 673 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  string* buff = (yyvsp[(3) - (4)].string_value);
		  for (string::iterator iter = buff->begin();
		       iter != buff->end(); iter++)
		    code_block->Put(*iter);
		  code_block->Put('\0');
		  delete (yyvsp[(3) - (4)].string_value);
		}
    break;

  case 71:
#line 684 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].number)->Put(*code_block); delete (yyvsp[(3) - (4)].number);
		}
    break;

  case 72:
#line 690 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].number)->Put(*code_block); delete (yyvsp[(3) - (4)].number);
		}
    break;

  case 73:
#line 696 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].number)->Put(*code_block); delete (yyvsp[(3) - (4)].number);
		}
    break;

  case 74:
#line 702 "qa.y"
    {
		  (yyvsp[(1) - (1)].instruction)->Put(*code_block); delete (yyvsp[(1) - (1)].instruction);
		}
    break;

  case 75:
#line 707 "qa.y"
    {
		  (yyvsp[(1) - (8)].instruction)->Put(*code_block); delete (yyvsp[(1) - (8)].instruction);
		  (yyvsp[(3) - (8)].constant)->Put(*code_block); delete (yyvsp[(3) - (8)].constant);
		  (yyvsp[(5) - (8)].number)->Put(*code_block); delete (yyvsp[(5) - (8)].number);
		  (yyvsp[(7) - (8)].number)->Put(*code_block); delete (yyvsp[(7) - (8)].number);
		}
    break;

  case 76:
#line 715 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction); 
		  (yyvsp[(3) - (6)].address)->Put(*code_block); delete (yyvsp[(3) - (6)].address);
		  (yyvsp[(5) - (6)].number)->Put(*code_block); delete (yyvsp[(5) - (6)].number);
		}
    break;

  case 77:
#line 722 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].address)->Put(*code_block); delete (yyvsp[(3) - (6)].address);
		  (yyvsp[(5) - (6)].number)->Put(*code_block); delete (yyvsp[(5) - (6)].number);
		}
    break;

  case 78:
#line 729 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].constant)->Put(*code_block); delete (yyvsp[(3) - (6)].constant);
		  (yyvsp[(5) - (6)].number)->Put(*code_block); delete (yyvsp[(5) - (6)].number);
		}
    break;

  case 79:
#line 736 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].address)->Put(*code_block); delete (yyvsp[(3) - (4)].address);
		}
    break;

  case 80:
#line 742 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].address)->Put(*code_block); delete (yyvsp[(3) - (4)].address);
		}
    break;

  case 81:
#line 748 "qa.y"
    {
		  (yyvsp[(1) - (1)].instruction)->Put(*code_block); delete (yyvsp[(1) - (1)].instruction);
		}
    break;

  case 82:
#line 753 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].address)->Put(*code_block); delete (yyvsp[(3) - (4)].address);
		}
    break;

  case 83:
#line 759 "qa.y"
    {
		  (yyvsp[(1) - (1)].instruction)->Put(*code_block); delete (yyvsp[(1) - (1)].instruction);
		}
    break;

  case 84:
#line 764 "qa.y"
    {
		  (yyvsp[(1) - (1)].instruction)->Put(*code_block); delete (yyvsp[(1) - (1)].instruction);
		}
    break;

  case 85:
#line 769 "qa.y"
    {
		  (yyvsp[(1) - (1)].instruction)->Put(*code_block); delete (yyvsp[(1) - (1)].instruction);
		}
    break;

  case 86:
#line 774 "qa.y"
    {
		  (yyvsp[(1) - (1)].instruction)->Put(*code_block); delete (yyvsp[(1) - (1)].instruction);
		}
    break;

  case 87:
#line 779 "qa.y"
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[(1) - (6)].instruction)->SizeOf() + (yyvsp[(3) - (6)].number)->SizeOf() + Code::SIZE_OF_OFFSET;

		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].number)->Put(*code_block); delete (yyvsp[(3) - (6)].number);

		  labels->AddReference(*(yyvsp[(5) - (6)].label_name), *code_block, jump_offset_base);
		}
    break;

  case 88:
#line 791 "qa.y"
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[(1) - (4)].instruction)->SizeOf() + Code::SIZE_OF_OFFSET;

		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  labels->AddReference(*(yyvsp[(3) - (4)].label_name), *code_block, jump_offset_base);
		}
    break;

  case 89:
#line 801 "qa.y"
    {
		  (yyvsp[(1) - (1)].instruction)->Put(*code_block); delete (yyvsp[(1) - (1)].instruction);
		}
    break;

  case 90:
#line 806 "qa.y"
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[(1) - (6)].instruction)->SizeOf() + (yyvsp[(3) - (6)].number)->SizeOf() + Code::SIZE_OF_OFFSET;

		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].number)->Put(*code_block); delete (yyvsp[(3) - (6)].number);

		  labels->AddReference(*(yyvsp[(5) - (6)].label_name), *code_block, jump_offset_base);
		}
    break;

  case 91:
#line 818 "qa.y"
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[(1) - (4)].instruction)->SizeOf() + Code::SIZE_OF_OFFSET;

		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  labels->AddReference(*(yyvsp[(3) - (4)].label_name), *code_block, jump_offset_base);
		}
    break;

  case 92:
#line 828 "qa.y"
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[(1) - (4)].instruction)->SizeOf() + Code::SIZE_OF_OFFSET;

		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  labels->AddReference(*(yyvsp[(3) - (4)].label_name), *code_block, jump_offset_base);
		}
    break;

  case 93:
#line 838 "qa.y"
    {
		  (yyvsp[(1) - (1)].instruction)->Put(*code_block); delete (yyvsp[(1) - (1)].instruction);
		}
    break;

  case 94:
#line 843 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
		}
    break;

  case 95:
#line 849 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
		}
    break;

  case 96:
#line 855 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].reg)->Put(*code_block); delete (yyvsp[(3) - (4)].reg);
		}
    break;

  case 97:
#line 867 "qa.y"
    {
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[(1) - (16)].instruction)->SizeOf() + (yyvsp[(3) - (16)].reg)->SizeOf() + 6 * Code::SIZE_OF_OFFSET;

		  (yyvsp[(1) - (16)].instruction)->Put(*code_block); delete (yyvsp[(1) - (16)].instruction);
		  (yyvsp[(3) - (16)].reg)->Put(*code_block); delete (yyvsp[(3) - (16)].reg);

		  labels->AddReference(*(yyvsp[(5) - (16)].label_name), *code_block, jump_offset_base);
		  labels->AddReference(*(yyvsp[(7) - (16)].label_name), *code_block, jump_offset_base);
		  labels->AddReference(*(yyvsp[(9) - (16)].label_name), *code_block, jump_offset_base);
		  labels->AddReference(*(yyvsp[(11) - (16)].label_name), *code_block, jump_offset_base);
		  labels->AddReference(*(yyvsp[(13) - (16)].label_name), *code_block, jump_offset_base);
		  labels->AddReference(*(yyvsp[(15) - (16)].label_name), *code_block, jump_offset_base);
		}
    break;

  case 98:
#line 886 "qa.y"
    {
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[(1) - (13)].instruction)->SizeOf() + (yyvsp[(3) - (13)].reg)->SizeOf() + (yyvsp[(5) - (13)].table_size)->SizeOf();

		  (yyvsp[(1) - (13)].instruction)->Put(*code_block); delete (yyvsp[(1) - (13)].instruction);
		  (yyvsp[(3) - (13)].reg)->Put(*code_block); delete (yyvsp[(3) - (13)].reg);
		  (yyvsp[(5) - (13)].table_size)->Put(*code_block); 

		  if (*(yyvsp[(8) - (13)].atom_name) != "$default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_structure");
		    }

		 ConstantSwitchTable switch_table(jump_offset_base,
							  (yyvsp[(5) - (13)].table_size), (yyvsp[(10) - (13)].label_name), (yyvsp[(11) - (13)].cl_list));

		  switch_table.Put(*code_block, *labels);

		  delete (yyvsp[(5) - (13)].table_size);
		  delete (yyvsp[(10) - (13)].label_name);
		  delete (yyvsp[(11) - (13)].cl_list);
		}
    break;

  case 99:
#line 914 "qa.y"
    {
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[(1) - (13)].instruction)->SizeOf() + (yyvsp[(3) - (13)].reg)->SizeOf() + (yyvsp[(5) - (13)].table_size)->SizeOf();

		  (yyvsp[(1) - (13)].instruction)->Put(*code_block); delete (yyvsp[(1) - (13)].instruction);
		  (yyvsp[(3) - (13)].reg)->Put(*code_block); delete (yyvsp[(3) - (13)].reg);
		  (yyvsp[(5) - (13)].table_size)->Put(*code_block);

		  if (*(yyvsp[(8) - (13)].atom_name) != "$default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_structure");
		    }

		  AtomSwitchTable switch_table(jump_offset_base,
							   (yyvsp[(5) - (13)].table_size), (yyvsp[(10) - (13)].label_name), (yyvsp[(11) - (13)].aal_list));

		  switch_table.Put(*code_block, *labels);

		  delete (yyvsp[(5) - (13)].table_size);
		  delete (yyvsp[(10) - (13)].label_name);
		  delete (yyvsp[(11) - (13)].aal_list);
		}
    break;

  case 100:
#line 942 "qa.y"
    {
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[(1) - (13)].instruction)->SizeOf() + (yyvsp[(3) - (13)].reg)->SizeOf() + (yyvsp[(5) - (13)].table_size)->SizeOf();

		  (yyvsp[(1) - (13)].instruction)->Put(*code_block); delete (yyvsp[(1) - (13)].instruction);
		  (yyvsp[(3) - (13)].reg)->Put(*code_block); delete (yyvsp[(3) - (13)].reg);
		  (yyvsp[(5) - (13)].table_size)->Put(*code_block);

		  if (*(yyvsp[(8) - (13)].atom_name) != "$default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_quantifier");
		    }

		  AtomSwitchTable switch_table(jump_offset_base,
							   (yyvsp[(5) - (13)].table_size), (yyvsp[(10) - (13)].label_name), (yyvsp[(11) - (13)].aal_list));

		  switch_table.Put(*code_block, *labels);

		  delete (yyvsp[(5) - (13)].table_size);
		  delete (yyvsp[(10) - (13)].label_name);
		  delete (yyvsp[(11) - (13)].aal_list);
		}
    break;

  case 101:
#line 969 "qa.y"
    {
		  (yyvsp[(1) - (4)].instruction)->Put(*code_block); delete (yyvsp[(1) - (4)].instruction);
		  (yyvsp[(3) - (4)].number)->Put(*code_block); delete (yyvsp[(3) - (4)].number);
		}
    break;

  case 102:
#line 975 "qa.y"
    {
		  (yyvsp[(1) - (6)].instruction)->Put(*code_block); delete (yyvsp[(1) - (6)].instruction);
		  (yyvsp[(3) - (6)].number)->Put(*code_block); delete (yyvsp[(3) - (6)].number);
		  (yyvsp[(5) - (6)].reg)->Put(*code_block); delete (yyvsp[(5) - (6)].reg);
		}
    break;

  case 103:
#line 982 "qa.y"
    {
		  (yyvsp[(1) - (8)].instruction)->Put(*code_block); delete (yyvsp[(1) - (8)].instruction);
		  (yyvsp[(3) - (8)].number)->Put(*code_block); delete (yyvsp[(3) - (8)].number);
		  (yyvsp[(5) - (8)].reg)->Put(*code_block); delete (yyvsp[(5) - (8)].reg);
		  (yyvsp[(7) - (8)].reg)->Put(*code_block); delete (yyvsp[(7) - (8)].reg);
		}
    break;

  case 104:
#line 990 "qa.y"
    {
		  (yyvsp[(1) - (10)].instruction)->Put(*code_block); delete (yyvsp[(1) - (10)].instruction);
		  (yyvsp[(3) - (10)].number)->Put(*code_block); delete (yyvsp[(3) - (10)].number);
		  (yyvsp[(5) - (10)].reg)->Put(*code_block); delete (yyvsp[(5) - (10)].reg);
		  (yyvsp[(7) - (10)].reg)->Put(*code_block); delete (yyvsp[(7) - (10)].reg);
		  (yyvsp[(9) - (10)].reg)->Put(*code_block); delete (yyvsp[(9) - (10)].reg);
		}
    break;

  case 105:
#line 1000 "qa.y"
    {
		  (yyvsp[(1) - (12)].instruction)->Put(*code_block); delete (yyvsp[(1) - (12)].instruction);
		  (yyvsp[(3) - (12)].number)->Put(*code_block); delete (yyvsp[(3) - (12)].number);
		  (yyvsp[(5) - (12)].reg)->Put(*code_block); delete (yyvsp[(5) - (12)].reg);
		  (yyvsp[(7) - (12)].reg)->Put(*code_block); delete (yyvsp[(7) - (12)].reg);
		  (yyvsp[(9) - (12)].reg)->Put(*code_block); delete (yyvsp[(9) - (12)].reg);
		  (yyvsp[(11) - (12)].reg)->Put(*code_block); delete (yyvsp[(11) - (12)].reg);
		}
    break;

  case 106:
#line 1010 "qa.y"
    {
		  (yyvsp[(1) - (14)].instruction)->Put(*code_block); delete (yyvsp[(1) - (14)].instruction);
		  (yyvsp[(3) - (14)].number)->Put(*code_block); delete (yyvsp[(3) - (14)].number);
		  (yyvsp[(5) - (14)].reg)->Put(*code_block); delete (yyvsp[(5) - (14)].reg);
		  (yyvsp[(7) - (14)].reg)->Put(*code_block); delete (yyvsp[(7) - (14)].reg);
		  (yyvsp[(9) - (14)].reg)->Put(*code_block); delete (yyvsp[(9) - (14)].reg);
		  (yyvsp[(11) - (14)].reg)->Put(*code_block); delete (yyvsp[(11) - (14)].reg);
		  (yyvsp[(13) - (14)].reg)->Put(*code_block); delete (yyvsp[(13) - (14)].reg);
		}
    break;

  case 107:
#line 1022 "qa.y"
    {
		  (yyval.cl_list) = NULL;
		}
    break;

  case 108:
#line 1026 "qa.y"
    {
		  (yyval.cl_list) = (yyvsp[(2) - (2)].cl_list);
		}
    break;

  case 109:
#line 1032 "qa.y"
    {
		  vector<ConstantLabel *> *tmp = new vector<ConstantLabel *>;

		  tmp->push_back((yyvsp[(1) - (1)].cl));

		  (yyval.cl_list) = tmp;
		}
    break;

  case 110:
#line 1040 "qa.y"
    {
		  (yyvsp[(1) - (3)].cl_list)->push_back((yyvsp[(3) - (3)].cl));

		  (yyval.cl_list) = (yyvsp[(1) - (3)].cl_list);
		}
    break;

  case 111:
#line 1048 "qa.y"
    {
		  (yyval.cl) = new ConstantLabel((yyvsp[(1) - (3)].constant), (yyvsp[(3) - (3)].label_name));
		}
    break;

  case 112:
#line 1054 "qa.y"
    {
		  (yyval.aal_list) = NULL;
		}
    break;

  case 113:
#line 1058 "qa.y"
    {
		  (yyval.aal_list) = (yyvsp[(2) - (2)].aal_list);
		}
    break;

  case 114:
#line 1064 "qa.y"
    {
		  vector<AtomArityLabel *> *tmp = new vector<AtomArityLabel *>;

		  tmp->push_back((yyvsp[(1) - (1)].aal));

		  (yyval.aal_list) = tmp;
		}
    break;

  case 115:
#line 1072 "qa.y"
    {
		  (yyvsp[(1) - (3)].aal_list)->push_back((yyvsp[(3) - (3)].aal));
		  (yyval.aal_list) = (yyvsp[(1) - (3)].aal_list);
		}
    break;

  case 116:
#line 1079 "qa.y"
    {
		  ASMStringPointer asm_atom((yyvsp[(1) - (5)].atom_name));
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  ASMInt<Code::ConstantSizedType> *atom = 
		    new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);


		  (yyval.aal) = new AtomArityLabel(atom, (yyvsp[(3) - (5)].number), (yyvsp[(5) - (5)].label_name));

		}
    break;

  case 117:
#line 1093 "qa.y"
    {
		  (yyval.aal_list) = NULL;
		}
    break;

  case 118:
#line 1097 "qa.y"
    {
		  (yyval.aal_list) = (yyvsp[(2) - (2)].aal_list);
		}
    break;

  case 119:
#line 1103 "qa.y"
    {
		  vector<AtomArityLabel *> *tmp = new vector<AtomArityLabel *>;

		  tmp->push_back((yyvsp[(1) - (1)].aal));

		  (yyval.aal_list) = tmp;
		}
    break;

  case 120:
#line 1111 "qa.y"
    {
		  (yyvsp[(1) - (3)].aal_list)->push_back((yyvsp[(3) - (3)].aal));

		  (yyval.aal_list) = (yyvsp[(1) - (3)].aal_list);
		}
    break;

  case 121:
#line 1119 "qa.y"
    {
		  ASMStringPointer asm_atom((yyvsp[(1) - (5)].atom_name));
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  ASMInt<Code::ConstantSizedType> *atom = 
		    new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);

		  (yyval.aal) = new AtomArityLabel(atom, (yyvsp[(3) - (5)].number), (yyvsp[(5) - (5)].label_name));
		}
    break;

  case 123:
#line 1132 "qa.y"
    {
		  if (*(yyvsp[(1) - (1)].atom_name) != "fail")
		    {
		      FatalS(__FUNCTION__, "invalid switch label ",
			     (yyvsp[(1) - (1)].atom_name)->c_str());
		    }
		}
    break;

  case 124:
#line 1142 "qa.y"
    {
		  ASMStringPointer asm_atom((yyvsp[(1) - (1)].atom_name));
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  (yyval.constant) = new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);
		}
    break;

  case 125:
#line 1149 "qa.y"
    {
		  (yyval.constant) = new ASMInt<Code::ConstantSizedType>((wordlong)((yyvsp[(1) - (1)].number_value)), ConstEntry::INTEGER_TYPE);

		}
    break;

  case 126:
#line 1154 "qa.y"
    {
		  (yyval.constant) = new ASMInt<Code::ConstantSizedType>((wordlong)((yyvsp[(2) - (2)].number_value)), ConstEntry::INTEGER_TYPE);

		}
    break;

  case 127:
#line 1159 "qa.y"
    {
		  (yyval.constant) = new ASMInt<Code::ConstantSizedType>((wordlong)(-(yyvsp[(2) - (2)].number_value)), ConstEntry::INTEGER_TYPE);

		}
    break;

  case 128:
#line 1166 "qa.y"
    {
		  (yyval.double_num) = new ASMDouble<double>((double)((yyvsp[(1) - (1)].double_value)), ConstEntry::INTEGER_TYPE);

		}
    break;

  case 129:
#line 1171 "qa.y"
    {
		  (yyval.double_num) = new ASMDouble<double>((double)((yyvsp[(2) - (2)].double_value)), ConstEntry::INTEGER_TYPE);

		}
    break;

  case 130:
#line 1176 "qa.y"
    {
		  (yyval.double_num) = new ASMDouble<double>((double)(-(yyvsp[(2) - (2)].double_value)), ConstEntry::INTEGER_TYPE);

		}
    break;

  case 131:
#line 1182 "qa.y"
    {
		  (yyval.number) = new ASMInt<Code::NumberSizedType>((yyvsp[(1) - (1)].number_value));

		}
    break;

  case 132:
#line 1191 "qa.y"
    {
		  (yyval.reg) = new ASMInt<Code::RegisterSizedType>((yyvsp[(1) - (1)].number_value));
		  
		}
    break;

  case 133:
#line 1198 "qa.y"
    {
		  (yyval.address) = new ASMInt<Code::AddressSizedType>((yyvsp[(1) - (1)].number_value));

		}
    break;

  case 134:
#line 1205 "qa.y"
    {
		  ASMStringPointer asm_atom((yyvsp[(1) - (1)].atom_name));
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);
		  (yyval.constant) = new ASMInt<Code::PredSizedType>(loc);
		}
    break;

  case 135:
#line 1213 "qa.y"
    {
		  (yyval.table_size) = new ASMInt<Code::TableSizeSizedType>((yyvsp[(1) - (1)].number_value));

		}
    break;


/* Line 1267 of yacc.c.  */
#line 3248 "qa.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1219 "qa.y"

#include "lexer.cc"

#include <stdlib.h>

#include "qa_options.h"
		
QaOptions *qa_options = NULL;

int
main(int argc, char **argv)
{
  qa_options = new QaOptions(argc, argv);

  if (!qa_options->Valid())
    {
      Usage(Program, qa_options->Usage());
    }

  if (streq(qa_options->InputFile(), qa_options->OutputFile()))
    {
      Fatal(__FUNCTION__, "Input and output file names are identical");
    }

  // Should also check for suspect extensions .qg, .qi, .qs, .ql, .qx
  asm_string_table = new ASMStringTable;
  predicate_code_blocks = new vector<CodeBlock *>;

  // Read in the assembler source
  yyin = fopen(qa_options->InputFile(), "r");
  if (yyin == NULL)
    {
      perror(__FUNCTION__);
      exit(EXIT_FAILURE);
    }
      
  int result = yyparse();
  if (result)
    {
      Fatal(__FUNCTION__, "bad .qs input file");
    }
  fclose(yyin);

  // Write out the assembled object

  // First check if any compiled predicates are too big - i.e. >= 2^16
  for (vector<CodeBlock *>::iterator iter = predicate_code_blocks->begin();
       iter != predicate_code_blocks->end();
       iter++)
    {
      if ((*iter)->Current() >= (1 << (8*sizeof(Code::OffsetSizedType))))
        {
	  Fatal(__FUNCTION__, "Compiled predicate is too big");
	}
    }


  ofstream ostrm(qa_options->OutputFile());

  asm_string_table->save(ostrm);

  if (query_code_block)
    {
      query_code_block->Save(ostrm);
    }
  else
    {
      IntSave<Code::OffsetSizedType>(ostrm, 0);
    }
  
  for (vector<CodeBlock *>::iterator iter = predicate_code_blocks->begin();
       iter != predicate_code_blocks->end();
       iter++)
    {
      (*iter)->Save(ostrm);
    }

  ostrm.close();

  exit(EXIT_SUCCESS);
}

int
yyerror(const char *s)
{
  Fatal(__FUNCTION__, s);
  return(1);
}

