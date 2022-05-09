/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

/* header for including string operations	*/
#include <string.h>

/* header for pgmEcho				*/
#include "pgmEcho.h"

/* header for pgm structures		*/
#include "pgmStruct.h"

/* header for reading the error code */
#include "errors.h"

/* header for openReadFile			 */
#include "openReadFile.h"

/* header for pgma2b                */
#include "pgma2b.h"

/* header for pgma2bFunc            */
#include "pgma2bFunc.h"


/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/


int main (int argc, char **argv)
{ /* main() */

	/* check for no input/output args */
	if (argc == 1)
	{/* print a bad usage message */
		printf("Usage: %s inputImage.pgm outputImage.pgm", argv[0]);
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

    /* malloc for a structure then pass it into pgmStructInit() */ 
    pgm *pgmStruct = NULL;
	pgmStruct = ((pgm*) malloc (sizeof(pgm)));
	pgmStructInit(pgmStruct);


    /* check that the file can be read successfully*/
    if (readFile(argv[1], pgmStruct) != 0)
    {
        /* return that the file could not be read from */
        printf("ERROR: Bad File Name (%s)", argv[1]);
        return EXIT_BAD_INPUT_FILE;
    }

    /* check that the magic number is not already P2, which is the magic number for raw pgm */
    if (pgmStruct->magic_number[1] != '2' && pgmStruct->magic_number[2] != '2')
    {
        /* return that the magic number was wrong */
        printf("ERROR: Bad Magic Number (%s)", argv[1]);
        return EXIT_BAD_MAGIC_NUMBER;
    }


    /* call a function to write the input ASCII pgm as a raw pgm to the output fille */
    if (a2b(pgmStruct, argv[2]) == 0)
    {
        /* return that it was sucessfully converted */
        printf("CONVERTED");
        return EXIT_NO_ERRORS;
    }
} /* main() */
