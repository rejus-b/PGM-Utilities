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
{ /* a2b() */
    /* open the outputfile in a writeable format */
    FILE *outputFile = fopen (fileName, "w");

    /* intialise the size of the image data */
    // int imageSize = (pgmStruct->width * pgmStruct->height);

    /* print in ASCII the header data of the pgm file to the output pgmn */
    fprintf(outputFile, "P5\n%d %d\n%d\n", pgmStruct->width, pgmStruct->height, pgmStruct->maxGray);

    /* print in binary the image data to the output file */
    // fwrite(pgmStruct->imageData, sizeof(unsigned char), imageSize, outputFile);

    for (int i = 0; i < pgmStruct->height; i++)
    {
        fwrite(pgmStruct->imageData[i], sizeof(unsigned char), pgmStruct->width, outputFile);
    }

    /* be tidy, clean up and close the file */
    fclose(outputFile);

    return EXIT_NO_ERRORS;
} /* a2b() */