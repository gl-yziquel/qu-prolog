/* A Bison parser, made from qa.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	put_x_variable	257
# define	put_y_variable	258
# define	put_x_value	259
# define	put_y_value	260
# define	put_constant	261
# define	put_integer	262
# define	put_list	263
# define	put_structure	264
# define	put_x_object_variable	265
# define	put_y_object_variable	266
# define	put_x_object_value	267
# define	put_y_object_value	268
# define	put_quantifier	269
# define	check_binder	270
# define	put_substitution	271
# define	put_x_term_substitution	272
# define	put_y_term_substitution	273
# define	put_initial_empty_substitution	274
# define	get_x_variable	275
# define	get_y_variable	276
# define	get_x_value	277
# define	get_y_value	278
# define	get_constant	279
# define	get_integer	280
# define	get_list	281
# define	get_structure	282
# define	get_structure_frame	283
# define	get_x_object_variable	284
# define	get_y_object_variable	285
# define	get_x_object_value	286
# define	get_y_object_value	287
# define	unify_x_variable	288
# define	unify_y_variable	289
# define	unify_x_value	290
# define	unify_y_value	291
# define	unify_void	292
# define	unify_constant	293
# define	unify_integer	294
# define	unify_x_ref	295
# define	unify_y_ref	296
# define	set_x_variable	297
# define	set_y_variable	298
# define	set_x_value	299
# define	set_y_value	300
# define	set_x_object_variable	301
# define	set_y_object_variable	302
# define	set_x_object_value	303
# define	set_y_object_value	304
# define	set_constant	305
# define	set_integer	306
# define	set_void	307
# define	set_object_void	308
# define	wam_allocate	309
# define	wam_deallocate	310
# define	call_predicate	311
# define	call_address	312
# define	call_escape	313
# define	execute_predicate	314
# define	execute_address	315
# define	execute_escape	316
# define	noop	317
# define	jump	318
# define	proceed	319
# define	wam_fail	320
# define	halt	321
# define	wam_exit	322
# define	try_me_else	323
# define	retry_me_else	324
# define	trust_me_else_fail	325
# define	wam_try	326
# define	retry	327
# define	trust	328
# define	neck_cut	329
# define	get_x_level	330
# define	get_y_level	331
# define	cut	332
# define	switch_on_term	333
# define	switch_on_constant	334
# define	switch_on_structure	335
# define	switch_on_quantifier	336
# define	pseudo_instr0	337
# define	pseudo_instr1	338
# define	pseudo_instr2	339
# define	pseudo_instr3	340
# define	pseudo_instr4	341
# define	pseudo_instr5	342
# define	NUMBER_TOKEN	343
# define	ATOM_TOKEN	344
# define	LABEL_TOKEN	345
# define	END_TOKEN	346

#line 1 "qa.y"

/*
 * Copyright (C) 1999 
 * Department of Computer Science and Electrical Engineering, 
 * The University of Queensland
 */

#include <stdio.h>
#include <iostream.h>
#include <fstream.h>
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


