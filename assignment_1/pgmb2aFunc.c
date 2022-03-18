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


int b2a(pgm *pgmStruct, char *fileName)
{ /* b2a() */
    /* open the outputfile in a writeable format */
    FILE *outputFile = fopen (fileName, "rb");

    /* intialise the size of the image data */
    // int imageSize = (pgmStruct->width * pgmStruct->height);

    /* print in ASCII the header data of the pgm file to the output pgmn */
    fprintf(outputFile, "P2\n%d %d\n%d\n", pgmStruct->width, pgmStruct->height, pgmStruct->maxGray);

    // /* print in ASCII the image data to the output file */
    // fprintf(pgmStruct->imageData, sizeof(unsigned char), imageSize, outputFile);

    // writeFile(fileName, pgmStruct);

    /* be tidy, clean up and close the file */
    fclose(outputFile);

    return EXIT_NO_ERRORS;
} /* b2a() */


// I can put a fread wrapper to swap the magic nums around the gray readers / gray writers