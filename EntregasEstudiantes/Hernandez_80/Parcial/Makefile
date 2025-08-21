# Makefile para Parcial2 - FDTD 

CXX       := g++
CXXFLAGS  := -O2 -std=c++17 -Wall -Iinclude
LDFLAGS   :=

SRC       := src/fdtd.cpp main.cpp
OBJ       := $(SRC:.cpp=.o)
TARGET    := main.exe

.PHONY: all clean run help

all: $(TARGET)

# Enlazar
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@ $(LDFLAGS)
	@echo "=> Ejecutable $(TARGET) creado."

# Regla genérica de compilación
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ejecutar simulación y generar fields.dat
run: $(TARGET)
	./$(TARGET) periodic 1500 0.49 fields.dat 1.0
	@echo "=> Simulación completada, datos guardados en fields.dat"

# Limpieza
clean:
	del /Q $(OBJ) $(TARGET) fields.dat 2>nul || true
	@if exist analysis_outputs rmdir /S /Q analysis_outputs
	@echo "=> Limpieza completa."

# Ayuda
help:
	@echo "Targets disponibles:"
	@echo "  make         -> compila el ejecutable main.exe"
	@echo "  make run     -> ejecuta simulación con parámetros por defecto (periodic, 1500 pasos, beta=0.49, dz=1.0)"
	@echo "  make clean   -> borra objetos, ejecutable y fields.dat"
	@echo "  make help    -> muestra esta ayuda"
