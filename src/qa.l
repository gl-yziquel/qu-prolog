%option noyywrap
%{
/*
 * Copyright (C) 1990, 1996
 *
 * Department of Computer Science,
 * University of Queensland
 */

#include <iostream.h>

#include "asm_objects.h"
#include "errors.h"
#include "instructions.h"
#include "string.h"

#define RETURN_INSTR(opcode, token)					\
	do {								\
	  yylval.instruction =						\
            new ASMInt<Code::InstructionSizedType>(opcode);		\
	  if (yylval.instruction == NULL)				\
	    {								\
              OutOfMemory(Program);					\
	    }								\
									\
	  return token;							\
	} while (0)

void read_comment(void);

size_t read_atom(char *, const size_t);

%}
%%
put_x_variable		RETURN_INSTR(PUT_X_VARIABLE, put_x_variable);
put_y_variable		RETURN_INSTR(PUT_Y_VARIABLE, put_y_variable);
put_x_value		RETURN_INSTR(PUT_X_VALUE, put_x_value);
put_y_value		RETURN_INSTR(PUT_Y_VALUE, put_y_value);
put_constant		RETURN_INSTR(PUT_CONSTANT, put_constant);
put_integer		RETURN_INSTR(PUT_INTEGER, put_integer);
put_list		RETURN_INSTR(PUT_LIST, put_list); 
put_structure		RETURN_INSTR(PUT_STRUCTURE, put_structure);
put_x_object_variable	RETURN_INSTR(PUT_X_OBJECT_VARIABLE, put_x_object_variable);
put_y_object_variable	RETURN_INSTR(PUT_Y_OBJECT_VARIABLE, put_y_object_variable);
put_x_object_value	RETURN_INSTR(PUT_X_OBJECT_VALUE, put_x_object_value);
put_y_object_value	RETURN_INSTR(PUT_Y_OBJECT_VALUE, put_y_object_value);
put_quantifier		RETURN_INSTR(PUT_QUANTIFIER, put_quantifier);
check_binder		RETURN_INSTR(CHECK_BINDER, check_binder);
put_substitution	RETURN_INSTR(PUT_SUBSTITUTION, put_substitution);
put_x_term_substitution	RETURN_INSTR(PUT_X_TERM_SUBSTITUTION, put_x_term_substitution);
put_y_term_substitution	RETURN_INSTR(PUT_Y_TERM_SUBSTITUTION, put_y_term_substitution);
put_initial_empty_substitution	RETURN_INSTR(PUT_INITIAL_EMPTY_SUBSTITUTION, put_initial_empty_substitution);
get_x_variable		RETURN_INSTR(GET_X_VARIABLE, get_x_variable);
get_y_variable		RETURN_INSTR(GET_Y_VARIABLE, get_y_variable);
get_x_value		RETURN_INSTR(GET_X_VALUE, get_x_value);
get_y_value		RETURN_INSTR(GET_Y_VALUE, get_y_value);
get_constant		RETURN_INSTR(GET_CONSTANT, get_constant);
get_integer		RETURN_INSTR(GET_INTEGER, get_integer);
get_list		RETURN_INSTR(GET_LIST, get_list);
get_structure		RETURN_INSTR(GET_STRUCTURE, get_structure);
get_structure_frame	RETURN_INSTR(GET_STRUCTURE_FRAME, get_structure_frame);
get_x_object_variable	RETURN_INSTR(GET_X_OBJECT_VARIABLE, get_x_object_variable);
get_y_object_variable	RETURN_INSTR(GET_Y_OBJECT_VARIABLE, get_y_object_variable);
get_x_object_value	RETURN_INSTR(GET_X_OBJECT_VALUE, get_x_object_value);
get_y_object_value	RETURN_INSTR(GET_Y_OBJECT_VALUE, get_y_object_value);
unify_x_variable	RETURN_INSTR(UNIFY_X_VARIABLE, unify_x_variable);
unify_y_variable	RETURN_INSTR(UNIFY_Y_VARIABLE, unify_y_variable);
unify_x_ref		RETURN_INSTR(UNIFY_X_REF, unify_x_ref);
unify_y_ref		RETURN_INSTR(UNIFY_Y_REF, unify_y_ref);
unify_x_value		RETURN_INSTR(UNIFY_X_VALUE, unify_x_value);	
unify_y_value		RETURN_INSTR(UNIFY_Y_VALUE, unify_y_value);
unify_constant		RETURN_INSTR(UNIFY_CONSTANT, unify_constant);		
unify_integer		RETURN_INSTR(UNIFY_INTEGER, unify_integer);		
unify_void		RETURN_INSTR(UNIFY_VOID, unify_void);
set_x_variable		RETURN_INSTR(SET_X_VARIABLE, set_x_variable);
set_y_variable		RETURN_INSTR(SET_Y_VARIABLE, set_y_variable);
set_x_value		RETURN_INSTR(SET_X_VALUE, set_x_value);
set_y_value		RETURN_INSTR(SET_Y_VALUE, set_y_value);
set_x_object_variable	RETURN_INSTR(SET_X_OBJECT_VARIABLE, set_x_object_variable);
set_y_object_variable	RETURN_INSTR(SET_Y_OBJECT_VARIABLE, set_y_object_variable);
set_x_object_value	RETURN_INSTR(SET_X_OBJECT_VALUE, set_x_object_value);
set_y_object_value	RETURN_INSTR(SET_Y_OBJECT_VALUE, set_y_object_value);
set_constant		RETURN_INSTR(SET_CONSTANT, set_constant);
set_integer		RETURN_INSTR(SET_INTEGER, set_integer);
set_void		RETURN_INSTR(SET_VOID, set_void);
set_object_void		RETURN_INSTR(SET_OBJECT_VOID, set_object_void);
allocate		RETURN_INSTR(ALLOCATE, wam_allocate);
deallocate		RETURN_INSTR(DEALLOCATE, wam_deallocate);
call_predicate		RETURN_INSTR(CALL_PREDICATE, call_predicate);
call_address		RETURN_INSTR(CALL_ADDRESS, call_address);
call_escape		RETURN_INSTR(CALL_ESCAPE, call_escape);
execute_predicate	RETURN_INSTR(EXECUTE_PREDICATE, execute_predicate);
execute_address		RETURN_INSTR(EXECUTE_ADDRESS, execute_address);
execute_escape		RETURN_INSTR(EXECUTE_ESCAPE, execute_escape);
noop			RETURN_INSTR(NOOP, noop);
jump			RETURN_INSTR(JUMP, jump);
proceed			RETURN_INSTR(PROCEED, proceed);
fail			RETURN_INSTR(FAIL, wam_fail);
halt			RETURN_INSTR(HALT, halt);
exit			RETURN_INSTR(EXIT, wam_exit);
try_me_else		RETURN_INSTR(TRY_ME_ELSE, try_me_else);
retry_me_else		RETURN_INSTR(RETRY_ME_ELSE, retry_me_else);
trust_me_else_fail	RETURN_INSTR(TRUST_ME_ELSE_FAIL, trust_me_else_fail);
try			RETURN_INSTR(TRY, wam_try);
retry			RETURN_INSTR(RETRY, retry);
trust			RETURN_INSTR(TRUST, trust);
neck_cut		RETURN_INSTR(NECK_CUT, neck_cut);
get_x_level		RETURN_INSTR(GET_X_LEVEL, get_x_level);
get_y_level		RETURN_INSTR(GET_Y_LEVEL, get_y_level);
cut			RETURN_INSTR(CUT, cut);
switch_on_term		RETURN_INSTR(SWITCH_ON_TERM, switch_on_term);
switch_on_constant	RETURN_INSTR(SWITCH_ON_CONSTANT, switch_on_constant);
switch_on_structure	RETURN_INSTR(SWITCH_ON_STRUCTURE, switch_on_structure);
switch_on_quantifier	RETURN_INSTR(SWITCH_ON_QUANTIFIER, switch_on_quantifier);
pseudo_instr0		RETURN_INSTR(PSEUDO_INSTR0, pseudo_instr0);	
pseudo_instr1		RETURN_INSTR(PSEUDO_INSTR1, pseudo_instr1);	
pseudo_instr2		RETURN_INSTR(PSEUDO_INSTR2, pseudo_instr2);	
pseudo_instr3		RETURN_INSTR(PSEUDO_INSTR3, pseudo_instr3);	
pseudo_instr4		RETURN_INSTR(PSEUDO_INSTR4, pseudo_instr4);	
pseudo_instr5		RETURN_INSTR(PSEUDO_INSTR5, pseudo_instr5);