#line 36 "qa.y"
#ifndef YYSTYPE
typedef union {
  signed long int number_value;

  String *label_name;
  String *atom_name;

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
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		522
#define	YYFLAG		-32768
#define	YYNTBASE	102

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 346 ? yytranslate[x] : 127)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
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
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     3,     6,    10,    15,    23,    24,    27,
      29,    31,    34,    41,    48,    55,    62,    69,    76,    81,
      88,    95,   102,   109,   116,   121,   126,   133,   140,   147,
     152,   159,   166,   173,   180,   187,   194,   199,   208,   215,
     222,   229,   236,   243,   248,   253,   258,   263,   268,   273,
     278,   283,   288,   293,   298,   303,   308,   313,   318,   323,
     328,   333,   338,   343,   348,   353,   355,   364,   371,   378,
     385,   390,   395,   397,   402,   404,   406,   408,   410,   417,
     422,   424,   431,   436,   441,   443,   448,   453,   458,   475,
     489,   503,   517,   522,   529,   538,   549,   562,   577,   578,
     581,   583,   587,   591,   592,   595,   597,   601,   607,   608,
     611,   613,   617,   623,   625,   627,   629,   631,   634,   637,
     639,   641,   643,   645
};
static const short yyrhs[] =
{
     103,     0,     0,   103,   104,     0,   105,   107,   106,     0,
     125,    93,   122,    94,     0,    92,    95,   125,    93,   122,
      96,    94,     0,     0,   107,   108,     0,   109,     0,   110,
       0,    91,    94,     0,     3,    95,   123,    97,   123,    96,
       0,     4,    95,   123,    97,   123,    96,     0,     5,    95,
     123,    97,   123,    96,     0,     6,    95,   123,    97,   123,
      96,     0,     7,    95,   121,    97,   123,    96,     0,     8,
      95,   121,    97,   123,    96,     0,     9,    95,   123,    96,
       0,    10,    95,   122,    97,   123,    96,     0,    11,    95,
     123,    97,   123,    96,     0,    12,    95,   123,    97,   123,
      96,     0,    13,    95,   123,    97,   123,    96,     0,    14,
      95,   123,    97,   123,    96,     0,    15,    95,   123,    96,
       0,    16,    95,   123,    96,     0,    17,    95,   122,    97,
     123,    96,     0,    18,    95,   123,    97,   123,    96,     0,
      19,    95,   123,    97,   123,    96,     0,    20,    95,   123,
      96,     0,    21,    95,   123,    97,   123,    96,     0,    22,
      95,   123,    97,   123,    96,     0,    23,    95,   123,    97,
     123,    96,     0,    24,    95,   123,    97,   123,    96,     0,
      25,    95,   121,    97,   123,    96,     0,    26,    95,   121,
      97,   123,    96,     0,    27,    95,   123,    96,     0,    28,
      95,   121,    97,   122,    97,   123,    96,     0,    29,    95,
     122,    97,   123,    96,     0,    30,    95,   123,    97,   123,
      96,     0,    31,    95,   123,    97,   123,    96,     0,    32,
      95,   123,    97,   123,    96,     0,    33,    95,   123,    97,
     123,    96,     0,    34,    95,   123,    96,     0,    35,    95,
     123,    96,     0,    36,    95,   123,    96,     0,    37,    95,
     123,    96,     0,    39,    95,   121,    96,     0,    40,    95,
     121,    96,     0,    38,    95,   122,    96,     0,    41,    95,
     123,    96,     0,    42,    95,   123,    96,     0,    43,    95,
     123,    96,     0,    44,    95,   123,    96,     0,    45,    95,
     123,    96,     0,    46,    95,   123,    96,     0,    47,    95,
     123,    96,     0,    48,    95,   123,    96,     0,    49,    95,
     123,    96,     0,    50,    95,   123,    96,     0,    51,    95,
     121,    96,     0,    52,    95,   121,    96,     0,    53,    95,
     122,    96,     0,    54,    95,   122,    96,     0,    55,    95,
     122,    96,     0,    56,     0,    57,    95,   125,    97,   122,
      97,   122,    96,     0,    58,    95,   124,    97,   122,    96,
       0,    59,    95,   124,    97,   122,    96,     0,    60,    95,
     125,    97,   122,    96,     0,    61,    95,   124,    96,     0,
      62,    95,   124,    96,     0,    63,     0,    64,    95,   124,
      96,     0,    65,     0,    66,     0,    67,     0,    68,     0,
      69,    95,   122,    97,    91,    96,     0,    70,    95,    91,
      96,     0,    71,     0,    72,    95,   122,    97,    91,    96,
       0,    73,    95,    91,    96,     0,    74,    95,    91,    96,
       0,    75,     0,    76,    95,   123,    96,     0,    77,    95,
     123,    96,     0,    78,    95,   123,    96,     0,    79,    95,
     123,    97,   120,    97,   120,    97,   120,    97,   120,    97,
     120,    97,   120,    96,     0,    80,    95,   123,    97,   126,
      97,    98,    90,    94,   120,   111,    99,    96,     0,    81,
      95,   123,    97,   126,    97,    98,    90,    94,   120,   114,
      99,    96,     0,    82,    95,   123,    97,   126,    97,    98,
      90,    94,   120,   117,    99,    96,     0,    83,    95,   122,
      96,     0,    84,    95,   122,    97,   123,    96,     0,    85,
      95,   122,    97,   123,    97,   123,    96,     0,    86,    95,
     122,    97,   123,    97,   123,    97,   123,    96,     0,    87,
      95,   122,    97,   123,    97,   123,    97,   123,    97,   123,
      96,     0,    88,    95,   122,    97,   123,    97,   123,    97,
     123,    97,   123,    97,   123,    96,     0,     0,    97,   112,
       0,   113,     0,   112,    97,   113,     0,   121,    94,   120,
       0,     0,    97,   115,     0,   116,     0,   115,    97,   116,
       0,    90,    93,   122,    94,   120,     0,     0,    97,   118,
       0,   119,     0,   118,    97,   119,     0,    90,    93,   122,
      94,   120,     0,    91,     0,    90,     0,    90,     0,    89,
       0,   100,    89,     0,   101,    89,     0,    89,     0,    89,
       0,    89,     0,    90,     0,    89,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   187,   190,   191,   194,   197,   239,   264,   265,   268,
     269,   272,   278,   285,   292,   299,   306,   313,   320,   326,
     333,   340,   347,   354,   361,   367,   373,   380,   387,   394,
     400,   407,   414,   421,   428,   435,   442,   448,   456,   463,
     470,   477,   484,   491,   497,   503,   509,   515,   521,   527,
     533,   539,   545,   551,   557,   563,   569,   575,   581,   587,
     593,   599,   605,   611,   617,   623,   628,   636,   643,   650,
     657,   663,   669,   674,   680,   685,   690,   695,   700,   712,
     722,   727,   739,   749,   759,   764,   770,   776,   782,   806,
     834,   862,   890,   896,   903,   911,   920,   930,   943,   947,
     953,   966,   974,   985,   989,   995,  1008,  1015,  1037,  1041,
    1047,  1060,  1068,  1088,  1089,  1099,  1110,  1119,  1128,  1139,
    1149,  1160,  1171,  1183
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "put_x_variable", "put_y_variable", 
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
  "'('", "')'", "','", "'['", "']'", "'+'", "'-'", "assembler_file", 
  "predicate_list", "predicate", "predicate_start", "predicate_end", 
  "source_line_list", "source_line", "label_instance", "instr", 
  "constant_labels", "constant_label_list", "constant_label", 
  "atom_arity_labels", "atom_arity_label_list", "atom_arity_label", 
  "quantifier_labels", "quantifier_label_list", "quantifier_label", 
  "switch_label", "constant", "number", "reg", "address", "atom", 
  "table_size", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,   102,   103,   103,   104,   105,   106,   107,   107,   108,
     108,   109,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   111,   111,
     112,   112,   113,   114,   114,   115,   115,   116,   117,   117,
     118,   118,   119,   120,   120,   121,   121,   121,   121,   122,
     123,   124,   125,   126
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     0,     2,     3,     4,     7,     0,     2,     1,
       1,     2,     6,     6,     6,     6,     6,     6,     4,     6,
       6,     6,     6,     6,     4,     4,     6,     6,     6,     4,
       6,     6,     6,     6,     6,     6,     4,     8,     6,     6,
       6,     6,     6,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     1,     8,     6,     6,     6,
       4,     4,     1,     4,     1,     1,     1,     1,     6,     4,
       1,     6,     4,     4,     1,     4,     4,     4,    16,    13,
      13,    13,     4,     6,     8,    10,    12,    14,     0,     2,
       1,     3,     3,     0,     2,     1,     3,     5,     0,     2,
       1,     3,     5,     1,     1,     1,     1,     2,     2,     1,
       1,     1,     1,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       2,     1,   122,     3,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    65,     0,     0,     0,     0,     0,     0,    72,     0,
      74,    75,    76,    77,     0,     0,    80,     0,     0,     0,
      84,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     4,     8,     9,    10,
     119,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      11,     0,     5,   120,     0,     0,     0,     0,   116,   115,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,   118,     0,     0,    18,     0,     0,     0,
       0,     0,    24,    25,     0,     0,     0,    29,     0,     0,
       0,     0,     0,     0,    36,     0,     0,     0,     0,     0,
       0,    43,    44,    45,    46,    49,    47,    48,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,     0,     0,     0,     0,    70,    71,    73,
       0,    79,     0,    82,    83,    85,    86,    87,     0,     0,
       0,     0,    92,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   114,   113,     0,   123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    12,    13,    14,    15,    16,    17,
      19,    20,    21,    22,    23,    26,    27,    28,    30,    31,
      32,    33,    34,    35,     0,    38,    39,    40,    41,    42,
       0,    67,    68,    69,    78,    81,     0,     0,     0,     0,
      93,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,    37,    66,     0,
       0,     0,     0,    94,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    98,   103,   108,    95,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    99,   100,     0,     0,     0,   104,   105,     0,     0,
     109,   110,     0,    96,     0,     0,     0,     0,    89,     0,
       0,    90,     0,     0,    91,     0,     0,   101,   102,     0,
     106,     0,   111,    97,     0,     0,     0,    88,   107,   112,
       0,     0,     0
};

