# Nombre del compilador a usar (GNU C++ Compiler)
CXX = g++

# Opciones del compilador:
# -Wall: activa todas las advertencias útiles
# -std=c++17: usa el estándar C++17
# -Iinclude: le dice al compilador que busque archivos .h en la carpeta "include"
CXXFLAGS = -Wall -std=c++17 -Iinclude

# Archivos fuente del proyecto (.cpp)
SRC = src/flow.cpp  main.cpp

# Archivos objeto correspondientes (.o), usando una sustitución de sufijo
OBJ = $(SRC:.cpp=.o)

# Nombre del ejecutable que se generará
TARGET = flow.out

# Nombre del archivo GIF a eliminar (ajusta el nombre si es necesario)
GIF_FILE = dinamica_de_fluidos.gif

# Regla por defecto: si haces "make" sin argumentos, esta es la que se ejecuta
all: $(TARGET)

# Cómo construir el ejecutable final
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Regla para limpiar (eliminar) el ejecutable, archivos .txt en data/ y el GIF
clean:
	rm -f $(TARGET)
	rm -f data/*.txt
	rm -f $(GIF_FILE)