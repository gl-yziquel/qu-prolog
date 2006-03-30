/* A Bison parser, made by GNU Bison 2.0.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

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
     put_list = 265,
     put_structure = 266,
     put_x_object_variable = 267,
     put_y_object_variable = 268,
     put_x_object_value = 269,
     put_y_object_value = 270,
     put_quantifier = 271,
     check_binder = 272,
     put_substitution = 273,
     put_x_term_substitution = 274,
     put_y_term_substitution = 275,
     put_initial_empty_substitution = 276,
     get_x_variable = 277,
     get_y_variable = 278,
     get_x_value = 279,
     get_y_value = 280,
     get_constant = 281,
     get_integer = 282,
     get_double = 283,
     get_list = 284,
     get_structure = 285,
     get_structure_frame = 286,
     get_x_object_variable = 287,
     get_y_object_variable = 288,
     get_x_object_value = 289,
     get_y_object_value = 290,
     unify_x_variable = 291,
     unify_y_variable = 292,
     unify_x_value = 293,
     unify_y_value = 294,
     unify_void = 295,
     unify_constant = 296,
     unify_integer = 297,
     unify_double = 298,
     unify_x_ref = 299,
     unify_y_ref = 300,
     set_x_variable = 301,
     set_y_variable = 302,
     set_x_value = 303,
     set_y_value = 304,
     set_x_object_variable = 305,
     set_y_object_variable = 306,
     set_x_object_value = 307,
     set_y_object_value = 308,
     set_constant = 309,
     set_integer = 310,
     set_double = 311,
     set_void = 312,
     set_object_void = 313,
     wam_allocate = 314,
     wam_deallocate = 315,
     call_predicate = 316,
     call_address = 317,
     call_escape = 318,
     execute_predicate = 319,
     execute_address = 320,
     execute_escape = 321,
     noop = 322,
     jump = 323,
     proceed = 324,
     wam_fail = 325,
     halt = 326,
     wam_exit = 327,
     try_me_else = 328,
     retry_me_else = 329,
     trust_me_else_fail = 330,
     wam_try = 331,
     retry = 332,
     trust = 333,
     neck_cut = 334,
     get_x_level = 335,
     get_y_level = 336,
     cut = 337,
     switch_on_term = 338,
     switch_on_constant = 339,
     switch_on_structure = 340,
     switch_on_quantifier = 341,
     pseudo_instr0 = 342,
     pseudo_instr1 = 343,
     pseudo_instr2 = 344,
     pseudo_instr3 = 345,
     pseudo_instr4 = 346,
     pseudo_instr5 = 347,
     NUMBER_TOKEN = 348,
     DOUBLE_TOKEN = 349,
     ATOM_TOKEN = 350,
     LABEL_TOKEN = 351,
     END_TOKEN = 352
   };
#endif
#define put_x_variable 258
#define put_y_variable 259
#define put_x_value 260
#define put_y_value 261
#define put_constant 262
#define put_integer 263
#define put_double 264
#define put_list 265
#define put_structure 266
#define put_x_object_variable 267
#define put_y_object_variable 268
#define put_x_object_value 269
#define put_y_object_value 270
#define put_quantifier 271
#define check_binder 272
#define put_substitution 273
#define put_x_term_substitution 274
#define put_y_term_substitution 275
#define put_initial_empty_substitution 276
#define get_x_variable 277
#define get_y_variable 278
#define get_x_value 279
#define get_y_value 280
#define get_constant 281
#define get_integer 282
#define get_double 283
#define get_list 284
#define get_structure 285
#define get_structure_frame 286
#define get_x_object_variable 287
#define get_y_object_variable 288
#define get_x_object_value 289
#define get_y_object_value 290
#define unify_x_variable 291
#define unify_y_variable 292
#define unify_x_value 293
#define unify_y_value 294
#define unify_void 295
#define unify_constant 296
#define unify_integer 297
#define unify_double 298
#define unify_x_ref 299
#define unify_y_ref 300
#define set_x_variable 301
#define set_y_variable 302
#define set_x_value 303
#define set_y_value 304
#define set_x_object_variable 305
#define set_y_object_variable 306
#define set_x_object_value 307
#define set_y_object_value 308
#define set_constant 309
#define set_integer 310
#define set_double 311
#define set_void 312
#define set_object_void 313
#define wam_allocate 314
#define wam_deallocate 315
#define call_predicate 316
#define call_address 317
#define call_escape 318
#define execute_predicate 319
#define execute_address 320
#define execute_escape 321
#define noop 322
#define jump 323
#define proceed 324
#define wam_fail 325
#define halt 326
#define wam_exit 327
#define try_me_else 328
#define retry_me_else 329
#define trust_me_else_fail 330
#define wam_try 331
#define retry 332
#define trust 333
#define neck_cut 334
#define get_x_level 335
#define get_y_level 336
#define cut 337
#define switch_on_term 338
#define switch_on_constant 339
#define switch_on_structure 340
#define switch_on_quantifier 341
#define pseudo_instr0 342
#define pseudo_instr1 343
#define pseudo_instr2 344
#define pseudo_instr3 345
#define pseudo_instr4 346
#define pseudo_instr5 347
#define NUMBER_TOKEN 348
#define DOUBLE_TOKEN 349
#define ATOM_TOKEN 350
#define LABEL_TOKEN 351
#define END_TOKEN 352




/* Copy the first part of user declarations.  */
#line 1 "qa.y"

