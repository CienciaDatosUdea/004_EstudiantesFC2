# --- Compilador y Banderas ---
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -I./include

# --- Directorios ---
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
DATADIR = data

# --- Archivos ---
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE = $(BINDIR)/proyecto

# --- Reglas de Compilación ---
all: $(EXECUTABLE)

# Regla para enlazar los archivos objeto y crear el ejecutable final
$(EXECUTABLE): $(OBJECTS)
	-@mkdir $(BINDIR)
	@echo "Enlazando para crear el ejecutable..."
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "¡Ejecutable '$@' creado con éxito!"

# Regla patrón para compilar los archivos fuente (.cpp) en archivos objeto (.o)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	-@mkdir $(OBJDIR)
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# --- Reglas de Utilidad ---
run: $(EXECUTABLE)
	-@mkdir $(DATADIR)
	@echo "Ejecutando la simulación..."
	./$(EXECUTABLE)

clean:
	@echo "Limpiando el proyecto..."
	@if exist $(OBJDIR) (rmdir /s /q $(OBJDIR))
	@if exist $(BINDIR) (rmdir /s /q $(BINDIR))
	@if exist $(DATADIR) (rmdir /s /q $(DATADIR))
	@echo "Limpieza completada."

.PHONY: all run clean