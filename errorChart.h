#ifndef ERRORCHART_H
#define ERRORCHART_H

#include <stdio.h>
#include <stdlib.h>
#include "constantsTable.h"

#define SYNERR "syntax error"
#define NOT_ENOUGH_MEMORY "cant complete allocation, not enough memory"
#define LINE_TOO_LONG "the line is too long for the buffer to hold"
#define NOT_LABLE_NAME "SYNERR,error with label: %s"
#define NOT_ENOUGH_OP "cant recognize operators"
#define MISSING_ARG "SYNERR, cant recognize arguments, please provide"
#define NOT_ARG_NAME "SYNERR, cant recognize argument name"
#define NOT_OP_NAME "SYNERR, cant recognize opcode name"

extern char *newFileName;
STATUS errorAlert(int errorLine); /*prototype*/
#endif
