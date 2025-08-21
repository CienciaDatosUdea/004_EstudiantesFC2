CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

SRC_DIR = src
TEST_DIR = test

SRCS = $(SRC_DIR)/fdtd.cpp
OBJS = $(SRCS:.cpp=.o)

MAINS = main1.cpp main2.cpp main3.cpp
MAIN_EXES = $(MAINS:.cpp=)

TESTS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_EXES = $(patsubst $(TEST_DIR)/%.cpp,$(TEST_DIR)/%,$(TESTS))

all: $(MAIN_EXES) $(TEST_EXES)

main1: main1.o $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

main2: main2.o $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ 

main3: main3.o $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_DIR)/%: $(TEST_DIR)/%.o $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f *.o $(SRC_DIR)/*.o $(MAIN_EXES) $(TEST_DIR)/*.o $(TEST_EXES) *.txt $(SRC_DIR)/*.txt $(TEST_DIR)/*.txt
	rm -rf python/animaciones

.PHONY: all