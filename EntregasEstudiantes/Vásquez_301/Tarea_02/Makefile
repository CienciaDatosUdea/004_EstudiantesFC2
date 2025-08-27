CXX = g++
CXXFLAGS = -std=c++17 -Wall

TARGET = difusion_model.out

SRCS = main.cpp \
       src/Geometria.cpp \
       src/Condiciones.cpp \
       src/DiffusionSolver.cpp

OBJS = $(SRCS:.cpp=.o)


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean