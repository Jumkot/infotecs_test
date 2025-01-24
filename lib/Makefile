CXX = g++
CXXFLAGS = -fPIC -shared -Wall -Wextra -O2
TARGET = libstringops.so
SRC = libstringops.cpp
HEADER = libstringops.h

all: $(TARGET)

$(TARGET): $(SRC) $(HEADER)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean