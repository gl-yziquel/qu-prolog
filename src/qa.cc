/* A Bison parser, made by GNU Bison 1.875c.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

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
     put_list = 264,
     put_structure = 265,
     put_x_object_variable = 266,
     put_y_object_variable = 267,
     put_x_object_value = 268,
     put_y_object_value = 269,
     put_quantifier = 270,
     check_binder = 271,
     put_substitution = 272,
     put_x_term_substitution = 273,
     put_y_term_substitution = 274,
     put_initial_empty_substitution = 275,
     get_x_variable = 276,
     get_y_variable = 277,
     get_x_value = 278,
     get_y_value = 279,
     get_constant = 280,
     get_integer = 281,
     get_list = 282,
     get_structure = 283,
     get_structure_frame = 284,
     get_x_object_variable = 285,
     get_y_object_variable = 286,
     get_x_object_value = 287,
     get_y_object_value = 288,
     unify_x_variable = 289,
     unify_y_variable = 290,
     unify_x_value = 291,
     unify_y_value = 292,
     unify_void = 293,
     unify_constant = 294,
     unify_integer = 295,
     unify_x_ref = 296,
     unify_y_ref = 297,
     set_x_variable = 298,
     set_y_variable = 299,
     set_x_value = 300,
     set_y_value = 301,
     set_x_object_variable = 302,
     set_y_object_variable = 303,
     set_x_object_value = 304,
     set_y_object_value = 305,
     set_constant = 306,
     set_integer = 307,
     set_void = 308,
     set_object_void = 309,
     wam_allocate = 310,
     wam_deallocate = 311,
     call_predicate = 312,
     call_address = 313,
     call_escape = 314,
     execute_predicate = 315,
     execute_address = 316,
     execute_escape = 317,
     noop = 318,
     jump = 319,
     proceed = 320,
     wam_fail = 321,
     halt = 322,
     wam_exit = 323,
     try_me_else = 324,
     retry_me_else = 325,
     trust_me_else_fail = 326,
     wam_try = 327,
     retry = 328,
     trust = 329,
     neck_cut = 330,
     get_x_level = 331,
     get_y_level = 332,
     cut = 333,
     switch_on_term = 334,
     switch_on_constant = 335,
     switch_on_structure = 336,
     switch_on_quantifier = 337,
     pseudo_instr0 = 338,
     pseudo_instr1 = 339,
     pseudo_instr2 = 340,
     pseudo_instr3 = 341,
     pseudo_instr4 = 342,
     pseudo_instr5 = 343,
     NUMBER_TOKEN = 344,
     ATOM_TOKEN = 345,
     LABEL_TOKEN = 346,
     END_TOKEN = 347
   };
#endif
#define put_x_variable 258
#define put_y_variable 259
#define put_x_value 260
#define put_y_value 261
#define put_constant 262
#define put_integer 263
#define put_list 264
#define put_structure 265
#define put_x_object_variable 266
#define put_y_object_variable 267
#define put_x_object_value 268
#define put_y_object_value 269
#define put_quantifier 270
#define check_binder 271
#define put_substitution 272
#define put_x_term_substitution 273
#define put_y_term_substitution 274
#define put_initial_empty_substitution 275
#define get_x_variable 276
#define get_y_variable 277
#define get_x_value 278
#define get_y_value 279
#define get_constant 280
#define get_integer 281
#define get_list 282
#define get_structure 283
#define get_structure_frame 284
#define get_x_object_variable 285
#define get_y_object_variable 286
#define get_x_object_value 287
#define get_y_object_value 288
#define unify_x_variable 289
#define unify_y_variable 290
#define unify_x_value 291
#define unify_y_value 292
#define unify_void 293
#define unify_constant 294
#define unify_integer 295
#define unify_x_ref 296
#define unify_y_ref 297
#define set_x_variable 298
#define set_y_variable 299
#define set_x_value 300
#define set_y_value 301
#define set_x_object_variable 302
#define set_y_object_variable 303
#define set_x_object_value 304
#define set_y_object_value 305
#define set_constant 306
#define set_integer 307
#define set_void 308
#define set_object_void 309
#define wam_allocate 310
#define wam_deallocate 311
#define call_predicate 312
#define call_address 313
#define call_escape 314
#define execute_predicate 315
#define execute_address 316
#define execute_escape 317
#define noop 318
#define jump 319
#define proceed 320
#define wam_fail 321
#define halt 322
#define wam_exit 323
#define try_me_else 324
#define retry_me_else 325
#define trust_me_else_fail 326
#define wam_try 327
#define retry 328
#define trust 329
#define neck_cut 330
#define get_x_level 331
#define get_y_level 332
#define cut 333
#define switch_on_term 334
#define switch_on_constant 335
#define switch_on_structure 336
#define switch_on_quantifier 337
#define pseudo_instr0 338
#define pseudo_instr1 339
#define pseudo_instr2 340
#define pseudo_instr3 341
#define pseudo_instr4 342
#define pseudo_instr5 343
#define NUMBER_TOKEN 344
#define ATOM_TOKEN 345
#define LABEL_TOKEN 346
#define END_TOKEN 347




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

  string *label_name;
  string *atom_name;

  ASMLoc loc;

  ASMInt<Code::InstructionSizedType> *instruction;
  ASMInt<Code::ConstantSizedType> *constant;
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
/* Line 191 of yacc.c.  */
#line 320 "qa.cc"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 332 "qa.cc"

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
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
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
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
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
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   556

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  102
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  26
/* YYNRULES -- Number of rules. */
#define YYNRULES  124
/* YYNRULES -- Number of states. */
#define YYNSTATES  522

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   347

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      95,    96,     2,   100,    97,   101,     2,    93,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    94,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    98,     2,    99,     2,     2,     2,     2,     2,     2,
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
      85,    86,    87,    88,    89,    90,    91,    92
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    13,    18,    26,    27,
      30,    32,    34,    37,    44,    51,    58,    65,    72,    79,
      84,    91,    98,   105,   112,   119,   124,   129,   136,   143,
     150,   155,   162,   169,   176,   183,   190,   197,   202,   211,
     218,   225,   232,   239,   246,   251,   256,   261,   266,   271,
     276,   281,   286,   291,   296,   301,   306,   311,   316,   321,
     326,   331,   336,   341,   346,   351,   356,   358,   367,   374,
     381,   388,   393,   398,   400,   405,   407,   409,   411,   413,
     420,   425,   427,   434,   439,   444,   446,   451,   456,   461,
     478,   492,   506,   520,   525,   532,   541,   552,   565,   580,
     581,   584,   586,   590,   594,   595,   598,   600,   604,   610,
     611,   614,   616,   620,   626,   628,   630,   632,   634,   637,
     640,   642,   644,   646,   648
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
     103,     0,    -1,   104,    -1,    -1,   104,   105,    -1,   106,
     108,   107,    -1,   126,    93,   123,    94,    -1,    92,    95,
     126,    93,   123,    96,    94,    -1,    -1,   108,   109,    -1,
     110,    -1,   111,    -1,    91,    94,    -1,     3,    95,   124,
      97,   124,    96,    -1,     4,    95,   124,    97,   124,    96,
      -1,     5,    95,   124,    97,   124,    96,    -1,     6,    95,
     124,    97,   124,    96,    -1,     7,    95,   122,    97,   124,
      96,    -1,     8,    95,   122,    97,   124,    96,    -1,     9,
      95,   124,    96,    -1,    10,    95,   123,    97,   124,    96,
      -1,    11,    95,   124,    97,   124,    96,    -1,    12,    95,
     124,    97,   124,    96,    -1,    13,    95,   124,    97,   124,
      96,    -1,    14,    95,   124,    97,   124,    96,    -1,    15,
      95,   124,    96,    -1,    16,    95,   124,    96,    -1,    17,
      95,   123,    97,   124,    96,    -1,    18,    95,   124,    97,
     124,    96,    -1,    19,    95,   124,    97,   124,    96,    -1,
      20,    95,   124,    96,    -1,    21,    95,   124,    97,   124,
      96,    -1,    22,    95,   124,    97,   124,    96,    -1,    23,
      95,   124,    97,   124,    96,    -1,    24,    95,   124,    97,
     124,    96,    -1,    25,    95,   122,    97,   124,    96,    -1,
      26,    95,   122,    97,   124,    96,    -1,    27,    95,   124,
      96,    -1,    28,    95,   122,    97,   123,    97,   124,    96,
      -1,    29,    95,   123,    97,   124,    96,    -1,    30,    95,
     124,    97,   124,    96,    -1,    31,    95,   124,    97,   124,
      96,    -1,    32,    95,   124,    97,   124,    96,    -1,    33,
      95,   124,    97,   124,    96,    -1,    34,    95,   124,    96,
      -1,    35,    95,   124,    96,    -1,    36,    95,   124,    96,
      -1,    37,    95,   124,    96,    -1,    39,    95,   122,    96,
      -1,    40,    95,   122,    96,    -1,    38,    95,   123,    96,
      -1,    41,    95,   124,    96,    -1,    42,    95,   124,    96,
      -1,    43,    95,   124,    96,    -1,    44,    95,   124,    96,
      -1,    45,    95,   124,    96,    -1,    46,    95,   124,    96,
      -1,    47,    95,   124,    96,    -1,    48,    95,   124,    96,
      -1,    49,    95,   124,    96,    -1,    50,    95,   124,    96,
      -1,    51,    95,   122,    96,    -1,    52,    95,   122,    96,
      -1,    53,    95,   123,    96,    -1,    54,    95,   123,    96,
      -1,    55,    95,   123,    96,    -1,    56,    -1,    57,    95,
     126,    97,   123,    97,   123,    96,    -1,    58,    95,   125,
      97,   123,    96,    -1,    59,    95,   125,    97,   123,    96,
      -1,    60,    95,   126,    97,   123,    96,    -1,    61,    95,
     125,    96,    -1,    62,    95,   125,    96,    -1,    63,    -1,
      64,    95,   125,    96,    -1,    65,    -1,    66,    -1,    67,
      -1,    68,    -1,    69,    95,   123,    97,    91,    96,    -1,
      70,    95,    91,    96,    -1,    71,    -1,    72,    95,   123,
      97,    91,    96,    -1,    73,    95,    91,    96,    -1,    74,
      95,    91,    96,    -1,    75,    -1,    76,    95,   124,    96,
      -1,    77,    95,   124,    96,    -1,    78,    95,   124,    96,
      -1,    79,    95,   124,    97,   121,    97,   121,    97,   121,
      97,   121,    97,   121,    97,   121,    96,    -1,    80,    95,
     124,    97,   127,    97,    98,    90,    94,   121,   112,    99,
      96,    -1,    81,    95,   124,    97,   127,    97,    98,    90,
      94,   121,   115,    99,    96,    -1,    82,    95,   124,    97,
     127,    97,    98,    90,    94,   121,   118,    99,    96,    -1,
      83,    95,   123,    96,    -1,    84,    95,   123,    97,   124,
      96,    -1,    85,    95,   123,    97,   124,    97,   124,    96,
      -1,    86,    95,   123,    97,   124,    97,   124,    97,   124,
      96,    -1,    87,    95,   123,    97,   124,    97,   124,    97,
     124,    97,   124,    96,    -1,    88,    95,   123,    97,   124,
      97,   124,    97,   124,    97,   124,    97,   124,    96,    -1,
      -1,    97,   113,    -1,   114,    -1,   113,    97,   114,    -1,
     122,    94,   121,    -1,    -1,    97,   116,    -1,   117,    -1,
     116,    97,   117,    -1,    90,    93,   123,    94,   121,    -1,
      -1,    97,   119,    -1,   120,    -1,   119,    97,   120,    -1,
      90,    93,   123,    94,   121,    -1,    91,    -1,    90,    -1,
      90,    -1,    89,    -1,   100,    89,    -1,   101,    89,    -1,
      89,    -1,    89,    -1,    89,    -1,    90,    -1,    89,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   187,   187,   190,   191,   194,   197,   228,   254,   255,
     258,   259,   262,   268,   275,   282,   289,   296,   303,   310,
     316,   323,   330,   337,   344,   351,   357,   363,   370,   377,
     384,   390,   397,   404,   411,   418,   425,   432,   438,   446,
     453,   460,   467,   474,   481,   487,   493,   499,   505,   511,
     517,   523,   529,   535,   541,   547,   553,   559,   565,   571,
     577,   583,   589,   595,   601,   607,   613,   618,   626,   633,
     640,   647,   653,   659,   664,   670,   675,   680,   685,   690,
     702,   712,   717,   729,   739,   749,   754,   760,   766,   772,
     796,   824,   852,   880,   886,   893,   901,   910,   920,   934,
     937,   943,   951,   959,   967,   970,   976,   984,   991,  1006,
    1009,  1015,  1023,  1031,  1043,  1044,  1054,  1061,  1066,  1071,
    1078,  1085,  1092,  1099,  1107
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "put_x_variable", "put_y_variable",
  "put_x_value", "put_y_value", "put_constant", "put_integer", "put_list",
  "put_structure", "put_x_object_variable", "put_y_object_variable",
  "put_x_object_value", "put_y_object_value", "put_quantifier",
  "check_binder", "put_substitution", "put_x_term_substitution",
  "put_y_term_substitution", "put_initial_empty_substitution",
  "get_x_variable", "get_y_variable", "get_x_value", "get_y_value",
  "get_constant", "get_integer", "get_list", "get_structure",
  "get_structure_frame", "get_x_object_variable", "get_y_object_variable",
  "get_x_object_value", "get_y_object_value", "unify_x_variable",
  "unify_y_variable", "unify_x_value", "unify_y_value", "unify_void",
  "unify_constant", "unify_integer", "unify_x_ref", "unify_y_ref",
  "set_x_variable", "set_y_variable", "set_x_value", "set_y_value",
  "set_x_object_variable", "set_y_object_variable", "set_x_object_value",
  "set_y_object_value", "set_constant", "set_integer", "set_void",
  "set_object_void", "wam_allocate", "wam_deallocate", "call_predicate",
  "call_address", "call_escape", "execute_predicate", "execute_address",
  "execute_escape", "noop", "jump", "proceed", "wam_fail", "halt",
  "wam_exit", "try_me_else", "retry_me_else", "trust_me_else_fail",
  "wam_try", "retry", "trust", "neck_cut", "get_x_level", "get_y_level",
  "cut", "switch_on_term", "switch_on_constant", "switch_on_structure",
  "switch_on_quantifier", "pseudo_instr0", "pseudo_instr1",
  "pseudo_instr2", "pseudo_instr3", "pseudo_instr4", "pseudo_instr5",
  "NUMBER_TOKEN", "ATOM_TOKEN", "LABEL_TOKEN", "END_TOKEN", "'/'", "':'",
  "'('", "')'", "','", "'['", "']'", "'+'", "'-'", "$accept",
  "assembler_file", "predicate_list", "predicate", "predicate_start",
  "predicate_end", "source_line_list", "source_line", "label_instance",
  "instr", "constant_labels", "constant_label_list", "constant_label",
  "atom_arity_labels", "atom_arity_label_list", "atom_arity_label",
  "quantifier_labels", "quantifier_label_list", "quantifier_label",
  "switch_label", "constant", "number", "reg", "address", "atom",
  "table_size", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
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
     345,   346,   347,    47,    58,    40,    41,    44,    91,    93,
      43,    45
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   102,   103,   104,   104,   105,   106,   107,   108,   108,
     109,   109,   110,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   112,
     112,   113,   113,   114,   115,   115,   116,   116,   117,   118,
     118,   119,   119,   120,   121,   121,   122,   122,   122,   122,
     123,   124,   125,   126,   127
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     0,     2,     3,     4,     7,     0,     2,
       1,     1,     2,     6,     6,     6,     6,     6,     6,     4,
       6,     6,     6,     6,     6,     4,     4,     6,     6,     6,
       4,     6,     6,     6,     6,     6,     6,     4,     8,     6,
       6,     6,     6,     6,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     1,     8,     6,     6,
       6,     4,     4,     1,     4,     1,     1,     1,     1,     6,
       4,     1,     6,     4,     4,     1,     4,     4,     4,    16,
      13,    13,    13,     4,     6,     8,    10,    12,    14,     0,
       2,     1,     3,     3,     0,     2,     1,     3,     5,     0,
       2,     1,     3,     5,     1,     1,     1,     1,     2,     2,
       1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       3,     0,     2,     1,   123,     4,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    66,     0,     0,     0,     0,     0,     0,
      73,     0,    75,    76,    77,    78,     0,     0,    81,     0,
       0,     0,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     9,
      10,    11,   120,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    12,     0,     6,   121,     0,     0,     0,     0,
     117,   116,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   122,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   118,   119,     0,     0,    19,     0,
       0,     0,     0,     0,    25,    26,     0,     0,     0,    30,
       0,     0,     0,     0,     0,     0,    37,     0,     0,     0,
       0,     0,     0,    44,    45,    46,    47,    50,    48,    49,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,     0,     0,     0,     0,    71,
      72,    74,     0,    80,     0,    83,    84,    86,    87,    88,
       0,     0,     0,     0,    93,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,   114,     0,   124,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    13,    14,    15,    16,
      17,    18,    20,    21,    22,    23,    24,    27,    28,    29,
      31,    32,    33,    34,    35,    36,     0,    39,    40,    41,
      42,    43,     0,    68,    69,    70,    79,    82,     0,     0,
       0,     0,    94,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     7,    38,
      67,     0,     0,     0,     0,    95,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    99,   104,   109,
      96,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   100,   101,     0,     0,     0,   105,   106,
       0,     0,   110,   111,     0,    97,     0,     0,     0,     0,
      90,     0,     0,    91,     0,     0,    92,     0,     0,   102,
     103,     0,   107,     0,   112,    98,     0,     0,     0,    89,
     108,   113
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     1,     2,     5,     6,    98,     8,    99,   100,   101,
     475,   483,   484,   477,   488,   489,   479,   492,   493,   385,
     485,   103,   186,   245,     7,   387
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -330
static const short yypact[] =
{
    -330,     9,   -75,  -330,  -330,  -330,  -330,   -71,   464,   -63,
     -66,   -65,   -64,   -62,   -59,   -58,   -57,   -56,   -55,   -54,
     -53,   -47,   -46,   -45,   -44,   -43,   -41,   -39,   -38,   -37,
     -36,   -35,   -34,   -33,   -32,   -31,   -24,   -23,   -22,   -21,
     -17,   -16,   -14,    -7,     1,     2,     5,    14,    15,    16,
      28,    29,    30,    31,    32,    33,    34,    35,    39,    40,
      41,    43,    51,  -330,    52,    53,    54,    55,    56,    57,
    -330,    59,  -330,  -330,  -330,  -330,    60,    61,  -330,    62,
      63,    64,  -330,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    76,    77,    78,   -76,    79,  -330,  -330,
    -330,  -330,  -330,    81,    87,    87,    87,    87,   -84,   -84,
      87,   -63,    87,    87,    87,    87,    87,    87,   -63,    87,
      87,    87,    87,    87,    87,    87,   -84,   -84,    87,   -84,
     -63,    87,    87,    87,    87,    87,    87,    87,    87,   -63,
     -84,   -84,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,   -84,   -84,   -63,   -63,   -63,   -75,    88,    88,
     -75,    88,    88,    88,   -63,    89,   -63,    90,    91,    87,
      87,    87,    87,    87,    87,    87,   -63,   -63,   -63,   -63,
     -63,   -63,  -330,   -75,  -330,  -330,    86,    93,    94,    95,
    -330,  -330,    96,    98,    97,    99,    82,   100,   101,   102,
     103,   104,   106,   107,   108,   109,   110,   112,   113,   114,
     115,   116,   121,   122,   124,   125,   126,   127,   128,   129,
     130,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   148,   149,   152,   158,   159,   163,   170,   171,
     177,   178,   179,   180,  -330,   181,   182,   183,   185,   186,
     187,   188,   190,   191,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   203,   204,   205,   206,   207,   208,   -61,
      87,    87,    87,    87,  -330,  -330,    87,    87,  -330,    87,
      87,    87,    87,    87,  -330,  -330,    87,    87,    87,  -330,
      87,    87,    87,    87,    87,    87,  -330,   -63,    87,    87,
      87,    87,    87,  -330,  -330,  -330,  -330,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,   -63,   -63,   -63,   -63,  -330,
    -330,  -330,   118,  -330,   209,  -330,  -330,  -330,  -330,  -330,
     -77,   217,   217,   217,  -330,    87,    87,    87,    87,    87,
     -63,   211,   212,   213,   214,   216,   218,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   240,   241,   242,   243,   244,   245,   247,   248,
     249,   250,   251,  -330,  -330,   252,  -330,   253,   254,   255,
     257,   258,   259,   260,   261,   263,  -330,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,  -330,    87,  -330,  -330,  -330,
    -330,  -330,   -63,  -330,  -330,  -330,  -330,  -330,   -77,   123,
     189,   215,  -330,    87,    87,    87,    87,   266,   265,   267,
     268,   105,   264,   272,   270,   271,   273,   274,  -330,  -330,
    -330,   -77,   275,   278,   279,  -330,    87,    87,    87,   277,
     -77,   -77,   -77,   280,   281,   282,   -77,   283,   284,   285,
    -330,    87,    87,   286,   -84,    85,   287,   276,   294,   288,
     289,   291,   -77,   292,  -330,   297,   296,   111,   298,  -330,
     300,   301,   302,  -330,   304,  -330,    87,   305,   -84,   -77,
    -330,   -63,   287,  -330,   -63,   294,  -330,   311,   -77,  -330,
    -330,   303,  -330,   307,  -330,  -330,   312,   -77,   -77,  -330,
    -330,  -330
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,  -330,
    -330,  -330,  -305,  -330,  -330,  -226,  -330,  -330,  -221,  -329,
    -106,  -111,   -30,  -151,  -156,  -318
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned short yytable[] =
{
     197,   243,   194,   195,   247,   190,   191,   204,   246,     3,
     248,   249,   250,   383,   384,     4,   192,   193,   182,   216,
     212,   213,     9,   215,   388,   389,   102,   269,   225,   104,
     105,   106,   350,   107,   226,   227,   108,   109,   110,   111,
     112,   113,   114,   240,   241,   242,   238,   239,   115,   116,
     117,   118,   119,   251,   120,   253,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   263,   264,   265,   266,   267,
     268,   130,   131,   132,   133,   187,   188,   189,   134,   135,
     196,   136,   198,   199,   200,   201,   202,   203,   137,   205,
     206,   207,   208,   209,   210,   211,   138,   139,   214,   440,
     140,   217,   218,   219,   220,   221,   222,   223,   224,   141,
     142,   143,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   459,   144,   145,   146,   147,   148,   149,   150,
     151,   467,   468,   469,   152,   153,   154,   473,   155,   256,
     257,   258,   259,   260,   261,   262,   156,   157,   158,   159,
     160,   161,   162,   497,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     510,   179,   180,   181,   183,   184,   185,   244,   278,   516,
     252,   254,   255,   270,   486,   274,   371,   275,   520,   521,
     271,   272,   273,   509,   276,   452,   277,   279,   280,   281,
     282,   283,   284,   285,   501,   286,   287,   288,   289,   381,
     290,   291,   292,   293,   377,   378,   379,   380,   294,   295,
     296,   441,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   395,
     351,   352,   353,   354,   314,   315,   355,   356,   316,   357,
     358,   359,   360,   361,   317,   318,   362,   363,   364,   319,
     365,   366,   367,   368,   369,   370,   320,   321,   372,   373,
     374,   375,   376,   322,   323,   324,   512,   325,   326,   327,
     328,   329,   330,   331,   514,   332,   333,   442,   334,   335,
     336,   337,   338,   339,     0,   340,   341,   342,   343,   344,
     382,   345,   346,   347,   348,   349,   386,   396,   397,   398,
     399,   439,   400,   443,   401,   390,   391,   392,   393,   394,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   411,
     412,   413,   414,   415,     0,   416,   417,   418,   419,   420,
     421,     0,   422,   423,   424,   425,   426,   427,     0,   428,
     429,   430,   431,   432,   453,   433,   434,   435,   436,   437,
     448,   449,   454,   450,     0,   451,   455,     0,   456,   460,
     457,   458,   461,   462,   466,   490,   470,   487,   471,   472,
     474,   476,   478,   482,   491,   495,   438,   494,   496,   498,
     511,   499,   500,   513,   504,   502,   503,   517,     0,   505,
     506,   518,   508,   444,   445,   446,   447,   515,   519,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   463,   464,   465,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   480,   481,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   507,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,     0,     0,    96,    97
};

static const short yycheck[] =
{
     111,   157,   108,   109,   160,    89,    90,   118,   159,     0,
     161,   162,   163,    90,    91,    90,   100,   101,    94,   130,
     126,   127,    93,   129,   342,   343,    89,   183,   139,    95,
      95,    95,    93,    95,   140,   141,    95,    95,    95,    95,
      95,    95,    95,   154,   155,   156,   152,   153,    95,    95,
      95,    95,    95,   164,    95,   166,    95,    95,    95,    95,
      95,    95,    95,    95,    95,   176,   177,   178,   179,   180,
     181,    95,    95,    95,    95,   105,   106,   107,    95,    95,
     110,    95,   112,   113,   114,   115,   116,   117,    95,   119,
     120,   121,   122,   123,   124,   125,    95,    95,   128,   428,
      95,   131,   132,   133,   134,   135,   136,   137,   138,    95,
      95,    95,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   451,    95,    95,    95,    95,    95,    95,    95,
      95,   460,   461,   462,    95,    95,    95,   466,    95,   169,
     170,   171,   172,   173,   174,   175,    95,    95,    95,    95,
      95,    95,    95,   482,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
     499,    95,    95,    95,    95,    94,    89,    89,    96,   508,
      91,    91,    91,    97,    99,    89,   297,    89,   517,   518,
      97,    97,    97,   498,    97,    90,    97,    97,    97,    97,
      97,    97,    96,    96,    93,    97,    97,    97,    96,    91,
      97,    97,    97,    97,   325,   326,   327,   328,    97,    97,
      96,    98,    97,    97,    97,    97,    97,    97,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,   350,
     270,   271,   272,   273,    96,    96,   276,   277,    96,   279,
     280,   281,   282,   283,    96,    96,   286,   287,   288,    96,
     290,   291,   292,   293,   294,   295,    96,    96,   298,   299,
     300,   301,   302,    96,    96,    96,   502,    97,    97,    97,
      97,    96,    96,    96,   505,    97,    96,    98,    97,    96,
      96,    96,    96,    96,    -1,    97,    97,    97,    97,    96,
      91,    97,    97,    97,    97,    97,    89,    96,    96,    96,
      96,   422,    96,    98,    96,   345,   346,   347,   348,   349,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    -1,    97,    96,    96,    96,    96,
      96,    -1,    97,    96,    96,    96,    96,    96,    -1,    97,
      97,    97,    97,    96,    90,    97,    97,    97,    97,    96,
      94,    96,    90,    96,    -1,    97,    96,    -1,    97,    94,
      97,    97,    94,    94,    97,    99,    96,    90,    97,    97,
      97,    97,    97,    97,    90,    96,   416,    99,    97,    97,
     501,    94,    96,   504,    93,    97,    96,    94,    -1,    97,
      96,    94,    97,   433,   434,   435,   436,    96,    96,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   456,   457,   458,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   471,   472,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   496,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    -1,    -1,    91,    92
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,   103,   104,     0,    90,   105,   106,   126,   108,    93,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    91,    92,   107,   109,
     110,   111,    89,   123,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    94,    95,    94,    89,   124,   124,   124,   124,
      89,    90,   100,   101,   122,   122,   124,   123,   124,   124,
     124,   124,   124,   124,   123,   124,   124,   124,   124,   124,
     124,   124,   122,   122,   124,   122,   123,   124,   124,   124,
     124,   124,   124,   124,   124,   123,   122,   122,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   122,   122,
     123,   123,   123,   126,    89,   125,   125,   126,   125,   125,
     125,   123,    91,   123,    91,    91,   124,   124,   124,   124,
     124,   124,   124,   123,   123,   123,   123,   123,   123,   126,
      97,    97,    97,    97,    89,    89,    97,    97,    96,    97,
      97,    97,    97,    97,    96,    96,    97,    97,    97,    96,
      97,    97,    97,    97,    97,    97,    96,    97,    97,    97,
      97,    97,    97,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    97,    97,    97,    97,    96,
      96,    96,    97,    96,    97,    96,    96,    96,    96,    96,
      97,    97,    97,    97,    96,    97,    97,    97,    97,    97,
      93,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   123,   124,   124,   124,   124,   124,   123,   123,   123,
     123,    91,    91,    90,    91,   121,    89,   127,   127,   127,
     124,   124,   124,   124,   124,   123,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    97,    96,    96,    96,
      96,    96,    97,    96,    96,    96,    96,    96,    97,    97,
      97,    97,    96,    97,    97,    97,    97,    96,   124,   123,
     121,    98,    98,    98,   124,   124,   124,   124,    94,    96,
      96,    97,    90,    90,    90,    96,    97,    97,    97,   121,
      94,    94,    94,   124,   124,   124,    97,   121,   121,   121,
      96,    97,    97,   121,    97,   112,    97,   115,    97,   118,
     124,   124,    97,   113,   114,   122,    99,    90,   116,   117,
      99,    90,   119,   120,    99,    96,    97,   121,    97,    94,
      96,    93,    97,    96,    93,    97,    96,   124,    97,   114,
     121,   123,   117,   123,   120,    96,   121,    94,    94,    96,
     121,   121
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

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
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

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
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
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

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
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

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
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

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



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
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
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

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
	short *yyss1 = yyss;


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
	short *yyss1 = yyss;
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
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

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
#line 198 "qa.y"
    {
		  labels = new LabelTable;

		  // Is it the query code block?
		  if ((*asm_string_table)[yyvsp[-3].constant->Value()] == "$query" &&
		      yyvsp[-1].number->Value() == 0)
		    {
		      if (query_code_block != NULL)
			{
			  Fatal(__FUNCTION__, 
				"more than one query code block");
			}
		      query_code_block = new CodeBlock(QUERY_BLOCK,
						       yyvsp[-3].constant->Value(),
						       yyvsp[-1].number->Value());

		      code_block = query_code_block;
		    }
		  else
		    {
		      code_block = new CodeBlock(PREDICATE_BLOCK,
						 yyvsp[-3].constant->Value(),
						 yyvsp[-1].number->Value());
		    }

		  delete yyvsp[-3].constant;
		  delete yyvsp[-1].number;
		}
    break;

  case 7:
#line 229 "qa.y"
    {
		  if (yyvsp[-4].constant->Value() != code_block->Atom() ||
		      yyvsp[-2].number->Value() != code_block->Arity())
		    {
		      Fatal(__FUNCTION__, 
			    "atom or arity mismatch in predicate");
		    }

		  delete yyvsp[-4].constant;
		  delete yyvsp[-2].number;

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
#line 263 "qa.y"
    {
		  labels->Resolve(*yyvsp[-1].label_name, *code_block);
		}
    break;

  case 13:
#line 269 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 14:
#line 276 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 15:
#line 283 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 16:
#line 290 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 17:
#line 297 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].constant->Put(*code_block); delete yyvsp[-3].constant;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 18:
#line 304 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].constant->Put(*code_block); delete yyvsp[-3].constant;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 19:
#line 311 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 20:
#line 317 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].number->Put(*code_block); delete yyvsp[-3].number;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 21:
#line 324 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 22:
#line 331 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 23:
#line 338 "qa.y"
    {
		   yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		   yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		   yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		 }
    break;

  case 24:
#line 345 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 25:
#line 352 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 26:
#line 358 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 27:
#line 364 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].number->Put(*code_block); delete yyvsp[-3].number;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 28:
#line 371 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 29:
#line 378 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 30:
#line 385 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 31:
#line 391 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 32:
#line 398 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 33:
#line 405 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 34:
#line 412 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 35:
#line 419 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].constant->Put(*code_block); delete yyvsp[-3].constant;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 36:
#line 426 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].constant->Put(*code_block); delete yyvsp[-3].constant;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 37:
#line 433 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 38:
#line 439 "qa.y"
    {
		  yyvsp[-7].instruction->Put(*code_block); delete yyvsp[-7].instruction;
		  yyvsp[-5].constant->Put(*code_block); delete yyvsp[-5].constant;
		  yyvsp[-3].number->Put(*code_block); delete yyvsp[-3].number;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 39:
#line 447 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].number->Put(*code_block); delete yyvsp[-3].number;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 40:
#line 454 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 41:
#line 461 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 42:
#line 468 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 43:
#line 475 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 44:
#line 482 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;

  case 45:
#line 488 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;

  case 46:
#line 494 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;

  case 47:
#line 500 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;

  case 48:
#line 506 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].constant->Put(*code_block); delete yyvsp[-1].constant;
		}
    break;

  case 49:
#line 512 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].constant->Put(*code_block); delete yyvsp[-1].constant;
		}
    break;

  case 50:
#line 518 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
	        }
    break;

  case 51:
#line 524 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;

  case 52:
#line 530 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;

  case 53:
#line 536 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;

  case 54:
#line 542 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
	        }
    break;

  case 55:
#line 548 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;

  case 56:
#line 554 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;

  case 57:
#line 560 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;

  case 58:
#line 566 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;

  case 59:
#line 572 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;

  case 60:
#line 578 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
	        }
    break;

  case 61:
#line 584 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].constant->Put(*code_block); delete yyvsp[-1].constant;
		}
    break;

  case 62:
#line 590 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].constant->Put(*code_block); delete yyvsp[-1].constant;
		}
    break;

  case 63:
#line 596 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
		}
    break;

  case 64:
#line 602 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
		}
    break;

  case 65:
#line 608 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
		}
    break;

  case 66:
#line 614 "qa.y"
    {
		  yyvsp[0].instruction->Put(*code_block); delete yyvsp[0].instruction;
		}
    break;

  case 67:
#line 619 "qa.y"
    {
		  yyvsp[-7].instruction->Put(*code_block); delete yyvsp[-7].instruction;
		  yyvsp[-5].constant->Put(*code_block); delete yyvsp[-5].constant;
		  yyvsp[-3].number->Put(*code_block); delete yyvsp[-3].number;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
		}
    break;

  case 68:
#line 627 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction; 
		  yyvsp[-3].address->Put(*code_block); delete yyvsp[-3].address;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
		}
    break;

  case 69:
#line 634 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].address->Put(*code_block); delete yyvsp[-3].address;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
		}
    break;

  case 70:
#line 641 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].constant->Put(*code_block); delete yyvsp[-3].constant;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
		}
    break;

  case 71:
#line 648 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].address->Put(*code_block); delete yyvsp[-1].address;
		}
    break;

  case 72:
#line 654 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].address->Put(*code_block); delete yyvsp[-1].address;
		}
    break;

  case 73:
#line 660 "qa.y"
    {
		  yyvsp[0].instruction->Put(*code_block); delete yyvsp[0].instruction;
		}
    break;

  case 74:
#line 665 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].address->Put(*code_block); delete yyvsp[-1].address;
		}
    break;

  case 75:
#line 671 "qa.y"
    {
		  yyvsp[0].instruction->Put(*code_block); delete yyvsp[0].instruction;
		}
    break;

  case 76:
#line 676 "qa.y"
    {
		  yyvsp[0].instruction->Put(*code_block); delete yyvsp[0].instruction;
		}
    break;

  case 77:
#line 681 "qa.y"
    {
		  yyvsp[0].instruction->Put(*code_block); delete yyvsp[0].instruction;
		}
    break;

  case 78:
#line 686 "qa.y"
    {
		  yyvsp[0].instruction->Put(*code_block); delete yyvsp[0].instruction;
		}
    break;

  case 79:
#line 691 "qa.y"
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      yyvsp[-5].instruction->SizeOf() + yyvsp[-3].number->SizeOf() + Code::SIZE_OF_OFFSET;

		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].number->Put(*code_block); delete yyvsp[-3].number;

		  labels->AddReference(*yyvsp[-1].label_name, *code_block, jump_offset_base);
		}
    break;

  case 80:
