#include <stdio.h>
#include <string.h>
#include <dbg/hexdump.h>
#define BUF_SIZE 256

int main(int argc, char **argv){
	puts("[HEXDUMP]Before vars and buffers definitons.");
	hexdump(&argc, BUF_SIZE);
	int var = 5;
	char buffer1[8], buffer2[8];
	puts("[HEXDUMP]After.");
	hexdump(buffer2, BUF_SIZE);

	strcpy(buffer1, "one");
	strcpy(buffer2, "two");

	printf(	"[BEFORE] buffer2 is at %p and contains '%s'.\n",
		buffer2, buffer2
	);
	printf(	"[BEFORE] buffer1 is at %p and contains '%s'.\n",
		buffer1, buffer1
	);
	printf(	"[BEFORE] value is at %p and is %d (0x%08x).\n",
		&var, var, var
	);
	puts("[HEXDUMP]:");
	hexdump(buffer2, BUF_SIZE);

	printf(	"\n[STRCPY] copying %d bytes into buffer2.\n\n",
		strlen(argv[1])
	);
	strcpy(buffer2, argv[1]);

	printf(	"[AFTER] buffer2 is at %p and contains '%s'\n",
		buffer2, buffer2
	);
	printf(	"[AFTER] buffer1 is at %p and contains '%s'\n",
		buffer1, buffer1
	);
	printf(	"[AFTER] var is at %p and is %d (0x%08x)\n",
		&var, var, var
	);
	puts("[HEXDUMP]:");
	hexdump(buffer2, BUF_SIZE);
	/* Exit. */
	return 0;
}
