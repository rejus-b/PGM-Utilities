CC=gcc
CCFLAGS = -g -std=c99 -Wall -Werror
MAINS = pgmEcho.o 
MODULES = openReadFile.o
TARGETS = pgmEcho

all:	${TARGETS}

pgmEcho:	pgmEcho.o ${MODULES}
	${CC} ${CCFLAGS} -o pgmEcho pgmEcho.o ${MODULES}

pgmEcho.o:	pgmEcho.c	pgmEcho.h	pgmStruct.h	errors.h	openReadFile.h
	${CC} -c ${CCFLAGS} -o pgmEcho.o pgmEcho.c

openReadFile.o:		openReadFile.c		pgmStruct.h	errors.h	openReadFile.h
	${CC} -c ${CCFLAGS} -o openReadFile.o openReadFile.c

clean:
	rm ${TARGETS} ${MAINS} ${MODULES}


