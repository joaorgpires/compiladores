  /* parser to be done here */

%{
#include "abssyn.h"
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

%nonassoc NEG EQ GT LT LE GE NEQ

%left OR
%left AND
%left MINUS PLUS
%left TIMES DIV MOD
%left SC COM

%type <intVal, strVal> exp

%%
exp :    NUM                      { }
      |  exp PLUS exp             { }
      |  exp MINUS exp            { }
      |  exp TIMES exp            { }
      |  exp DIV exp              { }
      |  exp MOD exp              { }
      |  exp OR exp               { }
      |  exp AND exp              { }
      |  exp EQ exp               { }
      |  exp NEQ exp              { }
      |  exp LT exp               { }
      |  exp LE exp               { }
      |  exp GT exp               { }
      |  exp GE exp               { }
      |  NEG exp                  { }
      |  LP exp RP                { }
      |  VAR                      { }
;
%%

main()
{
yyparse();
}
