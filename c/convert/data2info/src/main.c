#include "./header.h"

void using(char *progname){
	printf("Using: %s type_data data type_info\n", progname);
}

int main(int argc, char **argv){
	if(argc<4){
		/* help */
		using(argv[0]);
		exit(1);
	}

	char **types = {
		"ascii",
		"int",
		NULL
	};
	uint8_t numtypes = grpsize(types); 
	char buf[BUFSIZE];

	strlow(argv[1]);
	strlow(argv[3]);

	/* with start we convert to the bin format */
	switch( str_switch(types, numtypes, argv[1]) ){
		case str_switch(types, numtypes, "int"):
			break;
		case str_switch(types, numtypes, "ascii"):
			break;
	}

	/* after we convert from bin to needed format */

	/* succesful exit */
	return 0;
}
