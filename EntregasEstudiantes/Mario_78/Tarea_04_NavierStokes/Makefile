# Nombre del compilador a usar (GNU C++ Compiler)
CXX = g++

# Opciones del compilador
CXXFLAGS = -Wall -std=c++17 -Iinclude

# Archivos fuente del proyecto (.cpp)
SRC = src/flow.cpp main.cpp

# Archivos objeto correspondientes (.o)
OBJ = $(SRC:.cpp=.o)

# Nombre del ejecutable que se generará
TARGET = flow.out

# Regla por defecto: compilar y asegurar que data/ existe
all: $(TARGET) prepare_dirs

# Cómo construir el ejecutable final
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Crear carpeta data si no existe
prepare_dirs:
	mkdir -p data

# Regla para limpiar
clean:
	rm -f $(TARGET)
	rm -rf data
