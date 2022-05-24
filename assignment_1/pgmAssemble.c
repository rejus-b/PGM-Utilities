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


int main(int argc, char **argv)
	{ 
	/* main() */

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
		/* print an error message        */
		printf("ERROR: Bad Argument Count");
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
		} /* wrong arg count */

	/* malloc for a structure then pass it into pgmStructInit() */ 
	pgm *pgmStruct = NULL;
	pgmStruct = ((pgm*) malloc (sizeof(pgm)));
	pgmStructInit(pgmStruct);
	
    /* this is too check that the input file is a valid file name */
	for (int i = 0; i < argc; i += 3)
	{	
		if (readFile(argv[6+i], pgmStruct) != 0)
		{
			/* exit the code */
			printf("ERROR: Bad File Name (%s)", argv[1]);
			return EXIT_BAD_INPUT_FILE;
		}
	}

	/* If it works print 'ASSEMBLED'*/
	printf("ASSEMBLED");

	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;
} /* main() */

