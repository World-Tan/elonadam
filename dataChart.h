#ifndef DATACHART_H
#define DATACHART_H


#include <stdio.h> 
#include <stdlib.h> 
#include "structs.h"
#include "constantsTable.h"
#include "base32Convert.h"

extern linkedList currList;

/*prototypes*/
/*int cmdDataLength(); should return the length of cmd list*/
static node* queue(node * head,int data);/*add new nodes with values to the linked list*/
int printDataList(int printLine);
int clearDataList(); /*delete current list*/


#endif
