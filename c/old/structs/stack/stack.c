#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

typedef void * pvoid ;

struct Stack {
	/* Stack for containing any values. */
	uint64_t size;
	uint64_t peak_index;
	pvoid *start;
} ;

struct Stack *crtStack(uint64_t size){
	/* This function returns pointer to the new stack. */

	struct Stack *ret = malloc(sizeof(struct Stack)) ;

	ret->size = size ;
	ret->peak_index = 0 ;
	ret->start = malloc(sizeof(pvoid)*size) ;

	return ret ;
}

int pushEl(struct Stack *stack, pvoid el){
	/* Pushing an element of stack. */
	if( stack->peak_index>stack->size ){
		/* Could not push the value. */
		return 1 ;
	}

	stack->start[++stack->peak_index] = el ;

	/* Success. */
	return 0 ;
}

pvoid *popEl(struct Stack *stack){
	/* Popping an element of stack. */
	if(stack->peak_index >= stack->size){
		/* Could not pop. */
		return NULL ;
	}

	/* Success. */
	return stack->start[stack->peak_index--] ;
}

#ifndef __MAIN_FILE_GOT

int main(int argc, char **argv){
	struct Stack *stack = crtStack(128) ;
	pvoid values[128];

	values[0] = malloc(sizeof(int)) ;
	values[1] = malloc(sizeof(int)) ;
	values[2] = malloc(sizeof(int)) ;
		*(int *)values[0] = 1 ;
		*(int *)values[1] = 2 ;
		*(int *)values[2] = 3 ;

	pushEl(stack, values[0] );
	pushEl(stack, values[1]);
	pushEl(stack, values[2]);

	printf("%d\n", *(int *)popEl(stack));
	printf("%d\n", *(int *)popEl(stack));

	/* Successful exit. */
	return 0 ;
}

#endif /* __MAIN_FILE_GOT */
