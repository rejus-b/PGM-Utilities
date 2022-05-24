
/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

/* header for including string operations	*/
#include <string.h>

/* header for pgmComp				*/
#include "pgmComp.h"

/* header for pgm structures		*/
#include "pgmStruct.h"

/* header for reading the error code */
#include "errors.h"

/* header for openReadFile			 */
#include "openReadFile.h"



/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: first file name        */
/* argv[2]: second file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/



int main(int argc, char **argv)
{ /* main() */

	/* check for no input/output args */
	if (argc == 1)
	{/* print a bad usage message */
		printf("Usage: %s inputImage.pgm inputImage.pgm", argv[0]);
		/* return no errors */
		return EXIT_NO_ERRORS;
	}

    /* check for correct number of arguments */
    if (argc != 3)
	{ /* wrong arg count */
		/* print an error message        */
		printf("ERROR: Bad Argument Count");
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
	} /* wrong arg count */

	/* malloc for a structure for the first input file then pass it into pgmStructInit() */ 
	pgm *pgmStructFileOne = NULL;
	pgmStructFileOne = ((pgm*) malloc (sizeof(pgm)));
	pgmStructInit(pgmStructFileOne);
	
	
    /* malloc for a structure for the second input file then pass it into pgmStructInit() */ 
	pgm *pgmStructFileTwo = NULL;
	pgmStructFileTwo = ((pgm*) malloc (sizeof(pgm)));
	pgmStructInit(pgmStructFileTwo);

    /* pass the first pgm to be read from */
    if (readFile(argv[1], pgmStructFileOne) == 0)
	{
		/* pass the second pgm to be read from */
		if (readFile(argv[2], pgmStructFileTwo) == 0)
		{
			/* If no errors are thrown when reading the two data files, see if they are equivelant */
			if (equivalence(pgmStructFileOne, pgmStructFileTwo) == 0)
			{
				/* free the structures initialised at the start */
				free(pgmStructFileOne);
				free(pgmStructFileTwo);
				/* image compared succesfully identical, print 'IDENTICAL' */
				printf("IDENTICAL");
				return EXIT_NO_ERRORS;
			}
			else 
			{
				/* free the structures initialised at the start */
				free(pgmStructFileOne);
				free(pgmStructFileTwo);
				/* image compared  succesfully different, print 'DIFFERENT' */
				printf("DIFFERENT");
				return EXIT_NO_ERRORS;
			}
		}
	}

} /* main() */


int equivalence(pgm *pgmStructFileOne, pgm *pgmStructFileTwo)
{ /* equivalence()	*/
	/* check that the maxGray of the two input files is equivalent */
	if (pgmStructFileOne->magic_number[0] != pgmStructFileTwo->magic_number[0])
	{
		return EXIT_MISCELLANEOUS;
	}

	if (pgmStructFileOne->width != pgmStructFileTwo->width )
	{
		return EXIT_MISCELLANEOUS;
	}

	else if (pgmStructFileOne->height != pgmStructFileTwo->height)
	{
		return EXIT_MISCELLANEOUS;
	}

	/* check that the maxGray of the two input files is equivalent */
	else if (pgmStructFileOne->maxGray != pgmStructFileTwo->maxGray)
	{
		return EXIT_MISCELLANEOUS;
	}


	/* compares each pixel's image data against one another */
	for (int i = 0; i < pgmStructFileOne->height; i++)
	{
		for (int j = 0; j < pgmStructFileOne->width; j++)
		{
			if (pgmStructFileOne->imageData[i][j] != pgmStructFileTwo->imageData[i][j])
			{
				return EXIT_MISCELLANEOUS;
			}
		}
	}
	
	return EXIT_NO_ERRORS;

} /* equivalence()	*/
