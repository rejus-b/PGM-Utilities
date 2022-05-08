/* 
To convert from ASCII to binary fscanf() automatically converts the input data to binary, if I just fwrite it out to a file it will keep the binary representation

So I can try use the read file to read in the data and pass it through the write file, hopefully it stays in binary representation?


Make a struct for pgm -> then read with the default read file assinging the pgm struct values -> then write to it using fwrite
*/


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

    /* check that the magic number is not already P5, which is the magic number for raw pgm */
    if (pgmStruct->magic_number[1] != '2')
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