static const short yydefgoto[] =
{
     520,     1,     3,     4,    96,     6,    97,    98,    99,   473,
     481,   482,   475,   486,   487,   477,   490,   491,   383,   483,
     101,   184,   243,     5,   385
};

static const short yypact[] =
{
  -32768,   -81,-32768,-32768,-32768,   -78,   464,   -71,   -73,   -69,
     -66,   -65,   -64,   -63,   -62,   -59,   -58,   -57,   -56,   -55,
     -54,   -53,   -47,   -46,   -45,   -44,   -43,   -41,   -39,   -38,
     -37,   -36,   -35,   -34,   -33,   -32,   -31,   -24,   -23,   -22,
     -21,   -17,   -16,   -14,    -7,     1,     2,     5,    14,    15,
      16,    28,    29,    30,    31,    32,    33,    34,    35,    39,
      40,-32768,    41,    43,    51,    52,    53,    54,-32768,    55,
  -32768,-32768,-32768,-32768,    56,    57,-32768,    59,    60,    61,
  -32768,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    77,    78,-32768,-32768,-32768,-32768,
  -32768,    80,    83,    83,    83,    83,   -84,   -84,    83,   -71,
      83,    83,    83,    83,    83,    83,   -71,    83,    83,    83,
      83,    83,    83,    83,   -84,   -84,    83,   -84,   -71,    83,
      83,    83,    83,    83,    83,    83,    83,   -71,   -84,   -84,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
     -84,   -84,   -71,   -71,   -71,   -81,    86,    86,   -81,    86,
      86,    86,   -71,    85,   -71,    87,    89,    83,    83,    83,
      83,    83,    83,    83,   -71,   -71,   -71,   -71,   -71,   -71,
  -32768,   -81,-32768,-32768,    84,    88,    90,    93,-32768,-32768,
      94,    95,    96,    97,    81,    98,    99,   100,   101,   102,
     104,   105,   106,   107,   108,   110,   111,   112,   113,   114,
     115,   116,   122,   123,   124,   125,   126,   127,   128,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   148,   149,   152,   158,   159,   163,   170,   171,
     177,   178,-32768,   179,   180,   181,   183,   184,   185,   186,
     188,   189,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   201,   202,   203,   204,   205,   206,   109,    83,    83,
      83,    83,-32768,-32768,    83,    83,-32768,    83,    83,    83,
      83,    83,-32768,-32768,    83,    83,    83,-32768,    83,    83,
      83,    83,    83,    83,-32768,   -71,    83,    83,    83,    83,
      83,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,   -71,   -71,   -71,   -71,-32768,-32768,-32768,
      91,-32768,   207,-32768,-32768,-32768,-32768,-32768,   -77,   103,
     103,   103,-32768,    83,    83,    83,    83,    83,   -71,   208,
     209,   210,   211,   212,   213,   214,   216,   217,   218,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     236,   237,   238,   239,   240,   241,   243,   244,   245,   246,
     247,-32768,-32768,   248,-32768,   249,   250,   251,   253,   254,
     255,   256,   257,   259,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,    83,-32768,-32768,-32768,-32768,-32768,
     -71,-32768,-32768,-32768,-32768,-32768,   -77,   121,   176,   187,
  -32768,    83,    83,    83,    83,   262,   261,   263,   264,   117,
     260,   268,   266,   267,   269,   270,-32768,-32768,-32768,   -77,
     271,   274,   275,-32768,    83,    83,    83,   273,   -77,   -77,
     -77,   276,   277,   278,   -77,   279,   280,   281,-32768,    83,
      83,   282,   -84,    92,   283,   272,   290,   284,   285,   287,
     -77,   288,-32768,   293,   286,   295,   292,-32768,   296,   298,
     297,-32768,   299,-32768,    83,   300,   -84,   -77,-32768,   -71,
     283,-32768,   -71,   290,-32768,   302,   -77,-32768,-32768,   305,
  -32768,   306,-32768,-32768,   311,   -77,   -77,-32768,-32768,-32768,
     330,   337,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,  -214,-32768,-32768,  -208,-32768,-32768,  -159,  -327,  -104,
    -109,   -28,  -149,  -154,  -316
};


