# Nombre del compilador
CXX := g++

# Flags del compilador: warnings, C++17 y buscar headers en la carpeta actual
CXXFLAGS := -Wall -std=c++17 -I.

# Ficheros fuente
SRC := Tarea02_main.cpp src.cpp

# Nombre del ejecutable
TARGET := Tarea02.out

# Regla por defecto
all: $(TARGET)

# Cómo enlazar el ejecutable a partir de los .cpp
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para regenerar únicamente objetos (opcional si quieres compilación incremental):
# SRC_O := $(SRC:.cpp=.o)
# $(SRC_O): %.o: %.cpp
#	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar ejecutable y posibles .o
clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
