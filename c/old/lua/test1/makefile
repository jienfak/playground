# Just another test of embedded Lua.
TARGET  = test1
PREFIX  = /usr/local/bin
SRCS    = $(wildcard ./src/*.c)
OBJS    = $(SRCS:.c=.o)
CFLAGS  = -I/usr/local/include -L/usr/local/lib -llua -lm

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
