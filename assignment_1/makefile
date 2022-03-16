CC=gcc
CCFLAGS = -g -std=c99 -Wall -Werror
MAINS = pgmEcho.o 
MODULES = openReadFile.o openWriteFile.o
TARGETS = pgmEcho

all:	${TARGETS}

pgmEcho:	pgmEcho.o ${MODULES}
	${CC} ${CCFLAGS} -o pgmEcho pgmEcho.o ${MODULES}

pgmEcho.o:	pgmEcho.c	pgmEcho.h	openReadFile.o	openWriteFile.o
	${CC} -c ${CCFLAGS} -o pgmEcho.o pgmEcho.c

openReadFile.o:		openReadFile.c		pgmStruct.h	errors.h	openReadFile.h
	${CC} -c ${CCFLAGS} -o openReadFile.o	openReadFile.c

openWriteFile.o:	openWriteFile.c		pgmStruct.h	errors.h	openWriteFile.h
	${CC} -c ${CCFLAGS} -o openWriteFile.o	openWriteFile.c

clean:
	rm ${TARGETS} ${MAINS} ${MODULES}


