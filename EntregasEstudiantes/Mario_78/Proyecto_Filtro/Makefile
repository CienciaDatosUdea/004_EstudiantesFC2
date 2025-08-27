# Nombre del compilador a usar (GNU C++ Compiler)
CXX = g++

# Opciones del compilador:
# -Wall: activa todas las advertencias útiles
# -std=c++17: usa el estándar C++17
# -Iinclude: le dice al compilador que busque archivos .h en la carpeta "include"
CXXFLAGS = -Wall -std=c++17 -Iinclude

# Archivos fuente del proyecto (.cpp)
SRC = src/fir_filter.cpp src/flow.cpp main.cpp

# Archivos objeto correspondientes (.o)
OBJ = $(SRC:.cpp=.o)

# Nombre del ejecutable que se generará
TARGET = fir_filtro.out

# Carpeta de salida para los .txt
DATADIR = datos

# Regla por defecto
all: $(TARGET)

# Cómo construir el ejecutable final
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Regla para limpiar
clean:
	rm -f $(TARGET) $(OBJ)
	rm -f $(DATADIR)/*.txt

# ====================================================
# Cómo usarlo: digitar en consola las instrucciones
# ====================================================
# make              --> Compilar el programa principal
# ./fir_filtro.out  --> Ejecutar
# make clean        --> Limpiar ejecutables, .out y archivos .txt de datos/
