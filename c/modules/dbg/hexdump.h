#ifndef H_HEXDUMP
#define H_HEXDUMP

#include <inttypes.h>
#include <stdio.h>
#include "../shortypes.h"

#define HEX_TABLE_HEADER \
"\n%16x| 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F    0123456789ABCDEF\n \
-------------------------------------------------------------------------------------\n"

/* 'hexdump'. */
/* Prints hex dump in hex-editors like view
 * hexaddresoffdata  0  1  3  4  5  6  7  8  9  A  B  C  D  E  F    0123456789ABCDEF
 * 0000000000000000  hexhexhexhexhexhexhexhexhexhexhexhexhexhexh    charcharcharchar
 * 0000000000000010  hexhexhexhexhexhexhexhexhexhexhexhexhexhexh    charcharcharchar
 * #------^  -  it's bias.
 * ...
 */
int64_t hexdump(uchar *data, uint64_t dsize); /* Alias to print to 'stdout'. */
int64_t fhexdump(FILE *fp, uchar *data, uint64_t dsize ); /* To the file, returns num of printed bytes. */

#endif /* H_HEXDUMP */
