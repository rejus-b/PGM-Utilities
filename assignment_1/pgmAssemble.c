/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

/* header for pgm structures		*/
#include "pgmStruct.h"

/* header for reading the error code */
#include "errors.h"

/* header for openReadFile			 */
#include "openReadFile.h"

/* header for openWriteFile			*/
#include "openWriteFile.h"

/* header for pgmAssemble				*/
#include "pgmAssemble.h"

/*************************************/
/* main routine                      */
/*                                   */
/* CLI parameters:                   */
/* argv[0]: executable name          */
/* argv[1]: output file name         */
/* argv[2]: output file width	     */
/* argv[3]: output file height       */
/* argv[4]: rowStart			     */
/* argv[5]: columnStart			     */
/* argv[6]: input file			     */
/* argv[4] - argv[6] can repeat		 */
/* returns 0 on success              */
/* non-zero error code on fail       */
/*************************************/

int main(int argc, char **argv)
	{ /* main() */

	/* check for no input/output args */
	if (argc == 1)
	{/* print a bad usage message */
		printf("Usage: %s outputImage.pgm width height (row column inputImage.pgm)+", argv[0]);
		/* return no errors */
		return EXIT_NO_ERRORS;
	}

	/* check for correct number of arguments */
	if (argc < 6 || argc % 3 != 1)	
		{ /* wrong arg count */
		/* print an error message */
		printf("ERROR: Bad Argument Count");
		/* and return an error code */
		return EXIT_WRONG_ARG_COUNT;
		} /* wrong arg count */

	/* malloc for an input pgm structure, which corresponds to argv[6] then pass it into pgmStructInit() */ 
	pgm *inputPgmStruct = NULL;
	inputPgmStruct = ((pgm*) malloc (sizeof(pgm)));
	pgmStructInit(inputPgmStruct);

	/* malloc for a canvas pgm structure, which corresponds to argv[1] then pass it into pgmStructInit() */ 
	pgm *canvasPgmStruct = NULL;
	canvasPgmStruct = ((pgm*) malloc (sizeof(pgm)));
	pgmStructInit(canvasPgmStruct);

    /* this is to check that the input file is a valid file name */
	for (int fileArg = 6; fileArg < argc; fileArg += 3)
	{	
		if (readFile(argv[fileArg], inputPgmStruct) != 0)
		{
			/* exit the code */
			printf("ERROR: Bad File Name (%s)", argv[fileArg]);
			return EXIT_BAD_INPUT_FILE;
		}
	}
	
	/* set dimensions of the canvas as the user input output file dimension values */
	canvasPgmStruct->width = atoi(argv[2]);
	canvasPgmStruct->height = atoi(argv[3]);

	/* malloc a 2D array to store the image data of the pgm that will be writen to */
	canvasPgmStruct->imageData = (unsigned char **) malloc(canvasPgmStruct->height * sizeof(unsigned char*));
	for (int row = 0; row < canvasPgmStruct->width; row++)
	{
		canvasPgmStruct->imageData[row] = (unsigned char *) malloc (canvasPgmStruct->width * sizeof(unsigned char));
	}

	/* make the start row and column -1 as if these do not change, you know the assembley did not work */
	int rowStart = -1;
	int columnStart = -1;
	char *inputFile = "";
	for (int fileArg = 4; fileArg < argc; fileArg++)
	{
		/* this detects for every input file */
		if(fileArg % 3 == 0)
		{
			/* set the canvas pgm's magic number to the same as the last input image so that there is no conflict when assembling either ASCII or binary */
			inputFile = argv[fileArg];

			/* read in the image data from the input image then have it assemble onto the canvas */
			readFile(inputFile, inputPgmStruct);
			canvasPgmStruct->magic_number[0] = inputPgmStruct->magic_number[0];
			canvasPgmStruct->magic_number[1] = inputPgmStruct->magic_number[1];
			assemble(canvasPgmStruct, inputPgmStruct, rowStart, columnStart, inputFile);
		}
		/* reads in every row starting position to assemble an image */
		if (fileArg % 3 == 1)
		{
			rowStart = atoi(argv[fileArg]);
		}
		/* reads in every column starting position to assemble an image */
		if (fileArg % 3 == 2)
		{
			columnStart = atoi(argv[fileArg]);
		}
	}

	/* create a pgm of the canvas with all the sub-image data after all the files have been scanned */
	if (writeFile(argv[1], canvasPgmStruct) == 0)
	{
		/* If it works print 'ASSEMBLED' */
		printf("ASSEMBLED");

		/* at this point, we are done and can exit with a success code */
		return EXIT_NO_ERRORS;
	}
} /* main() */

int assemble(pgm *canvasPgmStruct, pgm *inputPgmStruct, int rowOrigin, int colOrigin, char *fileName)
{ /* assemble()	*/
	for (int row = 0; row < inputPgmStruct->height; row++)
	{
		for (int col = 0; col < inputPgmStruct->width; col++)
		{
			canvasPgmStruct->imageData[rowOrigin + row][colOrigin + col] = inputPgmStruct->imageData[row][col];			
		}
	}
	return EXIT_NO_ERRORS;
} /* assemble()	*/

