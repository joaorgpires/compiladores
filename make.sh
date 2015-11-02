flex lexer.lex
bison -d parser.y
gcc lex.yy.c parser.tab.c
