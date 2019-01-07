TARGET = empty_window
CC = cc
SRCS = empty_window.c 
OBJS = $(SRCS:.c=.o)
CFLAGS = `pkg-config -- cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`

all: $(OBJS)
	$(CC) -o ./$(TARGET) $(OBJS) $(CFLAGS)

.c.o:
	$(CC) -c $< -o $@.o
