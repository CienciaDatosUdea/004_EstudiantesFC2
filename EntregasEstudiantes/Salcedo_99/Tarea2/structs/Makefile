CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

SRC = src/implementation.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = simulation_structs

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
