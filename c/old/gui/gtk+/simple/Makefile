CC     = cc
TARGET = simple
SRCS   = simple.c
OBJS   = $(SRC:.c=.o)
CFLAGS = `pkg-config --libs --cflags gtk+-2.0`

all:$(TARGET)

$(TARGET):$(OBJS)

.c.o:
	$(CC) -o $@ $< $(CFLAGS)


