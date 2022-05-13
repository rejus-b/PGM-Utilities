/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

/* header for including string operations	*/
#include <string.h>

/* header for pgm structures		*/
#include "pgmStruct.h"

/* header for reading the error code */
#include "errors.h"

/* header for openReadFile macros */
#include "openReadFile.h"

int magicNumCheck(unsigned short *magic_Number, FILE *inputFile, char *fileName)
{ /* magicNumCheck()	*/
	/* sanity check on the magic number      */
	/* sanity checks on size & grays         */
	/* must read exactly three values        */
	if (*magic_Number != MAGIC_NUMBER_ASCII_PGM && *magic_Number != MAGIC_NUMBER_RAW_PGM)
		{ /* failed magic number check   */
		/* be tidy: close the file       */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Bad Magic Number (%s)", fileName);	
		
		/* and return                    */
		exit(EXIT_BAD_MAGIC_NUMBER);
	} /* failed magic number check   */

	return EXIT_NO_ERRORS;
} /* magicNumCheck()	*/

int imageMallocCheck(FILE *inputFile, pgm *pgmStruct)
{	/* imageMallocCheck()	*/
	/* sanity check for memory allocation    */
	for (int i = 0; i < pgmStruct->width; i++)
	{
		if (pgmStruct->imageData[i] == NULL)	
		{ /* malloc failed */
		/* free up memory                */
		free(pgmStruct->commentLine);

		/* close file pointer            */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Image Malloc Failed");	
		
		/* return error code             */
		exit(EXIT_IMAGE_MALLOC_FAILED);
		} /* malloc failed */
	}
	return 0;
}

