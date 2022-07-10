#include "symChart.h"
#include "assembler.h"
#include "base32Convert.h"
					/*TDL*/
				/*not writen getRandom,relocate*/

					LAnodeList labelList = {NULL}; /*sets head of new list to be null*/
/*static*/ EXnodeList exList = {NULL};
/*static*/ENnodeList enList = {NULL};
/*static prototypes*/
static label *newLabel(char *name, int memoLoc,char externn, char opcode);
static LAnode *newLAnode(label *this, LAnode *next);

	static label *newLabel(char *name, int memoLoc,char externn, char opcode) { 
		label *newLab;
		if((newLab = calloc(1,sizeof(label))) == NULL){
			/*pop error not enough ram storge*/
			return NULL;} /*end of if*/
		if ((copyFunc(&newLab->id.name, name)) == FALSE) { /*if couldent copy name*/
			free(newLab);
			/*pop error out of ram*/
			return NULL;}
		newLab->id.memoLoc = memoLoc;
		newLab->externn = externn;
		newLab->opcode = opcode;
		return newLab;} /*end of method succesfuly created new label*/
		
	static LAnode *newLAnode(label *this, LAnode *next){
		LAnode *newNode ;
			if((newNode = calloc(1,sizeof(LAnode))) == NULL || this == NULL){
				free(this);
				free(newNode);
			/*pop error not enough ram storge*/
			return NULL;} /*end of if*/
		(*newNode).this = this;
		(*newNode).next = next;
		return newNode;} /*end of method succesfuly created new label node*/
		
		
/*~~~~~~~~~~~~~~~~~~~~add label, add extren , add entry funcs~~~~~~~~~~~~~~~~~*/
	int addLabelToChart(char *name, int memoLoc, char externn, char opcode) { /*adds new label to symbols chart*/
		LAnode *LAnew; /*maybe to replace LAnew on lanode to match the others*/
		LAnode *current = labelList.head;
	
		if(name == NULL) {
			/*pop error not recived labal name*/
			return FALSE;}
		for(; current != NULL; (current = current->next)) {/*check if lable name isnt taken */
			if(strcmp(current->this->id.name,name) == 0) /*strcmp return 0 if found a match*/{
				/*pop error, name is already used as label*/
			return FALSE;}
			}/*end of for*/
		
			LAnew = (newLAnode(newLabel(name,memoLoc,externn,opcode),NULL)); /*add label to label node list*/
			if(LAnew == NULL) {
			/*optional pop error - couldent create new node*/
				return FALSE;}
			
			if (labelList.head == NULL) /*if (!labelList.head) */
				labelList.head = LAnew;
			else
				current->next = LAnew;
			return TRUE;} /*succesfuly added label*/	
		
	int addExternnToChart(char *name, int memoLoc) {
		EXnode *exnode = exList.head; /*set new node from type extern */
		
		if(!exnode) {
		/*pop error  RAM Full*/
		return ERR;}

		exnode = calloc(1,sizeof(exnode));
		if (exnode == NULL) {
		/*pop error RAM FULL*/
		return ERR;}
		
		if(exList.head ==NULL) 
			exList.head = exnode;
		else {
			for(; exnode != NULL; (exnode = exnode->next)); /*run till end of list*/
			(exnode->next) = calloc(1,sizeof(exnode));
			if (exnode == NULL) {
				/*pop error RAM FULL*/
				return ERR;}
			exnode =exnode->next; }/*end of else*/
		
		copyFunc(&exnode->id.name,name);
		exnode->id.memoLoc = memoLoc + MEMORY_START_ADDRESS;
		exnode->next = NULL;
		return TRUE; }		/*succesfuly added extern */	
		
	int addEntryToChart(label *labelName) {
		ENnode *ennode = enList.head;
		if(!ennode) {
		/*pop error  RAM Full*/
		return FALSE;}
		ennode = calloc(1,sizeof(ennode));
		if (ennode == NULL) {
		/*pop error RAM FULL*/
		return ERR;}
		
		if (enList.head == NULL)
			enList.head = ennode;
		else {
			for(; ennode != NULL; (ennode = ennode->next)); /*run till end of list*/
			(ennode->next) = calloc(1,sizeof(ennode));
			if (ennode == NULL) {
				/*pop error RAM FULL*/
				return ERR;}
			ennode =ennode->next; }/*end of else*/
		
		ennode->id.name = labelName -> id.name;
		ennode->id.memoLoc = labelName-> id.memoLoc;
		ennode->next =NULL;
		return TRUE;} /*succesfuly added entry label*/	
			
/*~~~~~~~~~~~~~~~~~~~~end of add label, add extren  add entry funcs~~~~~~~~~~~~~~~~~*/


/*~~~~~~~~~~~~~~~~~~~~pop extren  pop entry  funcs~~~~~~~~~~~~~~~~~*/

	char *externPop(int *memoLoc){
		EXnode *exnode = exList.head;
		char *name;
		if (!exnode)
			return NULL;
		exList.head = exnode->next;
		*memoLoc = exnode->id.memoLoc;
		name = exnode->id.name;
		free(exnode);
		return name; } /*end of extern pop*/
		
	char *entryPop(int *memoLoc){
		ENnode *ennode = enList.head;
		char *name;
		if (!ennode)
			return NULL;
		enList.head = ennode->next;
		*memoLoc = ennode->id.memoLoc;
		name = ennode->id.name;
		free(ennode);
		return name; } /*end of entry pop*/

/*~~~~~~~~~~~~~~~~~~~~end of pop extren , pop entry funcs~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~label search funcs~~~~~~~~~~~~~~~~~*/

	label *searchLabel (char *name){
		LAnode *lanode = labelList.head;
		
		if (strcmp(lanode->this->id.name,name) == 0) /*check for the first lanode*/
			return lanode->this;
		while((lanode = lanode->next) != NULL)/*chec for rest of the list*/
			if (strcmp(lanode->this->id.name,name) == 0) /*strcmp return 0 when found match*/
				return lanode->this; 
		return NULL;} /*end of searchLabel*/
		
		char isLabelExsist (char *name){
		 return searchLabel(name) ? TRUE : FALSE;}

/*~~~~~~~~~~~~~~~~~~~~end label search funcs~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~print and clean funcs~~~~~~~~~~~~~~~~~*/

	int PrintSymList () {
		LAnode *lanode = labelList.head;
		if (!lanode)
			return ERR;
		else {
		printf("%s\t %s\t %s\t %s\n","name","memoLoc","externn","opcode");
		for(;(lanode->next) != NULL; lanode = lanode->next) {
			printf("%s\t %s\t %d\t %d\n",(lanode->this->id.name), ( baseConvertor(lanode->this->id.memoLoc)), (lanode->this->externn),
 (lanode->this->opcode)); }
			return FALSE;}
			}/*endof printSymList*/


	int clearSymList() {
		LAnode *lanode = labelList.head;
		if (lanode == NULL)
			return FALSE;
		else {
			for(;(lanode->next) != NULL; lanode = lanode->next) {
				labelList.head = lanode->next;
				free(lanode->this->id.name);
				free(lanode->this);
				free(lanode); }
			labelList.head = NULL;}
		return FALSE;} /*endof clearSymList*/

/*~~~~~~~~~~~~~~~~~~~~end print and clean funcs~~~~~~~~~~~~~~~~~*/



