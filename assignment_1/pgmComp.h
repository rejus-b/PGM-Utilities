#ifndef PGMCOMP
#define PGMCOMP

#include "pgmStruct.h"

int main(int argc, char **argv);

int pgmStructInit(pgm *pgmStruct);

int equivalence(pgm *pgmStructFileOne, pgm *pgmStructFileTwo);

#endif
