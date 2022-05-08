/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

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
		printf("ERROR: Bad Magic Number (%s)\n", fileName);	
		
		/* and return                    */
		exit(EXIT_BAD_MAGIC_NUMBER);
	} /* failed magic number check   */

	return EXIT_NO_ERRORS;
} /* magicNumCheck()	*/

int readFile(char *fileName, pgm *pgmStruct)
{ /* openReadFile()		*/

	/* now start reading in the data         */
	/* try to open the file for text I/O     */
	/* in ASCII mode b/c the header is text  */
	FILE *inputFile = fopen(fileName, "r");

	/* if it fails, return error code        */
	if (inputFile == NULL)
	{
		printf("ERROR: Bad File Name (%s)\n", fileName);
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
		pgmStruct->commentLine = (char *) malloc(MAX_COMMENT_LINE_LENGTH);
		/* fgets() reads a line          */
		/* capture return value          */
		char *commentString = fgets(pgmStruct->commentLine, MAX_COMMENT_LINE_LENGTH, inputFile);
		/* NULL means failure            */
		if (commentString == NULL)
			{ /* NULL comment read   */
			/* free memory           */
			free(pgmStruct->commentLine);
			/* close file            */
			fclose(inputFile);

			/* print an error message */
			printf("ERROR: Bad Comment Line (%s)\n", fileName);	
		
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
		printf("ERROR: Bad Dimensions (%s)\n", fileName);	
		
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
		printf("ERROR: Bad Max Gray Value (%s)\n", fileName);	
		
		/* and return                    */
		exit(EXIT_BAD_MAX_GRAY_VALUE);
		} /* failed maxGray sanity check    */
	

	/* allocate the data pointer             */
	long nImageBytes = pgmStruct->width * pgmStruct->height * sizeof(unsigned char);
	pgmStruct->imageData = (unsigned char *) malloc(nImageBytes);

	/* sanity check for memory allocation    */
	if (pgmStruct->imageData == NULL)
		{ /* malloc failed */
		/* free up memory                */
		free(pgmStruct->commentLine);

		/* close file pointer            */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Image Malloc Failed\n");	
		
		/* return error code             */
		exit(EXIT_IMAGE_MALLOC_FAILED);
		} /* malloc failed */

	

	if (pgmStruct->magic_number[1] == '2'){
		/* pointer for efficient read code       */
		for (unsigned char *nextGrayValue = pgmStruct->imageData; nextGrayValue < pgmStruct->imageData + nImageBytes; nextGrayValue++)
			{ /* per gray value */
			/* read next value               */
			int grayValue = -1;
			int scanCount = fscanf(inputFile, " %u", &grayValue);

			/* sanity check too little data		*/
			if (scanCount > (pgmStruct->width*pgmStruct->height))
			{
				/* free memory			*/
				free(pgmStruct->commentLine);
				free(pgmStruct->imageData);

				/* print error message */
				printf("ERROR: Bad Data (%s)\n", fileName);

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
				printf("ERROR: Bad Gray Value\n");	
			
				/* and return            */
				return EXIT_MISCELLANEOUS;
				} /* fscanf failed */

			/* set the pixel value           */
			*nextGrayValue = (unsigned char) grayValue;
			} /* per gray value */
		}
	/* if the magic number is binary read in binary data */
	else if (pgmStruct->magic_number[1] == '5'){
		fread(pgmStruct->imageData, sizeof(unsigned char), pgmStruct->width * pgmStruct->height, inputFile);
	}


	/* we're done with the file, so close it */
	fclose(inputFile);

	return EXIT_NO_ERRORS;

} /* openReadFile()		*/
