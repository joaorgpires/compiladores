  /* parser to be done here */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("%s\n", s);
}
%}

%union
{
  int intVal;
  char strVal[100];
}

%token <intVal> NUM
%token <strVal> VAR
%token INT BOOL
%token IF ELSE
%token WHILE
%token TRUE FALSE
%token MOD
%token LP RP
%token LB RB
%token SC COM
%token NEG OR AND
%token EQ GT LT LE GE NEQ

%token PLUS
%token MINUS
%token TIMES
%token DIV

%left MINUS PLUS
%left TIMES DIV

%type <intVal> exp

%%
exp :    NUM                  { $$ = $1;       }
 //   |  exp '+' exp          {                }
 //   |  exp '-' exp          {                }
 //   |  exp '*' exp          {                }
 //   |  exp '/' exp          {                }
;
%%

main()
{
yyparse();
}
