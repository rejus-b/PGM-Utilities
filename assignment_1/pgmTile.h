#ifndef PGMTILE
#define PGMTILE

int main(int argc, char **argv);
int tile(pgm *pgmStruct, pgm *tilePgmStruct, char *inputFile, int tileFactor, const char *extension);

#endif