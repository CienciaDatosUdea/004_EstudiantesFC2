CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

SRC = src/complex.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = complex_demo

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
