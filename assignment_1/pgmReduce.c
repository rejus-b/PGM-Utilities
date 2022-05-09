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



	/* this converts the string integer factor to an integer */
	int reduc_factor = atoi(argv[2]);

    /* this is too check that the input file is a valid file name */
	if (readFile(argv[1], pgmStruct) != 0)
    {
        /* exit the code */
        printf("ERROR: Bad File Name (%s)", argv[1]);
        return EXIT_BAD_INPUT_FILE;
    }

    /* this checks that the integer factor is valid (less than 1, or greater than dimensions) */
	if (reduc_factor < 1 || reduc_factor  > pgmStruct->width || reduc_factor  > pgmStruct->height)
    {
        /* exit the code */
        printf("ERROR: Miscellaneous (Bad integer reduction factor)");
        return EXIT_MISCELLANEOUS;
    }


    /* this runs the code to actually reduce the code */
    if (reduce(pgmStruct, reducedPgmStruct, argv[1], reduc_factor, argv[3]) == 0)
    {
        /* if no errors occur print 'REDUCED' */
        printf("REDUCED");
    }


	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;
	} /* main() */


int reduce(pgm *pgmStruct, pgm *reducedPgmStruct, char *inputFile, int reductionFactor, char *outputFile)
{
/* reduce() */

	/* calcualting the size of the new pgm file */
	reducedPgmStruct->width = (pgmStruct->width + reductionFactor -1) / reductionFactor;
	reducedPgmStruct->height = (pgmStruct->height + reductionFactor -1) / reductionFactor;
	
	/* mallocing the nessecary amount of data for the new pgm files image data */
	long nImageBytes = reducedPgmStruct->width * reducedPgmStruct->height * sizeof(unsigned char);
	reducedPgmStruct -> imageData = (unsigned char *) malloc(nImageBytes);

	/* initalises a 2D array for storing the reduced image data */
	int reducedImage [reducedPgmStruct->width][reducedPgmStruct->height];

	/* this counts the subposition of the original image data */
	int subCount = 0;

	/* through the reduced image */
	for (int i = 0; i < reducedPgmStruct->width; i++)
	{
		/* finds the correct image data from the original image */
		subCount = pgmStruct->width * reductionFactor * i;
		for (int j = 0; j < reducedPgmStruct->height; j++)
		{
			/* assigns data to the 2D array */
			reducedImage[i][j] = pgmStruct->imageData[subCount];		

			/* increments the subCount by the reduction factor */
			subCount += reductionFactor;

		}
	}

	// /* sets the reduced images magic number to the original magic number */
	reducedPgmStruct->magic_number[0] = pgmStruct->magic_number[0];
	reducedPgmStruct->magic_number[1] = pgmStruct->magic_number[1];



	/* initalises a count for how much data is to be read */
	int writeToCount = 0;
	/* loops through the reduce image */
	for (int i = 0; i < reducedPgmStruct->height; i++)
	{
		for (int j = 0; j < reducedPgmStruct->width; j++)
		{
			/* assigns the reduced image data from the 2D array */
			reducedPgmStruct->imageData[writeToCount] = reducedImage[i][j];
			/* increment the data to be read too */
			writeToCount ++;
		}

	}

	/* write to an output file the reduced iamge */
	writeFile(outputFile, reducedPgmStruct);

	/* return on success */
    return EXIT_NO_ERRORS;

} /* reduce() */




