CC = cc
TARGET = power.so
SRCS = ./hellofunc.c

all:$(TARGET)

$(TARGET):
	$(CC) -Wall -shared -fPIC -o $(TARGET) -I/usr/include/lua5.1 -llua5.1 $(SRCS)

clean:
	rm -rf $(TARGET)
