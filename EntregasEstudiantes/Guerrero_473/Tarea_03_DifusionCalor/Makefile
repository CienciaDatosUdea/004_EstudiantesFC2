# Compilador y banderas
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Carpetas
INCLUDE_DIR = include
SRC_DIR = src
PYTHON_DIR = python
RESULTS_DIR = results  # Carpeta donde se guardan datos 
BIN_DIR = bin

# Archivos fuente y encabezados
SRC = $(SRC_DIR)/DifusionCalor.cpp main.cpp
HEADERS = $(INCLUDE_DIR)/DifusionCalor.h

# Ejecutable
TARGET = $(BIN_DIR)/main

# Reglas principales
.PHONY: all run viz clean help prepare-viz

all: $(TARGET)
	@echo "=== Compilación completa ==="

# Compilación del ejecutable
$(TARGET): $(SRC) $(HEADERS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -o $@ $(SRC)
	@echo "Ejecutable creado: $@"

# Ejecutar simulación
run: $(TARGET)
	@echo "=== Ejecutando simulación ==="
	./$(TARGET)

# Preparar visualización
prepare-viz:
	@mkdir -p $(PYTHON_DIR)/$(RESULTS_DIR)
	@cp $(RESULTS_DIR)/*.dat $(PYTHON_DIR)/$(RESULTS_DIR)/ 2>/dev/null || echo "No hay archivos para copiar."
	@echo "Resultados copiados a: $(PYTHON_DIR)/$(RESULTS_DIR)/"

# Visualizar resultados
viz: prepare-viz
	@echo "=== Visualizando resultados ==="
	cd $(PYTHON_DIR) && python3 visualizacion.py

# Limpiar
clean:
	@echo "=== Limpiando ==="
	rm -rf $(BIN_DIR) $(PYTHON_DIR)/$(RESULTS_DIR)
	@echo "Limpieza completada."

# Ayuda
help:
	@echo "=== MAKE TARGETS DISPONIBLES ==="
	@echo "make            - Compilar el ejecutable"
	@echo "make run        - Ejecutar simulación"
	@echo "make viz        - Visualizar resultados"
	@echo "make clean      - Limpiar todo"