/*
 * Copyright (C) 1999 
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
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 36 "qa.y"
typedef union YYSTYPE {
  signed long int number_value;
  double double_value;

  string *label_name;
  string *atom_name;

  ASMLoc loc;

  ASMInt<Code::InstructionSizedType> *instruction;
  ASMInt<Code::ConstantSizedType> *constant;
  ASMInt<double> *double_num;
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
} YYSTYPE;
/* Line 190 of yacc.c.  */
#line 332 "qa.cc"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 213 of yacc.c.  */
#line 344 "qa.cc"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
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
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   582

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  107
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  27
/* YYNRULES -- Number of rules. */
#define YYNRULES  131
/* YYNRULES -- Number of states. */
#define YYNSTATES  547

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   352

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     100,   101,     2,   105,   102,   106,     2,    98,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    99,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   103,     2,   104,     2,     2,     2,     2,     2,     2,
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
      95,    96,    97
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    13,    18,    26,    27,
      30,    32,    34,    37,    44,    51,    58,    65,    72,    79,
      86,    91,    98,   105,   112,   119,   126,   131,   136,   143,
     150,   157,   162,   169,   176,   183,   190,   197,   204,   211,
     216,   225,   232,   239,   246,   253,   260,   265,   270,   275,
     280,   285,   290,   295,   300,   305,   310,   315,   320,   325,
     330,   335,   340,   345,   350,   355,   360,   365,   370,   375,
     380,   382,   391,   398,   405,   412,   417,   422,   424,   429,
     431,   433,   435,   437,   444,   449,   451,   458,   463,   468,
     470,   475,   480,   485,   502,   516,   530,   544,   549,   556,
     565,   576,   589,   604,   605,   608,   610,   614,   618,   619,
     622,   624,   628,   634,   635,   638,   640,   644,   650,   652,
     654,   656,   658,   661,   664,   666,   669,   672,   674,   676,
     678,   680
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
     108,     0,    -1,   109,    -1,    -1,   109,   110,    -1,   111,
     113,   112,    -1,   132,    98,   129,    99,    -1,    97,   100,
     132,    98,   129,   101,    99,    -1,    -1,   113,   114,    -1,
     115,    -1,   116,    -1,    96,    99,    -1,     3,   100,   130,
     102,   130,   101,    -1,     4,   100,   130,   102,   130,   101,
      -1,     5,   100,   130,   102,   130,   101,    -1,     6,   100,
     130,   102,   130,   101,    -1,     7,   100,   127,   102,   130,
     101,    -1,     8,   100,   127,   102,   130,   101,    -1,     9,
     100,   128,   102,   130,   101,    -1,    10,   100,   130,   101,
      -1,    11,   100,   129,   102,   130,   101,    -1,    12,   100,
     130,   102,   130,   101,    -1,    13,   100,   130,   102,   130,
     101,    -1,    14,   100,   130,   102,   130,   101,    -1,    15,
     100,   130,   102,   130,   101,    -1,    16,   100,   130,   101,
      -1,    17,   100,   130,   101,    -1,    18,   100,   129,   102,
     130,   101,    -1,    19,   100,   130,   102,   130,   101,    -1,
      20,   100,   130,   102,   130,   101,    -1,    21,   100,   130,
     101,    -1,    22,   100,   130,   102,   130,   101,    -1,    23,
     100,   130,   102,   130,   101,    -1,    24,   100,   130,   102,
     130,   101,    -1,    25,   100,   130,   102,   130,   101,    -1,
      26,   100,   127,   102,   130,   101,    -1,    27,   100,   127,
     102,   130,   101,    -1,    28,   100,   128,   102,   130,   101,
      -1,    29,   100,   130,   101,    -1,    30,   100,   127,   102,
     129,   102,   130,   101,    -1,    31,   100,   129,   102,   130,
     101,    -1,    32,   100,   130,   102,   130,   101,    -1,    33,
     100,   130,   102,   130,   101,    -1,    34,   100,   130,   102,
     130,   101,    -1,    35,   100,   130,   102,   130,   101,    -1,
      36,   100,   130,   101,    -1,    37,   100,   130,   101,    -1,
      38,   100,   130,   101,    -1,    39,   100,   130,   101,    -1,
      41,   100,   127,   101,    -1,    42,   100,   127,   101,    -1,
      43,   100,   128,   101,    -1,    40,   100,   129,   101,    -1,
      44,   100,   130,   101,    -1,    45,   100,   130,   101,    -1,
      46,   100,   130,   101,    -1,    47,   100,   130,   101,    -1,
      48,   100,   130,   101,    -1,    49,   100,   130,   101,    -1,
      50,   100,   130,   101,    -1,    51,   100,   130,   101,    -1,
      52,   100,   130,   101,    -1,    53,   100,   130,   101,    -1,
      54,   100,   127,   101,    -1,    55,   100,   127,   101,    -1,
      56,   100,   128,   101,    -1,    57,   100,   129,   101,    -1,
      58,   100,   129,   101,    -1,    59,   100,   129,   101,    -1,
      60,    -1,    61,   100,   132,   102,   129,   102,   129,   101,
      -1,    62,   100,   131,   102,   129,   101,    -1,    63,   100,
     131,   102,   129,   101,    -1,    64,   100,   132,   102,   129,
     101,    -1,    65,   100,   131,   101,    -1,    66,   100,   131,
     101,    -1,    67,    -1,    68,   100,   131,   101,    -1,    69,
      -1,    70,    -1,    71,    -1,    72,    -1,    73,   100,   129,
     102,    96,   101,    -1,    74,   100,    96,   101,    -1,    75,
      -1,    76,   100,   129,   102,    96,   101,    -1,    77,   100,
      96,   101,    -1,    78,   100,    96,   101,    -1,    79,    -1,
      80,   100,   130,   101,    -1,    81,   100,   130,   101,    -1,
      82,   100,   130,   101,    -1,    83,   100,   130,   102,   126,
     102,   126,   102,   126,   102,   126,   102,   126,   102,   126,
     101,    -1,    84,   100,   130,   102,   133,   102,   103,    95,
      99,   126,   117,   104,   101,    -1,    85,   100,   130,   102,
     133,   102,   103,    95,    99,   126,   120,   104,   101,    -1,
      86,   100,   130,   102,   133,   102,   103,    95,    99,   126,
     123,   104,   101,    -1,    87,   100,   129,   101,    -1,    88,
     100,   129,   102,   130,   101,    -1,    89,   100,   129,   102,
     130,   102,   130,   101,    -1,    90,   100,   129,   102,   130,
     102,   130,   102,   130,   101,    -1,    91,   100,   129,   102,
     130,   102,   130,   102,   130,   102,   130,   101,    -1,    92,
     100,   129,   102,   130,   102,   130,   102,   130,   102,   130,
     102,   130,   101,    -1,    -1,   102,   118,    -1,   119,    -1,
     118,   102,   119,    -1,   127,    99,   126,    -1,    -1,   102,
     121,    -1,   122,    -1,   121,   102,   122,    -1,    95,    98,
     129,    99,   126,    -1,    -1,   102,   124,    -1,   125,    -1,
     124,   102,   125,    -1,    95,    98,   129,    99,   126,    -1,
      96,    -1,    95,    -1,    95,    -1,    93,    -1,   105,    93,
      -1,   106,    93,    -1,    94,    -1,   105,    94,    -1,   106,
      94,    -1,    93,    -1,    93,    -1,    93,    -1,    95,    -1,
      93,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   195,   195,   198,   199,   202,   205,   236,   262,   263,
     266,   267,   270,   276,   283,   290,   297,   304,   311,   317,
     324,   330,   337,   344,   351,   358,   365,   371,   377,   384,
     391,   398,   404,   411,   418,   425,   432,   439,   446,   453,
     459,   467,   474,   481,   488,   495,   502,   508,   514,   520,
     526,   532,   538,   544,   550,   556,   562,   568,   574,   580,
     586,   592,   598,   604,   610,   616,   622,   628,   634,   640,
     646,   651,   659,   666,   673,   680,   686,   692,   697,   703,
     708,   713,   718,   723,   735,   745,   750,   762,   772,   782,
     787,   793,   799,   805,   829,   857,   885,   913,   919,   926,
     934,   943,   953,   967,   970,   976,   984,   992,  1000,  1003,
    1009,  1017,  1024,  1039,  1042,  1048,  1056,  1064,  1076,  1077,
    1087,  1094,  1099,  1104,  1111,  1116,  1121,  1127,  1134,  1141,
    1148,  1156
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "put_x_variable", "put_y_variable",
  "put_x_value", "put_y_value", "put_constant", "put_integer",
  "put_double", "put_list", "put_structure", "put_x_object_variable",
  "put_y_object_variable", "put_x_object_value", "put_y_object_value",
  "put_quantifier", "check_binder", "put_substitution",
  "put_x_term_substitution", "put_y_term_substitution",
  "put_initial_empty_substitution", "get_x_variable", "get_y_variable",
  "get_x_value", "get_y_value", "get_constant", "get_integer",
  "get_double", "get_list", "get_structure", "get_structure_frame",
  "get_x_object_variable", "get_y_object_variable", "get_x_object_value",
  "get_y_object_value", "unify_x_variable", "unify_y_variable",
  "unify_x_value", "unify_y_value", "unify_void", "unify_constant",
  "unify_integer", "unify_double", "unify_x_ref", "unify_y_ref",
  "set_x_variable", "set_y_variable", "set_x_value", "set_y_value",
  "set_x_object_variable", "set_y_object_variable", "set_x_object_value",
  "set_y_object_value", "set_constant", "set_integer", "set_double",
  "set_void", "set_object_void", "wam_allocate", "wam_deallocate",
  "call_predicate", "call_address", "call_escape", "execute_predicate",
  "execute_address", "execute_escape", "noop", "jump", "proceed",
  "wam_fail", "halt", "wam_exit", "try_me_else", "retry_me_else",
  "trust_me_else_fail", "wam_try", "retry", "trust", "neck_cut",
  "get_x_level", "get_y_level", "cut", "switch_on_term",
  "switch_on_constant", "switch_on_structure", "switch_on_quantifier",
  "pseudo_instr0", "pseudo_instr1", "pseudo_instr2", "pseudo_instr3",
  "pseudo_instr4", "pseudo_instr5", "NUMBER_TOKEN", "DOUBLE_TOKEN",
  "ATOM_TOKEN", "LABEL_TOKEN", "END_TOKEN", "'/'", "':'", "'('", "')'",
  "','", "'['", "']'", "'+'", "'-'", "$accept", "assembler_file",
  "predicate_list", "predicate", "predicate_start", "predicate_end",
  "source_line_list", "source_line", "label_instance", "instr",
  "constant_labels", "constant_label_list", "constant_label",
  "atom_arity_labels", "atom_arity_label_list", "atom_arity_label",
  "quantifier_labels", "quantifier_label_list", "quantifier_label",
  "switch_label", "constant", "double_num", "number", "reg", "address",
  "atom", "table_size", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
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
     345,   346,   347,   348,   349,   350,   351,   352,    47,    58,
      40,    41,    44,    91,    93,    43,    45
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   107,   108,   109,   109,   110,   111,   112,   113,   113,
     114,   114,   115,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   117,   117,   118,   118,   119,   120,   120,
     121,   121,   122,   123,   123,   124,   124,   125,   126,   126,
     127,   127,   127,   127,   128,   128,   128,   129,   130,   131,
     132,   133
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     0,     2,     3,     4,     7,     0,     2,
       1,     1,     2,     6,     6,     6,     6,     6,     6,     6,
       4,     6,     6,     6,     6,     6,     4,     4,     6,     6,
       6,     4,     6,     6,     6,     6,     6,     6,     6,     4,
       8,     6,     6,     6,     6,     6,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       1,     8,     6,     6,     6,     4,     4,     1,     4,     1,
       1,     1,     1,     6,     4,     1,     6,     4,     4,     1,
       4,     4,     4,    16,    13,    13,    13,     4,     6,     8,
      10,    12,    14,     0,     2,     1,     3,     3,     0,     2,
       1,     3,     5,     0,     2,     1,     3,     5,     1,     1,
       1,     1,     2,     2,     1,     2,     2,     1,     1,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       3,     0,     2,     1,   130,     4,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,     0,    77,     0,    79,    80,    81,    82,
       0,     0,    85,     0,     0,     0,    89,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     5,     9,    10,    11,   127,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      12,     0,     6,   128,     0,     0,     0,     0,   121,   120,
       0,     0,     0,     0,   124,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   129,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   122,
     123,     0,     0,   125,   126,     0,    20,     0,     0,     0,
       0,     0,    26,    27,     0,     0,     0,    31,     0,     0,
       0,     0,     0,     0,     0,    39,     0,     0,     0,     0,
       0,     0,    46,    47,    48,    49,    53,    50,    51,    52,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,     0,     0,     0,     0,
      75,    76,    78,     0,    84,     0,    87,    88,    90,    91,
      92,     0,     0,     0,     0,    97,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   119,   118,     0,   131,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
      14,    15,    16,    17,    18,    19,    21,    22,    23,    24,
      25,    28,    29,    30,    32,    33,    34,    35,    36,    37,
      38,     0,    41,    42,    43,    44,    45,     0,    72,    73,
      74,    83,    86,     0,     0,     0,     0,    98,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     7,    40,    71,     0,     0,     0,     0,
      99,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   103,   108,   113,   100,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   104,   105,
       0,     0,     0,   109,   110,     0,     0,   114,   115,     0,
     101,     0,     0,     0,     0,    94,     0,     0,    95,     0,
       0,    96,     0,     0,   106,   107,     0,   111,     0,   116,
     102,     0,     0,     0,    93,   112,   117
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     1,     2,     5,     6,   102,     8,   103,   104,   105,
     500,   508,   509,   502,   513,   514,   504,   517,   518,   408,
     510,   207,   107,   194,   260,     7,   410
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -352
static const short int yypact[] =
{
    -352,     1,   -67,  -352,  -352,  -352,  -352,   -68,   485,   -60,
     -66,   -65,   -62,   -61,   -59,   -58,   -57,   -56,   -55,   -49,
     -48,   -47,   -46,   -45,   -43,   -41,   -40,   -39,   -38,   -37,
     -36,   -35,   -33,   -26,   -22,   -21,   -20,   -18,   -11,    -3,
      -2,    -1,    11,    12,    13,    14,    26,    27,    28,    29,
      30,    31,    32,    33,    37,    38,    39,    41,    42,    50,
      51,    52,    53,    54,    55,    57,    58,  -352,    59,    60,
      61,    62,    63,    64,  -352,    65,  -352,  -352,  -352,  -352,
      66,    67,  -352,    68,    69,    70,  -352,    71,    72,    74,
      75,    76,    77,    78,    79,    80,    81,    83,    84,    85,
       2,    86,  -352,  -352,  -352,  -352,  -352,    88,   -53,   -53,
     -53,   -53,   -82,   -82,   -88,   -53,   -60,   -53,   -53,   -53,
     -53,   -53,   -53,   -60,   -53,   -53,   -53,   -53,   -53,   -53,
     -53,   -82,   -82,   -88,   -53,   -82,   -60,   -53,   -53,   -53,
     -53,   -53,   -53,   -53,   -53,   -60,   -82,   -82,   -88,   -53,
     -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   -82,
     -82,   -88,   -60,   -60,   -60,   -67,   -27,   -27,   -67,   -27,
     -27,   -27,   -60,    92,   -60,    93,    94,   -53,   -53,   -53,
     -53,   -53,   -53,   -53,   -60,   -60,   -60,   -60,   -60,   -60,
    -352,   -67,  -352,  -352,    91,    95,    96,    97,  -352,  -352,
     101,   102,    99,   100,  -352,   109,   110,   103,   105,   106,
     107,   108,   111,   112,   114,   115,   116,   117,   118,   120,
     121,   122,   123,   124,   125,   126,   127,   133,   134,   135,
     136,   137,   138,   139,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   155,   158,   159,   161,   167,   168,   172,
     180,   181,   187,   188,   189,   190,   191,   192,   193,  -352,
     194,   195,   196,   198,   199,   200,   201,   203,   204,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   216,   217,
     218,   219,   220,   221,    98,   -53,   -53,   -53,   -53,  -352,
    -352,   -53,   -53,  -352,  -352,   -53,  -352,   -53,   -53,   -53,
     -53,   -53,  -352,  -352,   -53,   -53,   -53,  -352,   -53,   -53,
     -53,   -53,   -53,   -53,   -53,  -352,   -60,   -53,   -53,   -53,
     -53,   -53,  -352,  -352,  -352,  -352,  -352,  -352,  -352,  -352,
    -352,  -352,  -352,  -352,  -352,  -352,  -352,  -352,  -352,  -352,
    -352,  -352,  -352,  -352,  -352,  -352,   -60,   -60,   -60,   -60,
    -352,  -352,  -352,   222,  -352,   228,  -352,  -352,  -352,  -352,
    -352,   -86,   119,   119,   119,  -352,   -53,   -53,   -53,   -53,
     -53,   -60,   224,   225,   226,   227,   229,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   255,   256,   257,   258,   259,
     260,   262,   263,   264,   265,   266,  -352,  -352,   267,  -352,
     268,   269,   270,   272,   273,   274,   275,   276,   278,  -352,
    -352,  -352,  -352,  -352,  -352,  -352,  -352,  -352,  -352,  -352,
    -352,  -352,  -352,  -352,  -352,  -352,  -352,  -352,  -352,  -352,
    -352,   -53,  -352,  -352,  -352,  -352,  -352,   -60,  -352,  -352,
    -352,  -352,  -352,   -86,   104,   132,   202,  -352,   -53,   -53,
     -53,   -53,   230,   279,   280,   281,   287,   289,   290,   285,
     286,   288,   291,  -352,  -352,  -352,   -86,   292,   293,   295,
    -352,   -53,   -53,   -53,   294,   -86,   -86,   -86,   296,   297,
     298,   -86,   299,   300,   301,  -352,   -53,   -53,   302,   -82,
     113,   303,   283,   310,   304,   305,   307,   -86,   309,  -352,
     313,   314,   316,   315,  -352,   317,   318,   319,  -352,   321,
    -352,   -53,   326,   -82,   -86,  -352,   -60,   303,  -352,   -60,
     310,  -352,   322,   -86,  -352,  -352,   320,  -352,   330,  -352,
    -352,   329,   -86,   -86,  -352,  -352,  -352
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -352,  -352,  -352,  -352,  -352,  -352,  -352,  -352,  -352,  -352,
    -352,  -352,  -312,  -352,  -352,  -305,  -352,  -352,  -236,  -351,
    -110,  -129,  -116,   -34,  -155,  -160,  -337
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short int yytable[] =
{
     209,     3,   202,   203,   226,   258,   204,   216,   262,   406,
     407,   198,   261,   199,   263,   264,   265,   205,   206,   241,
     229,   224,   225,   200,   201,   228,   411,   412,     4,   238,
       9,   284,   254,   106,   108,   109,   239,   240,   110,   111,
     193,   112,   113,   114,   115,   116,   255,   256,   257,   252,
     253,   117,   118,   119,   120,   121,   266,   122,   268,   123,
     124,   125,   126,   127,   128,   129,   259,   130,   278,   279,
     280,   281,   282,   283,   131,   195,   196,   197,   132,   133,
     134,   208,   135,   210,   211,   212,   213,   214,   215,   136,
     217,   218,   219,   220,   221,   222,   223,   137,   138,   139,
     227,   190,   465,   230,   231,   232,   233,   234,   235,   236,
     237,   140,   141,   142,   143,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   484,   144,   145,   146,   147,
     148,   149,   150,   151,   492,   493,   494,   152,   153,   154,
     498,   155,   156,   271,   272,   273,   274,   275,   276,   277,
     157,   158,   159,   160,   161,   162,   522,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   535,   179,   180,   181,   182,   183,   184,
     185,   186,   541,   187,   188,   189,   191,   192,   267,   269,
     270,   545,   546,   285,   289,   290,   371,   286,   287,   288,
     394,   291,   292,   293,   294,   295,   296,   466,   297,   298,
     299,   534,   409,   300,   301,   302,   303,   511,   304,   305,
     306,   307,   537,   308,   309,   310,   311,   312,   313,   314,
     400,   401,   402,   403,   315,   467,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   372,   373,   374,   375,   418,   331,   376,   377,   332,
     333,   378,   334,   379,   380,   381,   382,   383,   335,   336,
     384,   385,   386,   337,   387,   388,   389,   390,   391,   392,
     393,   338,   339,   395,   396,   397,   398,   399,   340,   341,
     342,   343,   344,   345,   539,   346,   347,   348,   349,   350,
     351,   352,     0,   353,   354,   468,   355,   356,   357,   358,
     359,   360,     0,   361,   362,   363,   364,   365,   404,   366,
     367,   368,   369,   370,   405,   419,   420,   421,   422,   473,
     423,   464,   413,   414,   415,   416,   417,   424,   425,   426,
     427,   428,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,     0,   441,   442,   443,   444,   445,
     446,     0,   447,   448,   449,   450,   451,   452,     0,   453,
     454,   455,   456,   457,     0,   458,   459,   460,   461,   462,
     474,   475,   477,   476,   478,   479,   480,   515,   481,     0,
     482,   485,   486,   483,   487,     0,   491,   495,   512,   496,
     497,   499,   501,   503,   507,   516,   520,   463,   519,   521,
     536,   523,   524,   538,   526,   525,   529,   527,   528,   542,
       0,   530,   531,   540,   469,   470,   471,   472,   533,   543,
     544,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   488,   489,   490,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   505,   506,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   532,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,     0,     0,
       0,   100,   101
};

static const short int yycheck[] =
{
     116,     0,   112,   113,   133,   165,    94,   123,   168,    95,
      96,    93,   167,    95,   169,   170,   171,   105,   106,   148,
     136,   131,   132,   105,   106,   135,   363,   364,    95,   145,
      98,   191,   161,    93,   100,   100,   146,   147,   100,   100,
      93,   100,   100,   100,   100,   100,   162,   163,   164,   159,
     160,   100,   100,   100,   100,   100,   172,   100,   174,   100,
     100,   100,   100,   100,   100,   100,    93,   100,   184,   185,
     186,   187,   188,   189,   100,   109,   110,   111,   100,   100,
     100,   115,   100,   117,   118,   119,   120,   121,   122,   100,
     124,   125,   126,   127,   128,   129,   130,   100,   100,   100,
     134,    99,   453,   137,   138,   139,   140,   141,   142,   143,
     144,   100,   100,   100,   100,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   476,   100,   100,   100,   100,
     100,   100,   100,   100,   485,   486,   487,   100,   100,   100,
     491,   100,   100,   177,   178,   179,   180,   181,   182,   183,
     100,   100,   100,   100,   100,   100,   507,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   524,   100,   100,   100,   100,   100,   100,
     100,   100,   533,   100,   100,   100,   100,    99,    96,    96,
      96,   542,   543,   102,    93,    93,    98,   102,   102,   102,
     316,   102,   102,    94,    94,   102,   101,   103,   102,   102,
     102,   523,    93,   102,   102,   101,   101,   104,   102,   102,
     102,   101,   527,   102,   102,   102,   102,   102,   102,   102,
     346,   347,   348,   349,   101,   103,   102,   102,   102,   102,
     102,   102,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   285,   286,   287,   288,   371,   101,   291,   292,   101,
     101,   295,   101,   297,   298,   299,   300,   301,   101,   101,
     304,   305,   306,   101,   308,   309,   310,   311,   312,   313,
     314,   101,   101,   317,   318,   319,   320,   321,   101,   101,
     101,   101,   101,   101,   530,   102,   102,   102,   102,   101,
     101,   101,    -1,   102,   101,   103,   102,   101,   101,   101,
     101,   101,    -1,   102,   102,   102,   102,   101,    96,   102,
     102,   102,   102,   102,    96,   101,   101,   101,   101,    99,
     101,   447,   366,   367,   368,   369,   370,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,    -1,   102,   101,   101,   101,   101,
     101,    -1,   102,   101,   101,   101,   101,   101,    -1,   102,
     102,   102,   102,   101,    -1,   102,   102,   102,   102,   101,
     101,   101,    95,   102,    95,    95,   101,   104,   102,    -1,
     102,    99,    99,   102,    99,    -1,   102,   101,    95,   102,
     102,   102,   102,   102,   102,    95,   101,   441,   104,   102,
     526,   102,    99,   529,    98,   101,    98,   102,   101,    99,
      -1,   102,   101,   101,   458,   459,   460,   461,   102,    99,
     101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   481,   482,   483,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   496,   497,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   521,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    -1,    -1,
      -1,    96,    97
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,   108,   109,     0,    95,   110,   111,   132,   113,    98,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      96,    97,   112,   114,   115,   116,    93,   129,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
      99,   100,    99,    93,   130,   130,   130,   130,    93,    95,
     105,   106,   127,   127,    94,   105,   106,   128,   130,   129,
     130,   130,   130,   130,   130,   130,   129,   130,   130,   130,
     130,   130,   130,   130,   127,   127,   128,   130,   127,   129,
     130,   130,   130,   130,   130,   130,   130,   130,   129,   127,
     127,   128,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   127,   127,   128,   129,   129,   129,   132,    93,
     131,   131,   132,   131,   131,   131,   129,    96,   129,    96,
      96,   130,   130,   130,   130,   130,   130,   130,   129,   129,
     129,   129,   129,   129,   132,   102,   102,   102,   102,    93,
      93,   102,   102,    94,    94,   102,   101,   102,   102,   102,
     102,   102,   101,   101,   102,   102,   102,   101,   102,   102,
     102,   102,   102,   102,   102,   101,   102,   102,   102,   102,
     102,   102,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   102,   102,   102,   102,
     101,   101,   101,   102,   101,   102,   101,   101,   101,   101,
     101,   102,   102,   102,   102,   101,   102,   102,   102,   102,
     102,    98,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   129,   130,   130,   130,   130,   130,
     129,   129,   129,   129,    96,    96,    95,    96,   126,    93,
     133,   133,   133,   130,   130,   130,   130,   130,   129,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   102,   101,   101,   101,   101,   101,   102,   101,   101,
     101,   101,   101,   102,   102,   102,   102,   101,   102,   102,
     102,   102,   101,   130,   129,   126,   103,   103,   103,   130,
     130,   130,   130,    99,   101,   101,   102,    95,    95,    95,
     101,   102,   102,   102,   126,    99,    99,    99,   130,   130,
     130,   102,   126,   126,   126,   101,   102,   102,   126,   102,
     117,   102,   120,   102,   123,   130,   130,   102,   118,   119,
     127,   104,    95,   121,   122,   104,    95,   124,   125,   104,
     101,   102,   126,   102,    99,   101,    98,   102,   101,    98,
     102,   101,   130,   102,   119,   126,   129,   122,   129,   125,
     101,   126,    99,    99,   101,   126,   126
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

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
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
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
    while (0)
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
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
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
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
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
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

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
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
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
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

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


  yyvsp[0] = yylval;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
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

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

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

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
#line 206 "qa.y"
    {
		  labels = new LabelTable;

		  // Is it the query code block?
		  if ((*asm_string_table)[(yyvsp[-3].constant)->Value()] == "$query" &&
		      (yyvsp[-1].number)->Value() == 0)
		    {
		      if (query_code_block != NULL)
			{
			  Fatal(__FUNCTION__, 
				"more than one query code block");
			}
		      query_code_block = new CodeBlock(QUERY_BLOCK,
						       (yyvsp[-3].constant)->Value(),
						       (yyvsp[-1].number)->Value());

		      code_block = query_code_block;
		    }
		  else
		    {
		      code_block = new CodeBlock(PREDICATE_BLOCK,
						 (yyvsp[-3].constant)->Value(),
						 (yyvsp[-1].number)->Value());
		    }

		  delete (yyvsp[-3].constant);
		  delete (yyvsp[-1].number);
		}
    break;

  case 7:
#line 237 "qa.y"
    {
		  if ((yyvsp[-4].constant)->Value() != code_block->Atom() ||
		      (yyvsp[-2].number)->Value() != code_block->Arity())
		    {
		      Fatal(__FUNCTION__, 
			    "atom or arity mismatch in predicate");
		    }

		  delete (yyvsp[-4].constant);
		  delete (yyvsp[-2].number);

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
#line 271 "qa.y"
    {
		  labels->Resolve(*(yyvsp[-1].label_name), *code_block);
		}
    break;

  case 13:
#line 277 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 14:
#line 284 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 15:
#line 291 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 16:
#line 298 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 17:
#line 305 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].constant)->Put(*code_block); delete (yyvsp[-3].constant);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 18:
#line 312 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].constant)->Put(*code_block); delete (yyvsp[-3].constant);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 19:
#line 318 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].double_num)->Put(*code_block); delete (yyvsp[-3].double_num);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 20:
#line 325 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 21:
#line 331 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].number)->Put(*code_block); delete (yyvsp[-3].number);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 22:
#line 338 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 23:
#line 345 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 24:
#line 352 "qa.y"
    {
		   (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		   (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		   (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		 }
    break;

  case 25:
#line 359 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 26:
#line 366 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 27:
#line 372 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 28:
#line 378 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].number)->Put(*code_block); delete (yyvsp[-3].number);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 29:
#line 385 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 30:
#line 392 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 31:
#line 399 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 32:
#line 405 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 33:
#line 412 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 34:
#line 419 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 35:
#line 426 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 36:
#line 433 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].constant)->Put(*code_block); delete (yyvsp[-3].constant);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 37:
#line 440 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].constant)->Put(*code_block); delete (yyvsp[-3].constant);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 38:
#line 447 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].double_num)->Put(*code_block); delete (yyvsp[-3].double_num);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 39:
#line 454 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 40:
#line 460 "qa.y"
    {
		  (yyvsp[-7].instruction)->Put(*code_block); delete (yyvsp[-7].instruction);
		  (yyvsp[-5].constant)->Put(*code_block); delete (yyvsp[-5].constant);
		  (yyvsp[-3].number)->Put(*code_block); delete (yyvsp[-3].number);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 41:
#line 468 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].number)->Put(*code_block); delete (yyvsp[-3].number);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 42:
#line 475 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 43:
#line 482 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 44:
#line 489 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 45:
#line 496 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 46:
#line 503 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
    break;

  case 47:
#line 509 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
    break;

  case 48:
#line 515 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
    break;

  case 49:
#line 521 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
    break;

  case 50:
#line 527 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].constant)->Put(*code_block); delete (yyvsp[-1].constant);
		}
    break;

  case 51:
#line 533 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].constant)->Put(*code_block); delete (yyvsp[-1].constant);
		}
    break;

  case 52:
#line 539 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].double_num)->Put(*code_block); delete (yyvsp[-1].double_num);
		}
    break;

  case 53:
#line 545 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
	        }
    break;

  case 54:
#line 551 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
    break;

  case 55:
#line 557 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
    break;

  case 56:
#line 563 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
    break;

  case 57:
#line 569 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
	        }
    break;

  case 58:
#line 575 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
    break;

  case 59:
#line 581 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
    break;

  case 60:
#line 587 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
    break;

  case 61:
#line 593 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
    break;

  case 62:
#line 599 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
        	}
    break;

  case 63:
#line 605 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
	        }
    break;

  case 64:
