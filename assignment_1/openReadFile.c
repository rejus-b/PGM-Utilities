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

	/* read in the magic number              */
	pgmStruct->magic_number[0] = getc(inputFile);
	pgmStruct->magic_number[1] = getc(inputFile);
	pgmStruct->magic_Number = (unsigned short *) pgmStruct->magic_number;
	

	// Difficulty implementing the below code as you cannot simply pgmStruct->*magic_Number
	// Maybe it would work since magic_Number is just a pointer to magic_number array


	// /* sanity check on the magic number      */
	// if (*magic_Number != MAGIC_NUMBER_ASCII_PGM)
	// 	{ /* failed magic number check   */
	// 	/* be tidy: close the file       */
	// 	fclose(inputFile);

	// 	/* print an error message */
	// 	printf("Error: Failed to read pgm image from file %s\n", argv[1]);	
		
	// 	/* and return                    */
	// 	return EXIT_BAD_INPUT_FILE;
	// 	} /* failed magic number check   */

	/* scan whitespace if present            */
	int scanCount = fscanf(inputFile, " ");


}