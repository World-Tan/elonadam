
#include "assembler.h"
/*#include "errorChart.h"*/
/*this file get a line from file, create memory for the line and sets cells tp null*/
/* delete spaces recognize labels and args*/
/*can be compiled !!! 26/6/22*/
/*0*/

Status status; /*in assembler, 0/1 values*/
/*static funcs prototype*/
static int getArgs(char *origin, char *dest);
static int findOpCode(char **opTable, char *strToCheck);


lineData* readLine (FILE *originf) {

	char *opName[] = {"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","get","prn","jsr","rts","hlt",".data",".string",".extern",".entry"}; /*only opcodes cant with enum*/
	lineData* currLine;
	char originStr[MAX_LINE_SIZE], tmpStr[MAX_LINE_SIZE];
	/*char errTextBody[ERR_MESSAGE_LEN]; */
	char *p;
	char *q;
	int length, ptr, mode, indexStr;
	indexStr = 0;

	/*checks */
	if(!(currLine = malloc(sizeof(lineData)))) { /*create memory maybe calloc*/
		/*errorAlert(sprintf(errTextBody,NOT_ENOUGH_MEMORY));													example to err message*/
		freeAllFields(currLine);
		return NULL;}
		
		(*currLine).lbl = NULL;
		(*currLine).args = malloc(sizeof(char*) * MAX_ARGS); /*maybe calloc*/
		(*currLine).eof = FALSE;
		(*currLine).ignorLine = FALSE;
		
		/*if memory susceded set all cells to null insted of zero*/
		for (ptr = 0; ptr < MAX_ARGS;ptr++)
			(*currLine).args[ptr] = NULL; /*to search for diff way to do it*/
			
		if(!fgets(originStr,MAX_LINE_SIZE,originf)) { /*eof encounterd, check diff way to do*/
			(*currLine).eof = TRUE;
			return currLine; }
			
		if((length = strlen(originStr)) == 0 || tmpStr[0] == NOTE) { /*is the line is empty or note to ignore*/
			(*currLine).ignorLine = TRUE;
			free((*currLine).args);
			(*currLine).args = NULL; /*if i make args for null its not free them ?*/
			return currLine;}
		else if(originStr[length-1] != NEW_LINE) {/*the line beyond limit 0f 81*/
																																																			/*pop some error*/
			freeAllFields(currLine);
			return NULL; }
			
			/*remove spaces*/
			p = q = originStr; /*pointing to the scaned line from file*/
			while (isspace(*q))
				q++;
			if(q == STR_END) {
				free((*currLine).args);
				(*currLine).args = NULL;
				(*currLine).ignorLine = TRUE;
				return currLine;}
			while ((q - originStr) < (length - 1)) {
				if (isspace(*q) && isspace(*(q+1)))
					continue;
				*p++ = isspace(*q) ? SPACE : *q;
				q++ ;}
			*p = STR_END;
			/*end  remove spaces*/
			
			sscanf(originStr,"%s",tmpStr);
			
			/*recognize label*/
			if (tmpStr[(length = strlen(tmpStr)) -1] == COLON) {/*too complicated*/
				tmpStr[length - 1] = STR_END;
				if(isRegister(tmpStr)) { /*if true, reg cant be label*/
																																																				/*pop some err* - reg cant be label*/
					freeAllFields(currLine);
					return NULL; }
					
				if(isLabel(tmpStr)) {
					if (copyFunc(&((*currLine).lbl),tmpStr))
					indexStr += strlen((*currLine).lbl) + 2;
					else {
																																		/*maybe pop error here*/
					freeAllFields(currLine);
					return NULL;}
				}
				else {
																																			/*pop spme error - not legal label*/
				freeAllFields(currLine);
				return NULL; }
				
				if ( !sscanf((originStr + indexStr), "%s", tmpStr)) { /*read the next word for the operator rcognition*/
																																	/*pop error - syntax missing, missing op*/
					freeAllFields(currLine);
					return NULL; }
			}
			 else 
				(*currLine).lbl = NULL;
			/*end of label check*/
			
			/*recognize op*/
			if (((*currLine).cmd = findOpCode(opName,tmpStr)) == ERR) {
				freeAllFields(currLine);
				return NULL;}
			else
				indexStr += (strlen(tmpStr) + (strcmp(tmpStr,originStr + indexStr) == 0 ? 0:1)); /*way too complicated*/
			if ( (*currLine).cmd >= DOT_EXTERN) {
				free((*currLine).lbl);
				(*currLine).lbl = NULL; }
				/*end recognize op*/
				
			/*seperate arguments */
			ptr = 0;
			if (!(mode = getArgs(originStr + indexStr, tmpStr))) {
				free((*currLine).args);
				(*currLine).args = NULL;}
			else if (mode == ERR)
				return NULL;
			else {
				ptr ++;
				if (!(copyFunc(&((*currLine).args[0]), tmpStr))) {
					freeAllFields(currLine);
					return NULL; }
				while ((mode = getArgs(NULL, tmpStr))) {
					if (mode == ERR)
						return NULL;
					if (!(copyFunc(&((*currLine).args[ptr]),tmpStr))) {
						freeAllFields(currLine);
						return NULL; }
					ptr++; }
				} /*end of else*/
			
			if ((length = ptr) > 0){
				(*currLine).args = realloc((*currLine).args, sizeof(char *) * length + 1);} /*off the record but- its cant fail bc its shirnking*/
			/*end args checks*/
			return currLine;
		}/*end of readLine*/
			
		
		int freeAllFields(lineData* currLine) {/*free all  the memory from the struct*/
			int j;
			if (!currLine)
				return 2; /*was just returnl*/
			if((*currLine).args != NULL)
				for(j = 0;(*currLine).args[j] != NULL; j++)
					free((*currLine).args[j]);
			free((*currLine).lbl);
			free((*currLine).args);
			free(currLine);
			return TRUE;
		}/*end of freeAllFields*/
		
		
		/*check if  given str is register name*/
		int isRegister (char *givenStr) {/*was const char*/
			if (givenStr[0] == REG_SYM &&  (abs(REGS_NUM - givenStr[1]) >= 0) && (strlen(givenStr) < 3))/*if the str start with r, has 0-7 num and not more then 2 chars*/
				return TRUE;
			return FALSE;}
		
		/*check if  given str is label name*/
		int isLabel (char *givenStr) {		/*was const char*/
			int ptr = 0;
			if (isRegister(givenStr))
				return FALSE; /*str already identify as register*/
			if(!isalpha(givenStr[ptr])) /*check is first char is not letter*/
				return FALSE;
			for(ptr = 1; givenStr[ptr]; ptr++){ /*check if rest chars are alpha numeric*/
				if(!isalnum(givenStr[ptr]))
					return FALSE; }/*end of for*/
			return TRUE; }/*end isLabel*/
					
			char copyFunc (char **dst,char *src) {
				int strPtr = 0;
				if (!(*dst = malloc(strPtr = (strlen(src) + 1)))) {
																											/*pop spme err*/	 				/*maybe something with strlcpy(dst,src,dstsize)*/
					return FALSE;}
				strcpy(*dst,src);
				return TRUE;
			}/*end method*/
		
		/*~~~~~~~~~~~~~~~static functions~~~~~~~~~~~~~~*/	
		
		static int getArgs(char *origin, char *dest) {
			static char *origStr;
			int inLine = 0;
			int ptr;
			if (origin != NULL) /*source nor empty*/
				origStr = origin;
			while (isspace(*origStr)) /*ignore spaces*/
				origStr++;
			for(ptr = 0; *origStr != COMMA && *origStr != STR_END; origStr++) {
				if (inLine) {
					if(*origStr == QUOTE)
							inLine = 0;}
				else if (isspace(*origStr))
					break;
				else if (*origStr == QUOTE) 
						inLine = 1;
				dest[ptr] = *origStr;
				ptr++;} /* end of for loop*/
			if (ptr == 0) {
																																			/*pop error syntax err empty arg*/
				return ERR;}
			while (isspace(*origStr))
				origStr++; /*ignore spaces*/
			if (*origStr != STR_END && *origStr != COMMA) {
																															/*pop some error, syntax err unknown arg type*/
				return ERR;}
			dest[ptr] = STR_END;
			if (*origStr == COMMA) {
				origStr++;
				if(*origStr == STR_END) {
																																			/*pop error syntax empty args value*/
					return ERR; }
			}
			return TRUE;
		}/*end of getArgs*/
		
		static int findOpCode(char **opTable, char *strToCheck) {/*, char opAmount*/
			int i = 0;
			while(i < OPCODE_AMOUNT) {
				if(strcmp(opTable[i],strToCheck) == 0) /*its a match*/
					return i;
				i++;}
																																			/*pop error - syntx - unknown op code*/
			return ERR; } /*end of method*/
		
			/*~~~~~~~~~~~~~~~end of static functions~~~~~~~~~~~~~~*/	
			