#line 703 "qa.y"
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      yyvsp[-3].instruction->SizeOf() + Code::SIZE_OF_OFFSET;

		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  labels->AddReference(*yyvsp[-1].label_name, *code_block, jump_offset_base);
		}
    break;

  case 81:
#line 713 "qa.y"
    {
		  yyvsp[0].instruction->Put(*code_block); delete yyvsp[0].instruction;
		}
    break;

  case 82:
#line 718 "qa.y"
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      yyvsp[-5].instruction->SizeOf() + yyvsp[-3].number->SizeOf() + Code::SIZE_OF_OFFSET;

		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].number->Put(*code_block); delete yyvsp[-3].number;

		  labels->AddReference(*yyvsp[-1].label_name, *code_block, jump_offset_base);
		}
    break;

  case 83:
#line 730 "qa.y"
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      yyvsp[-3].instruction->SizeOf() + Code::SIZE_OF_OFFSET;

		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  labels->AddReference(*yyvsp[-1].label_name, *code_block, jump_offset_base);
		}
    break;

  case 84:
#line 740 "qa.y"
    {
		  unsigned jump_offset_base =
		    code_block->Current() +
		      yyvsp[-3].instruction->SizeOf() + Code::SIZE_OF_OFFSET;

		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  labels->AddReference(*yyvsp[-1].label_name, *code_block, jump_offset_base);
		}
    break;

  case 85:
