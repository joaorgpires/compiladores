/* picking up the code from Duarte */
%{
#include "y.tab.h"
#include <stdlib.h>
%}

digit    [0-9]
alpha    [a-zA-Z]

%%
"int"                                {return TokenTInt;}    /* Types */
"bool"                               {return TokenTBool;}

"if"                                 {return TokenIf;}      /* If */
"else"                               {return TokenElse;}

"while"                              {return TokenWhile;}   /* While */

{digit}+                             {yylval = atoi(yytext); /* Types and variables */
				      return TokenInt; }

"true"                               {return TokenTrue;}
"false"                              {return TokenFalse;}

{alpha}({alpha}|{digit})*            {yylval.id = strdup(yytext);
				      return TokenVar;}
%%

int yywrap(void){return 1;}