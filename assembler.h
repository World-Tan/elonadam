/*this will include franqualy used libaries*/

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
#include <math.h>
#include "constantsTable.h" 
#include "structs.h"

/*prototypes*/
int freeAllFields(lineData* currLine);/*in header*/
int isRegister (char *givenStr);
int isLabel (char *givenStr);
char copyFunc (char **dst, char *src);
/*static int getArgs(char *origin, char *dest);*/
/*static int findOpCode(char **opTable, char *strToCheck);*/
/*prototypes*/

#endif
