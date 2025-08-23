CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

SRC = $(wildcard src/*.cpp)
TESTS = $(wildcard tests/*.cpp)
TARGET = test
MAIN = main
MAIN_SRC = main.cpp

.PHONY: all test clean

all: $(MAIN)

$(MAIN): $(SRC) $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(MAIN_SRC) $(SRC)

test: $(SRC) $(TESTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TESTS) $(SRC)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(MAIN) *.gif *.dat *.txt

