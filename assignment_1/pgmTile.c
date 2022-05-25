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

/* header for openReadFile			 */
#include "openReadFile.h"

/* header for openWriteFile			*/
#include "openWriteFile.h"

/* header for pgmTile				*/
#include "pgmTile.h"


/*************************************/
/* main routine                      */
/*                                   */
/* CLI parameters:                   */
/* argv[0]: executable name          */
/* argv[1]: input file name          */
/* argv[2]: integer tile factor		 */
/* argv[3]: output file name         */
/* returns 0 on success              */
/* non-zero error code on fail       */
/*************************************/


int main(int argc, char **argv)
{ /* main() */

	/* check for no input/output args */
	if (argc == 1)
	{/* print a bad usage message */
		printf("Usage: %s inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm", argv[0]);
		/* return no errors */
		return EXIT_NO_ERRORS;
	}

	/* check for correct number of arguments */
	if (argc != 4)	
		{ /* wrong arg count */
		/* print an error message        */
		printf("ERROR: Bad Argument Count");
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
		} /* wrong arg count */

	/* check that the output file name is formatted correctly */
	checkExtension(argv[3]);

	/* malloc for a structure then pass it into pgmStructInit() */ 
	pgm *pgmStruct = NULL;
	pgmStruct = ((pgm*) malloc (sizeof(pgm)));
	pgmStructInit(pgmStruct);

	/* initialising a new structure that will store the tiled pgm image */
	pgm *tilePgmStruct = NULL;
	tilePgmStruct = ((pgm*) malloc (sizeof(pgm)));
	pgmStructInit(tilePgmStruct);
	
    /* this is too check that the input file is a valid file name */
	if (readFile(argv[1], pgmStruct) != 0)
    { /* invalid file name */
        /* free the structures initialised at the start */
		free(pgmStruct);
		free(tilePgmStruct);
        /* exit the code */
        printf("ERROR: Bad File Name (%s)", argv[1]);
        return EXIT_BAD_INPUT_FILE;
    } /* invalid file name */

	/* this converts the string integer factor to an integer */
	int integerFactor = atoi(argv[2]);

    /* this checks that the integer factor is valid (less than 1, or greater than dimensions) */
	if (integerFactor < 1 || integerFactor  > pgmStruct->width || integerFactor  > pgmStruct->height)
    {
        /* free the structures initialised at the start */
		free(pgmStruct);
		free(tilePgmStruct);
        /* exit the code */
        printf("ERROR: Miscellaneous (Bad integer tile factor)");
        return EXIT_MISCELLANEOUS;
    }

	/* run the tile function to tile the code */
	if (tile(pgmStruct, tilePgmStruct, argv[3], atoi(argv[2])) == 0)
	{
		/* free the structures initialised at the start */
		free(pgmStruct);
		free(tilePgmStruct);
		/* if it sucesfully tiles print 'TILED' */
		printf("TILED");
		/* at this point, we are done and can exit with a success code */
		return EXIT_NO_ERRORS;
	}

} /* main() */

int checkExtension(char *fileName)
{	/* checkExtension() */

	/* this checks that ending of the output file is in the correct format */
	const char* extension = "_<row>_<column>.pgm";
	int fileNameLength = strlen(fileName);
	const char* fileType = &fileName[fileNameLength - strlen(extension)];
	int checkExtension = strcmp(extension, fileType);

	/* if the user input format and the actual format do not match throw an error */
	if (checkExtension != 0)
	{
        /* exit the code */
        printf("ERROR: Miscellaneous (Bad tile layout)");
        exit(EXIT_MISCELLANEOUS);		
	}

	return EXIT_NO_ERRORS;
} /* checkExtension() */


int tile(pgm *pgmStruct, pgm *tilePgmStruct, char *inputFile, int tileFactor)
{ /* tile() */
	/* calcualting the size of a new pgm struct which will temporarily store each tile */
	tilePgmStruct->width = pgmStruct->width / tileFactor;
	tilePgmStruct->height = pgmStruct->height / tileFactor;
	
	/* assigns the tile magic number to the original magic number */
	tilePgmStruct->magic_number[0] = pgmStruct->magic_number[0];
	tilePgmStruct->magic_number[1] = pgmStruct->magic_number[1];

	/* malloc for a new 2D array to store the tiled image temporarily */
	tilePgmStruct->imageData = (unsigned char **) malloc(tilePgmStruct->height * sizeof(unsigned char*));

	for (int row = 0; row < tilePgmStruct->width; row++)
	{
		tilePgmStruct->imageData[row] = (unsigned char *) malloc(tilePgmStruct->width * sizeof(unsigned char));
	}

	/* finding the name of the file */
	/* initialise a new array to store the input file name */
	char name[strlen(inputFile) - 19];
	/* loop through the input file name up until the non-variable extension" */
	for (int inputNameChars = 0; inputNameChars < (strlen(inputFile) - 19); inputNameChars++)
	{
		/* loop through the file name to copy it letter by letter, add a newline character to terminate the string */
		name[inputNameChars+1] = '\0';
		name[inputNameChars] = inputFile[inputNameChars];
	}

	/* initialise a new string for the name that will be formated with row and column */
	char newName[strlen(name) + 19];

	/* segmenting the main image into tiles */
	for (int yOffSet = 0; yOffSet < tileFactor; yOffSet ++)
	{
		for (int xOffSet = 0; xOffSet < tileFactor; xOffSet ++)
		{
			for (int row = 0; row < tilePgmStruct->height; row++)
			{
				for (int col = 0; col < tilePgmStruct->width; col++)
				{
					/* assign the pixel of the tile to the corresponding input image pixel */
					tilePgmStruct->imageData[row][col] = pgmStruct->imageData[(yOffSet * tilePgmStruct->height) + row][(xOffSet * tilePgmStruct->height) + col];
				}
			}
			/* create a formated string with the row and columns then write it to a new file */
			sprintf(newName, "%s_%i_%i.pgm", name, yOffSet, xOffSet);
			writeFile(newName, tilePgmStruct);
			/* below comment line is for testing pgmAssemble */
			/* printf(" %i %i %s_%i_%i.pgm", xOffSet*tilePgmStruct->height, yOffSet*tilePgmStruct->width, name, xOffSet, yOffSet); */
		}
	}
	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;

} /* tile() */
