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
    FILE *outputFile = fopen (fileName, "w");

	/* write magic number, size & gray value */
	size_t nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", pgmStruct->width, pgmStruct->height, pgmStruct->maxGray);

    /* allocate the data pointer             */
    long nImageBytes = pgmStruct->width * pgmStruct->height * sizeof(unsigned char);

    // /* print in ASCII the header data of the pgm file to the output pgm */
    // fprintf(outputFile, "P2\n%d %d\n%d\n", pgmStruct->width, pgmStruct->height, pgmStruct->maxGray);

		for (unsigned char *nextGrayValue = pgmStruct->imageData; nextGrayValue < pgmStruct->imageData + nImageBytes; nextGrayValue++)
		{ /* per gray value */
        
			/* get next char's column        */
			int nextCol = (nextGrayValue - pgmStruct->imageData + 1) % pgmStruct->width;

			/* write the entry & whitespace  */
			nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n') );

			/* sanity check on write         */
			if (nBytesWritten < 0)
				{ /* data write failed   */
				/* free memory           */
				free(pgmStruct->commentLine);
				free(pgmStruct->imageData);

				/* print error message   */
				printf("ERROR: Output Failed (%s)\n", fileName);	

				/* return an error code  */
				return EXIT_OUTPUT_FAILED;
				} /* data write failed   */
		} /* per gray value */
	

    /* be tidy, clean up and close the file */
    fclose(outputFile);

    return EXIT_NO_ERRORS;
} /* b2a() */
