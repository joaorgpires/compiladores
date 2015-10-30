/* parser to be done here */

%{

%}

%union
{
  int intVal;
  char *strVal;
}

%token <intVal> NUM
%token <strVal> VAR
%token PLUS
%token MINUS
%token TIMES
%token DIV
%left MINUS PLUS
%left TIMES DIV

%%
exp :    NUM                  { $$ = $1;       }
      |  exp '+' exp          {                }
      |  exp '-' exp          {                }
      |  exp '*' exp          {                }
      |  exp '/' exp          {                }
