CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -I../lib
LDFLAGS = -L../lib -Wl,-rpath=../lib
LDLIBS = -lstringops

TARGET = prog2
SRCS = prog2.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean