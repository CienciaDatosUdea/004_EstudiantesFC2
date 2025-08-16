# Define el compilador C++ que usarás
CXX = g++

# Define las opciones de compilación
CXXFLAGS = -Wall -I include

# Define los archivos fuente (.cpp)
SRCS = src/complejos.cpp main.cpp

# Define los archivos objeto (.o)
OBJS = $(SRCS:.cpp=.o)

# Define el nombre del ejecutable final
TARGET = complejos

# Regla por defecto para construir el programa
all: $(TARGET)

# Regla para vincular los archivos objeto y crear el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# Regla genérica para compilar archivos .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nueva regla para compilar y luego ejecutar
run: $(TARGET)
	./$(TARGET)

# Regla para limpiar los archivos generados (objetos y ejecutable)
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean