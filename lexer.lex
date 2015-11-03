/* picking up the code from Duarte QUANDO COMPILAR DEPOIS NO BISON USAR FLAG -d PARA TER UM FICHEIRO .h QUE VAI TER OS TOKENS TODOS. INCULUIR ISSO AQUI E GARANTE-SE QUE OS TOKENS SAO IGUAIS */
%{
#include "abssyn.h"
#include "parser.tab.h"
#include <stdlib.h>
%}

digit    [0-9]
alpha    [a-zA-Z]

%%
   /* New Program */
"main"                               {return MAIN;}
"return 0"                           {return RETURN;}

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

"true"                               {yylval.boolVal = true;
				      return BOOLVAL;}      
"false"                              {yylval.boolVal = false;
				      return BOOLVAL;}

{alpha}({alpha}|{digit})*            {strcpy(yylval.strVal, yytext);
				      return VAR;}

   /* Atrib */
"="                                  {return ATTR;}

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
"?"                                  {return QM;}
":"                                  {return COL;}

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
"\n"                                 {}
"\t"                                 {}
" "                                  {}
.                                    {printf("Lexical error\n");
                                      exit(1);}

%%

int yywrap(void){return 1;}
