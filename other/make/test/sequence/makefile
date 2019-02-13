SRCS = test.c main.c string.c
OBJS = $(SRCS:.c=.o)

	
all: 1 2 3

1:
	@echo Calling 1 rule...

2:
	@echo Calling 2 rule...

3:
	@echo Calling 3 rule...

rule:$(OBJS)

$(OBJS): %.c %.o:$(SRCS)
	@echo $< $@

$(SRCS):
	@echo $< $@
