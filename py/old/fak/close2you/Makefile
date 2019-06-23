TARGET	= close2you
PREFIX	= /usr/local/bin
SHARE	= /usr/share/$(TARGET)
SRCS	= ./src

.PHONY: all install uninstall 

all:$(TARGET)

$(TARGET):

install:
	sudo install $(TARGET) $(PREFIX)
	sudo mkdir $(SHARE)
	sudo cp -r --preserve LICENSE $(SRCS) $(SHARE)/

uninstall:
	sudo rm -rf $(PREFIX)/$(TARGET)
	sudo rm -rf $(SHARE)
