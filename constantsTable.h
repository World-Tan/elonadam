/* this will be the place for all defines and enums*/
/*started in 19.6.22*/

#ifndef CONSTANTSTABLE_H 
#define CONSTANTSTABLE_H

/* Defines for numberic constants*/
#define MAX_MEMORY_SIZE 256
#define MEMORY_START_ADDRESS 100
#define OPCODE_AMOUNT 16
#define MAX_LINE_SIZE 81
#define WORD_SIZE 10
#define REGS_NUM 8 /*made name change so watch for err*/
#define FALSE 0
#define TRUE 2 /*lucky number*/
#define MAX_ARGS ((MAX_LINE_SIZE - 3)/2+1) /*to replace ASAP not understand*/ 
#define ERR -1
#define ENDING_LENGTH 5 /*include space for '/0' i think */
#define LAP_COMPLETE 0
#define LAP_FAIL 1
#define ERR_MESSAGE_LEN 100
#define TWO_BITFIELDS 2
#define FOUR_BITFIELDS 4
#define OPCODE_WORD 4


/* define for string constants*/
#define NEW_LINE '\n'
#define NOTE ';'
#define COLON ':'
#define REG_SYM 'r'
#define IMMED_SYM '#'
#define COMMA ','
#define SPACE ' '
#define QUOTE '"'
#define STR_END '\0'
#define SOURCE_EXT ".as"
#define ENTRY_EXT ".ent"
#define EXTERN_EXT ".ext"
#define OBJECT_EXT ".ob"

/*  encode types*/
enum encode {
	ABST = 0,
	EXT,
	RELO 	};
	
/*addressing types*/
typedef enum addressing {
	IMMED = 0,
	DRCT,
	ARA, /*adressing record accec*/
	IRA /*imideatly register addresing */ } addressing;
	
/*args amount*/
enum ARGS_AMOUNT{
	ZERO_ARGS = 0,
	ONE_ARG,
	TWO_ARGS };
	
/*making status for lapControl*/
typedef enum {
	LAP_SUCCESS,
	LAP_ERROR } Status; 
	
/*opcode table*/
typedef enum {
	MOV,
	CMP,
	ADD,
	SUB,
	NOT,
	CLR,
	LEA,
	INC,
	DEC,
	JMP,
	BNE,
	GET,
	PRN,
	JSR,
	RTS,
	HLT } OPCODE;
	
/*sentence types*/
typedef enum {
	EMPTY,
	COMMENT,
	DIRECTING,
	ORDER } SEN_TYPE;
	
/*check this what*/
typedef enum {
	DOT_DATA = OPCODE_AMOUNT, DOT_STRING, DOT_EXTERN, DOT_ENTRY } instType;
#endif









