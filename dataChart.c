#include "dataChart.h"

														/*TDL*/
/*maybe to add condition to prevent overflow memory*/
/*try to change  set start pos syntax line 12*/
													/*compile yes 3.7*/
/*format %s expects argument of type char *, but argument 2 has type int  printf("\n%s  %s\n", baseConvertor(printLine)*/



/*extern static variable*/
linkedList currList = {NULL,0}; /*set start position for extern var*/                    /*try to change*/

	static node* queue(node * head,int data) { /*create node link at the end of the previus node*/
		node *current = head; 
		while(current->next != NULL) /*run until finds last node*/
			current = current->next;
		current->next = (node*)calloc(1,sizeof(node)); /*allocating memory for node*/
		if(current->next == NULL) { /*if cant find memory for node*/
			printf("\nnot enough memory to create new node");
			return FALSE;}
		else {
			current->data = data; /*store the last read char in the node*/
			current->next = NULL;
			currList.length++;}
		return FALSE ;} /*end of queue*/

	int printDataList(int printLine){
	node * current = currList.head;
	while (current != NULL) {
		printLine++;
		current = currList.head->next;
		printf("\n%s  %s\n", baseConvertor(printLine),baseConvertor(current->data));}/*end of while*/
		return FALSE;}/*end of printDataList*/
	
	int clearDataList() {/*delete the data from current list*/
		node * current = currList.head;
		node * tmp;
		currList.length = 0;
		while(current != NULL) { /*while not in the end of list*/
			tmp = current;
			current = currList.head->next;
			free(tmp); }
		return FALSE;}/*end of clearlist*/
	
	
	
	
	
	
	
	
	
	
