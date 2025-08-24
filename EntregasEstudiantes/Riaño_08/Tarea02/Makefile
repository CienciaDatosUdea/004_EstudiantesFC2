# Compilador y opciones
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Directorios
INCLUDE_DIR = include
SRC_DIR = src
BIN_DIR = bin
DISPLAY_DIR = display
DATA_DIR = $(DISPLAY_DIR)/datos

# Archivos
MAIN_SRC = main.cpp
MODEL_SRC = $(SRC_DIR)/difusion_model.cpp
MAIN_OBJ = $(BIN_DIR)/main.o
MODEL_OBJ = $(BIN_DIR)/difusion_model.o
TARGET = $(BIN_DIR)/solver
SOLUTION_FILE = $(DATA_DIR)/solucion_final.txt

# Regla para asegurar que los directorios existan
DIRS = $(BIN_DIR) $(DATA_DIR)

# Regla por defecto (compila y ejecuta)
all: compile run

# Regla para compilar
compile: $(TARGET)

$(TARGET): $(MAIN_OBJ) $(MODEL_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -I $(INCLUDE_DIR)
	@echo "Compilación exitosa. El ejecutable está en $(TARGET)"

$(MAIN_OBJ): $(MAIN_SRC) | $(DIRS)
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I $(INCLUDE_DIR)

$(MODEL_OBJ): $(MODEL_SRC) | $(DIRS)
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I $(INCLUDE_DIR)

# Regla para crear los directorios
$(DIRS):
	@mkdir -p $@

# Regla para ejecutar
run: $(TARGET)
	./$(TARGET)

# Regla para limpiar archivos
clean:
	@rm -rf $(BIN_DIR) $(DATA_DIR)
	@echo "Archivos generados en bin/ y datos de simulación limpiados."

.PHONY: all compile run clean $(DIRS)
