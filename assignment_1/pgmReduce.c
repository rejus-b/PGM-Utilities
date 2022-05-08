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
	/* check for correct number of arguments */
	if (argc != 4)	
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
        printf("ERROR: Bad File Name (%s)\n", argv[1]);
        return EXIT_BAD_INPUT_FILE;
    }

    /* this checks that the integer factor is valid (less than 1, or greater than dimensions) */
	if (reduc_factor < 1 || reduc_factor  > pgmStruct->width || reduc_factor  > pgmStruct->height)
    {
        /* exit the code */
        printf("ERROR: Miscellaneous (Bad integer reduction factor)\n");
        return EXIT_MISCELLANEOUS;
    }


    /* this runs the code to actually reduce the code */
    if (reduce(pgmStruct, reducedPgmStruct, argv[1], reduc_factor, argv[3]) == 0)
    {
        /* if no errors occur print 'REDUCED' */
        printf("REDUCED\n");
    }


	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;
	} /* main() */


int reduce(pgm *pgmStruct, pgm *reducedPgmStruct, char *inputFile, int reductionFactor, char *outputFile)
{
/* reduce() */

/* 12 MOD 5 = 2
        MY CURRENT IDEA : convert binary files to ASCII first then I can read via the gray values and then rewrite it skipping certain data points
                            this could be achieved possibly by e.g. rewriting the pgmStruct-> ImageData to only include set points
                            or make a custom openWriteFile that only writes certain points 
							
			I realise the previous idea might be much harder to implement based off the fact we also deal with binary files, writing specific parts
				of these is not the same as with ASCII. While I could convert the file to ASCII then use pgmb2a this would be very inefficient code
				and/or would have me restructure my whole pgmUtilities to allow this without actually making files.
				
			So I suppose in the end im going to have to use the 2D array approach and just restructure image data to only have the required data */

	//printf(" %i ", pgmStruct->imageData[2]);
 

	/* logic is that you create a new array for a secondary imageData set. 
		Now you calculat the width/height for this new imageData set with formula : (oldWidth  + factor -1) / factor 

		iterate over the old image data traversing n+factor, base case n=0 to get the imageData[x] that translates to the new imageData set[x] 
	*/




	/* calcualting the size of the new pgm file */
	reducedPgmStruct->width = (pgmStruct->width + reductionFactor -1) / reductionFactor;
	reducedPgmStruct->height = (pgmStruct->height + reductionFactor -1) / reductionFactor;
	
	/* mallocing the nessecary amount of data for the new pgm files image data */
	long nImageBytes = reducedPgmStruct->width * reducedPgmStruct->height * sizeof(unsigned char);
	reducedPgmStruct -> imageData = (unsigned char *) malloc(nImageBytes);


	/* use a double for loop to traverse a 2D array containing the original image data */
	// int reducedImage[reducedPgmStruct->width][reducedPgmStruct->height];


		/* COULD IT BE A PROBLEM LATER DOWN THE LINE THAT I am looping through the reduced imageData and just moving along the original imageData by a 
			a factor instead of directly looping through the original imageData
		*/

	printf("%i, %i \n",reducedPgmStruct->width, reducedPgmStruct->height);
	/* this will be used to count what part of the imageData array we are currently corresponding to on a 2d array */
	int count = 0;
	int newImageCount = 0;
	for (int i=0; i < reducedPgmStruct->height; i ++)
	{

	// if (i + reductionFactor > reducedPgmStruct->height)
	// {
	// 	i+= reductionFactor;
	// }


	// IIMPROVE THIS BY HAVING A SEPERATE COUNT FOR KNOWING WHICH PART OF THE IMAGE DATA from PGM STRUCT WE ARE READING


	// = reductionFactor REMOVING THIS CODE FROM THE 'j++' makes the first row work 
		for (int j=0; j < reducedPgmStruct->width ; j ++)
		{
			/* if the rows pass the total width skip to next row */          // REMOVING these out of bound reset checks made the first row fully work
			// if (reducedPgmStruct->width - j < reductionFactor)
			// {
			// 	count += count % j;
			// 	break;
			// }
			

			reducedPgmStruct->imageData[newImageCount] = pgmStruct->imageData[count];
			count += reductionFactor;
			newImageCount ++;
		
			
		}

		
		// count += reducedPgmStruct->width;
	}

	/* sets the reduced images magic number to the original magic number */
	reducedPgmStruct->magic_number[0] = pgmStruct->magic_number[0];
	reducedPgmStruct->magic_number[1] = pgmStruct->magic_number[1];

	// printf("%i\n", reducedImage[reducedPgmStruct->width][reducedPgmStruct->height]);

	// IMPORTANT: I believe reducedPgmStruct is incomplete since passing along pgmStruct allows the file to be written to
	writeFile(outputFile, reducedPgmStruct);


    return EXIT_NO_ERRORS;

} /* reduce() */




/* A function for initialising all the values of each pgm image */
int pgmStructInit(pgm *pgmStruct) 
	{
	/* pgmStructInit() */

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