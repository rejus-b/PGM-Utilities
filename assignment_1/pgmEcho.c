/***********************************/
/* COMP 1921M Programming Project  */
/* 2021-22 Spring Semester         */
/*                                 */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

/* header for pgmEcho				*/
#include "pgmEcho.h"

/* header for pgm structures		*/
#include "pgmStruct.h"

/* header for reading the error code */
#include "errors.h"

/* header for openReadFile			 */
#include "openReadFile.h"

/* header for openWriteFile			*/
#include "openWriteFile.h"

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


int main(int argc, char **argv)
	{ 
	/* main() */

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

	/* invoke the function to open the file and read from it */
	/* it will also check that it succesfully wrote to the target file */
	if ((readFile(argv[1], pgmStruct) == 0 ) && (writeFile(argv[2], pgmStruct) == 0))
	{
		/* free the structures initialised at the start */
		free(pgmStruct);
		/* if it works print 'ECHOED'*/
		printf("ECHOED");
	}

	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;
	} /* main() */