int readFile(char *fileName, pgm *pgmStruct)
{ /* openReadFile()		*/

	/* now start reading in the data         */
	/* try to open the file for text I/O     */
	/* in ASCII mode b/c the header is text  */
	FILE *inputFile = fopen(fileName, "r");

	/* if it fails, return error code        */
	if (inputFile == NULL)
	{
		printf("ERROR: Bad File Name (%s)", fileName);
		exit(EXIT_BAD_INPUT_FILE);
	}

	/* read in the magic number              */
	pgmStruct->magic_number[0] = getc(inputFile);
	pgmStruct->magic_number[1] = getc(inputFile);
	pgmStruct->magic_Number = (unsigned short *) pgmStruct->magic_number;
	
	/* checks that the magic number is valid */
	magicNumCheck(pgmStruct->magic_Number, inputFile, fileName);
	
	/* scan whitespace if present            */
	int scanCount = fscanf(inputFile, " ");

	/* check for a comment line              */
	char nextChar = fgetc(inputFile);
	if (nextChar == '#')
		{ /* comment line                */
		/* allocate buffer               */
		pgmStruct->commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH +2 );
		/* fgets() reads a line          */
		/* capture return value          */
		char *commentString = fgets(pgmStruct->commentLine, MAX_COMMENT_LINE_LENGTH + 2, inputFile);
		/* NULL means failure            */
		if (commentString == NULL || strlen(commentString) > 128)
			{ /* NULL comment read   */
			/* free memory           */
			free(pgmStruct->commentLine);
			/* close file            */
			fclose(inputFile);

			/* print an error message */
			printf("ERROR: Bad Comment Line (%s)", fileName);	
		
			/* and return            */
			exit(EXIT_BAD_COMMENT_LINE);
			} /* NULL comment read   */
		} /* comment line */
	else
	{ 	
		/* not a comment line			 */
		/* put character back            */
		ungetc(nextChar, inputFile);
	} /* not a comment line 			*/


	/* read in width, height, grays          */
	/* whitespace to skip blanks             */
	scanCount = fscanf(inputFile, " %u %u %u ", &(pgmStruct->width), &(pgmStruct->height), &(pgmStruct->maxGray));

	if 	(
		(scanCount != 3				)	||
		(pgmStruct->width 	< MIN_IMAGE_DIMENSION	) 	||
		(pgmStruct->width 	> MAX_IMAGE_DIMENSION	) 	||
		(pgmStruct->height < MIN_IMAGE_DIMENSION	) 	||
		(pgmStruct->height > MAX_IMAGE_DIMENSION	)		
		)
		{ /* failed size sanity check    */
		/* free up the memory            */
		free(pgmStruct->commentLine);

		/* be tidy: close file pointer   */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Bad Dimensions (%s)", fileName);	
		
		/* and return                    */
		exit(EXIT_BAD_DIMENSIONS);
		} /* failed size sanity check    */

	if (pgmStruct->maxGray != 255)
	{ /* failed maxGray sanity check	*/
		/* free up the memory 				*/
		free(pgmStruct->commentLine);

		/* be tidy: close file pointer   */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Bad Max Gray Value (%s)", fileName);	
		
		/* and return                    */
		exit(EXIT_BAD_MAX_GRAY_VALUE);
		} /* failed maxGray sanity check    */
	

	/* mallocing for a 2D array, malloc a 1D array first, then malloc arrays into this array */
	pgmStruct->imageData = (unsigned char **) malloc(pgmStruct->height * sizeof(unsigned char*));
	for (int i = 0; i < pgmStruct->width; i++)
	{
		pgmStruct->imageData[i] = (unsigned char *) malloc (pgmStruct->width * sizeof(unsigned char));
	}

	/* sanity check for memory allocation    */
	imageMallocCheck(inputFile, pgmStruct);

	if (pgmStruct->magic_number[1] == '2')
	{
		for (int i = 0; i < pgmStruct->height; i++)
		{
			for (int j = 0; j < pgmStruct->width; j++)
			{				
				// 	/* read next value               */
					int grayValue = -1;
					int scanCount = fscanf(inputFile, " %u", &grayValue);

					/* sanity check too little data		*/
					if (scanCount > (pgmStruct->width*pgmStruct->height))
					{
						/* free memory			*/
						free(pgmStruct->commentLine);
						free(pgmStruct->imageData);

						/* print error message */
						printf("ERROR: Bad Data (%s)", fileName);

						/* exit with error code */
						exit(EXIT_BAD_DATA);
					}


					/* sanity check	                 */
					if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255))
						{ /* fscanf failed */
						/* free memory           */
						free(pgmStruct->commentLine);
						free(pgmStruct->imageData);	

						/* close file            */
						fclose(inputFile);

						/* print error message   */
						printf("ERROR: Bad Gray Value");	
					
						/* and return            */
						return EXIT_MISCELLANEOUS;
						} /* fscanf failed */

					/* set the pixel value           */
					pgmStruct->imageData[i][j] = (unsigned char) grayValue;
				}
			}

			/* try read from the file again, if another file is read return that there is too much data */
			int grayValue = -1;
			scanCount = fscanf(inputFile, " %u", &grayValue);
		
			/* sanity check	                 */
			if ((scanCount != -1))
			{ /* fscanf failed */
				/* free memory           */
				free(pgmStruct->commentLine);
				free(pgmStruct->imageData);	
		
				/* close file            */
				fclose(inputFile);
		
				/* print error message */
				printf("ERROR: Bad Data (%s)", fileName);
			
				/* exit with error code */
				exit(EXIT_BAD_DATA);
			} /* fscanf failed */
		}

		
	/* if the magic number is binary read in binary data */
	else if (pgmStruct->magic_number[1] == '5'){
		/* loop through the image data to be fread, reading in a row at a time */
		for (int i = 0; i < pgmStruct->height; i++)
		{
			/* this tests for too little data */
			if (fread(pgmStruct->imageData[i], sizeof(unsigned char), pgmStruct->width, inputFile) == 0)
			{
				free(pgmStruct->commentLine);
				free(pgmStruct->imageData);	
		
				/* close file            */
				fclose(inputFile);
		
				/* print error message */
				printf("ERROR: Bad Data (%s)", fileName);
			
				/* exit with error code */
				exit(EXIT_BAD_DATA);
			}
		}
	}

	/* we're done with the file, so close it */
	fclose(inputFile);

	return EXIT_NO_ERRORS;

} /* openReadFile()		*/