#line 750 "qa.y"
    {
		  yyvsp[0].instruction->Put(*code_block); delete yyvsp[0].instruction;
		}
    break;

  case 86:
#line 755 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 87:
#line 761 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 88:
#line 767 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 89:
#line 779 "qa.y"
    {
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      yyvsp[-15].instruction->SizeOf() + yyvsp[-13].reg->SizeOf() + 6 * Code::SIZE_OF_OFFSET;

		  yyvsp[-15].instruction->Put(*code_block); delete yyvsp[-15].instruction;
		  yyvsp[-13].reg->Put(*code_block); delete yyvsp[-13].reg;

		  labels->AddReference(*yyvsp[-11].label_name, *code_block, jump_offset_base);
		  labels->AddReference(*yyvsp[-9].label_name, *code_block, jump_offset_base);
		  labels->AddReference(*yyvsp[-7].label_name, *code_block, jump_offset_base);
		  labels->AddReference(*yyvsp[-5].label_name, *code_block, jump_offset_base);
		  labels->AddReference(*yyvsp[-3].label_name, *code_block, jump_offset_base);
		  labels->AddReference(*yyvsp[-1].label_name, *code_block, jump_offset_base);
		}
    break;

  case 90:
#line 798 "qa.y"
    {
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      yyvsp[-12].instruction->SizeOf() + yyvsp[-10].reg->SizeOf() + yyvsp[-8].table_size->SizeOf();

		  yyvsp[-12].instruction->Put(*code_block); delete yyvsp[-12].instruction;
		  yyvsp[-10].reg->Put(*code_block); delete yyvsp[-10].reg;
		  yyvsp[-8].table_size->Put(*code_block); 

		  if (*yyvsp[-5].atom_name != "$default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_structure");
		    }

		 ConstantSwitchTable switch_table(jump_offset_base,
							  yyvsp[-8].table_size, yyvsp[-3].label_name, yyvsp[-2].cl_list);

		  switch_table.Put(*code_block, *labels);

		  delete yyvsp[-8].table_size;
		  delete yyvsp[-3].label_name;
		  delete yyvsp[-2].cl_list;
		}
    break;

  case 91:
