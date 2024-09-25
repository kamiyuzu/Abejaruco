# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

# Target executable
TARGET = main

# Target directory
TARGET_DIR = target

# Object files
OBJS = main.o Sensor.o NoiseReduction.o

# Include directories (include src directory for headers)
INCLUDES = -Isrc

# Build the executable
$(TARGET): $(OBJS) | $(TARGET_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET_DIR)/$(TARGET)

# Create the target directory if it doesn't exist
$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

# Compile each source file into an object file
%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET_DIR)/$(TARGET) || true
	rm *.csv || true

# Phony target to force execution
.PHONY: clean
