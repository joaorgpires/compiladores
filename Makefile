CCC = gcc
LEX = flex
YACC = bison
YFLAGS = -d

compiler: parser.tab.o lex.yy.o abssyn.o icg.o
	${CCC} lex.yy.c parser.tab.c abssyn.c icg.c -o compiler -lfl

icg.o: icg.c icg.h
	${CCC} ${CCFLAGS} -c icg.c

abssyn.o: abssyn.c abssyn.h
	${CCC} -c abssyn.c

parser.tab.o: parser.y
	${YACC} ${YFLAGS} parser.y
	${CCC} parser.tab.c -c

lex.yy.o: lexer.lex
	${LEX} lexer.lex
	${CCC} lex.yy.c -c

clean:
	/bin/rm -f lex.yy.* parser.tab.* *.o *.asm compiler
