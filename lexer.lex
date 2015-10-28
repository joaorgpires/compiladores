/* picking up the code from Duarte QUANDO COMPILAR DEPOIS NO BISON USAR FLAG -d PARA TER UM FICHEIRO .h QUE VAI TER OS TOKENS TODOS. INCULUIR ISSO AQUI E GARANTE-SE QUE OS TOKENS SAO IGUAIS */
%{
#include "y.tab.h"
#include <stdlib.h>
%}

digit    [0-9]
alpha    [a-zA-Z]

%%
"int"                                {return TokenTInt;}      /* Types */
"bool"                               {return TokenTBool;}

"if"                                 {return TokenIf;}        /* If */
"else"                               {return TokenElse;}

"while"                              {return TokenWhile;}     /* While */

{digit}+                             {yylval = atoi(yytext);  /* Types and variables */
				      return TokenInt; }

"true"                               {return TokenTrue;}      
"false"                              {return TokenFalse;}

{alpha}({alpha}|{digit})*            {yylval.id = strdup(yytext);
				      return TokenVar;}
%%

int yywrap(void){return 1;}
