flex lexer.lex
bison -d parser.y
gcc parser.tab.c lex.yy.c abssyn.c
