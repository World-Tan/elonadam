/*convert from base 10 to 32*/

/*working well*/
/*compile with 2 warnings about static methods*/
#include "base32Convert.h"
#include "assembler.h"

	char* baseConvertor(long unsigned int inputNum) { /*have to be long ?*/
		char buff[WORD_SIZE +2]; /* why 2 ? maybe because thr null and minus before*/
		int index = sizeof(buff);
		char *tmp = 0;
		tmp = (char*)calloc(1,sizeof(buff));
		buff[--index] = '\0'; /*maybe buff [index - 1] will work too*/
		if (index <= 0) /*if buff empty*/
			return NULL;
		while (inputNum > 0) {
			buff[--index] = uniqBase(inputNum % OUTPUT_BASE);
			inputNum /= OUTPUT_BASE;
			}
		strcpy(tmp,buff + index); /*maybe to add & to tmp ?*/
		return tmp;
		}
		
