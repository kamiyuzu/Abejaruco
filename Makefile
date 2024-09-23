# Variables
CC = gcc
CFLAGS = -lm
TARGET_DIR = target
SRC1 = sensor.c
SRC2 = noise_reduction.c
OBJ1 = $(TARGET_DIR)/sensor.o
OBJ2 = $(TARGET_DIR)/noise_reduction.o
TARGET1 = $(TARGET_DIR)/sensor
TARGET2 = $(TARGET_DIR)/noise_reduction
CSV1 = sensor_data_with_noise.csv
CSV2 = smoothed_data.csv

# Create the target directory if it doesn't exist
$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

# Default target to compile all programs
all: $(TARGET_DIR) $(TARGET1) $(TARGET2)

# Compile sensor program (generate object file and executable)
$(TARGET1): $(OBJ1)
	$(CC) -o $(TARGET1) $(OBJ1) $(CFLAGS)

$(OBJ1): $(SRC1) | $(TARGET_DIR)
	$(CC) -c $(SRC1) -o $(OBJ1)

# Compile noise_reduction program (generate object file and executable)
$(TARGET2): $(OBJ2)
	$(CC) -o $(TARGET2) $(OBJ2) $(CFLAGS)

$(OBJ2): $(SRC2) | $(TARGET_DIR)
	$(CC) -c $(SRC2) -o $(OBJ2)

# Run sensor program
run_sensor: $(TARGET1)
	./$(TARGET1)

# Run noise_reduction program
run_noise_reduction: $(TARGET2)
	./$(TARGET2)

# Clean up generated files
clean:
	rm -rf $(TARGET_DIR) $(CSV1) $(CSV2)

# Optional: force run without making any changes
.PHONY: clean all run_sensor run_noise_reduction
