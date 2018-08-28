# Define required macros here.
CXX     = g++
SHELL   = /bin/sh
OBJS    = hello.o main.o factorial.o
CFLAG   = -Wall -g
CC      = $(CXX)
INCLUDE = 
LIBS    = -lm

hello: ${OBJS}
	${CC} ${CFLAGS} ${INCLUDES} -o $@ ${OBJS} ${LIBS}

clean:
	-rm -f *.o core *.core

.cpp.o:
	@echo [$@]
	${CC} ${CFLAGS} ${INCLUDES} -c $<
