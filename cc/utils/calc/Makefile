# Calc wrote just for lols
CC	= g++
TARGET	= calc
PREFIX	= /usr/local/bin
SRCS	= ./main.c ./calc.c 
OBJS	= $(SRCS:.c=.o);

.PHONY: all clean install uninstall

all:$(TARGET)

$(TARGET): $(OBJS)
	echo "Building " $(TARGET)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

.c.o:
	echo "Compiling " $<
	$(CC) $(CFLAGS)	-c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)

install:
	sudo install bin/$(TARGET) $(PREFIX)

uninstall:
	rm -rf $(PREFIX)/$(TARGET)
