#include "./header.h"

/* I guess logically will be convert all to
 * bin and after to needed me type from bin.
 * I need write functions kinda of *2bin and bin2*
 */

/* 
 	*2bin functions:
		Prototype has to be like "char *functionName(char *dest, char *src)"
		and be returning a destination.
*/

/* easiest function */
char *str2bin(char *dest, char *src){
	/* I know that's not secure, maybe later 
	* I will change strcpy to strcpy_s
	*/
	strcpy(dest, src);
	return (char *)dest;
}

char *int2bin(char *dest, char *src){
	*( (int *)dest ) = atoi(src);
	return (char *)dest;
}

