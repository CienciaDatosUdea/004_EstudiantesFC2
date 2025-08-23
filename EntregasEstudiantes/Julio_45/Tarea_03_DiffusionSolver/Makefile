CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC_DIR = src
TEST_DIR = test
OBJ_DIR = build

# Archivos fuente principales
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.out,$(SRCS))

# Ejecutable principal
MAIN = $(OBJ_DIR)/main.out

# Todos los tests: cada .cpp en test/ genera un ejecutable en build/
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TESTS = $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/%.out,$(TEST_SRCS))

# Regla por defecto
all: $(MAIN) $(TESTS)

# Main
$(OBJ_DIR)/main.out: main.cpp $(OBJS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Regla genérica para tests
$(OBJ_DIR)/%.out: $(TEST_DIR)/%.cpp $(OBJS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilar objetos de src/
$(OBJ_DIR)/%.out: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear carpeta de objetos y ejecutables
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpiar
clean:
	rm -rf $(OBJ_DIR)

# Ejecutar main
run: $(MAIN)
	./$(MAIN)

# Ejecutar todos los tests
test: $(TESTS)
	@echo "Todos los tests compilados en build/ (ejecuta manualmente con ./build/<test>)"