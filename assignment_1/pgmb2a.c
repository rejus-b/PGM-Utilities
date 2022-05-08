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

/* header for openWriteFile			*/
#include "openWriteFile.h"

/* header for pgma2bFunc            */
#include "pgmb2aFunc.h"


int main (int argc, char **argv)
{ /* main() */
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

    /* check that the binary to ASCII conversion does not throw an error */
    if (b2a(pgmStruct, argv[2]) == 0)
    {
        /* return that it was sucessfully converted */
        printf("CONVERTED");
        return EXIT_NO_ERRORS;
    }
} /* main() */
