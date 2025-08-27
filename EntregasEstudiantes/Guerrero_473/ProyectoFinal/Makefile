# Configuración del compilador
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

# Directorios
SRC_DIR = src
PYTHON_DIR = python
RESULTS_1D = resultados
RESULTS_2D = resultados_2d

# Archivos fuente comunes
SRC_COMMON = $(SRC_DIR)/TISE.cpp $(SRC_DIR)/wavepacket.cpp

# Archivos fuente para 1D
SRC_1D = $(SRC_COMMON) $(SRC_DIR)/TDSE.cpp main_1d.cpp

# Archivos fuente para 2D
SRC_2D = $(SRC_COMMON) $(SRC_DIR)/TDSE_2D.cpp $(SRC_DIR)/TISE_2D.cpp main_2d.cpp

# Ejecutables
TARGET_1D = main_1d
TARGET_2D = main_2d

# Reglas principales
.PHONY: all 1d 2d clean prepare-viz-1d prepare-viz-2d run-1d run-2d viz-1d viz-2d help

# Compilar ambos
all: 1d 2d

# Simulación 1D
1d: $(TARGET_1D)
	@echo "Simulación 1D compilada"

$(TARGET_1D): $(SRC_1D)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC_1D)

# Simulación 2D
2d: $(TARGET_2D)
	@echo " Simulación 2D compilada"

$(TARGET_2D): $(SRC_2D)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC_2D)

# Preparar visualización 1D
prepare-viz-1d:
	@mkdir -p $(PYTHON_DIR)/$(RESULTS_1D)
	@cp $(RESULTS_1D)/*.dat $(PYTHON_DIR)/$(RESULTS_1D)/ 2>/dev/null || echo " No hay archivos 1D para copiar"
	@echo " Resultados 1D copiados a: $(PYTHON_DIR)/$(RESULTS_1D)/"

# Preparar visualización 2D
prepare-viz-2d:
	@mkdir -p $(PYTHON_DIR)/$(RESULTS_2D)
	@cp $(RESULTS_2D)/*.dat $(PYTHON_DIR)/$(RESULTS_2D)/ 2>/dev/null || echo " No hay archivos 2D para copiar"
	@echo " Resultados 2D copiados a: $(PYTHON_DIR)/$(RESULTS_2D)/"

# Ejecutar simulación 1D
run-1d: $(TARGET_1D) prepare-viz-1d
	@echo " Ejecutando simulación 1D..."
	@./$(TARGET_1D)

# Ejecutar simulación 2D
run-2d: $(TARGET_2D) prepare-viz-2d
	@echo " Ejecutando simulación 2D..."
	@./$(TARGET_2D)

# Visualizar 1D
viz-1d: prepare-viz-1d
	@echo "Visualizando resultados 1D..."
	@cd $(PYTHON_DIR) && python visualizacion_1d.py

# Visualizar 2D
viz-2d: prepare-viz-2d
	@echo " Visualizando resultados 2D..."
	@cd $(PYTHON_DIR) && python visualizacion_2d.py

# Limpiar todo
clean:
	@echo " Limpiando..."
	rm -f $(TARGET_1D) $(TARGET_2D) *.o
	rm -rf $(RESULTS_1D) $(RESULTS_2D)
	rm -rf $(PYTHON_DIR)/$(RESULTS_1D) $(PYTHON_DIR)/$(RESULTS_2D)
	@echo " Limpieza completada"

# Ayuda
help:
	@echo "=== MAKE TARGETS DISPONIBLES ==="
	@echo "make all        - Compilar 1D y 2D"
	@echo "make 1d         - Solo compilar 1D"
	@echo "make 2d         - Solo compilar 2D"
	@echo "make run-1d     - Ejecutar simulación 1D"
	@echo "make run-2d     - Ejecutar simulación 2D"
	@echo "make viz-1d     - Visualizar resultados 1D"
	@echo "make viz-2d     - Visualizar resultados 2D"
	@echo "make clean      - Limpiar todo"

