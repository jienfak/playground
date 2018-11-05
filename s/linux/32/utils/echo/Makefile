# Makefile for assembler projects.
# Out file.
TARGET = ./bin/rls/echo
# Place to install.
PREFIX = /usr/local/bin
# Your codes.
SRCS   = ./src/echo.s
OBJS   = $(SRCS:.s=.o)
# Your Assembler.
CC     = as
BITS   = 32
ARCH   = elf_i386

.PHONY: all clean 

all: $(TARGET)

$(TARGET): $(OBJS)
	ld -m$(ARCH) -s $(OBJS) -o $(TARGET)

.s.o:
	$(CC) --$(BITS) -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)
