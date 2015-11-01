/* picking up the code from Duarte QUANDO COMPILAR DEPOIS NO BISON USAR FLAG -d PARA TER UM FICHEIRO .h QUE VAI TER OS TOKENS TODOS. INCULUIR ISSO AQUI E GARANTE-SE QUE OS TOKENS SAO IGUAIS */
%{
#include "y.tab.h"
#include <stdlib.h>
%}

digit    [0-9]
alpha    [a-zA-Z]

%%
   /* Types */
"int"                                {return INT;}
"bool"                               {return BOOL;}

   /*If and Else */
"if"                                 {return IF;}
"else"                               {return ELSE;}

   /* While */
"while"                              {return WHILE;}

   /* Types and variables */
{digit}+                             {yylval.intVal = atoi(yytext);
				      return NUM; }

"true"                               {return TRUE;}      
"false"                              {return FALSE;}

{alpha}({alpha}|{digit})*            {yylval.strVal = strdup(yytext);
				      return VAR;}

   /* Arithmetic Expressions */
"+"                                  {return PLUS;}
"-"                                  {return MINUS;}
"*"                                  {return TIMES;}
"/"                                  {return DIV;}
"%"                                  {return MOD;}
"("                                  {return LP;}
")"                                  {return RP;}
"{"                                  {return LB;}
"}"                                  {return RB;}
";"                                  {return SC;}
","                                  {return COM;}

   /* Boolean Expressions */
"!"                                  {return NEG;}
"||"                                 {return OR;}
"&&"                                 {return AND;}
"=="                                 {return EQ;}
"<"                                  {return GT;}
">"                                  {return LT;}
"<="                                 {return LE;}
">="                                 {return GE;}
"!="                                 {return NEQ;}

   /* Anything else */
.                                    {printf("Lexical error: %s\n", yytext);
                                      exit(1);}

%%

int yywrap(void){return 1;}
