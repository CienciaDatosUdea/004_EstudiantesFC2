# Compilador y flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude

# Directorios
SRC_DIR := src
INC_DIR := include
TEST_DIR := test
BUILD_DIR := build
BIN_DIR := bin

# Archivos fuente de src/
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

# Main en el directorio raíz
MAIN_SRC := main.cpp
MAIN_OBJ := $(BUILD_DIR)/main.o

# Ejecutable principal
TARGET := $(BIN_DIR)/main.out

# Regla por defecto
all: $(TARGET)

# Linkeo del ejecutable principal
$(TARGET): $(OBJ) $(MAIN_OBJ) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilación de src/*.cpp -> build/*.o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilación de main.cpp -> build/main.o
$(BUILD_DIR)/main.o: $(MAIN_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ejecutables de test (un ejecutable por cada .cpp en test/)
TESTS_SRC := $(wildcard $(TEST_DIR)/*.cpp)
TESTS_BIN := $(patsubst $(TEST_DIR)/%.cpp, $(BIN_DIR)/test_%, $(TESTS_SRC))

tests: $(TESTS_BIN)

$(BIN_DIR)/test_%: $(TEST_DIR)/%.cpp $(OBJ) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Crear directorios si no existen
$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@

# Limpieza
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean tests
