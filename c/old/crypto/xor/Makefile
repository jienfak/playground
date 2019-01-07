TARGET = xor_crypt
CC = cc
SRCS = $(wildcard *.c )
OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

.c.o:
	$(CC) -o $@ -c $<
