CXX = g++
CXXFLAGS = -O2 -std=c++17 -Iinclude

SRC = src/geometry.cpp src/boundary.cpp src/solver.cpp main.cpp
OBJ = $(SRC:.cpp=.o)

BIN_DIR = bin
TARGET = $(BIN_DIR)/diffusion

all: $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

run: $(TARGET)
	$(TARGET)
	python3 viz.py

clean:
	rm -f src/*.o main.o
	rm -f $(TARGET)
	rm -f diffusion.gif
	rm -f data/solucion_final.txt
