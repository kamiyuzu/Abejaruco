# Variables
CC = gcc
CFLAGS = -lm
TARGET = sensor
SRC = sensor.c
CSV = sensor_data_with_noise.csv

# Default target to compile the program
all: $(TARGET)

# Compilation command
$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)

# Run the program after compilation
run: $(TARGET)
	./$(TARGET)

# Clean up generated files
clean:
	rm -f $(TARGET) $(CSV)

# Optional: force run without making any changes
.PHONY: clean all run
