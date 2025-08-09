# Nombre del compilador a usar (GNU C++ Compiler)
CXX = g++

# Opciones del compilador:
# -Wall: activa todas las advertencias útiles
# -std=c++17: usa el estándar C++17
# -Iinclude: le dice al compilador que busque archivos .h en la carpeta "include"
CXXFLAGS = -Wall -std=c++17 -Iinclude


# Archivos fuente del proyecto (.cpp)
SRC = src/difusion_model.cpp  src/main.cpp

# Archivos objeto correspondientes (.o), usando una sustitución de sufijo
#.o no se generan por separado en la regla final
OBJ = $(SRC:.cpp=.o)
# Nombre del ejecutable que se generará
TARGET = difusion_model.out

# Archivos fuente para poder compilar el test
TEST_SRC = src/difusion_model.cpp test/test_geometria.cpp
TEST_TARGET = test.out

.PHONY: all test clean

# Regla por defecto: si haces "make" sin argumentos, esta es la que se ejecuta
# Regla por defecto: siempre recompila
all:
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Construir y ejecutar el test
test:
	@$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC)


# Limpiar
clean:
	@rm -f $(TARGET) $(TEST_TARGET)

