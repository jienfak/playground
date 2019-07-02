#include "./header.h"

/* help */
void help(void){
	puts(
"fakgen - program for generating password lists by a keywords.\n\
\n\
Usage:fakgen [keywords] [options]\n\
Options:\n\
\t{--help|-h} - show this message.\n\
\t{--version|-v} - show version of program.\n\
\t{--out|-o} [file] - write dictionary to 'file' or to 'dict.txt'\n\
\t\tif file is not speciefed.\n\
\t{--nwords|-n} [n] -print only n-words length passwords or '4'\n\
\t\tif n is not speciefed.\n\
\t{--max-repeats|-m} [m] -print only m-words repeated words passwords\n\
\t\tor not repeated if not speciefed.\n\
\t{--separators|-s} [seps] - use 'seps' like separators in generated words\n\
\t\tor use ' -_' as a standard value.\n\
\t{--reverse|-r} - add reversed variations of strings to output\
"			
	);

}

int main(us_t cli_argc, char **cli_argv){
	if(cli_argc==1){/* num of arguments */
		printf("%s: Too few arguments, enter 'fakgen -h' or 'fakgen --help' to get help.\n", PROGNAME);
		exit(1);
	}

	hndl_f hndls[] = {/* hndls to handle args */
		versionHndl,
		helpHndl,
		outHndl,
		nwordsHndl,
		separatorsHndl,
		maxrepsHndl,
		reverseHndl
	};

	char *long_hndls[] = {/* long option(GNU style) */
		"version",
		"help",
		"out",
		"nwords",
		"separators",
		"max-repeats",
		"reverse"
	};

	char shrt_hndls[] = {/* short options(UNIX style) */
		'v',
		'h',
		'o',
		'n',
		's',
		'm',
		'r'
	};

	char *stded_argv[PBUFF_SIZE];/* sorted args */
	char *init_kws[PBUFF_SIZE];/* got keywords */

	int num_hndls = strlen(shrt_hndls);/* num of all handles */

	ul_t flags = parseArgs ( /* parsing of arguments CLI(watch './args.c') */
			cli_argv, cli_argc, num_hndls,
			long_hndls,
			shrt_hndls,
			hndls,
			stded_argv,
			init_kws
	);

	if( (flags&VERSION_FLAG) || (flags&HELP_FLAG) ){/* help or version */

		if( flags & HELP_FLAG ){
			help();
		}

		if( flags & VERSION_FLAG ){/* version */
			puts(VERSION);
		}

		exit(0);
	}

	uint8_t num_kws = grpSize(init_kws);
	if(num_kws == 0){
		printf("%s: Keywords not found.", PROGNAME);
		exit(1);
	}

	#ifdef IS_DBG
	printf("%s: Keywords:\n", PROGNAME);
	for(int i=0 ; i<num_kws ; ++i){
		printf("%d)'%s'\n", i, init_kws[i]);
	}
	#endif

	#ifdef IS_DBG
	printf("%s: Making 'fout'", PROGNAME);
	#endif
	FILE *fout = stdout;
	if( flags & OUT_FLAG ){
		fout = fopen(stded_argv[OUTFILE], "w");

		if(!fout){/* file opening error */
			perror(PROGNAME);
			exit(1);
		}
	}
	#ifdef IS_DBG
	printf("%s: made 'fout'", PROGNAME);
	#endif
	
	#ifdef IS_DBG
	printf("%s: Making 'nwords'\n", PROGNAME);
	#endif
	unsigned nwords = num_kws;
	if( flags & NWORDS_FLAG ){
		nwords = atoi(stded_argv[NWORDS]);
	}
	#ifdef IS_DBG
	printf("%s: 'nwords' = '%d'\n", PROGNAME, nwords);
	#endif

	#ifdef IS_DBG
	printf("%s: Making 'max_reps'\n", PROGNAME);
	#endif
	unsigned int max_reps = PBUFF_SIZE;
	if( flags & MAXREPS_FLAG ){
		max_reps = atoi(stded_argv[MAXREPS]);	
	}
	#ifdef IS_DBG
	printf("%s: 'max_reps' = '%d'\n", PROGNAME, max_reps);
	#endif

	#ifdef IS_DBG
	printf("%s: Making 'num_seps'\n", PROGNAME);
	#endif
	us_t num_seps = 0;
	if( flags & SEPS_FLAG ){
		if(stded_argv[SEPS]){
			num_seps = strlen(stded_argv[SEPS]) ;
		}
	}
	#ifdef IS_DBG
	printf("%s: 'num_seps' = '%d'\n", PROGNAME, num_seps);
	#endif

	#ifdef IS_DBG
	printf("%s: Making 'reverse'\n", PROGNAME);
	#endif
	if( flags & REVERSE_FLAG ){
		uint8_t bias = num_kws ;
		char *pbuff;

		for(uint8_t i=0 ; i<num_kws ; ++i){
			if(strlen(init_kws[i]) > 1){
				pbuff = malloc( sizeof(char) * (strlen(init_kws[i])+1) ) ;
				init_kws[bias+i] = strrev(pbuff, init_kws[i]);
			}else{
				--bias;
			}
		}

		num_kws += bias;
	}
	#ifdef IS_DBG
	printf("%s: Made 'reverse'\n", PROGNAME);
	#endif

	/* main part (generating of passwrod and their outputting) */
	for(ul_t num_combs, cur_len=1 ; cur_len<=nwords ; ++cur_len){
		num_combs = powO(num_kws, cur_len) ;

		/* default */
		for( ul_t i=0 ; i<num_combs ; ++i){
			if( !(flags & MAXREPS_FLAG) || isMv(i, init_kws, num_kws, cur_len, max_reps) ){
				fputs(passGen(i, init_kws, num_kws, cur_len, ""), fout );
				fputs("\n", fout);
			}
		}

		/* separators */
		if( flags & SEPS_FLAG ){
			char buf_sep[2]; 
			buf_sep[1] = '\0';

			for( us_t cur_sep=0 ; cur_sep<num_seps ; ++cur_sep){	
				buf_sep[0] = stded_argv[SEPS][cur_sep];

				for( ul_t i=0 ; i<num_combs ; ++i){

					if( !(flags & MAXREPS_FLAG) || isMv(i, init_kws, num_kws, cur_len, max_reps) ){
						fputs(passGen(i, init_kws, num_kws, cur_len, buf_sep), fout );
						fputs("\n", fout);
					}

				}
			}
		}
	}

	/* default exit if all is ok */
	exit(0);
}