[[:space:]]+		/* Skip whitespace */

%.*$			/* Comment: Skip till \n */

"/*"  			read_comment();

'			{
				static char buf[ATOM_LENGTH];

				const int len = read_atom(buf, ATOM_LENGTH);
				if (len == -1)
				{
				  Fatal(__FUNCTION__, "bad atom");
				}
				yylval.atom_name = new String(buf);
				if (yylval.atom_name == NULL)
				  {
                                    OutOfMemory(Program);
				  }

				return ATOM_TOKEN;
			}

end			{
				/* End of predicate tag */
				return END_TOKEN;
			}

[[:digit:]]+		{
				yylval.number_value = atoi(yytext);
				return NUMBER_TOKEN;
			}

"$"([_[:alnum:]])+	{
  				yylval.label_name = new String(yytext);

				if (yylval.label_name == NULL)
				  {
                                    OutOfMemory(Program);
				  }

				return LABEL_TOKEN;
			}

":"			|
"-"			|
"["			|
"]"			|
"("			|
")"			|
"/"			|
","			{
				/* Punctuation */
				return yytext[0];
			}

.			{
				/* Unrecognised character */
				fprintf(stderr,
					"Bad character in input %c\n",
					yytext[0]);
			}

%%

void read_comment(void)
{
  int c, d;

  c = yyinput();
  
  if (c == EOF)
    {
      Fatal(Program, "unexpected EOF in comment");
    }
  
  d = yyinput();
  
  if (d == EOF)
    {
      Fatal(Program, "unexpected EOF in comment");
    }
  
  while (!(c == '*' && d == '/'))
    {
      c = d;
      
      d = yyinput();
      
      if (d == EOF)
	{
	  Fatal(Program, "unexpected EOF in comment");
	}
    }
}

