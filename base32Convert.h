#ifndef BASE32CONVERT_H
#define BASE32CONVERT_H

#include "assembler.h"
/*the one under is working in testing*/

#define uniqBase(x) (x) < 10 ?  uniqarr[x] : (x - 10) + 'a'
#define OUTPUT_BASE 32
#define UNIQBASE_WORD_SIZE (int)(WORD_SIZE + (int))
char uniqarr[] = {'!','@','#','$','%','^','&','*','<','>'};

char* baseConvertor(long unsigned int inputNum);

#endif
	

