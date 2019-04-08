# My string module which I'm trying to write with Dvorak.
SRCS  = ./find_sub.c
OBJS  = $(SRCS:.c=.o)

UNIT_TEST_SRC = ./unit_test.c
UNIT_TEST     = $(UNIT_TEST_SRC:.c=)
UNIT_TEST_OBJ = $(UNIT_TEST_SRC:.c=.o)


.PHONY: all clean

all:$(OBJS)

test:$(OBJS) $(UNIT_TEST_OBJ)
	$(CC) $(UNIT_TEST_OBJ) $(OBJS) -o $(UNIT_TEST)
	exec $(UNIT_TEST)

.c.:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf  $(OBJS) $(UNIT_TEST)
