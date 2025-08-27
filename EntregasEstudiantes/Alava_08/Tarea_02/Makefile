# Compilador y banderas
CXX = g++
CXXFLAGS = -Wall -O2 -std=c++11 -Iinclude

# Archivos fuente y ejecutable
SRC = main.cpp src/diffusion_solver.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = difusion_model.out

# Regla principal
all: $(TARGET)

# Enlazado final
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilación de cada .cpp en .o
%.o: %.cpp include/diffusion.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar compilados
clean:
	rm -f $(OBJ) $(TARGET)
