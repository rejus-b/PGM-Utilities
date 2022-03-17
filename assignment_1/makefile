CC=gcc
CCFLAGS = -g -std=c99 -Wall -Werror
MAINS = pgmEcho.o pgmComp.o pgma2b.o
MODULES = openReadFile.o openWriteFile.o pgma2bFunc.o
TARGETS = pgmEcho pgmComp pgma2b

all:	${TARGETS}



pgmEcho:	pgmEcho.o ${MODULES}
	${CC} ${CCFLAGS} -o pgmEcho pgmEcho.o ${MODULES}

pgmComp:	pgmComp.o ${MODULES}
	${CC} ${CCFLAGS} -o pgmComp pgmComp.o ${MODULES}

pgma2b:		pgma2b.o ${MODULES}
	${CC} ${CCFLAGS} -o pgma2b pgma2b.o ${MODULES}



pgmEcho.o:	pgmEcho.c	pgmEcho.h	openReadFile.o	openWriteFile.o
	${CC} -c ${CCFLAGS} -o pgmEcho.o pgmEcho.c

pgmComp.o:	pgmComp.c
	${CC} -c ${CCFLAGS} -o pgmComp.o pgmComp.c

pgma2b.o:	pgma2b.c	pgma2b.h	pgma2bFunc.h
	${CC} -c ${CCFLAGS} -o pgma2b.o	pgma2b.c



openReadFile.o:		openReadFile.c		pgmStruct.h	errors.h	openReadFile.h
	${CC} -c ${CCFLAGS} -o openReadFile.o	openReadFile.c

openWriteFile.o:	openWriteFile.c		pgmStruct.h	errors.h	openWriteFile.h
	${CC} -c ${CCFLAGS} -o openWriteFile.o	openWriteFile.c

pgma2bFunc.o:	pgma2bFunc.c	pgmStruct.h	errors.h	openWriteFile.h
	${CC} -c ${CCFLAGS} -o pgma2bFunc.o	pgma2bFunc.c	



clean:
	rm ${TARGETS} ${MAINS} ${MODULES}


