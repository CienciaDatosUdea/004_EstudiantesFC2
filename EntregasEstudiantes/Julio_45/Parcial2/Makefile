CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC_DIR = src
OBJ_DIR = obj

# Archivos fuente principales
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.out,$(SRCS))

# Ejecutable
MAIN = $(OBJ_DIR)/main.out

# Regla por defecto
all: $(MAIN)

# Enlazar ejecutable
$(OBJ_DIR)/main.out: main.cpp $(OBJS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilar objetos (desde src/)
$(OBJ_DIR)/%.out: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar objetos (desde raíz)
$(OBJ_DIR)/%.out: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear carpeta
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpiar
clean:
	rm -rf $(OBJ_DIR)

# Ejecutar
run: $(MAIN)
	./$(MAIN)

