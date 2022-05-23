#ifndef PGMTILE
#define PGMTILE


int main(int argc, char **argv);
int tile(pgm *pgmStruct, pgm *tilePgmStruct, char *inputFile, int tileFactor);
int checkExtension(char *fileName);

int pgmStructInit(pgm *pgmStruct);
#endif