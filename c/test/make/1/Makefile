# Define required macros here.
#
# CPP compiler.
CXX     = g++
SHELL   = /bin/sh
OBJS    = hello.o main.o factorial.o
CFLAG   = -Wall -g
# C compiler, but... I'm too lazy about it.
CC      = $(CXX)
INCLUDE = 
LIBS    = -lm

# It shows dependencies from all object files.
hello: ${OBJS}
	${CC} ${CFLAGS} ${INCLUDES} -o $@ ${OBJS} ${LIBS}

# '-' before a command, force to ignore error code.
clean:
	-rm -f *.o core *.core

# Rule for any *.cpp files.
.cpp.o:
	@echo [$@]
	${CC} ${CFLAGS} ${INCLUDES} -c $<
