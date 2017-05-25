# Seongwoo Choi
# scho29
# 1368039
# Winter 2017 
# CMPS 111
# Prof. Darrell Long

CC		= cc -ansi
PROG	= shell

${PROG}:	myshell.o lex.yy.o
	${CC} -o ${PROG} myshell.o lex.yy.o

shell.o:	myshell.c
	${CC} -c shell.c

lex.yy.o:	lex.yy.c
	${CC} -c lex.yy.c

lex.yy.c:	lex.c
	flex lex.c

clean:		${PROG}
	rm lex.yy.o myshell.o lex.yy.c ${PROG}

