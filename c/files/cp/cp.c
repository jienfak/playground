#include <unistd.h>

int main(int argc, char *argv[]){
	int fdr = open(argv[1], O_RDONLY);
	if(!fdr){
	};
	int fdw = open(argv[2], O_WRONLY);
	//exit(default)
	return 0;
};
