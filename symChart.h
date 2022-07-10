#ifndef SYMBOL_H
#define SYMBOL_H

#include <stdio.h>
#include "assembler.h"
#include "base32Convert.h"
#include "structs.h"



/*prototypes*/
/*static label *newLabel(char *name, int memoLoc,char externn, char opcode);
static LAnode *newLAnode(label *this, LAnode *next);*/
int addLabelToChart(char *name, int memoLoc, char externn, char opcode);
int addExternnToChart(char *name, int memoLoc);
int addEntryToChart(label *labelName);
char *externPop(int *memoLoc);
char *entryPop(int *memoLoc);
label *searchLabel (char *name);
char isLabelExsist (char *name);
int PrintSymList ();
int clearSymList();
#endif
