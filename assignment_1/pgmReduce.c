/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

/* header for including string operations	*/
#include <string.h>

/* header for pgm structures		*/
#include "pgmStruct.h"

/* header for reading the error code */
#include "errors.h"

/* header for openReadFile			 */
#include "openReadFile.h"

/* header for openWriteFile			*/
#include "openWriteFile.h"

/* header for pgmReduce             */
#include "pgmReduce.h"


/*************************************/
/* main routine                      */
/*                                   */
/* CLI parameters:                   */
/* argv[0]: executable name          */
/* argv[1]: input file name          */
/* argv[2]: integer reduction factor */
/* argv[3]: output file name         */
/* returns 0 on success              */
/* non-zero error code on fail       */
/*************************************/


int main(int argc, char **argv)
	{ 
	/* main() */

	/* check for no input/output args */
	if (argc == 1)
	{/* print a bad usage message */
		printf("Usage: %s inputImage.pgm reduction_factor outputImage.pgm", argv[0]);
		/* return no errors */
		return EXIT_NO_ERRORS;
	}

	/* check for correct number of arguments */
	if (argc != 4)	
		{ /* wrong arg count */
		/* print an error message        */
		printf("ERROR: Bad Argument Count");
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
	} /* wrong arg count */

	/* malloc for a structure then pass it into pgmStructInit() */ 
	pgm *pgmStruct = NULL;
	pgmStruct = ((pgm*) malloc (sizeof(pgm)));
	pgmStructInit(pgmStruct);

	/* initialising a new structure that will store the reduced pgm image */
	pgm *reducedPgmStruct = NULL;
	reducedPgmStruct = ((pgm*) malloc (sizeof(pgm)));
	pgmStructInit(reducedPgmStruct);


    /* this is too check that the input file is a valid file name */
	if (readFile(argv[1], pgmStruct) != 0)
    { /* invalid file name */
        /* free the structures initialised at the start */
		free(pgmStruct);
		free(reducedPgmStruct);
        /* exit the code */
        printf("ERROR: Bad File Name (%s)", argv[1]);
        return EXIT_BAD_INPUT_FILE;
    } /* invalid file name */

	/* this converts the string integer factor to an integer */
	int integerFactor = atoi(argv[2]);

    /* this checks that the integer factor is valid (less than 1, or greater than dimensions) */
	if (integerFactor < 1 || integerFactor  > pgmStruct->width || integerFactor  > pgmStruct->height)
    {
        /* free the structures initialised at the start */
		free(pgmStruct);
		free(reducedPgmStruct);
        /* exit the code */
        printf("ERROR: Miscellaneous (Bad integer reduction factor)");
        return EXIT_MISCELLANEOUS;
    }

    /* this runs the code to actually reduce the code */
    if (reduce(pgmStruct, reducedPgmStruct, argv[1], integerFactor, argv[3]) == 0)
    {
        /* free the structures initialised at the start */
		free(pgmStruct);
		free(reducedPgmStruct);
        /* if no errors occur print 'REDUCED' */
        printf("REDUCED");
    }

	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;
	} /* main() */


int reduce(pgm *pgmStruct, pgm *reducedPgmStruct, char *inputFile, int reductionFactor, char *outputFile)
{ /* reduce() */

	/* calcualting the size of the new pgm file */
	reducedPgmStruct->width = (pgmStruct->width + reductionFactor -1) / reductionFactor;
	reducedPgmStruct->height = (pgmStruct->height + reductionFactor -1) / reductionFactor;

	/* malloc data for a new structure to store the reduced image */
	reducedPgmStruct->imageData = (unsigned char **) malloc(reducedPgmStruct->height * sizeof(unsigned char*));

	/* malloc for a new array inside the first array to make a 2D array */
	for (int row = 0; row < reducedPgmStruct->width; row++)
	{
		reducedPgmStruct->imageData[row] = (unsigned char *) malloc(reducedPgmStruct->width * sizeof(unsigned char));
	}

	/* initialises the variables that count for the reduced image, they are initialised seperatley as they should only be incremented in cases
		where the pixel was read succesfully */
	int colCount = 0;
	int nextCol = 0;
	int rowCount = 0;

	/* loops through the reduced image */
	for (int row = 0; row < pgmStruct->height; row++)
	{
		rowCount = 0;
		for (int col = 0; col < pgmStruct->width; col++)
		{
			/* if the gray value MODULUS the reduction factor is 0 we are at the right gray value to copy */
			if (row % reductionFactor == 0 && col % reductionFactor == 0)
			{
				reducedPgmStruct->imageData[colCount][rowCount] = pgmStruct->imageData[row][col];
				rowCount ++;
				nextCol = 1;
			}
		}
		/* if any data has been read in this row then move onto the next row of image data */
		if (nextCol == 1)
		{
			colCount++;
			nextCol = 0;
		}
	}

	/* assigns the reduced image the same magic number as the original */
	reducedPgmStruct->magic_number[0] = pgmStruct->magic_number[0];
	reducedPgmStruct->magic_number[1] = pgmStruct->magic_number[1];

	/* write to an output file the reduced image */
	writeFile(outputFile, reducedPgmStruct);

	/* return on success */
    return EXIT_NO_ERRORS;

} /* reduce() */