#line 826 "qa.y"
    {
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      yyvsp[-12].instruction->SizeOf() + yyvsp[-10].reg->SizeOf() + yyvsp[-8].table_size->SizeOf();

		  yyvsp[-12].instruction->Put(*code_block); delete yyvsp[-12].instruction;
		  yyvsp[-10].reg->Put(*code_block); delete yyvsp[-10].reg;
		  yyvsp[-8].table_size->Put(*code_block);

		  if (*yyvsp[-5].atom_name != "$default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_structure");
		    }

		  AtomSwitchTable switch_table(jump_offset_base,
							   yyvsp[-8].table_size, yyvsp[-3].label_name, yyvsp[-2].aal_list);

		  switch_table.Put(*code_block, *labels);

		  delete yyvsp[-8].table_size;
		  delete yyvsp[-3].label_name;
		  delete yyvsp[-2].aal_list;
		}
    break;

  case 92:
#line 854 "qa.y"
    {
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      yyvsp[-12].instruction->SizeOf() + yyvsp[-10].reg->SizeOf() + yyvsp[-8].table_size->SizeOf();

		  yyvsp[-12].instruction->Put(*code_block); delete yyvsp[-12].instruction;
		  yyvsp[-10].reg->Put(*code_block); delete yyvsp[-10].reg;
		  yyvsp[-8].table_size->Put(*code_block);

		  if (*yyvsp[-5].atom_name != "$default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_quantifier");
		    }

		  AtomSwitchTable switch_table(jump_offset_base,
							   yyvsp[-8].table_size, yyvsp[-3].label_name, yyvsp[-2].aal_list);

		  switch_table.Put(*code_block, *labels);

		  delete yyvsp[-8].table_size;
		  delete yyvsp[-3].label_name;
		  delete yyvsp[-2].aal_list;
		}
    break;

  case 93:
