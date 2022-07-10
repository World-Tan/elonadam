#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
	char *lbl;
	char **args;
	char eof;
	char ignorLine;
	int cmd;} 
lineData;/*in structs line 8*/
	
typedef struct node{  /*build sturct for node to create linked list*/
	unsigned int data;
	struct node *next;}
node;
	
typedef struct linkedList{
	node* head;
	unsigned int length;}
linkedList;

/*labels related structs*/

struct ID { 	/*basic node info*/
	char *name;
	int memoLoc;}
ID;

typedef struct label{ /*if working to change here too the this struct*/
	struct ID id;
	char externn;
	char opcode;}
label;

typedef struct LAnode{  /*build sturct for label node to create linked list*/
	label *this;
	struct LAnode *next;}
LAnode;

typedef struct EXnode{  /*build sturct for label node to create linked list*/
	struct ID id;
	struct EXnode *next;}
EXnode;

typedef struct ENnode{ /*linked list for labels*/
	struct ID id;
	struct ENnode *next;}
ENnode;

typedef struct{
	LAnode *head;}
LAnodeList;

typedef struct{
	EXnode *head;}
EXnodeList;

typedef struct{
	ENnode *head;}
ENnodeList;
																					/*maybe missing extern LAnodeList symList*/
																					
typedef struct word {
	unsigned int ARE: TWO_BITFIELDS;
	unsigned int destOperand: TWO_BITFIELDS;
	unsigned int sourceOperand: TWO_BITFIELDS;
	unsigned int opCode: FOUR_BITFIELDS;}
word;

typedef struct word {
	unsigned int ARE: TWO_BITFIELDS;
	unsigned int Value: EIGHT_BIT;}
word;

word that will represent data like stringsd and nums
word for command like the first struct
word for register 
















typedef struct command_word{
	unsigned int opCode: FOUR_BITFIELDS;
	unsigned int destOperand: TWO_BITFIELDS;
	unsigned int sourceOperand: TWO_BITFIELDS;}
command_sentence;

typedef struct argument_word{
	unsigned int ARE: TWO_BITFIELDS;
	unsigned int ARE: TWO_BITFIELDS;

																		
typedef struct terNode{
	
#endif

