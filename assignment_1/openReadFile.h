#ifndef OPENREADFILE
#define OPENREADFILE

#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128

int readFile(char *fileName, pgm *pgmStruct);
int magicNumCheck(unsigned short *magic_Number, FILE *inputFile, char *fileName)


#endif