#line 611 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].constant)->Put(*code_block); delete (yyvsp[-1].constant);
		}
    break;

  case 65:
#line 617 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].constant)->Put(*code_block); delete (yyvsp[-1].constant);
		}
    break;

  case 66:
#line 623 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].double_num)->Put(*code_block); delete (yyvsp[-1].double_num);
		}
    break;

  case 67:
#line 629 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
		}
    break;

  case 68:
#line 635 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
		}
    break;

  case 69:
#line 641 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
		}
    break;

  case 70:
#line 647 "qa.y"
    {
		  (yyvsp[0].instruction)->Put(*code_block); delete (yyvsp[0].instruction);
		}
    break;

  case 71:
#line 652 "qa.y"
    {
		  (yyvsp[-7].instruction)->Put(*code_block); delete (yyvsp[-7].instruction);
		  (yyvsp[-5].constant)->Put(*code_block); delete (yyvsp[-5].constant);
		  (yyvsp[-3].number)->Put(*code_block); delete (yyvsp[-3].number);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
		}
    break;

  case 72:
#line 660 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction); 
		  (yyvsp[-3].address)->Put(*code_block); delete (yyvsp[-3].address);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
		}
    break;

  case 73:
#line 667 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].address)->Put(*code_block); delete (yyvsp[-3].address);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
		}
    break;

  case 74:
