# Compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -Wall -Wextra -O2 -std=c++17 -Iinclude

# Archivos fuente comunes
COMMON = src/em1d.cpp

# Ejecutables
TARGETS = fdtd1 fdtd2 fdtd3

# Detectar plataforma para crear carpetas
ifeq ($(OS),Windows_NT)
  # PowerShell crea directorios si no existen (-Force evita error si existen)
  MKDIR = powershell -NoProfile -Command "New-Item -ItemType Directory -Force -Path"
else
  MKDIR = mkdir -p
endif

.PHONY: all dirs clean run run1 run2 run3

all: dirs $(TARGETS)

# Crear carpetas necesarias (idempotente)
dirs:
	@echo "Verificando/creando directorios de salida..."
	$(MKDIR) output/Punto1
	$(MKDIR) output/Punto2a
	$(MKDIR) output/Punto2b
	$(MKDIR) Results/Punto1
	$(MKDIR) Results/Punto2a
	$(MKDIR) Results/Punto2b
	@echo "Directorios listos."

# Compilar versión main1.cpp
fdtd1: $(COMMON) main1.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(COMMON) main1.cpp

# Compilar versión main2_a.cpp
fdtd2: $(COMMON) main2_a.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(COMMON) main2_a.cpp

# Compilar versión main2_b.cpp
fdtd3: $(COMMON) main2_b.cpp
	$(CXX) $(CXXFLAGS) -o $@ $(COMMON) main2_b.cpp

# Limpiar ejecutables
clean:
	rm -f $(TARGETS)

# Ejecutar versiones individuales (asegura dirs creados antes de correr)
run1: dirs fdtd1
	./fdtd1

run2: dirs fdtd2
	./fdtd2

run3: dirs fdtd3
	./fdtd3
	python graph\generate_gifs.py

# Ejecutar las tres versiones en orden
run: dirs $(TARGETS)
	@echo "=== Ejecutando fdtd1 ==="
	./fdtd1
	@echo "=== Ejecutando fdtd2 ==="
	./fdtd2
	@echo "=== Ejecutando fdtd3 ==="
	./fdtd3
	python graph\generate_gifs.py
