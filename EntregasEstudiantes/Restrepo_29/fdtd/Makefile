CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC = src/main.cpp src/fdtd.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = sim

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Reglas de compilación con dependencia explícita del header
src/main.o: src/main.cpp include/fdtd.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o src/main.o

src/fdtd.o: src/fdtd.cpp include/fdtd.h
	$(CXX) $(CXXFLAGS) -c src/fdtd.cpp -o src/fdtd.o

run: $(TARGET)
	./$(TARGET)
	python3 src/simular.py

clean:
	rm -f src/*.o $(TARGET) campos.csv