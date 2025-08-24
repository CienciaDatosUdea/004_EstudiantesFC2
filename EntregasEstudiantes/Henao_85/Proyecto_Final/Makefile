# Compilador a usar
CXX = g++

# Opciones del compilador
CXXFLAGS = -Wall -std=c++17 -Iinclude

# Archivos fuente
SRC = src/wavepacket.cpp src/TDSE.cpp src/TISE.cpp main.cpp

# Nombre del ejecutable
TARGET = SE.out

# Regla por defecto
all: $(TARGET)

# Cómo compilar el ejecutable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Limpiar archivos generados
clean:
	rm -f $(TARGET) *.o


