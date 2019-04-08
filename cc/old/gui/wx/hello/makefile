TARGET = hello

SRCS = ./main.cc
OBJS = $(SRCS:.cc=.o)
CFLAGS = `wx-config --libs` `wx-config --cxxflags`

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CXX) $(OBJS) $(CFLAGS) -o $(TARGET)

.cc.o:
	$(CXX) $(CFLAGS) -c $< -o $@
