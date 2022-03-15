/***********************************/
/* COMP 1921M Programming Project  */
/* 2021-22 Spring Semester         */
/*                                 */
/* Hamish Carr                     */
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

// int magicNumberReader(int magNum)
// {

// }

int main(int argc, char **argv)
	{ 
	/* main() */
	/* check for correct number of arguments */
	if (argc != 3)	
		{ /* wrong arg count */
		/* print an error message        */
		printf("ERROR: Bad Argument Count\n");
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
		} /* wrong arg count */
	



	/* MALLOC for a structure then pass it into pgmStructInit() */ 
	pgm *pgmStruct;
	pgmStruct = ((pgm*) malloc (sizeof(pgm)));
	pgmStructInit(pgmStruct);


	/* now start reading in the data         */
	/* try to open the file for text I/O     */
	/* in ASCII mode b/c the header is text  */
	FILE *inputFile = fopen(argv[1], "r");

	/* if it fails, return error code        */
	if (inputFile == NULL)
	{
		printf("ERROR: Bad File Name %s\n", argv[1]);
		return EXIT_BAD_INPUT_FILE;
	}

	/* read in the magic number              */
	pgmStruct->magic_number[0] = getc(inputFile);
	pgmStruct->magic_number[1] = getc(inputFile);
	pgmStruct->magic_Number = (unsigned short *) pgmStruct->magic_number;
	
	/* sanity check on the magic number      */
	if (*magic_Number != MAGIC_NUMBER_ASCII_PGM)
		{ /* failed magic number check   */
		/* be tidy: close the file       */
		fclose(inputFile);

		/* print an error message */
		printf("Error: Failed to read pgm image from file %s\n", argv[1]);	
		
		/* and return                    */
		return EXIT_BAD_INPUT_FILE;
		} /* failed magic number check   */

	/* scan whitespace if present            */
	int scanCount = fscanf(inputFile, " ");

	/* check for a comment line              */
	char nextChar = fgetc(inputFile);
	if (nextChar == '#')
		{ /* comment line                */
		/* allocate buffer               */
		commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH);
		/* fgets() reads a line          */
		/* capture return value          */
		char *commentString = fgets(, MAX_COMMENT_LINE_LENGTH, inputFile);
		/* NULL means failure            */
		if (commentString == NULL)
			{ /* NULL comment read   */
			/* free memory           */
			free(commentLine);
			/* close file            */
			fclose(inputFile);

			/* print an error message */
			printf("Error: Failed to read pgm image from file %s\n", argv[1]);	
		
			/* and return            */
			return EXIT_BAD_INPUT_FILE;
			} /* NULL comment read   */
		} /* comment line */
	else
		{ /* not a comment line */
		/* put character back            */
		ungetc(nextChar, inputFile);
		} /* not a comment line */

	/* read in width, height, grays          */
	/* whitespace to skip blanks             */
	scanCount = fscanf(inputFile, " %u %u %u", &(width), &(height), &(maxGray));

	/* sanity checks on size & grays         */
	/* must read exactly three values        */
	if 	(
		(scanCount != 3				)	||
		(width 	< MIN_IMAGE_DIMENSION	) 	||
		(width 	> MAX_IMAGE_DIMENSION	) 	||
		(height < MIN_IMAGE_DIMENSION	) 	||
		(height > MAX_IMAGE_DIMENSION	) 	||
		(maxGray	!= 255		)
		)
		{ /* failed size sanity check    */
		/* free up the memory            */
		free(commentLine);

		/* be tidy: close file pointer   */
		fclose(inputFile);

		/* print an error message */
		printf("Error: Failed to read pgm image from file %s\n", argv[1]);	
		
		/* and return                    */
		return EXIT_BAD_INPUT_FILE;
		} /* failed size sanity check    */

	/* allocate the data pointer             */
	long nImageBytes = width * height * sizeof(unsigned char);
	imageData = (unsigned char *) malloc(nImageBytes);

	/* sanity check for memory allocation    */
	if (imageData == NULL)
		{ /* malloc failed */
		/* free up memory                */
		free(commentLine);

		/* close file pointer            */
		fclose(inputFile);

		/* print an error message */
		printf("Error: Failed to read pgm image from file %s\n", argv[1]);	
		
		/* return error code             */
		return EXIT_BAD_INPUT_FILE;
		} /* malloc failed */

	/* pointer for efficient read code       */
	for (unsigned char *nextGrayValue = imageData; nextGrayValue < imageData + nImageBytes; nextGrayValue++)
		{ /* per gray value */
		/* read next value               */
		int grayValue = -1;
		int scanCount = fscanf(inputFile, " %u", &grayValue);

		/* sanity check	                 */
		if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255))
			{ /* fscanf failed */
			/* free memory           */
			free(commentLine);
			free(imageData);	

			/* close file            */
			fclose(inputFile);

			/* print error message   */
			printf("Error: Failed to read pgm image from file %s\n", argv[1]);	
		
			/* and return            */
			return EXIT_BAD_INPUT_FILE;
			} /* fscanf failed */

		/* set the pixel value           */
		*nextGrayValue = (unsigned char) grayValue;
		} /* per gray value */

	/* we're done with the file, so close it */
	fclose(inputFile);

	/* open a file for writing               */
	FILE *outputFile = fopen(argv[2], "w");

	/* check whether file opening worked     */
	if (outputFile == NULL)
		{ /* NULL output file */
		/* free memory                   */
		free(commentLine);
		free(imageData);

		/* print an error message        */
		printf("Error: Failed to write pgm image to file %s\n", argv[2]);	

		/* return an error code          */
		return EXIT_BAD_OUTPUT_FILE;
		} /* NULL output file */
	
	/* write magic number, size & gray value */
	size_t nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", width, height, maxGray);

	/* check that dimensions wrote correctly */
	if (nBytesWritten < 0)
		{ /* dimensional write failed    */
		/* free memory                   */
		free(commentLine);
		free(imageData);

		/* print an error message        */
		printf("Error: Failed to write pgm image to file %s\n", argv[2]);	

		/* return an error code          */
		return EXIT_BAD_OUTPUT_FILE;
		} /* dimensional write failed    */

        /* pointer for efficient write code      */
        for (unsigned char *nextGrayValue = imageData; nextGrayValue < imageData + nImageBytes; nextGrayValue++)
                { /* per gray value */
		/* get next char's column        */
		int nextCol = (nextGrayValue - imageData + 1) % width;

		/* write the entry & whitespace  */
		nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n') );

		/* sanity check on write         */
		if (nBytesWritten < 0)
			{ /* data write failed   */
			/* free memory           */
			free(commentLine);
			free(imageData);

			/* print error message   */
			printf("Error: Failed to write pgm image to file %s\n", argv[2]);	

			/* return an error code  */
			return EXIT_BAD_OUTPUT_FILE;
			} /* data write failed   */
		} /* per gray value */

	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;
	} /* main() */






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
	return(0);
} /* pgmStructInit() */