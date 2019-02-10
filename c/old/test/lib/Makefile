TARGET          = test
SRCS            = test.c foo.c
OBJS            = test.o
LIBS            = foo
LIBOBJS         = $(LIBS:=.o)
LIBSHAREDOBJECTS= $($())
LIB_DIR         = /usr/lib
CFLAGS          = 
CC              = cc


all:$(TARGET)

install_lib:
	sudo install $(LIBSHAREDOBJECTS) $(LIB_DIR)
remove_lib:
	sudo rm -i $(LIB_DIR)/$(LIBSHAREDOBJECTS)

$(TARGET): $(OBJS) $(LIBSHAREDOBJECTS)
	$(CC) -Wall -fPIC -o $(TARGET) -l $(LIBS) -L$(shell pwd) $(OBJS)

$(LIBSHAREDOBJECTS): $(LIBOBJS)
	$(CC) -shared -o $@ $<

.c.o:
	$(CC) -c -Wall -Werror -fpic $< -o $@

.o.so:
	$(CC) -shared -o $@ $<

delete_all:
	rm -rf *.o *.so $(TARGET) 
