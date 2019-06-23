#include "./header.h"

unsigned long parseArgs ( char **argv, int argc, int numhndls,
			char **long_hndls,
			char *shrt_hndls,
			hndl_f hndls[],
			char **out_argv,
			char **lost_argv
		) {

	unsigned long flags = 0;

	for(int i=1 ; i<argc ; ++i){
		int hndl_index = strSwitch(long_hndls, numhndls, argv[i]+2);

		if(  argv[i]!=NULL && ( strlen(argv[i])>=2 ) && argv[i][0]=='-' && argv[i][1]=='-' && hndl_index>=0  ){

			if(hndl_index>=0){	//found handler
				int bias = hndls[hndl_index]( &flags, argv, argc, i, 1, out_argv);

				for(int endelm=i+bias+1 ; i<endelm ; ++i){
					argv[i] = NULL;
				}

				i+=bias;
			}else{			// unknown option
				printf("%s:Unknown option '%s'\n", PROGNAME, argv[i]);
				exit(1);
			}

		}

	}

	for(int i=1 ; i<argc ; ){

		if( argv[i]!=NULL && argv[i][0]== '-' && argv[i][1]!='-'){
			int bias = 0;
			char *curchr = argv[i]+1;

			while(*curchr){

				int hndl_index = chrSwitch(shrt_hndls, *curchr);
				#ifdef IS_DBG
				printf("hndl_index=%d\n", hndl_index);
				#endif

				if(hndl_index>=0){
					bias += hndls[hndl_index](&flags, argv, argc, i, bias+1, out_argv);
				}else{
					printf("%s:Unknown option '-%c'\n", PROGNAME, *curchr);
					exit(1);
				}

				++curchr;

			}

			#ifdef IS_DBG
			printf("'i' = '%d'\n", i);
			printf("'i+bias+1' = '%d'\n", i+bias+1);
			#endif

			for(int endelm=i+bias+1 ; i<endelm ; ++i){
				argv[i] = NULL;
			}
			continue;
		}
		++i;

	}

	for(int i=1, x=0 ; i<argc ; ++i){
		if( argv[i] ){
			lost_argv[x++] = argv[i];
		}
	}

	return flags;

}