#define	YYLAST		556


static const short yytable[] =
{
     195,   241,   192,   193,   245,   188,   189,   202,   244,     2,
     246,   247,   248,   381,   382,     7,   190,   191,   100,   214,
     210,   211,   102,   213,   386,   387,   103,   267,   223,   104,
     105,   106,   107,   108,   224,   225,   109,   110,   111,   112,
     113,   114,   115,   238,   239,   240,   236,   237,   116,   117,
     118,   119,   120,   249,   121,   251,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   261,   262,   263,   264,   265,
     266,   131,   132,   133,   134,   185,   186,   187,   135,   136,
     194,   137,   196,   197,   198,   199,   200,   201,   138,   203,
     204,   205,   206,   207,   208,   209,   139,   140,   212,   438,
     141,   215,   216,   217,   218,   219,   220,   221,   222,   142,
     143,   144,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   457,   145,   146,   147,   148,   149,   150,   151,
     152,   465,   466,   467,   153,   154,   155,   471,   156,   254,
     255,   256,   257,   258,   259,   260,   157,   158,   159,   160,
     161,   162,   163,   495,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     508,   180,   183,   181,   182,   242,   250,   276,   252,   514,
     253,   268,   379,   272,   273,   269,   369,   270,   518,   519,
     271,   484,   384,   274,   275,   277,   278,   279,   280,   281,
     282,   283,   348,   284,   285,   286,   287,   450,   288,   289,
     290,   291,   292,   293,   375,   376,   377,   378,   294,   439,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   393,
     349,   350,   351,   352,   314,   315,   353,   354,   316,   355,
     356,   357,   358,   359,   317,   318,   360,   361,   362,   319,
     363,   364,   365,   366,   367,   368,   320,   321,   370,   371,
     372,   373,   374,   322,   440,   323,   324,   325,   326,   327,
     328,   329,   507,   330,   331,   441,   332,   333,   334,   335,
     336,   337,   510,   338,   339,   340,   341,   342,   380,   343,
     344,   345,   346,   347,   394,   395,   396,   397,   398,   399,
     400,   437,   401,   402,   403,   388,   389,   390,   391,   392,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
     521,   414,   415,   416,   417,   418,   419,   522,   420,   421,
     422,   423,   424,   425,   512,   426,   427,   428,   429,   430,
     451,   431,   432,   433,   434,   435,   446,   447,   452,   448,
       0,   449,   453,     0,   454,   458,   455,   456,   459,   460,
     464,   488,   468,   485,   469,   470,   472,   474,   476,   480,
     489,   493,   498,   492,   494,   496,   436,   497,   499,   500,
     509,   502,   501,   511,   503,   504,     0,   506,   513,   515,
     516,     0,     0,   442,   443,   444,   445,   517,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   461,   462,   463,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   478,   479,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   505,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,     0,     0,    94,    95
};

static const short yycheck[] =
{
     109,   155,   106,   107,   158,    89,    90,   116,   157,    90,
     159,   160,   161,    90,    91,    93,   100,   101,    89,   128,
     124,   125,    95,   127,   340,   341,    95,   181,   137,    95,
      95,    95,    95,    95,   138,   139,    95,    95,    95,    95,
      95,    95,    95,   152,   153,   154,   150,   151,    95,    95,
      95,    95,    95,   162,    95,   164,    95,    95,    95,    95,
      95,    95,    95,    95,    95,   174,   175,   176,   177,   178,
     179,    95,    95,    95,    95,   103,   104,   105,    95,    95,
     108,    95,   110,   111,   112,   113,   114,   115,    95,   117,
     118,   119,   120,   121,   122,   123,    95,    95,   126,   426,
      95,   129,   130,   131,   132,   133,   134,   135,   136,    95,
      95,    95,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   449,    95,    95,    95,    95,    95,    95,    95,
      95,   458,   459,   460,    95,    95,    95,   464,    95,   167,
     168,   169,   170,   171,   172,   173,    95,    95,    95,    95,
      95,    95,    95,   480,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
     497,    94,    89,    95,    94,    89,    91,    96,    91,   506,
      91,    97,    91,    89,    89,    97,   295,    97,   515,   516,
      97,    99,    89,    97,    97,    97,    97,    97,    97,    97,
      96,    96,    93,    97,    97,    97,    96,    90,    97,    97,
      97,    97,    97,    97,   323,   324,   325,   326,    96,    98,
      97,    97,    97,    97,    97,    97,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,   348,
     268,   269,   270,   271,    96,    96,   274,   275,    96,   277,
     278,   279,   280,   281,    96,    96,   284,   285,   286,    96,
     288,   289,   290,   291,   292,   293,    96,    96,   296,   297,
     298,   299,   300,    96,    98,    97,    97,    97,    97,    96,
      96,    96,   496,    97,    96,    98,    97,    96,    96,    96,
      96,    96,   500,    97,    97,    97,    97,    96,    91,    97,
      97,    97,    97,    97,    96,    96,    96,    96,    96,    96,
      96,   420,    96,    96,    96,   343,   344,   345,   346,   347,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
       0,    97,    96,    96,    96,    96,    96,     0,    97,    96,
      96,    96,    96,    96,   503,    97,    97,    97,    97,    96,
      90,    97,    97,    97,    97,    96,    94,    96,    90,    96,
      -1,    97,    96,    -1,    97,    94,    97,    97,    94,    94,
      97,    99,    96,    90,    97,    97,    97,    97,    97,    97,
      90,    96,    96,    99,    97,    97,   414,    94,    93,    97,
     499,    93,    96,   502,    97,    96,    -1,    97,    96,    94,
      94,    -1,    -1,   431,   432,   433,   434,    96,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   454,   455,   456,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   469,   470,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   494,     3,     4,     5,
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
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

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

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
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
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
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
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


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
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
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
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


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
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
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

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

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
#endif

#line 315 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
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
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
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

  if (yyssp >= yyss + yystacksize - 1)
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
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
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
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 5:
#line 198 "qa.y"
{
		  labels = new LabelTable;
		  if (labels == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }

		  // Is it the query code block?
		  if ((*asm_string_table)[yyvsp[-3].constant->Value()] == "$query" &&
		      yyvsp[-1].number->Value() == 0)
		    {
		      if (query_code_block != NULL)
			{
			  Fatal(__FUNCTION__, "more than one query code block");
			}
		      query_code_block = new CodeBlock(QUERY_BLOCK,
						       yyvsp[-3].constant->Value(),
						       yyvsp[-1].number->Value());
		      if (query_code_block == NULL)
			{
			  OutOfMemory(__FUNCTION__);
			}

		      code_block = query_code_block;
		    }
		  else
		    {
		      code_block = new CodeBlock(PREDICATE_BLOCK,
						 yyvsp[-3].constant->Value(),
						 yyvsp[-1].number->Value());
		      if (code_block == NULL)
			{
			  OutOfMemory(__FUNCTION__);
			}
		    }

		  delete yyvsp[-3].constant;
		  delete yyvsp[-1].number;
		}
    break;
case 6:
#line 240 "qa.y"
{
		  if (yyvsp[-4].constant->Value() != code_block->Atom() ||
		      yyvsp[-2].number->Value() != code_block->Arity())
		    {
		      Fatal(__FUNCTION__, "atom or arity mismatch in predicate");
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
case 11:
#line 273 "qa.y"
{
		  labels->Resolve(*yyvsp[-1].label_name, *code_block);
		}
    break;
case 12:
#line 279 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 13:
#line 286 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 14:
#line 293 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 15:
#line 300 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 16:
#line 307 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].constant->Put(*code_block); delete yyvsp[-3].constant;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 17:
#line 314 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].constant->Put(*code_block); delete yyvsp[-3].constant;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 18:
#line 321 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 19:
#line 327 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].number->Put(*code_block); delete yyvsp[-3].number;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 20:
#line 334 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 21:
#line 341 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 22:
#line 348 "qa.y"
{
		   yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		   yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		   yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		 }
    break;
case 23:
#line 355 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 24:
#line 362 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 25:
#line 368 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 26:
#line 374 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].number->Put(*code_block); delete yyvsp[-3].number;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 27:
#line 381 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 28:
#line 388 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 29:
#line 395 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 30:
#line 401 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 31:
#line 408 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 32:
#line 415 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 33:
#line 422 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 34:
#line 429 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].constant->Put(*code_block); delete yyvsp[-3].constant;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 35:
#line 436 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].constant->Put(*code_block); delete yyvsp[-3].constant;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 36:
#line 443 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 37:
#line 449 "qa.y"
{
		  yyvsp[-7].instruction->Put(*code_block); delete yyvsp[-7].instruction;
		  yyvsp[-5].constant->Put(*code_block); delete yyvsp[-5].constant;
		  yyvsp[-3].number->Put(*code_block); delete yyvsp[-3].number;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 38:
#line 457 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].number->Put(*code_block); delete yyvsp[-3].number;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 39:
#line 464 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 40:
#line 471 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 41:
#line 478 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 42:
#line 485 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 43:
#line 492 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;
case 44:
#line 498 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;
case 45:
#line 504 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;
case 46:
#line 510 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;
case 47:
#line 516 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].constant->Put(*code_block); delete yyvsp[-1].constant;
		}
    break;
case 48:
#line 522 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].constant->Put(*code_block); delete yyvsp[-1].constant;
		}
    break;
case 49:
#line 528 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
	        }
    break;
case 50:
#line 534 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;
case 51:
#line 540 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;
case 52:
#line 546 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;
case 53:
#line 552 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
	        }
    break;
case 54:
#line 558 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;
case 55:
#line 564 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;
case 56:
#line 570 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;
case 57:
#line 576 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;
case 58:
#line 582 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
        	}
    break;
case 59:
#line 588 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
	        }
    break;
case 60:
#line 594 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].constant->Put(*code_block); delete yyvsp[-1].constant;
		}
    break;
case 61:
#line 600 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].constant->Put(*code_block); delete yyvsp[-1].constant;
		}
    break;
case 62:
#line 606 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
		}
    break;
case 63:
#line 612 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
		}
    break;
case 64:
#line 618 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
		}
    break;
case 65:
#line 624 "qa.y"
{
		  yyvsp[0].instruction->Put(*code_block); delete yyvsp[0].instruction;
		}
    break;
case 66:
#line 629 "qa.y"
{
		  yyvsp[-7].instruction->Put(*code_block); delete yyvsp[-7].instruction;
		  yyvsp[-5].constant->Put(*code_block); delete yyvsp[-5].constant;
		  yyvsp[-3].number->Put(*code_block); delete yyvsp[-3].number;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
		}
    break;
case 67:
#line 637 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction; 
		  yyvsp[-3].address->Put(*code_block); delete yyvsp[-3].address;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
		}
    break;
case 68:
#line 644 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].address->Put(*code_block); delete yyvsp[-3].address;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
		}
    break;
case 69:
#line 651 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].constant->Put(*code_block); delete yyvsp[-3].constant;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
		}
    break;
case 70:
#line 658 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].address->Put(*code_block); delete yyvsp[-1].address;
		}
    break;
case 71:
#line 664 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].address->Put(*code_block); delete yyvsp[-1].address;
		}
    break;
case 72:
#line 670 "qa.y"
{
		  yyvsp[0].instruction->Put(*code_block); delete yyvsp[0].instruction;
		}
    break;
case 73:
#line 675 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].address->Put(*code_block); delete yyvsp[-1].address;
		}
    break;
case 74:
#line 681 "qa.y"
{
		  yyvsp[0].instruction->Put(*code_block); delete yyvsp[0].instruction;
		}
    break;
case 75:
#line 686 "qa.y"
{
		  yyvsp[0].instruction->Put(*code_block); delete yyvsp[0].instruction;
		}
    break;
case 76:
#line 691 "qa.y"
{
		  yyvsp[0].instruction->Put(*code_block); delete yyvsp[0].instruction;
		}
    break;
case 77:
#line 696 "qa.y"
{
		  yyvsp[0].instruction->Put(*code_block); delete yyvsp[0].instruction;
		}
    break;
case 78:
#line 701 "qa.y"
{
		  unsigned jump_offset_base =
		    code_block->Current() +
		      yyvsp[-5].instruction->SizeOf() + yyvsp[-3].number->SizeOf() + Code::SIZE_OF_OFFSET;

		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].number->Put(*code_block); delete yyvsp[-3].number;

		  labels->AddReference(*yyvsp[-1].label_name, *code_block, jump_offset_base);
		}
    break;
case 79:
#line 713 "qa.y"
{
		  unsigned jump_offset_base =
		    code_block->Current() +
		      yyvsp[-3].instruction->SizeOf() + Code::SIZE_OF_OFFSET;

		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  labels->AddReference(*yyvsp[-1].label_name, *code_block, jump_offset_base);
		}
    break;
case 80:
#line 723 "qa.y"
{
		  yyvsp[0].instruction->Put(*code_block); delete yyvsp[0].instruction;
		}
    break;
case 81:
#line 728 "qa.y"
{
		  unsigned jump_offset_base =
		    code_block->Current() +
		      yyvsp[-5].instruction->SizeOf() + yyvsp[-3].number->SizeOf() + Code::SIZE_OF_OFFSET;

		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].number->Put(*code_block); delete yyvsp[-3].number;

		  labels->AddReference(*yyvsp[-1].label_name, *code_block, jump_offset_base);
		}
    break;
case 82:
#line 740 "qa.y"
{
		  unsigned jump_offset_base =
		    code_block->Current() +
		      yyvsp[-3].instruction->SizeOf() + Code::SIZE_OF_OFFSET;

		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  labels->AddReference(*yyvsp[-1].label_name, *code_block, jump_offset_base);
		}
    break;
case 83:
#line 750 "qa.y"
{
		  unsigned jump_offset_base =
		    code_block->Current() +
		      yyvsp[-3].instruction->SizeOf() + Code::SIZE_OF_OFFSET;

		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  labels->AddReference(*yyvsp[-1].label_name, *code_block, jump_offset_base);
		}
    break;
case 84:
#line 760 "qa.y"
{
		  yyvsp[0].instruction->Put(*code_block); delete yyvsp[0].instruction;
		}
    break;
case 85:
#line 765 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 86:
#line 771 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 87:
#line 777 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 88:
#line 789 "qa.y"
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
case 89:
#line 808 "qa.y"
{
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      yyvsp[-12].instruction->SizeOf() + yyvsp[-10].reg->SizeOf() + yyvsp[-8].table_size->SizeOf();

		  yyvsp[-12].instruction->Put(*code_block); delete yyvsp[-12].instruction;
		  yyvsp[-10].reg->Put(*code_block); delete yyvsp[-10].reg;
		  yyvsp[-8].table_size->Put(*code_block); 

		  if (*yyvsp[-5].atom_name != "default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_structure");
		    }

		  SwitchTable<ConstantLabel> switch_table(jump_offset_base,
							  yyvsp[-8].table_size, yyvsp[-3].label_name, yyvsp[-2].cl_list);

		  switch_table.Put(*code_block, *labels);

		  delete yyvsp[-8].table_size;
		  delete yyvsp[-3].label_name;
		  delete yyvsp[-2].cl_list;
		}
    break;
case 90:
#line 836 "qa.y"
{
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      yyvsp[-12].instruction->SizeOf() + yyvsp[-10].reg->SizeOf() + yyvsp[-8].table_size->SizeOf();

		  yyvsp[-12].instruction->Put(*code_block); delete yyvsp[-12].instruction;
		  yyvsp[-10].reg->Put(*code_block); delete yyvsp[-10].reg;
		  yyvsp[-8].table_size->Put(*code_block);

		  if (*yyvsp[-5].atom_name != "default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_structure");
		    }

		  SwitchTable<AtomArityLabel> switch_table(jump_offset_base,
							   yyvsp[-8].table_size, yyvsp[-3].label_name, yyvsp[-2].aal_list);

		  switch_table.Put(*code_block, *labels);

		  delete yyvsp[-8].table_size;
		  delete yyvsp[-3].label_name;
		  delete yyvsp[-2].aal_list;
		}
    break;
case 91:
#line 864 "qa.y"
{
		  // Calculate the pc value from which jumps will be offset
		  unsigned jump_offset_base =
		    code_block->Current() +
		      yyvsp[-12].instruction->SizeOf() + yyvsp[-10].reg->SizeOf() + yyvsp[-8].table_size->SizeOf();

		  yyvsp[-12].instruction->Put(*code_block); delete yyvsp[-12].instruction;
		  yyvsp[-10].reg->Put(*code_block); delete yyvsp[-10].reg;
		  yyvsp[-8].table_size->Put(*code_block);

		  if (*yyvsp[-5].atom_name != "default")
		    {
		      Fatal(__FUNCTION__,
			    "invalid default atom in switch_on_quantifier");
		    }

		  SwitchTable<AtomArityLabel> switch_table(jump_offset_base,
							   yyvsp[-8].table_size, yyvsp[-3].label_name, yyvsp[-2].aal_list);

		  switch_table.Put(*code_block, *labels);

		  delete yyvsp[-8].table_size;
		  delete yyvsp[-3].label_name;
		  delete yyvsp[-2].aal_list;
		}
    break;
case 92:
#line 891 "qa.y"
{
		  yyvsp[-3].instruction->Put(*code_block); delete yyvsp[-3].instruction;
		  yyvsp[-1].number->Put(*code_block); delete yyvsp[-1].number;
		}
    break;
case 93:
#line 897 "qa.y"
{
		  yyvsp[-5].instruction->Put(*code_block); delete yyvsp[-5].instruction;
		  yyvsp[-3].number->Put(*code_block); delete yyvsp[-3].number;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 94:
#line 904 "qa.y"
{
		  yyvsp[-7].instruction->Put(*code_block); delete yyvsp[-7].instruction;
		  yyvsp[-5].number->Put(*code_block); delete yyvsp[-5].number;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 95:
#line 912 "qa.y"
{
		  yyvsp[-9].instruction->Put(*code_block); delete yyvsp[-9].instruction;
		  yyvsp[-7].number->Put(*code_block); delete yyvsp[-7].number;
		  yyvsp[-5].reg->Put(*code_block); delete yyvsp[-5].reg;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 96:
#line 922 "qa.y"
{
		  yyvsp[-11].instruction->Put(*code_block); delete yyvsp[-11].instruction;
		  yyvsp[-9].number->Put(*code_block); delete yyvsp[-9].number;
		  yyvsp[-7].reg->Put(*code_block); delete yyvsp[-7].reg;
		  yyvsp[-5].reg->Put(*code_block); delete yyvsp[-5].reg;
		  yyvsp[-3].reg->Put(*code_block); delete yyvsp[-3].reg;
		  yyvsp[-1].reg->Put(*code_block); delete yyvsp[-1].reg;
		}
    break;
case 97:
#line 932 "qa.y"
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
case 98:
#line 944 "qa.y"
{
		  yyval.cl_list = NULL;
		}
    break;
case 99:
#line 948 "qa.y"
{
		  yyval.cl_list = yyvsp[0].cl_list;
		}
    break;
case 100:
#line 954 "qa.y"
{
		  vector<ConstantLabel *> *tmp = new vector<ConstantLabel *>;

		  if (tmp == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }

		  tmp->push_back(yyvsp[0].cl);

		  yyval.cl_list = tmp;
		}
    break;
case 101:
#line 967 "qa.y"
{
		  yyvsp[-2].cl_list->push_back(yyvsp[0].cl);

		  yyval.cl_list = yyvsp[-2].cl_list;
		}
    break;
case 102:
#line 975 "qa.y"
{
		  yyval.cl = new ConstantLabel(yyvsp[-2].constant, yyvsp[0].label_name);
		  
		  if (yyval.cl == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }
		}
    break;
case 103:
#line 986 "qa.y"
{
		  yyval.aal_list = NULL;
		}
    break;
case 104:
#line 990 "qa.y"
{
		  yyval.aal_list = yyvsp[0].aal_list;
		}
    break;
case 105:
#line 996 "qa.y"
{
		  vector<AtomArityLabel *> *tmp = new vector<AtomArityLabel *>;

		  if (tmp == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }

		  tmp->push_back(yyvsp[0].aal);

		  yyval.aal_list = tmp;
		}
    break;
case 106:
#line 1009 "qa.y"
{
		  yyvsp[-2].aal_list->push_back(yyvsp[0].aal);
		  yyval.aal_list = yyvsp[-2].aal_list;
		}
    break;
case 107:
#line 1016 "qa.y"
{
		  ASMStringPointer asm_atom(yyvsp[-4].atom_name);
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  ASMInt<Code::ConstantSizedType> *atom = 
		    new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);

		  if (atom == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }

		  yyval.aal = new AtomArityLabel(atom, yyvsp[-2].number, yyvsp[0].label_name);

		  if (yyval.aal == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }
		}
    break;
case 108:
#line 1038 "qa.y"
{
		  yyval.aal_list = NULL;
		}
    break;
case 109:
#line 1042 "qa.y"
{
		  yyval.aal_list = yyvsp[0].aal_list;
		}
    break;
case 110:
#line 1048 "qa.y"
{
		  vector<AtomArityLabel *> *tmp = new vector<AtomArityLabel *>;

		  if (tmp == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }

		  tmp->push_back(yyvsp[0].aal);

		  yyval.aal_list = tmp;
		}
    break;
case 111:
#line 1061 "qa.y"
{
		  yyvsp[-2].aal_list->push_back(yyvsp[0].aal);

		  yyval.aal_list = yyvsp[-2].aal_list;
		}
    break;
case 112:
#line 1069 "qa.y"
{
		  ASMStringPointer asm_atom(yyvsp[-4].atom_name);
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  ASMInt<Code::ConstantSizedType> *atom = 
		    new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);
		  if (atom == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }

		  yyval.aal = new AtomArityLabel(atom, yyvsp[-2].number, yyvsp[0].label_name);
		  if (yyval.aal == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }
		}
    break;
case 114:
#line 1090 "qa.y"
{
		  if (*yyvsp[0].atom_name != "fail")
		    {
		      Fatal(__FUNCTION__, "invalid switch label %s\n",
			    yyvsp[0].atom_name->Str());
		    }
		}
    break;
case 115:
#line 1100 "qa.y"
{
		  ASMStringPointer asm_atom(yyvsp[0].atom_name);
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);

		  yyval.constant = new ASMInt<Code::ConstantSizedType>(loc, ConstEntry::ATOM_TYPE);
		  if (yyval.constant == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }
		}
    break;
case 116:
#line 1111 "qa.y"
{
		  yyval.constant = new ASMInt<Code::ConstantSizedType>((word32)(yyvsp[0].number_value), ConstEntry::INTEGER_TYPE);

		  if (yyval.constant == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }
		}
    break;
case 117:
#line 1120 "qa.y"
{
		  yyval.constant = new ASMInt<Code::ConstantSizedType>((word32)(yyvsp[0].number_value), ConstEntry::INTEGER_TYPE);

		  if (yyval.constant == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }
		}
    break;
case 118:
#line 1129 "qa.y"
{
		  yyval.constant = new ASMInt<Code::ConstantSizedType>((word32)(-yyvsp[0].number_value), ConstEntry::INTEGER_TYPE);

		  if (yyval.constant == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }
		}
    break;
case 119:
#line 1140 "qa.y"
{
		  yyval.number = new ASMInt<Code::NumberSizedType>(yyvsp[0].number_value);
		  if (yyval.number == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }
		}
    break;
case 120:
#line 1150 "qa.y"
{
		  yyval.reg = new ASMInt<Code::RegisterSizedType>(yyvsp[0].number_value);
		  
		  if (yyval.reg == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }
		}
    break;
case 121:
#line 1161 "qa.y"
{
		  yyval.address = new ASMInt<Code::AddressSizedType>(yyvsp[0].number_value);

		  if (yyval.address == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }
		}
    break;
case 122:
#line 1172 "qa.y"
{
		  ASMStringPointer asm_atom(yyvsp[0].atom_name);
		  const ASMLoc loc = asm_string_table->lookup(asm_atom);
		  yyval.constant = new ASMInt<Code::PredSizedType>(loc);
		  if (yyval.constant == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }
		}
    break;
case 123:
#line 1184 "qa.y"
{
		  yyval.table_size = new ASMInt<Code::TableSizeSizedType>(yyvsp[0].number_value);

		  if (yyval.table_size == NULL)
		    {
		      OutOfMemory(__FUNCTION__);
		    }
		}
    break;
}

#line 705 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 1194 "qa.y"

#include "lexer.cc"

#include <stdlib.h>

#include "qa_options.h"
		
QaOptions *qa_options = NULL;

int
main(int argc, char **argv)
{
  qa_options = new QaOptions(argc, argv);
  if (qa_options == NULL)
    {
      OutOfMemory(__FUNCTION__);
    }

  if (!qa_options->Valid())
    {
      Usage(Program, qa_options->Usage());
    }

  if (streq(qa_options->InputFile(), qa_options->OutputFile()))
    {
      Fatal(Program, "Input and output file names are identical\n");
    }

  // Should also check for suspect extensions .qg, .qi, .qs, .ql, .qx
  asm_string_table = new ASMStringTable;
  if (asm_string_table == NULL)
    {
      OutOfMemory(__FUNCTION__);
    }

  predicate_code_blocks = new vector<CodeBlock *>;
  if (predicate_code_blocks == NULL)
    {
      OutOfMemory(__FUNCTION__);
    }

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
  Fatal(__FUNCTION__, "%s\n", s);
}
