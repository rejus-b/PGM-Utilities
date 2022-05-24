#ifndef PGMASSEMBLE
#define PGMASSEMBLE

int main(int argc, char **argv);
int pgmStructInit(pgm *pgmStruct);

int assemble(pgm *canvasPgmStruct, pgm *inputPgmStruct, int rowOrigin, int colOrigin);

#endif