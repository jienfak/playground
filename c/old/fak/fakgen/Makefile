#This program generates all needed you combinations of words
TARGET  = fakgen
PREFIX  = /usr/local/bin
SRCS    = ./src/main.c ./src/args.c ./src/passgen.c ./src/string.c ./src/handlers.c ./src/math.c
OBJS    = $(SRCS:.c=.o)

.PHONY: all clean install uninstall

all:$(TARGET)

$(TARGET): $(OBJS)
	-mkdir ./bin
	$(CC) -o ./bin/$(TARGET) $(OBJS) $(CFLAGS)

.c.o:
	$(CC) $(CFLAGS)	-c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)

install:
	sudo install bin/$(TARGET) $(PREFIX)

uninstall:
	rm -rf $(PREFIX)/$(TARGET)
