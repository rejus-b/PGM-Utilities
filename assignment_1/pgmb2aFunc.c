/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

/* header for pgm structures		*/
#include "pgmStruct.h"

/* header for reading the error code */
#include "errors.h"

/* header for openWriteFile			*/
#include "openWriteFile.h"

/* header for pgma2bFunc            */
#include "pgma2bFunc.h"


int b2a(pgm *pgmStruct, char *fileName, char *inputFileName)
{ /* b2a() */
    /* open the outputfile in a writeable format */
    FILE *outputFile = fopen (fileName, "w");

		/* write to the file the header data */
		fprintf(outputFile, "P2\n%d %d\n%d\n", pgmStruct->width, pgmStruct->height, pgmStruct->maxGray);

		/* loops through all the image data */
		for (int i = 0; i < pgmStruct->height; i++)
		{
			int colCount = 0;
			for (int j = 0; j < pgmStruct->width; j++)
			{
				/* finds the next column location */
				int nextCol = (colCount - pgmStruct->imageData[i][j] + 1) % pgmStruct->width;

				/* write the entry & whitespace  */
				int nBytesWritten = fprintf(outputFile, "%d%c", pgmStruct->imageData[i][j], (nextCol ? ' ' : '\n') );
				colCount++;

				/* sanity check on write         */
				if (nBytesWritten < 0)
					{ /* data write failed   */
					/* free memory           */
					free(pgmStruct->commentLine);
					free(pgmStruct->imageData);

					/* print error message   */
					printf("ERROR: Output Failed (%s)", fileName);	

					/* return an error code  */
					return EXIT_OUTPUT_FAILED;
					/* data write failed   */
					}
			} /* per row*/
		
		} /* per column */
	

    /* be tidy, clean up and close the file */
    fclose(outputFile);

    return EXIT_NO_ERRORS;
} /* b2a() */
