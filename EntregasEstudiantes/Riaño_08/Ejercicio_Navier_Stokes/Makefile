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
#.o no se generan por separado en la regla final
OBJ = $(SRC:.cpp=.o)
# Nombre del ejecutable que se generará
TARGET = flow.out

# Regla por defecto: si haces "make" sin argumentos, esta es la que se ejecuta
all: $(TARGET)

# Cómo construir el ejecutable final
# Compila 
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Nueva regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Regla para limpiar (eliminar) el ejecutable
# Útil para dejar el proyecto limpio antes de recompilar
clean:
	rm -f $(TARGET)