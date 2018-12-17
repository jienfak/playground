CC = cc

all:
	$(CC) -c -Wall -Werror -fpic foo.c
	$(CC) -shared -o libfoo.so foo.o
	$(CC) -Wall -o test main.c -L$(shell pwd) -lfoo
