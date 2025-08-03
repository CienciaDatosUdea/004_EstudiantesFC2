# General info:
# .h files contain declarations, .cpp files contain definitions. Multiple .cpp files can include the same .h file to share the same declarations without duplicating code. This way, all .cpp files can independently be compiled into .o files. In the final step, the .o files are linked to the actual .out executable.

# Practical info:	
# put this Makefile into the main folder of the project
# create a subfolder "src" that contains all .cpp files
# create a subfolder "include" that contains all .h files that are included in any of the .cpp files
# type "make", "make run", "make clean-obj" or "make clean-all" into terminal depending on what you want (make only compiles the executable, make run compiles it and runs it, make clean-obj deletes the object folder, make clean-all deletes the object folder and the executable). In case the .o files already exist, all of these only re-compile things if the corresponding .h or .cpp files have changed at a later timestamp (unless the -B flag is provided, in which case everything always recompiles).

# toggle useful makeflags
# MAKEFLAGS += -B # --always-make (always rebuild from scratch, even some files seem to not have changed)
MAKEFLAGS += -s # --silent (don't print out every linux command you'll execute, just execute them)

# declare all non-file targets as phony (best practice) 
.PHONY: all prebuild make_announce make_and_run_announce postbuild build run clean-all clean-obj

# THE ORDER OF ALL OF THE FOLLOWING LINES IS SIGNIFICANT. all HAS TO BE THE FIRST TARGET IN THE MAKEFILE ELSE "make" != "make all"
all: prebuild make_announce build postbuild

# compiler variables
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

# names of relevant directories (all will be built if necessary)
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# space-separated lists of all relevant source file paths
SRC = $(wildcard $(SRC_DIR)/*.cpp)
# space-separated lists of all relevant object file paths
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

# adapt name and path of the final executable here.
TARGET = $(BIN_DIR)/main.out

# rule for how to build executable (target) from the object files (also create bin directory before if it doesnt already exist)
$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# rule for how to build every object file from its corresponding source file (also create obj directory if it doesnt already exist)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# rule for how to create obj directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# rule for how to create bin directory 
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# just a variable for flushing the screen
CLEAR =	printf "\033[2J\033[H"

# actual make targets (some are only meant to be used inside other targets)

build: $(TARGET)

prebuild:
	$(CLEAR)

make_announce:
	echo "Making..."

make_and_run_announce:
	echo "Making, then running..."

# if the command tree exists, run it, else keep going and do not output any error.
postbuild:
	$(CLEAR)
	command -v tree >/dev/null && tree || true

run:
	$(MAKE) prebuild make_and_run_announce $(TARGET)
	$(CLEAR)
	./$(TARGET)

clean-all:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	$(CLEAR)
	command -v tree >/dev/null && tree || true

clean-obj:
	rm -rf $(OBJ_DIR)
	$(CLEAR)
	command -v tree >/dev/null && tree || true