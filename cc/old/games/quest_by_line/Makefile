# Quests by files program.
CC      = g++
TARGET	= quest_by_line
PREFIX	= /usr/local/bin
SRCS    = fs.cc main.cc line_work.cc handle_paragraph.cc
OBJS	= $(SRCS:.cc=.o);
CFLAGS  = 
LINE_WORK_SRCS = line_work.cc unit_line_work.cc fs.cc
LINE_WORK_OBJS = $(LINE_WORK_SRCS:.cc=.o)

.PHONY: all clean install uninstall unit_line_work

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

.cc.o:
	$(CC) $(CFLAGS)	-c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)

install:
	sudo install bin/$(TARGET) $(PREFIX)

uninstall:
	rm -rf $(PREFIX)/$(TARGET)

unit_line_work:$(LINE_WORK_OBJS)
	@echo "Checking line work..."
	$(CC) -o $@  $(LINE_WORK_OBJS)
	@./unit_line_work	
