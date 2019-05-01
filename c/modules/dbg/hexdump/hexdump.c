#include "../hexdump.h"

int64_t fhexdump(FILE *fp, uchar *data, uint64_t dsize){
	uint64_t linebytes, bytes = fprintf(fp, HEX_TABLE_HEADER, data) ;
	if( bytes == EOF){
		/* Could not output it. */
		return EOF ;
	}
	uint64_t iend, ibuf, j;
	
	for( uint64_t i=0 ; i<dsize ; ++i ){
		/* Print bias. */
		bytes += fprintf(fp, "%16x|", i) ;
		
		for( j=i, iend=i+16 ; j<iend && j<dsize ; ++j ){
			/* Hex. */
			bytes += fprintf(fp, "%2x ", data[j]) ;
		}
		/* Got to the end of data or row. */
		ibuf = j ;
		
		/* Compensate. */
		for( j=0, iend=(16-ibuf%16)%16 ; j<iend ; ++j){
			bytes += fprintf(fp, "   ") ;
		}
		
		bytes += fprintf(fp, "   ") ;
		for( j=i ; j<ibuf ; ++j ){
			/* Chars to show hex. */
			if( isprint(data[j]) ){
				bytes += fprintf(fp, "%c", data[j]) ;
			}else{
				bytes += fprintf(fp, ".") ;
			}
		}
		
		i = ibuf - 1 ;
		bytes += fprintf(fp, "\n") ;
	}

	return bytes ;
}

int64_t hexdump(uchar *data, uint64_t dsize){
	return fhexdump(stdout, data, dsize) ;
}
