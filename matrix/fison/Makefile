FLAGS=-O0 -g
all: calc.x

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c lex.yy.h: scanner.l parser.tab.h
	flex scanner.l

calc.x: lex.yy.c lex.yy.h parser.tab.c parser.tab.h
	g++ ${FLAGS} main.c parser.tab.c lex.yy.c matrix.cpp -o calc.x

clean:
	rm calc.x lex.yy.c lex.yy.h parser.tab.c parser.tab.h *.o
