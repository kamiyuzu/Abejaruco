# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Target executable
TARGET = main

# Source files (relative to src/ directory)
SRCS = main.cpp Sensor.cpp NoiseReduction.cpp

# Object files (generated in src/ directory)
OBJS = main.o Sensor.o NoiseReduction.o

# Include directories (include current directory for headers)
INCLUDES = -I.

# Build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Compile each source file into an object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)
	rm *.csv

# Phony target to force execution
.PHONY: clean
