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

/* header for openWriteFile */
#include "openWriteFile.h"



int writeFile(char *fileName, pgm *pgmStruct)
{ /* writeFile() */


	/* open a file for writing               */
	FILE *outputFile = fopen(fileName, "w");

	/* check whether file opening worked     */
	if (outputFile == NULL)
		{ /* NULL output file */
		/* free memory                   */
		free(pgmStruct->commentLine);
		free(pgmStruct->imageData);

		/* print an error message        */
		printf("ERROR: Output Failed (%s)", fileName);	

		/* return an error code          */
		exit(EXIT_OUTPUT_FAILED);
		} /* NULL output file */


	/* write magic number, size & gray value */
	size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n",pgmStruct->magic_number[1], pgmStruct->width, pgmStruct->height, pgmStruct->maxGray);


	/* allocate the data pointer             */
	// long nImageBytes = pgmStruct->width * pgmStruct->height * sizeof(unsigned char);

	/* check that dimensions wrote correctly */
	if (nBytesWritten < 0)
		{ /* dimensional write failed    */
		/* free memory                   */
		free(pgmStruct->commentLine);
		free(pgmStruct->imageData);

		/* print an error message        */
		printf("ERROR: Bad Dimensions (%s)", fileName);	

		/* return an error code          */
		return EXIT_BAD_DIMENSIONS;
		} /* dimensional write failed    */

        /* pointer for efficient write code      */

	/* run the code that prints in ASCII if the magic number is 2	*/
	if (pgmStruct->magic_number[1] == '2')
	{
		for (int i = 0; i < pgmStruct->height; i++)
		{
			int colCount = 0;
			for (int j = 0; j < pgmStruct->width; j++)
			{
				

				// for (unsigned char **nextGrayValue = pgmStruct->imageData; nextGrayValue < pgmStruct->imageData + nImageBytes; nextGrayValue++)
				// { /* per gray value */
					// int nextCol = (nextGrayValue - pgmStruct->imageData + 1) % pgmStruct->width;
					// int nextCol = pgmStruct->imageData[i][j];
					int nextCol = (colCount - pgmStruct->imageData[i][j] + 1) % pgmStruct->width;

					/* write the entry & whitespace  */
					nBytesWritten = fprintf(outputFile, "%d%c", pgmStruct->imageData[i][j], (nextCol ? ' ' : '\n') );

					
					colCount++;

					/* sanity check on write         */
					if (nBytesWritten < 0)
						{ /* data write failed   */
						/* free memory           */
						free(pgmStruct->commentLine);
						free(pgmStruct->imageData);

						/* print error message   */
						printf("ERROR: Output Failed (%s)", fileName);	

						/* return an error code  */
						return EXIT_OUTPUT_FAILED;
						// } /* data write failed   */
					} /* per gray value */
					
			}
		}
	}






		// for (unsigned char *nextGrayValue = pgmStruct->imageData; nextGrayValue < pgmStruct->imageData + nImageBytes; nextGrayValue++)
		// { /* per gray value */
		// 	/* get next char's column        */

		// 	int nextCol = (nextGrayValue - pgmStruct->imageData + 1) % pgmStruct->width;

		// 	/* write the entry & whitespace  */
		// 	nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n') );

		// 	/* sanity check on write         */
		// 	if (nBytesWritten < 0)
		// 		{ /* data write failed   */
		// 		/* free memory           */
		// 		free(pgmStruct->commentLine);
		// 		free(pgmStruct->imageData);

		// 		/* print error message   */
		// 		printf("ERROR: Output Failed (%s)", fileName);	

		// 		/* return an error code  */
		// 		return EXIT_OUTPUT_FAILED;
		// 		} /* data write failed   */
		// } /* per gray value */
	// } 

	/* if the magic number is binary then write the data in binary format	*/
	else if (pgmStruct->magic_number[1] == '5')
	{
		for (int i = 0; i < pgmStruct->height; i++)
		{
			fwrite(pgmStruct->imageData[i], sizeof(unsigned char), pgmStruct->width, outputFile);
		}
		
		// fwrite(pgmStruct->imageData, sizeof(unsigned char), pgmStruct->width * pgmStruct->height, outputFile);
	}

     return EXIT_NO_ERRORS;
}