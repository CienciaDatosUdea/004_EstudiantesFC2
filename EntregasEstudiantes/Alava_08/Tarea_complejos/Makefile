# Compilador
CXX = g++
CXXFLAGS = -Wall -Iinclude

# Archivos
SRC = src/complejos.cpp main.cpp
OBJ = $(SRC:.cpp=.o)

# Ejecutable
TARGET = complejos.out

# Regla por defecto
all: $(TARGET)

# Enlazar ejecutable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Compilar objetos
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(OBJ) $(TARGET)
