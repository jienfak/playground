WORDS    = abcd.c efgh.c 1234.so 5678.o
EMPTYWORDS = $(WORDS:.\*=)
NEWWORDS = $(WORDS:.c=.o)
NEWWORDS1= $(addprefix suf_,   $(WORDS) )
NEWWORDS2= $(addsuffix _preff, $(WORDS) )

all:
	@echo Empty words...
	@echo $(EMPTYWORDS)
	@echo Replacing...
	@echo $(NEWWORDS)
	@echo --------------
	@echo Adding prefix...
	@echo $(NEWWORDS1)
	@echo --------------
	@echo Adding suffix...
	@echo $(NEWWORDS2)
