TARGET	= data2info
PREFIX	= /usr/local/bin
SRCS	= ./src/main.c  ./src/string.c
OBJS	= $(SRCS:.c=.o);

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