#line 674 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].constant)->Put(*code_block); delete (yyvsp[-3].constant);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
		}
    break;

  case 75:
#line 681 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].address)->Put(*code_block); delete (yyvsp[-1].address);
		}
    break;

  case 76:
#line 687 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].address)->Put(*code_block); delete (yyvsp[-1].address);
		}
    break;

  case 77:
#line 693 "qa.y"
    {
		  (yyvsp[0].instruction)->Put(*code_block); delete (yyvsp[0].instruction);
		}
    break;

  case 78:
#line 698 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].address)->Put(*code_block); delete (yyvsp[-1].address);
		}
    break;

  case 79:
#line 704 "qa.y"
    {
		  (yyvsp[0].instruction)->Put(*code_block); delete (yyvsp[0].instruction);
		}
    break;

  case 80:
#line 709 "qa.y"
    {
		  (yyvsp[0].instruction)->Put(*code_block); delete (yyvsp[0].instruction);
		}
    break;

  case 81:
#line 714 "qa.y"
    {
		  (yyvsp[0].instruction)->Put(*code_block); delete (yyvsp[0].instruction);
		}
    break;

  case 82:
#line 719 "qa.y"
    {
		  (yyvsp[0].instruction)->Put(*code_block); delete (yyvsp[0].instruction);
		}
    break;

  case 83:
