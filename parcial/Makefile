CXX := g++
CXXFLAGS := -O3 -std=c++17 -Wall -Wextra -Iinclude

SRC := src/fdtd.cpp main.cpp
OBJ := $(SRC:.cpp=.o)
BIN := fdtd

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN) fdtd_output.csv

.PHONY: all clean
