/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

/* header for pgm structures		*/
#include "pgmStruct.h"

/* header for reading the error code */
#include "errors.h"

int openFile(char *fileName)
{

	/* now start reading in the data         */
	/* try to open the file for text I/O     */
	/* in ASCII mode b/c the header is text  */
	FILE *inputFile = fopen(fileName, "r");

	/* if it fails, return error code        */
	if (inputFile == NULL)
	{
		printf("ERROR: Bad File Name %s\n", fileName);
		return EXIT_BAD_INPUT_FILE;
	}

}