#line 724 "qa.y"
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-5].instruction)->SizeOf() + (yyvsp[-3].number)->SizeOf() + Code::SIZE_OF_OFFSET;

		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].number)->Put(*code_block); delete (yyvsp[-3].number);

		  labels->AddReference(*(yyvsp[-1].label_name), *code_block, jump_offset_base);
		}
    break;

  case 84:
#line 736 "qa.y"
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-3].instruction)->SizeOf() + Code::SIZE_OF_OFFSET;

		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  labels->AddReference(*(yyvsp[-1].label_name), *code_block, jump_offset_base);
		}
    break;

  case 85:
#line 746 "qa.y"
    {
		  (yyvsp[0].instruction)->Put(*code_block); delete (yyvsp[0].instruction);
		}
    break;

  case 86:
#line 751 "qa.y"
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-5].instruction)->SizeOf() + (yyvsp[-3].number)->SizeOf() + Code::SIZE_OF_OFFSET;

		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].number)->Put(*code_block); delete (yyvsp[-3].number);

		  labels->AddReference(*(yyvsp[-1].label_name), *code_block, jump_offset_base);
		}
    break;

  case 87:
#line 763 "qa.y"
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-3].instruction)->SizeOf() + Code::SIZE_OF_OFFSET;

		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  labels->AddReference(*(yyvsp[-1].label_name), *code_block, jump_offset_base);
		}
    break;

  case 88:
