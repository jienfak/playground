#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
	int aflag = 0 ;
	int bflag = 0 ;
	char *cvalue = NULL ;
	int index;
	int c;
	opterr = 0 ;
	while( (c=getopt(argc, argv, "abc:")) != -1 ){
		switch(c){
			case 'a' :/* Got -a option. */
				aflag = 1 ;
			break;

			case 'b' :/* Got -b option. */
				bflag = 1 ;
			break;

			case 'c' :/* Got -b option with an argument. */
				cvalue = optarg ;/* Using global variable "optarg". */
			break;

			case '?' :/* Got some error. */
				if(optopt == 'c'){/* optopt - current option which with we are working now. */
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
				}else if( isprint(optopt) ){/* Some checking about printability. */
					fprintf(stderr, "Unknown option `-%c'.\n", optopt);
				}else{
					fprintf(
					   "Unknown option character `\\x%x'.\n",
					   optopt
					);
					return 1 ;
				}
				return 1 ;
			break;
			
			default:
				abort(); /* Any stuipd mistake we got. */
			break;
		}
	}
	printf(
	   "aflag='%d', bflag='%d', cvalue='%s'\n",
	   aflag,       bflag,      cvalue
	);

	for( index=optind ; index<argc ; ++index ){/* Using global variable "optind". */
		printf("Non-option argument '%s\n'.", argv[index]);
	}
	/* Succesful exit. */
	return 0 ;
}
