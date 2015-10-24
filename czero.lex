/* scanner for a toy Pascal-like language */
%option noyywrap     
%{
         /* need this for the call to atof() below */
         #include <math.h>
%}
     
DIGIT    [0-9]
ID       [a-z][a-z0-9]*
OPENP    [(]
CLOSEP   [)]
OPENB    [{]
CLOSEB   [}]
POINTER  [*][a-z][a-z0-9]*
%%

{DIGIT}+    {
  printf( "TokenInt\tt%s\n", yytext,
	  atoi( yytext ) );
       }

{DIGIT}+"."{DIGIT}*        {
	   printf( "A float: %s (%g)\n", yytext,
		   atof( yytext ) );
			   }

if      printf("TokenIf\n", yytext );
else    printf("TokenElse\n",yytext);
while   printf("TokenWhile\n",yytext);

true|false {
  printf( "TokenBool\t%s\n", yytext);
}

         {OPENP}     printf("TokenOpenp\n",yytext);
	 {CLOSEP}    printf("TokenCloseP\n",yytext);
         {ID}        printf("TokenString\t%s\n", yytext);
         {POINTER}   printf("TokenPointer\t%s\n", yytext);
"+"   printf( "TokenPlus\n", yytext );
"-"   printf( "TokenMinus\n", yytext );
"*"   printf( "TokenTimes\n", yytext );
"/"   printf( "TokenDivide\n", yytext );
"{"   printf( "TokenOpenB\n",yytext);
"}"   printf( "TokenCloseB\n",yytext);
"="   printf("TokenAtribute\n",yytext);
"=="  printf("TokenCompare\n",yytext);
"<"   printf("TokenLess\n",yytext);
">"   printf("TokenGreater\n",yytext);
"<="  printf("TokenLessE\n",yytext);
">="  printf("TokenGreaterE\n",yytext);
";"   printf("TokenSemiColon\n",yytext);
"{"[\^{}}\n]*"}"     /* eat up one-line comments */

[ \t\n]+          /* eat up whitespace */

.           printf( "Unrecognized character: %s\n", yytext );

%%

int main( int argc, char **argv )
{
  ++argv, --argc;  /* skip over program name */
  if ( argc > 0 )
    yyin = fopen( argv[0], "r" );
  else
    yyin = stdin;
  
  yylex();
}
