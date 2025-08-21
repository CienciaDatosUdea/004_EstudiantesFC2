# Define el compilador y las opciones de compilación
CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall
INC_DIR = include
BUILD_DIR = build
SRC_DIR = src
PYTHON_DIR = python

# Define el nombre del ejecutable
EXEC = fdtd_sim

# Lista de archivos fuente
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
SRCS += main.cpp

# Lista de archivos objeto
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(filter $(SRC_DIR)/%.cpp, $(SRCS)))
OBJS += $(BUILD_DIR)/main.o

# Regla por defecto: compila y genera los datos de simulación
all: $(EXEC) data

# Crea el directorio de construcción si no existe
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Regla para construir el ejecutable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar archivos fuente a archivos objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(BUILD_DIR)/main.o: main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Regla para generar los archivos de datos ejecutando el programa
data: $(EXEC)
	@echo "Generando datos de simulación en la carpeta 'python'..."
	@cd $(PYTHON_DIR) && ../$(EXEC)

# Regla para limpiar los archivos de compilación y los datos generados
clean:
	rm -rf $(BUILD_DIR) $(EXEC) $(PYTHON_DIR)/*.txt
