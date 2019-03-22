TARGET = chr
CC = cc
SRCS = $(wildcard *.c )
OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

clean: 
	rm $(OBJS) $(TARGET)
.c.o:
	$(CC) -o $@ -c $<
