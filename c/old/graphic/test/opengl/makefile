# Template for simple C programs.
TARGET	= a.out
PREFIX	= /usr/local/bin
SRCS	= $(wildcard ./*.c)
OBJS	= $(SRCS:.c=.o)
CFLAGS  = -pipe -W -Wall -Wextra -ansi -Wunused-variable -pedantic-errors -lglut --verbose \
          -lGL -lGLU

.PHONY: all clean install uninstall

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)

install:
	sudo install $(TARGET) $(PREFIX)

uninstall:
	rm -rf $(PREFIX)/$(TARGET)
