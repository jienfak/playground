#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

static int verbose_flag;

int main(int argc, char **argv){
	int c;
	while(1){
		static struct option long_options[] = {
				/* These options set flags. */
				{"verbose", no_argument, &verbose_flag, 1},
				{"brief", no_argument,   &verbose_flag, 0},
				/* These don't. It uses indices. */
				{"add", no_argument,    0, 'a'},
				{"append", no_argument, 0, 'b'},
				{"delete", required_argument, 0, 'd'},
				{"create", required_argument, 0, 'c'},
				{"file",   required_argument, 0, 'f'}
			}
		;
		/* 'getopt_long' stores the option index here. */
		int option_index = 0 ;

		c = getopt_long(argc, argv, "abc:d:f",
				long_options, &option_index
			)
		;
		 /* Detect the end of the options. */
		if( c == -1 ){ break; }

		switch( c ){
			case 0 :
				/* If this option set a flag, do nothing else now. */
				if( long_options[option_index].flag != 0 ){ break; }
				printf("Option %s ;", long_options[option_index].name);
				if( optarg){
					printf("\n");
				}break;
			case 'a' :
				puts("Option -a ;\n");
				break;
			case 'b' :
				puts("Option -b ;\n");
				break;
			case 'c' :
				printf("Option -c with value '%s' ;\n", optarg);
				break;
			case 'd' :
				printf("Option -d with value '%s' ;\n", optarg);
			case 'f' :
				printf("Option -f with value '%s' ;\n");
			case '?' :
				/* 'getopt_long' already printed an error message. */
				break;

			default:
				abort();
		}

		/* Instead reporting '--verbose'
		 * and '--brief' as they are encountered,
		 * we report the final status resulting from them. */
		if(verbose_flag){
			/* Something with this flag to do. */
			puts("'verbose' flag is set;");
		}

		if( optind < argc ){
			printf("Non-option ARGV-elements: ");
			while( optind < argc ){
				printf("%s ", argv[optind]);
			}
			putchar('\n');
		}
	}

	return 0 ;
}
