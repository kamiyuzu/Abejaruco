#include <iostream>
#include <fstream>
#include "Sensor.hpp"
#include "NoiseReduction.hpp"

// Function to write data to CSV file
void writeToCSV(const std::string& filename, const std::vector<double>& data) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& value : data) {
            file << value << "\n";
        }
        file.close();
        std::cout << "Data written to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main() {
    // Step 1: Generate sensor data
    Sensor sensor(0.0, 50.0, 10000, 1000, 10, 2, 2.0);  // Customize parameters as needed
    const std::vector<double>& sensor_data = sensor.genData();

    // Step 2: Write sensor data to CSV file
    writeToCSV("sensor_data.csv", sensor_data);

    // Step 3: Apply noise reduction using NoiseReduction class
    unsigned int window_size = 5;  // Example window size for moving average filter
    NoiseReduction noise_reduction(window_size, sensor_data);
    const std::vector<double>& denoised_data = noise_reduction.denoise();

    // Step 4: Write denoised data to another CSV file
    writeToCSV("denoised_data.csv", denoised_data);

    return 0;
}

