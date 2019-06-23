#include "./header.h"

char *passGen(ul_t numcomb, char *keys[], us_t size, us_t len, char *sep){//generates password by keywords
	static char pass_out[BUFF_SIZE];//buffer for generating
	strcpy(pass_out, "");//clear buffer

	for(ul_t i=0 ; i<len ; ++i){
		strcat(pass_out, keys[ numcomb/((int)powO(size, i))%size ]);	
		strcat(pass_out, sep);
	}

	pass_out[ strlen(pass_out) - strlen(sep) ] = '\0';

	return pass_out ;
}

us_t isMv(ul_t numComb, char *keys[], us_t size, us_t len, us_t max){
	/* This function checks for repeatins and say is that right
	 * or no. */
	
	char *chr_arr[PBUFF_SIZE];/* Password mask before generating. */

	for(ul_t i=0 ; i<len ; ++i){
		chr_arr[i] = keys[  numComb / ( (int)powO(size, i) ) % size  ] ; 
	}

	/* Checking for repeatings. */
	for( int i=0; i<len ; ++i ){
		us_t counter = 0; /* It counts repeatings. */
		for(us_t x=0 ; x<len ; ++x){
			/* Pointer comparing to get faster. */
			if( (chr_arr[i])==(chr_arr[x]) ){
				++counter;
			}
		}
		
		if(counter>max+1){
			/* Got more, than we need. */
			return FALSE ;
		}
	}

	/* Old version, will be deleted. */
	/*if( maxRepsKws(pbuff, len, size) <= max+1 ){
		return TRUE ;
	}else{
		return FALSE ;
	}*/

	/* Not found more than we need. */
	return TRUE ;
}

int grpSize(char **group){
	ul_t i = 0;

	while(*group){
		++group, ++i;
	}

	return i;
}

void grpCpyByBits(ul_t dgrp, char *buff[], char *keys[], ul_t size){
	for(ul_t i = 0 ; i<size ; ++i){
		buff[i] = NULL ;
	}
	for(ul_t x=0, i=0 ; i<size ; ++i){
		if( dgrp & (1<<i) ){
			buff[x++]=keys[i] ;
		}
	}
}
