
#include "laps.h"
#include "assembler.h"
#include "symChart.h"
#include "dataChart.h"
/*include "beliveInYourSelfWords.h"*/
/*control the laps*/
status lapControl (FILE *curr) {
		status lapResult = LAP_COMPLETE; /*sets start conditon*/
		firstLap(curr); /*run first lap on current file*/
		if(lapResult == LAP_COMPLETE) /*passed the first lap*/
			secondLap(curr); /*send to second lap to fulfill missing values*/
		if(lapResult == LAP_COMPLETE) /*passes second lap*/
			wrapUp(); /*everything is fine send for final stage*/
			cleanAll(); }
			
			
/*FIRST LAP*/

	Status firstLap (FILE *src) {
		lineData *currLine;
		int i = 1;
		fseek(src,0,SEEK_SET);
		for(;TRUE;i++){ /*run on all lines*/
			if((currLine = readLine(src))) {
				if((*currLine).eof ) /*eof get TRUE or FALSE values in assembler.c*/
					freeAllFields(currLine);
					break;}
				if(!(*currLine).ignorLine) 
					break;
				if(!breakDownWord(currLine)) {
					if (/*replace.length + */ currList.length >=MAX_MEMORY_SIZE) {
						/*pop error out of storge*/
						/*elso report ? */
						return status;}
					/*pop differnt error mesage*/}
				else {
					/*another report*/;}
				freeAllFields(currLine);} /*end of for*/
			return status;}/*end of firstLap*/


	static int breakDownWord(lineData* currLine) {
		int opCode,externn,gotLabel,addWordCount;
		char result[OPCODE_WORD];
		int i,j;
		int *WordGroup[][] = {{"mov","cmp","add","sub","lea"}
													,{"not","clr","inc","dec","jmp","bne","get","prn","jsr"}
													,{"rts","hlt"}
													,{".data",".string",".extern",".entry"}}
		opCode = FALSE; externn = FALSE; gotLabel = FALSE; addWoedCount = 0;
		if ((*currLine).lbl)
			gotLabel =TRUE;
			
		result = (*currLine).cmd; /*save desired op code aside*/
		
		for (i = 0;i < 4; i++) /*search match with known opcode devide by groups*/
			for(j = 0; j<WordGroup[i].length;j++) {
				if (strcmp(result,WordGroup[i][j]) == 0)
					return i;
					
		if (i ==0){ /*opcode with 2 operands*/
			if(((*currLine).args != NULL) && ((*currLine).args[1] != NULL)) { /*opcode has 2 arguments*/
				if(!(isRegister((*currLine).args[0] && isRegister((*currLine).args[1]))))  /*check that is not from one reg to another*/
					++addWordCount; 
				else{
					/*pop error too less args expected 2 got 1*/
					return FALSE;}
					}/*end of first if*/
			else{
			/*pop error too less args expected 2 got 0*/
				return FALSE;}
				}
		if(i == 1) {/*opcode with 1 operand*/
			++addWordCount;}
		if(i == 2){
			 opCode = TRUE; 
			 	if (gotLabel) {
			 		if(!(newLabel((*currLine).lbl, /*cmdList.Length*/,externn,opcode))) 
			 			return FALSE;}
			 	moreLength(++addWordCount); /*count rows*/
			 	break;
			if(i == 3) { /*DOT DATA*/
		/*2 ways, make i 4 and i5 but its stupid*/
		/*search again with small array maybe better*/
		
		
			
































