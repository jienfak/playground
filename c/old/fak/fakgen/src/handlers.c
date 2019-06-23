#include "./header.h"

unsigned versionHndl(ul_t *flags, char **argv, int argc, int i, int bias, char **out_argv){
	if( !(*flags & VERSION_FLAG) ){
		*flags |= VERSION_FLAG;
	}

	return 0;
}

unsigned helpHndl(ul_t *flags, char **argv, int argc, int i, int bias, char **out_argv){
	if( !(*flags & HELP_FLAG) ){	
		*flags |= HELP_FLAG;
	}

	return 0;
}

unsigned outHndl(ul_t *flags, char **argv, int argc, int i, int bias, char **out_argv){
	if( !(*flags & OUT_FLAG) ){
		*flags |= OUT_FLAG;

		if( (i+bias)<argc && isKw(argv[i+bias]) ){
			out_argv[OUTFILE] = argv[i+bias];
			return 1;
		}else{
			out_argv[OUTFILE] = "dict.txt";
			return 0;
		}
	}

	return 1;
}

unsigned nwordsHndl(ul_t *flags, char **argv, int argc, int i, int bias, char **out_argv){
	if( !(*flags & NWORDS_FLAG) ){
		*flags |= NWORDS_FLAG;
		
		if( (i+bias)<argc && isKw(argv[i+bias]) ){

			if( !isNum(argv[i+bias]) ){
				printf("%s:'%s' is not a number.\n", PROGNAME, argv[i+bias]);
				exit(1);
			}

			out_argv[NWORDS] = argv[i+bias];
			return 1;
		}else{	//standard num
			out_argv[NWORDS] = "4";
			return 0;
		}
	}

	return 0;
}

unsigned separatorsHndl(ul_t *flags, char **argv, int argc, int i, int bias, char **out_argv){
	if( !(*flags & SEPS_FLAG) ){
		*flags |= SEPS_FLAG;

		if( (i+bias)<argc && isKw(argv[i+bias]) ){	
			out_argv[SEPS] = argv[i+bias];
			return 1;
		}else{
			out_argv[SEPS] = " -_";
			return 0;
		}
	}

	return 0;
}

unsigned maxrepsHndl(ul_t *flags, char **argv, int argc, int i, int bias, char **out_argv){
	if( !(*flags & MAXREPS_FLAG) ){	
		*flags |= MAXREPS_FLAG;

		if( (i+bias)<argc && isKw(argv[i+bias]) ){
			if( !isNum(argv[i+bias])){
				printf("%s: '%s' is not number.\n", PROGNAME, argv[i+bias]);
				exit(1);
			}

			out_argv[MAXREPS] = argv[i+bias];
			return 1;
		}else{
			out_argv[MAXREPS] = "0";
			return 0;
		}
	}

	return 0;
}

unsigned reverseHndl(ul_t *flags, char **argv, int argc, int i, int bias, char **out_argv){
	if( !(*flags & REVERSE_FLAG) ){
		*flags |= REVERSE_FLAG;
	}

	return 0;
}
