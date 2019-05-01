# Simple local sniffer.
TARGET  = a.out
PREFIX  = /usr/local/bin
SRCS    = $(wildcard ./src/*.c) $(S)/c/modules/dbg/hexdump/hexdump.c
OBJS    = $(SRCS:.c=.o)
CFLAGS  =

.PHONY: all clean install uninstall

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o bin/$(TARGET) $(OBJS) $(CFLAGS)

.c.o:
	$(CC) $(CFLAGS)	-c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)

install:
	sudo install bin/$(TARGET) $(PREFIX)

uninstall:
	rm -rf $(PREFIX)/$(TARGET)
