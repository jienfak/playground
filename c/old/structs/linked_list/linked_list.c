#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/* It's a backend of linked list to save any data.*/

struct LinkedList {
	/* Easiest linked list structure. */
	void *data;
	struct LinkedList *next;
	uint8_t type;
} ;

struct LinkedList *crtList(void){
	/* This function creates first element of list. */

	/* First element does not contain anything */
	/* Memory for first element of list. */
	struct LinkedList *structure = malloc( sizeof(struct LinkedList) ) ;

	/* Initialisation values. */
	structure->data = NULL ;
	structure->next = NULL ;

	/* This type means "Start of list.". */
	structure->type = 0 ;

	return structure ;
}

uint64_t sizeList( struct LinkedList *list){
	/* Function returns size of list(Logically). */
	struct LinkedList *cur = list ;

	uint64_t count = 0 ;

	while(cur->next){
		++count;
		cur = cur->next ;
	}

	return count ;
}

void addEl(struct LinkedList *start, void *pdata){
	struct LinkedList *cur = start ;

	/* Find last pointer */
	while( cur->next ){
		cur = cur->next ;
	}

	/* Get memory for the next element and get it after. */
	cur->next = malloc( sizeof(struct LinkedList) ) ;
	cur->next->next = NULL ;

	/* Initialisation. */
	cur->next->data = pdata ;
}

void *getEl(struct LinkedList *start, uint64_t index){
	/* This function returns a pointer to the data it saved.*/
	struct LinkedList *cur = start ;

	/* Find element my an index. */
	for( uint64_t i=0 ; i<index+1 ; ++i ){
		cur = cur->next ;
	}

	return cur->data ;
}

int8_t insEl(struct LinkedList *start, uint64_t index, void *pdata){
	/* This function inserts an element into a list and returns '0' if it's succesful. */
	struct LinkedList *cur = start ;
	struct LinkedList *last;

	if( sizeList(start)<index ){
		/* Too big index. */
		return 1 ;
	}

	for( uint64_t i=0 ; i<index ; ++i ){
		cur = cur->next ;
	}

	/* To save element which will go after inserted. */
	last = cur->next ;

	/* Initialisation of next element. */
	cur->next       = crtList();
	cur->next->next = last ;
	cur->next->data = pdata ;

	/* Succesful inserted. */
	return 0 ;
}

int8_t delEl(struct LinkedList *start, uint64_t index){
	struct LinkedList *cur = start ;
	struct LinkedList *last;

	if( sizeList(start)<=index ){
		/* Too big index. */
		return 1 ;
	}

	for( uint64_t i=0 ; i<index ; ++i ){
		cur = cur->next ;
	}

	
	/* Deleting. */
	free(cur->next);
	cur->next = cur->next->next ;

	/* Succesful deleted. */
	return 0 ;
}

void printElements(struct LinkedList* list){
	for( int i=0 ; i<sizeList(list) ; ++i ){
		printf("List[%d] = '%d'.\n", i, *(int *)getEl(list, i));
	}
}

int main(int argc, char **argv){
	struct LinkedList *list = crtList() ;

	void *values[128];

	/* Pointers to new data. */
	values[0] = malloc( sizeof(int) );
		*(int *)(values[0]) = 1 ;
	addEl(list, values[0] );

	values[1] = malloc( sizeof(int) );
		*(int *)(values[1]) =  2 ;
	addEl(list, values[1]);

	values[2] = malloc( sizeof(int) );
		*(int *)(values[2]) = 3 ;

	puts("\nBefore inserting to [1]...\n");
	printElements(list);

	insEl(list, 1, values[2]);
	puts("\nAfter inserting to [1]...\n");
	printElements(list);

	puts("\nAfter deleting [2]...\n");
	delEl(list, 2);
	printElements(list);
	
	/* Succesful exit. */
	return 0 ;
}
