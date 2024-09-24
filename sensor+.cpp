#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>

#define MIN_VALUE 5.0
#define MAX_VALUE 40.0

int main(int argc, char* argv[]) {
    // Parameters
    int num_samples = 10000, noise_step = 100;
    double noise_level = 10.0;  // Adjust this value to control the intensity of noise

    // Check for valid arguments
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " num_samples noise_step\n";
        std::cerr << "    num_samples: Number of samples (minimum 10000)\n";
        std::cerr << "    noise_step: Number of steps after which noise will be added\n";
        return 1;
    }

    // Initialize random seed for noise generation using random_device and mt19937
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-noise_level, noise_level);

    // Parse command line arguments
    num_samples = std::atoi(argv[1]);
    noise_step = std::atoi(argv[2]);

    if (num_samples < 10000) {
        std::cerr << "Number of samples must be at least 10000.\n";
        return 1;
    }

    // Open CSV file for writing
    std::ofstream file("sensor_data_with_noise.csv");
    if (!file) {
        std::cerr << "Error opening file!\n";
        return 1;
    }

    // Write header to CSV file
    file << "Sample,Value\n";

    // Generate sinusoidal values and write to the CSV file
    for (int i = 0; i < num_samples; i++) {
        // Generate a sinusoidal value in the range [0, 2*PI]
        double sine_value = sin(2 * M_PI * static_cast<double>(i) / num_samples);

        // Scale the value to fit between 5 and 40
        double scaled_value = MIN_VALUE + (sine_value + 1.0) * (MAX_VALUE - MIN_VALUE) / 2.0;

        // Add noise every 'noise_step' samples
        if (i % noise_step == 0) {
            // Generate random noise in the range [-noise_level, +noise_level]
            double noise = dis(gen);
            scaled_value += noise;
        }

        // Write the sample index and value to the CSV file
        file << (i + 1) << "," << scaled_value << "\n";
    }

    // Close the file
    file.close();

    std::cout << "Sensor data with noise written to 'sensor_data_with_noise.csv'.\n";
    
    return 0;
}