%{
#include <math.h>
#include "objects.h"
#include "heap_qp.h"
#include "name_table.h"
#include "atom_table.h"
#include "pedro_env.h"
#include "pedro_token.h"

YY_BUFFER_STATE buffstate;



#define YY_DECL int scanner(Thread* th, AtomTable* atoms, VarMap* vmap, Object** val, bool remember)
%}

%option noyywrap

DIGIT [0-9]
LOWER [a-z]
UPPER [A-Z]

%%
[0-9]+"."[0-9]+("e"|"e+"|"e-")[0-9]+  { *val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }
[0-9]+"."[0-9]+("E"|"E+"|"E-")[0-9]+  { *val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }
[0-9]+("e"|"e+"|"e-")[0-9]+  { *val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }
[0-9]+("E"|"E+"|"E-")[0-9]+  { *val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }
[0-9]+"."[0-9]+  { *val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }

"-"[0-9]+"."[0-9]+("e"|"e+"|"e-")[0-9]+  {*val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }
"-"[0-9]+"."[0-9]+("E"|"E+"|"E-")[0-9]+  {*val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }
"-"[0-9]+("e"|"e+"|"e-")[0-9]+  { *val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }
"-"[0-9]+("E"|"E+"|"E-")[0-9]+  { *val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }
"-"[0-9]+"."[0-9]+  { *val = th->TheHeap().newDouble(atof(yytext)); return TERM_TOKEN; }

[0-9]+    { *val = th->TheHeap().newInteger(atoi(yytext)); return TERM_TOKEN; }
"-"[0-9]+ { *val = th->TheHeap().newInteger(atoi(yytext)); return TERM_TOKEN; }




"("        { return OBRA_TOKEN; }
")"        { return CBRA_TOKEN; }
","        { return COMMA_TOKEN; }
"["        { return OSBRA_TOKEN; }
"]"        { return CSBRA_TOKEN; }


[_A-Z][A-Za-z0-9_]*  {
                      if (yytext[0] == '_') {
                        if (yytext[1] == '\0') *val = th->TheHeap().newVariable();
                        else *val = vmap->getVar(&(th->TheHeap()), atoms->add(yytext));
                      }
                      else if (remember) {
                        Atom* a = atoms->add(yytext);
                        *val = th->getNames().getVariable(a);
                        if (*val == NULL) {
                          *val = th->TheHeap().newVariable(true);
                          th->getNames().setNameNewVar(a, *val, *th);
                        }
                      }
                      else *val = vmap->getVar(&(th->TheHeap()), atoms->add(yytext));
                      return TERM_TOKEN; }

[a-z][A-Za-z0-9_]*  { *val = atoms->add(yytext); return TERM_TOKEN; }

"'"[^'\\]*("\\".[^'\\]*)*"'"  { 
                          int size = strlen(yytext);
                          char* copy = new char[size];
                          strncpy(copy, yytext+1, size-2);
                          copy[size-2] = '\0';
                          *val = atoms->add(copy); 
                          delete [] copy;
                          return TERM_TOKEN; 
                         }

"\""[^\"\\]*("\\".[^\"\\]*)*"\""  { 
                          int size = strlen(yytext);
                          char* copy = new char[size];
                          strncpy(copy, yytext+1, size-2);
                          copy[size-2] = '\0';
                          *val = th->TheHeap().newStringObject(copy); 
                          delete [] copy;
                          return TERM_TOKEN; }

[-/+*<=>#@$\\^&~`:.?!;]+  { *val = atoms->add(yytext); return TERM_TOKEN; }

"\n" { return NEWLINE_TOKEN; }
[ \t]+

. { return ERROR_TOKEN; } 

%%

void set_buffstate(char* buff, int size)
{
    buffstate = yy_scan_buffer(buff, size);
}

void delete_buffstate()
{
    yy_delete_buffer(buffstate);
}

/*
int
atomNeedsQuotes(const char *s)
{
  s++;
  if (strcmp(s, "'") == 0)
    {
      return(1);
    }
  else if ((strcmp(s, "[]'") == 0) ||
           (strcmp(s, ";'") == 0))
    {
      return(0);
    }
  else if (strchr("abcdefghijklmnopqrstuvwxyz", *s) != NULL)
    {
      s++;
      while(*s != '\0')
        {
          if (strchr("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789", *s) !=
          NULL)
            {
              //
              // index finds the given character in the 'safe'
              // range.  So check the next character.
              // 
              s++;
            }
          else
            {
              return (strcmp(s, "'") != 0);
            }
        }
      return(0);
    }
  else
    {
      while(*s != '\0')
        {
          if (strchr("#$&*+-./:<=>?@^~\\", *s) != NULL)
            {
              //
              // index finds the given character in the 'safe'
              // range.  So check the next character.
              // 
              s++;
            }
          else
            {
              return (strcmp(s, "'") != 0);
            }
        }
      return(0);
    }
}
*/
