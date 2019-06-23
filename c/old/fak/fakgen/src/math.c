#include "./header.h"

ul_t powO(ul_t sum, us_t power){
	ul_t buf = 1;
	for(ul_t i = 0 ; i<power ; ++i){
		buf*=sum;
	}
	return buf;
}

int bitsEqTrue(ul_t num){
	int buf = 0;
	for(int i = 0; i<64 ; ++i){
		if( num & (1<<i)){
			++buf;
		}
	}
	return buf;
}

us_t max_arr (us_t arr[], us_t size) {
	us_t max = 0;
	for( int i=0 ; i<size ; ++i ){
		max = arr[i]>max ? arr[i]:max;
	}
	return max;
}

us_t maxRepsKws(char *chr_arr[], us_t size_chr, us_t num_kws){
	us_t max_reps = 0 ;
	for( int i=0; i<size_chr ; ++i ){
			us_t counter = 0;
			for(us_t x=0 ; x<size_chr ; ++x){
				if( (chr_arr[i])==(chr_arr[x]) ){
					++counter;
				}
			}
			
			if(counter>max_reps){
				max_reps = counter;
			}
	}

	return max_reps;
}
