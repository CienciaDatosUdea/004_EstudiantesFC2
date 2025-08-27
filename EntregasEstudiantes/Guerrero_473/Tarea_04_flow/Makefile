# Compilador y flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2 -Iinclude

# Directorios
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin
PYTHON_DATA_DIR = python/datos

# Archivos fuente (main.cpp en raíz, otros en src/)
MAIN_SRC = main.cpp
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
ALL_SRCS = $(MAIN_SRC) $(SRC_FILES)

# Archivos objeto
MAIN_OBJ = $(BUILD_DIR)/main.o
SRC_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
OBJS = $(MAIN_OBJ) $(SRC_OBJS)

# Nombre del ejecutable
TARGET = $(BIN_DIR)/navier_stokes_sim

# Regla principal
all: create_dirs $(TARGET)

# Crear directorios necesarios
create_dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR) $(PYTHON_DATA_DIR)

# Compilar el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar main.cpp (está en el directorio raíz)
$(BUILD_DIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compilar archivos de src/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Limpiar archivos compilados
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Limpiar y recompilar
rebuild: clean all

# Ejecutar el programa
run: all
	./$(TARGET)

# Depuración con flags de debug
debug: CXXFLAGS += -g -DDEBUG
debug: rebuild

# Phony targets
.PHONY: all create_dirs clean rebuild run debug