size_t read_atom(char *buf, const size_t len)
{
  unsigned i = 0;
  bool done = false;

  int c = yyinput();

  while(!done && i < len - 1)
    {
      if(c == '\'')
	{
	  c = yyinput();
	  done = (c != '\'');
	}

      if(!done)
	if(c == '\n') 
	  {
	    buf[i++] = '\n';
	    c = yyinput();
	  }
	else if (c == '\t')
	  {
	    buf[i++] = '\t';
	    c = yyinput();
	  }
	else if (c == '\\')
	  {
	    c = yyinput();
	    switch (c)
	      {
	      case 'a':
		buf[i++] = '\a';
		c = yyinput();
		break;
	      case 'b':
		buf[i++] = '\b';
		c = yyinput();
		break;
	      case 'f':
		buf[i++] = '\f';
		c = yyinput();
		break;
	      case 'n':
		buf[i++] = '\n';
		c = yyinput();
		break;
	      case 'r':
		buf[i++] = '\r';
		c = yyinput();
		break;
	      case 't':
		buf[i++] = '\t';
		c = yyinput();
		break;
	      case 'v':
		buf[i++] = '\v';
		c = yyinput();
		break;
	      case '\\':
		buf[i++] = '\\';
		c = yyinput();
		break;
	      case '\'':
		buf[i++] = '\'';
		c = yyinput();
		break;
	      case '\"':
		buf[i++] = '\"';
		c = yyinput();
		break;
	      default:
		buf[i++] = '\\';
		break;
	      }
	  }
	else			
	  {
	    buf[i++] = c;
	    c = yyinput();
	  }
    }
  
  unput(c);

  if(i > len - 1) 
    {
      Fatal(Program, "atom too long (>%d chars) %s\n", i, buf);
    }

  buf[i] = '\0';

  return i;
}
