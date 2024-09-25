#include <iostream>
#include <fstream> 
#include <sstream>  
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


// Este metodo es para leer un csv si solo se quiere quitar el ruido de datos ya existentes -- no necesario en flujo normal
std::vector<double> read_csv_values(const std::string& file_name) {
    std::vector<double> data;
    std::ifstream file(file_name);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << file_name << std::endl;
        return data;
    }

    std::string line;

    // Read each line of the CSV
    while (std::getline(file, line)) {


        std::stringstream ss(line);
        std::string sample, value;

        // Read the 'Sample' and 'Value' fields (assuming two columns)
            try {
                // Convert the 'Value' field to double and store it in the vector
                data.push_back(std::stod(value));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid data format in the file. Skipping value: " << line << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: Value out of range. Skipping value: " << line << std::endl;
        }
    }

    file.close();
    return data;
}


int main(int argc, char** argv) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <num_samples>" << std::endl;
        return 1;
    }

    // Solo pido este dato para probarlo mas rapido -- CAMBIAR
    unsigned int num_samples;
    try {
        num_samples = std::stoi(argv[1]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Invalid number of samples provided." << std::endl;
        return 1;
    }


    // Step 1: Generate sensor data
    Sensor sensor(0.0, 50.0, num_samples, 1000, 10, 2, 2.0);  // Customize parameters as needed
    const std::vector<double>& sensor_data = sensor.genData();

    // Step 2: Write sensor data to CSV file
    writeToCSV("sensor_data.csv", sensor_data);

    // Step 3: Apply noise reduction using NoiseReduction class
    unsigned int window_size = 15;  // Example window size for moving average filter
    NoiseReduction noise_reduction(window_size, sensor_data);
    const std::vector<double>& denoised_data = noise_reduction.denoise();

    // Step 4: Write denoised data to another CSV file
    writeToCSV("denoised_data.csv", denoised_data);

    return 0;
}

