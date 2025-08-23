CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

SRC = src/Heat1d.cpp

all: simulation test/test_runner
	@rm -f main.o src/Heat1d.o test/test.o

simulation: main.cpp $(SRC)
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o
	$(CXX) $(CXXFLAGS) -c $(SRC) -o src/Heat1d.o
	$(CXX) $(CXXFLAGS) -o simulation main.o src/Heat1d.o

test/test_runner: test/test.cpp $(SRC)
	$(CXX) $(CXXFLAGS) -c test/test.cpp -o test/test.o
	$(CXX) $(CXXFLAGS) -c $(SRC) -o src/Heat1d.o
	$(CXX) $(CXXFLAGS) -o test/test_runner test/test.o src/Heat1d.o

clean:
	rm -f main.o src/Heat1d.o test/test.o simulation test/test_runner