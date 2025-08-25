# Nombre del compilador a usar (GNU C++ Compiler)
CXX = g++

# Opciones del compilador:
# -Wall: activa todas las advertencias útiles
# -std=c++17: usa el estándar C++17
# -Iinclude: le dice al compilador que busque archivos .h en la carpeta "include"
CXXFLAGS = -Wall -std=c++17 -Iinclude

# Archivos fuente del proyecto (.cpp)
SRC = src/difusion_model.cpp src/flow.cpp main.cpp

# Archivos objeto correspondientes (.o), usando una sustitución de sufijo
#.o no se generan por separado en la regla final
OBJ = $(SRC:.cpp=.o)
# Nombre del ejecutable que se generará
TARGET = difusion_model.out

# Regla por defecto: si haces "make" sin argumentos, esta es la que se ejecuta
all: $(TARGET)

# Cómo construir el ejecutable final
# Compila todos los archivos fuente con las banderas dadas

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) 

# ===============================
# Compilar test_geometria
# ===============================
test_geometria: src/difusion_model.cpp test/test_geometria.cpp
	$(CXX) $(CXXFLAGS) -o test_geometria.out src/difusion_model.cpp test/test_geometria.cpp


# Regla para limpiar (eliminar) el ejecutable
# Útil para dejar el proyecto limpio antes de recompilar
clean:
	rm -f $(TARGET)\
			difusion_model.out\
			test_geometria.out\
	rm -rf datos

# ====================================================
# Cómo usarlo: digitar en consola las instrucciones
# ====================================================
# make                 --> Compilar el programa principal
# ./difusion_model.out --> Ejecutar
# make test_geometria  -->  Compilar y ejecutar la geometría 
# ./test_geometria.out
# make clean           --> Limpiar los archivos .out y otras carpetas

# Forma alternativa de compilación del progrma principal:
# g++ -Wall -std=c++17 -Iinclude src/difusion_model.cpp main.cpp -o difusion_model.out