#line 773 "qa.y"
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-3].instruction)->SizeOf() + Code::SIZE_OF_OFFSET;

		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  labels->AddReference(*(yyvsp[-1].label_name), *code_block, jump_offset_base);
		}
    break;

  case 89:
#line 783 "qa.y"
    {
		  (yyvsp[0].instruction)->Put(*code_block); delete (yyvsp[0].instruction);
		}
    break;

  case 90:
#line 788 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 91:
#line 794 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 92:
#line 800 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 93:
#line 812 "qa.y"
    {
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-15].instruction)->SizeOf() + (yyvsp[-13].reg)->SizeOf() + 6 * Code::SIZE_OF_OFFSET;

		  (yyvsp[-15].instruction)->Put(*code_block); delete (yyvsp[-15].instruction);
		  (yyvsp[-13].reg)->Put(*code_block); delete (yyvsp[-13].reg);

		  labels->AddReference(*(yyvsp[-11].label_name), *code_block, jump_offset_base);
		  labels->AddReference(*(yyvsp[-9].label_name), *code_block, jump_offset_base);
		  labels->AddReference(*(yyvsp[-7].label_name), *code_block, jump_offset_base);
		  labels->AddReference(*(yyvsp[-5].label_name), *code_block, jump_offset_base);
		  labels->AddReference(*(yyvsp[-3].label_name), *code_block, jump_offset_base);
		  labels->AddReference(*(yyvsp[-1].label_name), *code_block, jump_offset_base);
		}
    break;

  case 94:
