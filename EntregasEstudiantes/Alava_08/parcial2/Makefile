#
# Makefile para el proyecto de simulación FDTD
# Versión alternativa compatible con la terminal de Windows (CMD).
#

# --- Variables de Configuración ---
COMPILER = g++
# Se eliminan flags adicionales para máxima compatibilidad con el original.
COMPILER_FLAGS = -std=c++11 -Wall -Iinclude

# --- Definición de Rutas ---
SOURCES_PATH = src
OBJECTS_PATH = obj
BIN_PATH = bin

# --- Archivos del Proyecto ---
EXECUTABLE_FILE = $(BIN_PATH)/simulador.exe
OBJECT_FILES = $(OBJECTS_PATH)/main.o $(OBJECTS_PATH)/fdtd.o

# --- Regla Principal (se ejecuta por defecto con 'make') ---
.PHONY: all
all: $(EXECUTABLE_FILE)
	@echo.
	@echo [!] Compilacion finalizada. Ejecutable disponible en: $(EXECUTABLE_FILE)

# --- Regla de Enlazado (Linking) ---
# Une todos los archivos objeto (.o) para crear el programa final (.exe)
$(EXECUTABLE_FILE): $(OBJECT_FILES) | $(BIN_PATH)
	@echo [i] Enlazando archivos objeto...
	$(COMPILER) $(COMPILER_FLAGS) -o $@ $^

# --- Reglas de Compilación Explícitas ---
# Convierte cada archivo .cpp en un archivo objeto .o
$(OBJECTS_PATH)/main.o: $(SOURCES_PATH)/main.cpp | $(OBJECTS_PATH)
	@echo [i] Compilando $<...
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

$(OBJECTS_PATH)/fdtd.o: $(SOURCES_PATH)/fdtd.cpp | $(OBJECTS_PATH)
	@echo [i] Compilando $<...
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

# --- Reglas para Crear Directorios (Estilo Windows) ---
$(OBJECTS_PATH):
	@if not exist $(OBJECTS_PATH) mkdir $(OBJECTS_PATH)

$(BIN_PATH):
	@if not exist $(BIN_PATH) mkdir $(BIN_PATH)

# --- Comandos de Utilidad ---
.PHONY: run clean

# Ejecuta el programa compilado
run: all
	@cls
	@echo --- EJECUTANDO SIMULACION ---
	@.\$(EXECUTABLE_FILE)

# Elimina todos los archivos y carpetas generados
clean:
	@echo [i] Eliminando archivos de compilacion...
	@if exist $(OBJECTS_PATH) rd /s /q $(OBJECTS_PATH)
	@if exist $(BIN_PATH) rd /s /q $(BIN_PATH)
	@echo [!] Limpieza completada.