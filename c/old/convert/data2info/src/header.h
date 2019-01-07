#ifndef UMainHeaderH
#define UMainHeaderH

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <inttypes.h>

#define BUFSIZE 102


int str_switch( char **strarr, int arrlen, char *str );
int chr_switch(char *str, char chr);

/* converting from cases */
char *strlow(char *dest, char *src);
char *strup(char *dest, char *src);
int grpsize(char **group);

#endif