#line 831 "qa.y"
    {
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-12].instruction)->SizeOf() + (yyvsp[-10].reg)->SizeOf() + (yyvsp[-8].table_size)->SizeOf();

		  (yyvsp[-12].instruction)->Put(*code_block); delete (yyvsp[-12].instruction);
		  (yyvsp[-10].reg)->Put(*code_block); delete (yyvsp[-10].reg);
		  (yyvsp[-8].table_size)->Put(*code_block); 

		  if (*(yyvsp[-5].atom_name) != "$default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_structure");
		    }

		 ConstantSwitchTable switch_table(jump_offset_base,
							  (yyvsp[-8].table_size), (yyvsp[-3].label_name), (yyvsp[-2].cl_list));

		  switch_table.Put(*code_block, *labels);

		  delete (yyvsp[-8].table_size);
		  delete (yyvsp[-3].label_name);
		  delete (yyvsp[-2].cl_list);
		}
    break;

  case 95:
#line 859 "qa.y"
    {
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-12].instruction)->SizeOf() + (yyvsp[-10].reg)->SizeOf() + (yyvsp[-8].table_size)->SizeOf();

		  (yyvsp[-12].instruction)->Put(*code_block); delete (yyvsp[-12].instruction);
		  (yyvsp[-10].reg)->Put(*code_block); delete (yyvsp[-10].reg);
		  (yyvsp[-8].table_size)->Put(*code_block);

		  if (*(yyvsp[-5].atom_name) != "$default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_structure");
		    }

		  AtomSwitchTable switch_table(jump_offset_base,
							   (yyvsp[-8].table_size), (yyvsp[-3].label_name), (yyvsp[-2].aal_list));

		  switch_table.Put(*code_block, *labels);

		  delete (yyvsp[-8].table_size);
		  delete (yyvsp[-3].label_name);
		  delete (yyvsp[-2].aal_list);
		}
    break;

  case 96:
#line 887 "qa.y"
    {
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      (yyvsp[-12].instruction)->SizeOf() + (yyvsp[-10].reg)->SizeOf() + (yyvsp[-8].table_size)->SizeOf();

		  (yyvsp[-12].instruction)->Put(*code_block); delete (yyvsp[-12].instruction);
		  (yyvsp[-10].reg)->Put(*code_block); delete (yyvsp[-10].reg);
		  (yyvsp[-8].table_size)->Put(*code_block);

		  if (*(yyvsp[-5].atom_name) != "$default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_quantifier");
		    }

		  AtomSwitchTable switch_table(jump_offset_base,
							   (yyvsp[-8].table_size), (yyvsp[-3].label_name), (yyvsp[-2].aal_list));

		  switch_table.Put(*code_block, *labels);

		  delete (yyvsp[-8].table_size);
		  delete (yyvsp[-3].label_name);
		  delete (yyvsp[-2].aal_list);
		}
    break;

  case 97:
#line 914 "qa.y"
    {
		  (yyvsp[-3].instruction)->Put(*code_block); delete (yyvsp[-3].instruction);
		  (yyvsp[-1].number)->Put(*code_block); delete (yyvsp[-1].number);
		}
    break;

  case 98:
#line 920 "qa.y"
    {
		  (yyvsp[-5].instruction)->Put(*code_block); delete (yyvsp[-5].instruction);
		  (yyvsp[-3].number)->Put(*code_block); delete (yyvsp[-3].number);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 99:
#line 927 "qa.y"
    {
		  (yyvsp[-7].instruction)->Put(*code_block); delete (yyvsp[-7].instruction);
		  (yyvsp[-5].number)->Put(*code_block); delete (yyvsp[-5].number);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 100:
#line 935 "qa.y"
    {
		  (yyvsp[-9].instruction)->Put(*code_block); delete (yyvsp[-9].instruction);
		  (yyvsp[-7].number)->Put(*code_block); delete (yyvsp[-7].number);
		  (yyvsp[-5].reg)->Put(*code_block); delete (yyvsp[-5].reg);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 101:
#line 945 "qa.y"
    {
		  (yyvsp[-11].instruction)->Put(*code_block); delete (yyvsp[-11].instruction);
		  (yyvsp[-9].number)->Put(*code_block); delete (yyvsp[-9].number);
		  (yyvsp[-7].reg)->Put(*code_block); delete (yyvsp[-7].reg);
		  (yyvsp[-5].reg)->Put(*code_block); delete (yyvsp[-5].reg);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 102:
#line 955 "qa.y"
    {
		  (yyvsp[-13].instruction)->Put(*code_block); delete (yyvsp[-13].instruction);
		  (yyvsp[-11].number)->Put(*code_block); delete (yyvsp[-11].number);
		  (yyvsp[-9].reg)->Put(*code_block); delete (yyvsp[-9].reg);
		  (yyvsp[-7].reg)->Put(*code_block); delete (yyvsp[-7].reg);
		  (yyvsp[-5].reg)->Put(*code_block); delete (yyvsp[-5].reg);
		  (yyvsp[-3].reg)->Put(*code_block); delete (yyvsp[-3].reg);
		  (yyvsp[-1].reg)->Put(*code_block); delete (yyvsp[-1].reg);
		}
    break;

  case 103:
#line 967 "qa.y"
    {
		  (yyval.cl_list) = NULL;
		}
    break;

  case 104:
#line 971 "qa.y"
    {
		  (yyval.cl_list) = (yyvsp[0].cl_list);
		}
    break;

  case 105:
#line 977 "qa.y"
    {
		  vector<ConstantLabel *> *tmp = new vector<ConstantLabel *>;

		  tmp->push_back((yyvsp[0].cl));

		  (yyval.cl_list) = tmp;
		}
    break;

  case 106:
#line 985 "qa.y"
    {
		  (yyvsp[-2].cl_list)->push_back((yyvsp[0].cl));

		  (yyval.cl_list) = (yyvsp[-2].cl_list);
		}
    break;

  case 107:
#line 993 "qa.y"
    {
		  (yyval.cl) = new ConstantLabel((yyvsp[-2].constant), (yyvsp[0].label_name));
		  
		}
    break;

  case 108:
#line 1000 "qa.y"
    {
		  (yyval.aal_list) = NULL;
		}
    break;

  case 109:
#line 1004 "qa.y"
    {
		  (yyval.aal_list) = (yyvsp[0].aal_list);
		}
    break;

  case 110:
#line 1010 "qa.y"
    {
		  vector<AtomArityLabel *> *tmp = new vector<AtomArityLabel *>;

		  tmp->push_back((yyvsp[0].aal));

		  (yyval.aal_list) = tmp;
		}
    break;

  case 111:
#line 1018 "qa.y"
    {
		  (yyvsp[-2].aal_list)->push_back((yyvsp[0].aal));
		  (yyval.aal_list) = (yyvsp[-2].aal_list);
		}
    break;

  case 112:
#line 1025 "qa.y"
    {
		  ASMStringPointer asm_atom((yyvsp[-4].atom_name));
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  ASMInt<Code::ConstantSizedType> *atom = 
		    new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);


		  (yyval.aal) = new AtomArityLabel(atom, (yyvsp[-2].number), (yyvsp[0].label_name));

		}
    break;

  case 113:
#line 1039 "qa.y"
    {
		  (yyval.aal_list) = NULL;
		}
    break;

  case 114:
#line 1043 "qa.y"
    {
		  (yyval.aal_list) = (yyvsp[0].aal_list);
		}
    break;

  case 115:
#line 1049 "qa.y"
    {
		  vector<AtomArityLabel *> *tmp = new vector<AtomArityLabel *>;

		  tmp->push_back((yyvsp[0].aal));

		  (yyval.aal_list) = tmp;
		}
    break;

  case 116:
#line 1057 "qa.y"
    {
		  (yyvsp[-2].aal_list)->push_back((yyvsp[0].aal));

		  (yyval.aal_list) = (yyvsp[-2].aal_list);
		}
    break;

  case 117:
#line 1065 "qa.y"
    {
		  ASMStringPointer asm_atom((yyvsp[-4].atom_name));
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  ASMInt<Code::ConstantSizedType> *atom = 
		    new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);

		  (yyval.aal) = new AtomArityLabel(atom, (yyvsp[-2].number), (yyvsp[0].label_name));
		}
    break;

  case 119:
#line 1078 "qa.y"
    {
		  if (*(yyvsp[0].atom_name) != "fail")
		    {
		      FatalS(__FUNCTION__, "invalid switch label ",
			     (yyvsp[0].atom_name)->c_str());
		    }
		}
    break;

  case 120:
#line 1088 "qa.y"
    {
		  ASMStringPointer asm_atom((yyvsp[0].atom_name));
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  (yyval.constant) = new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);
		}
    break;

  case 121:
#line 1095 "qa.y"
    {
		  (yyval.constant) = new ASMInt<Code::ConstantSizedType>((word32)((yyvsp[0].number_value)), ConstEntry::INTEGER_TYPE);

		}
    break;

  case 122:
#line 1100 "qa.y"
    {
		  (yyval.constant) = new ASMInt<Code::ConstantSizedType>((word32)((yyvsp[0].number_value)), ConstEntry::INTEGER_TYPE);

		}
    break;

  case 123:
#line 1105 "qa.y"
    {
		  (yyval.constant) = new ASMInt<Code::ConstantSizedType>((word32)(-(yyvsp[0].number_value)), ConstEntry::INTEGER_TYPE);

		}
    break;

  case 124:
#line 1112 "qa.y"
    {
		  (yyval.double_num) = new ASMInt<double>((double)((yyvsp[0].double_value)), ConstEntry::INTEGER_TYPE);

		}
    break;

  case 125:
#line 1117 "qa.y"
    {
		  (yyval.double_num) = new ASMInt<double>((double)((yyvsp[0].double_value)), ConstEntry::INTEGER_TYPE);

		}
    break;

  case 126:
#line 1122 "qa.y"
    {
		  (yyval.double_num) = new ASMInt<double>((double)(-(yyvsp[0].double_value)), ConstEntry::INTEGER_TYPE);

		}
    break;

  case 127:
#line 1128 "qa.y"
    {
		  (yyval.number) = new ASMInt<Code::NumberSizedType>((yyvsp[0].number_value));

		}
    break;

  case 128:
#line 1135 "qa.y"
    {
		  (yyval.reg) = new ASMInt<Code::RegisterSizedType>((yyvsp[0].number_value));
		  
		}
    break;

  case 129:
#line 1142 "qa.y"
    {
		  (yyval.address) = new ASMInt<Code::AddressSizedType>((yyvsp[0].number_value));

		}
    break;

  case 130:
#line 1149 "qa.y"
    {
		  ASMStringPointer asm_atom((yyvsp[0].atom_name));
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);
		  (yyval.constant) = new ASMInt<Code::PredSizedType>(loc);
		}
    break;

  case 131:
#line 1157 "qa.y"
    {
		  (yyval.table_size) = new ASMInt<Code::TableSizeSizedType>((yyvsp[0].number_value));

		}
    break;


    }

/* Line 1037 of yacc.c.  */
#line 2865 "qa.cc"

  yyvsp -= yylen;
  yyssp -= yylen;


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
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {

		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 yydestruct ("Error: popping",
                             yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  yydestruct ("Error: discarding", yytoken, &yylval);
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

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

yyvsp -= yylen;
  yyssp -= yylen;
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


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
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
  yydestruct ("Error: discarding lookahead",
              yytoken, &yylval);
  yychar = YYEMPTY;
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 1163 "qa.y"

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


