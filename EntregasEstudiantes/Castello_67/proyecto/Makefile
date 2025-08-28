# Makefile robusto y simple
CXX      := g++
MPICXX   := mpicxx
CXXSTD   := c++17
CXXFLAGS := -std=$(CXXSTD) -O2 -Wall -Wextra -Iinclude
SRC_DIR  := src
OBJ_DIR  := build

# Posibles archivos MPI dentro de src/
MPI_CANDIDATES := $(SRC_DIR)/All_Configurations.cpp $(SRC_DIR)/All_configurations.cpp
MPI_SRC := $(wildcard $(MPI_CANDIDATES))

# main.cpp en la raíz (si existe)
ROOT_MAIN := $(wildcard main.cpp)

# Fuentes normales: main.cpp (si existe) + todos los src/*.cpp menos los MPI_SRC
NORMAL_SRCS := $(ROOT_MAIN) $(filter-out $(MPI_SRC),$(wildcard $(SRC_DIR)/*.cpp))

# Objetos: build/<basename>.o (usa notdir para evitar rutas en el nombre)
OBJS := $(addprefix $(OBJ_DIR)/,$(patsubst %.cpp,%.o,$(notdir $(NORMAL_SRCS))))

# Ejecutable final (en la raíz, porque main.cpp está en la raíz)
TARGET := main

# Ejecutables MPI con sufijo _mpi en src/
MPI_PROGS := $(patsubst $(SRC_DIR)/%.cpp,$(SRC_DIR)/%_mpi,$(MPI_SRC))

.PHONY: all mpi clean

all: $(TARGET)
	@echo "Compilación completa."

# Linkear el ejecutable principal a partir de todos los objetos
$(TARGET): $(OBJS)
	@echo "Linkeando $@"
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Regla genérica para compilar cualquier build/<basename>.o
# Busca el .cpp correspondiente primero en src/, luego en la raíz.
$(OBJ_DIR)/%.o:
	@mkdir -p $(OBJ_DIR)
	@echo "Compilando objeto $@"
	@if [ -f "$(SRC_DIR)/$*.cpp" ]; then SRC="$(SRC_DIR)/$*.cpp"; \
	elif [ -f "$*.cpp" ]; then SRC="$*.cpp"; \
	else echo "ERROR: no se encontró fuente para $*"; exit 1; fi; \
	$(CXX) $(CXXFLAGS) -c $$SRC -o $@

# Target para compilar todos los MPI sources (si existen)
mpi: $(MPI_PROGS)
	@echo "Compilación MPI completa."

$(SRC_DIR)/%_mpi: $(SRC_DIR)/%.cpp
	@echo "Compilando (MPI) $< -> $@"
	$(MPICXX) -std=$(CXXSTD) -O2 -Wall -Wextra -Iinclude -o $@ $<

clean:
	@echo "Limpiando build, ejecutables y archivos .txt..."
	-rm -rf $(OBJ_DIR)
	-rm -f $(TARGET) $(MPI_PROGS)
	# borrar todos los .txt en todo el árbol del proyecto (recursivo)
	-find . -type f -name '*.txt' -print -exec rm -f {} +
	@echo "Limpieza completa."

