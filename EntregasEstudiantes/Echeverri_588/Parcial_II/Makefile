# Makefile para proyecto FDTD
# Compilador y flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2
DEBUG_FLAGS = -g -DDEBUG

# Directorios
INCLUDE_DIR = include
SRC_DIR = src

# Archivos fuente
SOURCES = main.cpp $(INCLUDE_DIR)/fdtd.cpp
HEADERS = $(SRC_DIR)/fdtd.h

# Ejecutable
TARGET = fdtd_simulation.out

all: $(TARGET)

# Compilar directamente a ejecutable
$(TARGET): $(SOURCES) $(HEADERS)
	@echo "Compilando proyecto FDTD..."
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) $(SOURCES) -o $(TARGET)
	@echo "✓ Compilación exitosa: $(TARGET)"

# Compilación en modo debug
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)
	@echo "✓ Compilación en modo debug completada"

# Ejecutar el programa
run: $(TARGET)
	@echo "Ejecutando simulación FDTD..."
	./$(TARGET)

# Ejecutar visualización Python (opcional)
visualize: $(TARGET)
	@echo "Ejecutando simulación y visualización..."
	./$(TARGET)
	@if [ -f python/sim_fdtd.py ]; then \
		echo "Iniciando visualización Python..."; \
		cd python && python3 sim_fdtd.py; \
	else \
		echo "Archivo de visualización no encontrado"; \
	fi

# Limpiar archivos compilados
clean:
	@echo "Limpiando archivos compilados..."
	rm -f $(OBJECTS) $(TARGET)
	@echo "✓ Limpieza completada"

# Limpiar solo objetos (mantener ejecutable)
clean-obj:
	@echo "Limpiando archivos objeto..."
	rm -f $(OBJECTS)
	@echo "✓ Objetos eliminados"

# Instalar dependencias Python (opcional)
install-python:
	@echo "Instalando dependencias Python..."
	pip3 install numpy matplotlib scipy
	@echo "✓ Dependencias Python instaladas"

# Verificar estructura del proyecto
check-structure:
	@echo "Verificando estructura del proyecto..."
	@echo "Archivos fuente encontrados:"
	@ls -la main.cpp 2>/dev/null || echo "  ⚠ main.cpp no encontrado"
	@ls -la $(INCLUDE_DIR)/fdtd.cpp 2>/dev/null || echo "  ⚠ include/fdtd.cpp no encontrado"
	@ls -la $(SRC_DIR)/fdtd.h 2>/dev/null || echo "  ⚠ src/fdtd.h no encontrado"
	@ls -la python/sim_fdtd.py 2>/dev/null || echo "  ⚠ python/sim_fdtd.py no encontrado (opcional)"

# Mostrar ayuda
help:
	@echo "Makefile para proyecto FDTD"
	@echo ""
	@echo "Comandos disponibles:"
	@echo "  make all          - Compilar el proyecto (default)"
	@echo "  make debug        - Compilar en modo debug"
	@echo "  make run          - Compilar y ejecutar"
	@echo "  make visualize    - Ejecutar con visualización Python"
	@echo "  make clean        - Limpiar todos los archivos compilados"
	@echo "  make clean-obj    - Limpiar solo archivos objeto"
	@echo "  make install-python - Instalar dependencias Python"
	@echo "  make check-structure - Verificar estructura del proyecto"
	@echo "  make help         - Mostrar esta ayuda"
	@echo ""
	@echo "Estructura esperada:"
	@echo "  main.cpp                 - Programa principal"
	@echo "  include/fdtd.cpp         - Implementación FDTD"
	@echo "  src/fdtd.h              - Headers FDTD"
	@echo "  python/sim_fdtd.py      - Visualización (opcional)"

.PHONY: all debug run visualize clean clean-obj install-python check-structure help