CC=gcc
CCFLAGS = -g -std=c99 -Wall -Werror
MAINS = pgmEcho.o 
MODULES =
TARGETS = pgmEcho

all:	${TARGETS}

pgmEcho:	pgmEcho.o ${MODULES}
	${CC} ${CCFLAGS} -o pgmEcho pgmEcho.o ${MODULES}

pgmEcho.o:	pgmEcho.c	pgmEcho.h	pgmStruct.h
	${CC} -c ${CCFLAGS} -o pgmEcho.o pgmEcho.c

clean:
	rm ${TARGETS} ${MAINS} ${MODULES}


