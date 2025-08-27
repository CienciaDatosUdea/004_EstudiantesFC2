# Compilador a usar
CXX = g++

# Opciones del compilador
# -Wall: advertencias
# -std=c++17: estándar moderno
# -Iinclude: para encontrar los headers en include/
CXXFLAGS = -Wall -std=c++17 -Iinclude

# Archivos fuente del proyecto
SRC = src/fdtd.cpp main.cpp

# Nombre del ejecutable
TARGET = fdtd_sim.out

# Regla por defecto
all: $(TARGET)

# Cómo compilar el ejecutable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Limpiar archivos generados
clean:
	rm -f $(TARGET) *.o

