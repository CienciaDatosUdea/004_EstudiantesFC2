CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC_DIR = src
OBJ_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

TARGET = main

# Regla por defecto
all: $(TARGET)

# Ejecutable principal
$(TARGET): main.cpp $(OBJS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilar objetos de src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear carpeta build
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpiar compilados
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Ejecutar
run: $(TARGET)
	./$(TARGET)
