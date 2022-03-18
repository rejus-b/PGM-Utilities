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
		printf("ERROR: Bad Argument Count\n");
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
	} /* wrong arg count */

    /* malloc for a structure then pass it into pgmStructInit() */ 
    pgm *pgmStruct = NULL;
	pgmStruct = ((pgm*) malloc (sizeof(pgm)));
	pgmStructInit(pgmStruct);


    // /* check that the file can be read successfully*/
    // if (readFile(argv[1], pgmStruct) != 0)
    // {
    //     /* return that the file could not be read from */
    //     printf("ERROR: Bad File Name %s \n", argv[1]);
    //     return EXIT_BAD_INPUT_FILE;
    // }

    // /* check that the magic number is not already P2, which is the magic number for ASCII pgm */
    // printf("%c\n",pgmStruct->magic_number[1]);
    // if (pgmStruct->magic_number[1] != '5')
    // {
    //     /* return that the magic number was wrong */
    //     printf("ERROR: Bad Magic Number %s \n", argv[1]);
    //     return EXIT_BAD_MAGIC_NUMBER;
    // }


    /* call a function to write the input binary pgm as a ASCII pgm to the output fille */

    
    // if (b2a(pgmStruct, argv[1], argv[2]) == 0)
    // {
    //     /* return that it was sucessfully converted */
    //     printf("CONVERTED \n");
    //     return EXIT_NO_ERRORS;
    // }



    // FILE *inputFile = fopen (argv[1], "rb");


    readFile(argv[1], pgmStruct, 1);
    
    if (pgmStruct->magic_number[1] == '5'){
        pgmStruct->magic_number[1] = '2';
    
    //FILE *outputFile = fopen(argv[2], "w");
    writeFile(argv[2], pgmStruct);
    }
    
return EXIT_NO_ERRORS;


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