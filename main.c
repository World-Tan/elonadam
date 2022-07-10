#include "assembler.h"
#include "constantsTable.h"
	char*newFileName; /*save it with globals for later use in cathing errors*/ /*was int*/
	FILE *curr; 
	int main(int argc, char *argv[]) {
	/*printf("\nCurrent program-run start time : %s",_TIME_);*/
	static char *ifp; /*input file pointer*/
	/*FILE *curr; */ /*was inside and made that global for laps*/
	int i,fileSize;
	char success = TRUE;
	if (argc < 2) {
		/*pop error not enough files*/
		return (success = FALSE); }
	else {
		while (--argc > 0) {
			i = argc;
			fileSize = (strlen(argv[i]) + ENDING_LENGTH); /*length of file name with extention*/
			ifp = malloc(fileSize);
			newFileName = snprintf(ifp,fileSize,"%s%s",argv[i],SOURCE_EXT); /*newfile is pointer but i think snprintf work with int*/
			if ((curr = fopen(newFileName, "r")) != NULL) { /*opened the file*/
				if (lapControl(curr) == LAP_FAIL) 
					fprintf(stderr,/*1*/LAP_FAIL, argv[i],SOURCE_EXT);
				else
					fprintf(stdout,/*2*/LAP_COMPLETE,argv[i],SOURCE_EXT); 
			}
			else
				/*pop error invalid filre name*/
				free(newFileName);
			}/*end of while*/
		return success;
		}/*end of else*/
	}
	
	
		
					
					
					
					
					
			
