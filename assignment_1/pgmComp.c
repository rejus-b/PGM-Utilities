
//* library for I/O routines        */
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
    /* check for correct number of arguments */
    if (argc != 3)
	{ /* wrong arg count */
		/* print an error message        */
		printf("ERROR: Bad Argument Count\n");
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

    // /* pass the first pgm to be read from */
    if (readFile(argv[1], pgmStructFileOne) == 0)
	{
		/* pass the second pgm to be read from */
		if (readFile(argv[2], pgmStructFileTwo) == 0)
		{
			/* If no errors are thrown when reading the two data files, see if they are equivelant */
			if (equivalence(pgmStructFileOne, pgmStructFileTwo) == 0)
			{
				printf("IDENTICAL \n");
				return EXIT_NO_ERRORS;
			}
			else 
			{
				printf("DIFFERENT \n");
				return EXIT_NO_ERRORS;
			}
		}
	}

} /* main() */


int equivalence(pgm *pgmStructFileOne, pgm *pgmStructFileTwo)
{ /* equivalence()	*/

	/* check that the width of the two input files is equivalent */
	if (pgmStructFileOne->width != pgmStructFileTwo->width )
	{
		printf("ERROR: Miscellaneous Width Not Equivalent \n");
		return EXIT_MISCELLANEOUS;
	}

	/* check that the height of the two input files is equivalent */
	else if (pgmStructFileOne->height != pgmStructFileTwo->height)
	{
		printf("ERROR: Miscellaneous Height Not Equivalent \n");
		return EXIT_MISCELLANEOUS;
	}

	/* check that the maxGray of the two input files is equivalent */
	else if (pgmStructFileOne->maxGray != pgmStructFileTwo->maxGray)
	{
		printf("ERROR: Miscellaneous Max Gray Not Equivalent \n");
		return EXIT_MISCELLANEOUS;
	}

	/* allocate the data pointer for one structure, this does not need to be done twice as you only have to read the data pointer once            */ 
	long nImageBytes = pgmStructFileOne->width * pgmStructFileTwo->height * sizeof(unsigned char);

	/* check that each pixel is equivalent  */
	if (memcmp(pgmStructFileOne->imageData, pgmStructFileTwo->imageData, nImageBytes) != 0)
	{
		printf("ERROR: Miscellaneous Image Data Not Equivalent \n");
		return EXIT_MISCELLANEOUS;			
	}

	return EXIT_NO_ERRORS;

} /* equivalence()	*/

/* A function for initialising all the values of each pgm image */
int pgmStructInit(pgm *pgmStruct) 
	{ /* pgmStructInit() */

	/* variables for storing the image   */

	/* the magic number		         	 */
	/* stored as two bytes to avoid	     */
	/* problems with endianness	         */
	/* Raw:    0x5035 or P5		         */
	/* ASCII:  0x5032 or P2		         */
	pgmStruct->magic_number[0] = '0';
	pgmStruct->magic_number[1] = '0';
	pgmStruct->magic_Number = NULL;
	
	/* we will store ONE comment	         */
	pgmStruct->commentLine = NULL;

	/* the logical width & height	         */
	/* note: cannot be negative	         */
	pgmStruct->width = 0, pgmStruct->height = 0;

	/* maximum gray value (assumed)	         */
	/* make it an integer for ease	         */
	pgmStruct->maxGray = 255;

	/* pointer to raw image data	         */
	pgmStruct->imageData = NULL;
	
	/* If there were no errors assigning the variables in the structure then --return 0-- to signify no errors */
	return EXIT_NO_ERRORS;
} /* pgmStructInit() */