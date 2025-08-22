# Compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -Wall -std=c++17 -Iinclude

# Archivos fuente
SRC = main.cpp src/fdtd.cpp

# Nombre del ejecutable
TARGET = fdtd.out

# Regla por defecto
all: $(TARGET)

# Cómo construir el ejecutable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Limpiar
clean:
	rm -f $(TARGET)
	rm -rf docs/datos.txt
