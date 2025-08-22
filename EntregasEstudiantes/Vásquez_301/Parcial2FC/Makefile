# Makefile Definitivo (Versión Explícita para Windows)

# --- CONFIGURACIÓN ---
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/main.exe

# --- LISTA EXPLÍCITA DE ARCHIVOS ---
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/fdtd.o

# --- REGLAS PRINCIPALES ---
.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# --- REGLAS DE COMPILACIÓN EXPLÍCITAS ---
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/fdtd.o: $(SRC_DIR)/fdtd.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- REGLAS DE DIRECTORIO ---
$(OBJ_DIR):
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

$(BIN_DIR):
	if not exist $(BIN_DIR) mkdir $(BIN_DIR)

# --- REGLAS DE LIMPIEZA Y EJECUCIÓN ---
.PHONY: run clean
run: all
	cls
	.\$(TARGET)

clean:
	if exist $(OBJ_DIR) rd /s /q $(OBJ_DIR)
	if exist $(BIN_DIR) rd /s /q $(BIN_DIR)