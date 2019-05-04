# Example of how stack overflow works.
TARGET	= a.out
PREFIX	= /usr/local/bin
SRCS	= $(wildcard ./*.c) $(S)/c/modules/dbg/hexdump/hexdump.c
OBJS	= $(SRCS:.c=.o)
CFLAGS  = -fno-stack-protector

.PHONY: all clean install uninstall

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

.c.o:
	$(CC) $(CFLAGS)	-c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)

install:
	sudo install $(TARGET) $(PREFIX)

uninstall:
	rm -rf $(PREFIX)/$(TARGET)
