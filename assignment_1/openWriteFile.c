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
		for (int i = 0; i < pgmStruct->height; i++)
			{
				free(pgmStruct->imageData[i]);
			}
		free (pgmStruct->imageData);

		/* print an error message        */
		printf("ERROR: Output Failed (%s)", fileName);	

		/* return an error code          */
		exit(EXIT_OUTPUT_FAILED);
		} /* NULL output file */


	/* write magic number, size & gray value */
	size_t nBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n",pgmStruct->magic_number[1], pgmStruct->width, pgmStruct->height, pgmStruct->maxGray);

	/* check that dimensions wrote correctly */
	if (nBytesWritten < 0)
		{ /* dimensional write failed    */
		/* free memory                   */
		free(pgmStruct->commentLine);
		for (int i = 0; i < pgmStruct->height; i++)
			{
				free(pgmStruct->imageData[i]);
			}
		free (pgmStruct->imageData);

		/* print an error message        */
		printf("ERROR: Bad Dimensions (%s)", fileName);	

		/* return an error code          */
		return EXIT_BAD_DIMENSIONS;
		} /* dimensional write failed    */

	/* run the code that prints in ASCII if the magic number is 2	*/
	if (pgmStruct->magic_number[1] == '2')
	{
		
		for (int i = 0; i < pgmStruct->height; i++)
		{
			
			for (int j = 0; j < pgmStruct->width; j++)
			{
				/* finds the next column location */
				// int nextCol = (colCount - pgmStruct->imageData[i][j] + 1) % pgmStruct->width;

				/* write the entry & whitespace  */
				nBytesWritten = fprintf(outputFile, "%d%c", pgmStruct->imageData[i][j], ' ');
				

				/* sanity check on write	*/
				if (nBytesWritten < 0)
					{ /* data write failed   */
					/* free memory           */
					free(pgmStruct->commentLine);
					for (int i = 0; i < pgmStruct->height; i++)
						{
							free(pgmStruct->imageData[i]);
						}
					free (pgmStruct->imageData);

					/* print error message   */
					printf("ERROR: Output Failed (%s)", fileName);	

					/* return an error code  */
					return EXIT_OUTPUT_FAILED;
					/* data write failed   */
				} 
			}
			/* print a newline after all the data has been written */
			fprintf(outputFile, "\n");

		}
		fclose(outputFile);
	}

	/* if the magic number is binary then write the data in binary format	*/
	else if (pgmStruct->magic_number[1] == '5')
	{
		for (int i = 0; i < pgmStruct->height; i++)
		{
			fwrite(pgmStruct->imageData[i], sizeof(unsigned char), pgmStruct->width, outputFile);
			free(pgmStruct->imageData[i]);
		}
		fclose(outputFile);
	}

     return EXIT_NO_ERRORS;
}