#line 881 "qa.y"
    {
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
		}
    break;

  case 94:
#line 887 "qa.y"
    {
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].number->Put(*code_block); delete yyvsp[-3].number;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 95:
#line 894 "qa.y"
    {
		  yyvsp[-7].instruction->Put(*code_block); delete yyvsp[-7].instruction;
		  yyvsp[-5].number->Put(*code_block); delete yyvsp[-5].number;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 96:
#line 902 "qa.y"
    {
		  yyvsp[-9].instruction->Put(*code_block); delete yyvsp[-9].instruction;
		  yyvsp[-7].number->Put(*code_block); delete yyvsp[-7].number;
		  yyvsp[-5].reg->Put(*code_block); delete yyvsp[-5].reg;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 97:
#line 912 "qa.y"
    {
		  yyvsp[-11].instruction->Put(*code_block); delete yyvsp[-11].instruction;
		  yyvsp[-9].number->Put(*code_block); delete yyvsp[-9].number;
		  yyvsp[-7].reg->Put(*code_block); delete yyvsp[-7].reg;
		  yyvsp[-5].reg->Put(*code_block); delete yyvsp[-5].reg;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 98:
#line 922 "qa.y"
    {
		  yyvsp[-13].instruction->Put(*code_block); delete yyvsp[-13].instruction;
		  yyvsp[-11].number->Put(*code_block); delete yyvsp[-11].number;
		  yyvsp[-9].reg->Put(*code_block); delete yyvsp[-9].reg;
		  yyvsp[-7].reg->Put(*code_block); delete yyvsp[-7].reg;
		  yyvsp[-5].reg->Put(*code_block); delete yyvsp[-5].reg;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;

  case 99:
#line 934 "qa.y"
    {
		  yyval.cl_list = NULL;
		}
    break;

  case 100:
#line 938 "qa.y"
    {
		  yyval.cl_list = yyvsp[0].cl_list;
		}
    break;

  case 101:
#line 944 "qa.y"
    {
		  vector<ConstantLabel *> *tmp = new vector<ConstantLabel *>;

		  tmp->push_back(yyvsp[0].cl);

		  yyval.cl_list = tmp;
		}
    break;

  case 102:
#line 952 "qa.y"
    {
		  yyvsp[-2].cl_list->push_back(yyvsp[0].cl);

		  yyval.cl_list = yyvsp[-2].cl_list;
		}
    break;

  case 103:
#line 960 "qa.y"
    {
		  yyval.cl = new ConstantLabel(yyvsp[-2].constant, yyvsp[0].label_name);
		  
		}
    break;

  case 104:
#line 967 "qa.y"
    {
		  yyval.aal_list = NULL;
		}
    break;

  case 105:
#line 971 "qa.y"
    {
		  yyval.aal_list = yyvsp[0].aal_list;
		}
    break;

  case 106:
#line 977 "qa.y"
    {
		  vector<AtomArityLabel *> *tmp = new vector<AtomArityLabel *>;

		  tmp->push_back(yyvsp[0].aal);

		  yyval.aal_list = tmp;
		}
    break;

  case 107:
#line 985 "qa.y"
    {
		  yyvsp[-2].aal_list->push_back(yyvsp[0].aal);
		  yyval.aal_list = yyvsp[-2].aal_list;
		}
    break;

  case 108:
#line 992 "qa.y"
    {
		  ASMStringPointer asm_atom(yyvsp[-4].atom_name);
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  ASMInt<Code::ConstantSizedType> *atom = 
		    new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);


		  yyval.aal = new AtomArityLabel(atom, yyvsp[-2].number, yyvsp[0].label_name);

		}
    break;

  case 109:
#line 1006 "qa.y"
    {
		  yyval.aal_list = NULL;
		}
    break;

  case 110:
#line 1010 "qa.y"
    {
		  yyval.aal_list = yyvsp[0].aal_list;
		}
    break;

  case 111:
#line 1016 "qa.y"
    {
		  vector<AtomArityLabel *> *tmp = new vector<AtomArityLabel *>;

		  tmp->push_back(yyvsp[0].aal);

		  yyval.aal_list = tmp;
		}
    break;

  case 112:
#line 1024 "qa.y"
    {
		  yyvsp[-2].aal_list->push_back(yyvsp[0].aal);

		  yyval.aal_list = yyvsp[-2].aal_list;
		}
    break;

  case 113:
#line 1032 "qa.y"
    {
		  ASMStringPointer asm_atom(yyvsp[-4].atom_name);
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  ASMInt<Code::ConstantSizedType> *atom = 
		    new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);

		  yyval.aal = new AtomArityLabel(atom, yyvsp[-2].number, yyvsp[0].label_name);
		}
    break;

  case 115:
#line 1045 "qa.y"
    {
		  if (*yyvsp[0].atom_name != "fail")
		    {
		      FatalS(__FUNCTION__, "invalid switch label ",
			     yyvsp[0].atom_name->c_str());
		    }
		}
    break;

  case 116:
#line 1055 "qa.y"
    {
		  ASMStringPointer asm_atom(yyvsp[0].atom_name);
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  yyval.constant = new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);
		}
    break;

  case 117:
#line 1062 "qa.y"
    {
		  yyval.constant = new ASMInt<Code::ConstantSizedType>((word32)(yyvsp[0].number_value), ConstEntry::INTEGER_TYPE);

		}
    break;

  case 118:
#line 1067 "qa.y"
    {
		  yyval.constant = new ASMInt<Code::ConstantSizedType>((word32)(yyvsp[0].number_value), ConstEntry::INTEGER_TYPE);

		}
    break;

  case 119:
#line 1072 "qa.y"
    {
		  yyval.constant = new ASMInt<Code::ConstantSizedType>((word32)(-yyvsp[0].number_value), ConstEntry::INTEGER_TYPE);

		}
    break;

  case 120:
#line 1079 "qa.y"
    {
		  yyval.number = new ASMInt<Code::NumberSizedType>(yyvsp[0].number_value);

		}
    break;

  case 121:
#line 1086 "qa.y"
    {
		  yyval.reg = new ASMInt<Code::RegisterSizedType>(yyvsp[0].number_value);
		  
		}
    break;

  case 122:
#line 1093 "qa.y"
    {
		  yyval.address = new ASMInt<Code::AddressSizedType>(yyvsp[0].number_value);

		}
    break;

  case 123:
#line 1100 "qa.y"
    {
		  ASMStringPointer asm_atom(yyvsp[0].atom_name);
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);
		  yyval.constant = new ASMInt<Code::PredSizedType>(loc);
		}
    break;

  case 124:
#line 1108 "qa.y"
    {
		  yyval.table_size = new ASMInt<Code::TableSizeSizedType>(yyvsp[0].number_value);

		}
    break;


    }

/* Line 1000 of yacc.c.  */
#line 2746 "qa.cc"

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
      /* If just tried and failed to reuse lookahead token after an
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
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval);
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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


#line 1114 "qa.y"

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
}


