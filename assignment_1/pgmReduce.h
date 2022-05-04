#ifndef PGMREDUCE
#define PGMREDUCE

int main(int argc, char **argv);
int reduce(pgm *pgmStruct, char *inputFile, int reductionFactor, char *outputFile);

int pgmStructInit(pgm *pgmStruct);

#endif