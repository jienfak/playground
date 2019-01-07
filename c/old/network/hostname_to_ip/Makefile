#This program generates all needed you combinations of words
TARGET	= hostname_to_ip
SRCS	= $(wildcard *.c)
OBJS	= $(SRCS:.c=.o);

.PHONY: all clean install uninstall

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

.c.o:
	$(CC) $(CFLAGS)	-c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)

#install:
#	sudo install bin/$(TARGET) $(PREFIX)

#uninstall:
#	rm -rf $(PREFIX)/$(TARGET)
