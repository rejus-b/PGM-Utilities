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

/* header for pgmEcho				*/
#include "pgmEcho.h"

/* header for pgmTile				*/
#include "pgmTile.h"


int main(int argc, char **argv)
	{ 
	/* main() */

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


	const char *fileName = argv[3];
	const char* extension = "_<row>_<column>.pgm";
	int length = strlen(fileName);
	const char* fileType = &fileName[length - 19];
	int check = strcmp(extension, fileType);
	if (check != 0)
	{
        /* exit the code */
        printf("ERROR: Miscellaneous (Bad tile layout)");
		printf("\n %s \n", fileType);
        exit(EXIT_MISCELLANEOUS);		
	}


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
    {
        /* exit the code */
        printf("ERROR: Bad File Name (%s)", argv[1]);
        return EXIT_BAD_INPUT_FILE;
    }

	/* If it works print 'TILED'*/
	printf("TILED");

	tile(pgmStruct, tilePgmStruct, argv[3], 256, extension);

	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;
	} /* main() */


int tile(pgm *pgmStruct, pgm *tilePgmStruct, char *inputFile, int tileFactor, const char *extension)
{ /* tile() */
	/* calcualting the size of a new pgm struct which will temporarily store each tile */
	tilePgmStruct->width = tileFactor;
	tilePgmStruct->height = tileFactor;
	printf("\n %i \n", tileFactor);
	tilePgmStruct->magic_number[0] = pgmStruct->magic_number[0];
	tilePgmStruct->magic_number[1] = pgmStruct->magic_number[1];

	/* malloc data for a new structure to store the tiled image temporarily */
	tilePgmStruct->imageData = (unsigned char **) malloc(tilePgmStruct->height * sizeof(unsigned char*));

	for (int i = 0; i < tilePgmStruct->width; i++)
	{
		tilePgmStruct->imageData[i] = (unsigned char *) malloc(tilePgmStruct->width * sizeof(unsigned char));
	}

	/* finding the name of the file */

	char name[strlen(inputFile)-strlen(extension)];
	for (int i = 0; i < (strlen(inputFile)-strlen(extension)); i++)
	{
		name[i+1] = '\0';
		name[i] = inputFile[i];
	}
	char newName[strlen(name)+strlen(extension)];

	printf ("\nBUFFER:  %c\n", name[1]);


	/* segmenting the main image into tiles */

	
	int yCount = 0;

	for (int yOffSet = 0; yOffSet < pgmStruct->height; yOffSet += tileFactor)
	{
		int xCount = 0;
		for (int xOffSet = 0; xOffSet < pgmStruct->width; xOffSet += tileFactor)
		{
			for (int i = 0; i < tilePgmStruct->height; i++)
			{
				for (int j = 0; j < tilePgmStruct->width; j++)
				{
					tilePgmStruct->imageData[i][j] = pgmStruct->imageData[i+xOffSet][j+yOffSet];
				}
			}
			
			printf("\n x %i y %i\n", xCount, yCount);
			sprintf(newName, "%s_<%i>_<%i>", name, xCount, yCount);
			writeFile(newName, tilePgmStruct);
			xCount ++;
		}
		yCount ++;
	}


	/* at this point, we are done and can exit with a success code */
	return EXIT_NO_ERRORS;

} /* tile() */
