# Compiler and flags
CXX       := g++
CXXFLAGS  := -O2 -std=c++17 -fopenmp -Wall -Wextra
LDFLAGS   := -fopenmp

# Directories
SRC_DIR   := src
BIN_DIR   := bin
INC_DIR   := include

# Files
TARGET    := $(BIN_DIR)/flow_sim
SRCS      := $(SRC_DIR)/flow.cpp main.cpp
OBJS      := $(SRCS:.cpp=.o)

# Rules
all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(SRC_DIR)/*.o *.o $(TARGET)

.PHONY: all clean
