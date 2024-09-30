# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wextra -Werror -g -lpthread -pthread --coverage

# Target executable
TARGET = main

# Source files
SERVER_SRC = main.cpp
SRC = MetricCalculator.cpp MSTAlgorithms.cpp MSTFactory.cpp Graph.cpp ActiveObjectImpl.cpp Kruskal.cpp LeaderFollowerMetrics.cpp Pipeline.cpp Prim.cpp

# Header files (if applicable)
HEADERS = MSTAlgorithms.hpp MetricCalculator.hpp MSTFactory.hpp Graph.hpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Default rule to compile the program
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJ) $(SERVER_SRC:.cpp=.o)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(SERVER_SRC:.cpp=.o)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJ) $(TARGET) *.gcno *.gcda *.gcov *.o

# Rebuild everything from scratch
rebuild: clean all

# PHONY targets to avoid conflicts with files named clean or all
.PHONY: all clean rebuild
