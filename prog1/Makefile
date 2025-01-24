CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -I../lib
LDFLAGS = -L../lib -Wl,-rpath=../lib
LDLIBS = -lstringops -lpthread

TARGET = prog1
SRCS = prog1.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean