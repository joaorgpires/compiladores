  /* parser to be done here */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abssyn.h"

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
  bool boolVal;
  Exp e;
  Cmd c;
  Prg p;
}

%token <intVal> NUM
%token <strVal> VAR
%token <boolVal> BOOLVAL
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
%token ATTR
%token MAIN RETURN
%token QM COL

%token PLUS
%token MINUS
%token TIMES
%token DIV

%left OR
%left AND

%nonassoc NEG EQ GT LT LE GE NEQ

%left MINUS PLUS
%left TIMES DIV MOD
%left SC COM

%type <c> cmd
%type <e> exp
%type <p> prg
%type <c> whi

%start prg

%%

prg :    INT MAIN LP RP LB cmd RETURN SC RB    { $$ = PrgNotEps($6); printTree($$); }
      |  INT MAIN LP RP LB RETURN SC RB        { $$ = PrgEps();                     }
;

cmd :    VAR ATTR exp                          { $$ = Attr($1, $3);           }
      |  INT VAR ATTR exp                      { $$ = DecAt(Int, $2, $4);     }
      |  BOOL VAR ATTR exp                     { $$ = DecAt(Bool, $2, $4);    }
      |  INT VAR                               { $$ = Dec(Int, $2);           }
      |  BOOL VAR                              { $$ = Dec(Bool, $2);          }
      |  WHILE LP exp RP whi                   { $$ = WhileExp($3, $5);       }
      |  IF LP exp RP whi ELSE whi             { $$ = IfElseExp($3, $5, $7);  }
      |  IF LP exp RP whi                      { $$ = IfExp($3, $5);          }
      |  cmd SC                                { $$ = $1;                     }
      |  cmd SC cmd                            { $$ = CmdSeq($1, $3);         }
;

whi :    LB cmd RB                             { $$ = SCmd($2);               }
      |  cmd                                   { $$ = SCmd($1);               }
;

exp :    exp PLUS exp                          { $$ = OpExp($1, Plus, $3);    }
      |  exp MINUS exp                         { $$ = OpExp($1, Minus, $3);   }
      |  exp TIMES exp                         { $$ = OpExp($1, Times, $3);   }
      |  exp DIV exp                           { $$ = OpExp($1, Div, $3);     }
      |  exp MOD exp                           { $$ = OpExp($1, Mod, $3);     }
      |  exp OR exp                            { $$ = OpExp($1, Or, $3);      }
      |  exp AND exp                           { $$ = OpExp($1, And, $3);     }
      |  exp EQ exp                            { $$ = OpExp($1, Eq, $3);      }
      |  exp NEQ exp                           { $$ = OpExp($1, Neq, $3);     }
      |  exp LT exp                            { $$ = OpExp($1, Lt, $3);      }
      |  exp LE exp                            { $$ = OpExp($1, Le, $3);      }
      |  exp GT exp                            { $$ = OpExp($1, Gt, $3);      }
      |  exp GE exp                            { $$ = OpExp($1, Ge, $3);      }
      |  NEG exp                               { }
      |  LP exp RP                             { $$ = $2;                     }
      |  VAR                                   { $$ = VarExp($1);             }
      |  NUM                                   { $$ = NumExp($1);             }
      |  BOOLVAL                               { $$ = BoolExp($1);            }
;
%%

main()
{
yyparse();
}
