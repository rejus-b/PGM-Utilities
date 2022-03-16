/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

/* header for pgm structures		*/
#include "pgmStruct.h"

/* header for reading the error code */
#include "errors.h"

/* header for openWriteFile */
#include "openWriteFile.h"



int writeFile(char *fileName, pgm *pgmStruct)
{ /* writeFile() */

	/* open a file for writing               */
	FILE *outputFile = fopen(fileName, "w");

	/* check whether file opening worked     */
	if (outputFile == NULL)
		{ /* NULL output file */
		/* free memory                   */
		free(pgmStruct->commentLine);
		free(pgmStruct->imageData);

		/* print an error message        */
		printf("Error: Failed to write pgm image to file %s\n", fileName);	

		/* return an error code          */
		return EXIT_OUTPUT_FAILED;
		} /* NULL output file */

    // return EXIT_NO_ERRORS;
}