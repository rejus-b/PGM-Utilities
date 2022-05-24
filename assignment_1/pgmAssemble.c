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
/* argv[6]: inputFile			     */
/* argv[3] - argv[6] can repeat		 */
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
	if (argc < 6 && argc % 3 != 0)	
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

	/* malloc for a tile pgm structure, which corresponds to argv[1] then pass it into pgmStructInit() */ 
	// pgm *tilePgmStruct = NULL;
	// tilePgmStruct = ((pgm*) malloc (sizeof(pgm)));
	// pgmStructInit(tilePgmStruct);
	
    /* this is too check that the input file is a valid file name */
	// for (int i = 4; i < argc; i += 3)
	// {	
		if (readFile(argv[6], inputPgmStruct) != 0)
		{
			/* exit the code */
			printf("ERROR: Bad File Name (%s)", argv[6]);
			return EXIT_BAD_INPUT_FILE;
		}
	// }

	/* set the canvas pgm's magic number to the same as the last input image so that there is no conflict when assembling either ASCII or binary */
	canvasPgmStruct->magic_number[0] = inputPgmStruct->magic_number[0];
	canvasPgmStruct->magic_number[1] = inputPgmStruct->magic_number[1];
	/* set dimensions of the canvas as the user input output file dimension values */
	canvasPgmStruct->width = atoi(argv[2]);
	canvasPgmStruct->height = atoi(argv[3]);

	canvasPgmStruct->imageData = (unsigned char **) malloc(canvasPgmStruct->height * sizeof(unsigned char*));
	for (int i = 0; i < canvasPgmStruct->width; i++)
	{
		canvasPgmStruct->imageData[i] = (unsigned char *) malloc (canvasPgmStruct->width * sizeof(unsigned char));
	}

	
	for (int i = 0; i < argc; i += 3)
	{	
		readFile(argv[6+i], inputPgmStruct);
		assemble(canvasPgmStruct, inputPgmStruct, atoi(argv[4]), atoi(argv[5]));
	}


	/*  
		plan for assemble is too make a pgm file that reads the input image 
		make a second pgm file that will be a canvas for the tiles to be appended too
		a third pgm that gets constantly rewritten to contain the tiles that are being appended
	*/

	/* If it works print 'ASSEMBLED' */
	printf("ASSEMBLED");

	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;
} /* main() */

int assemble(pgm *canvasPgmStruct, pgm *inputPgmStruct, int row, int col)
{ /* assemble()	*/



	return EXIT_NO_ERRORS;
} /* assemble()	*/

