
// Read the contents of the pgm into pgmStruct
// compare it with a second pgm struct
// if two attributes != then break

// malloc space for both structures then pass both into the openReadFile - Saul did the two structure approach
// or just do 1 structure and then compare the values directly after reading the second set of values

// pass by reference all the structs so that the original location data changes for them and thus can still be called through main


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



/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: first file name        */
/* argv[1]: second file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/



int main(int argc, char **argv)
{ /* main() */
    /* check for correct number of arguments */
    if (argc != 2)
	{ /* wrong arg count */
		/* print an error message        */
		printf("ERROR: Bad Argument Count\n");
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
	} /* wrong arg count */


	/* malloc for a structure for the first input file then pass it into pgmStructInit() */ 
	pgm *pgmStructFileOne = NULL;
	pgmStructFileOne = ((pgm*) malloc (sizeof(pgm)));
	pgmStructInit(*pgmStructFileOne);

    /* malloc for a structure for the second input file then pass it into pgmStructInit() */ 
	pgm *pgmStructFileTwo = NULL;
	pgmStructFileTwo = ((pgm*) malloc (sizeof(pgm)));
	pgmStructInit(*pgmStructFileTwo);


    /* pass the first pgm to be read from */
    int readFile(argv[0], *pgmStructFileOne);

    /* pass the second pgm to be read from */
    int readFile(argv[1], *pgmStructFileTwo);

    



} /* main() */




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