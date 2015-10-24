//picking up the code from Duarte
%{
#include "y.tab.h"
#include <stdlib.h>
%}

digit    [0-9]
alpha    [a-zA-Z]

%%
//Types
"int"                                {return TokenTInt;}
"bool"                               {return TokenTBool;}
//If
//While
"while"                              {return TokenWhile;}
//Types and variables
{digit}+                             {yylval = atoi(yytext);
				      return TokenInt; }
"true"                               {return TokenTrue;}
"false"                              {return TokenFalse;}
{alpha}({alpha}|{digit})*            {yylval.id = strdup(yytext);
				      return TokenVar;}
%%

int yywrap(void){return 1;}
