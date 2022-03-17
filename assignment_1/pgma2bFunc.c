/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

/* header for pgmEcho				*/
#include "pgmEcho.h"

/* header for pgm structures		*/
#include "pgmStruct.h"

/* header for reading the error code */
#include "errors.h"

/* header for openWriteFile			*/
#include "openWriteFile.h"

/* header for pgma2bFunc            */
#include "pgma2bFunc.h"

int a2b(pgm *pgmStruct, char *fileName)
{
    FILE *outputFile = fopen (fileName, "w");

    int imageSize = (pgmStruct->width * pgmStruct->height);

    fprintf(outputFile, "P5\n%d %d\n%d\n", pgmStruct->width, pgmStruct->height, pgmStruct->maxGray);

    fwrite(pgmStruct->imageData, sizeof(unsigned char), imageSize, outputFile);

    fclose(outputFile);

    return EXIT_NO_ERRORS;
}