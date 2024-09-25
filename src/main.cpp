#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
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
    // Parameters
    double MIN_VALUE = 0.0;
    double MAX_VALUE = 50.0;
    unsigned int num_samples = 10000;
    unsigned int period = 10000;
    unsigned int adc_resolution = 10;
    unsigned int adc_noise_lsb = 2;
    double sensor_noise_c = 2.0;
    unsigned int window_size = 15;

    //Arguments parsing
    for (int i = 1; i < argc; i++) {
        try {
            if (!std::strcmp(argv[i], "--help")) {
                std::cerr << "Modo de empleo: " << argv[0] <<" [OPCIONES]\n\t--min-value NUM\t\tValor minimo de temperatura\n\t--max-value NUM\t\tValor maximo de temperatura\n\t--num-samples NUM\tNumero de muestras a generar\n\t--period NUM\t\tNumero de muestras en un dia\n\t--adc-resolution NUM\tResolucion en bits del ADC\n\t--adc-noise NUM\t\tRuido caracteristico del ADC en LSBs\n\t--sensor-noise NUM\tRuido caracteristico del sensor en ºC\n\t--window-size NUM\tTamaño de la ventana para la reduccion del ruido\n";
                return 0;
            }
            else if (!std::strcmp(argv[i], "--min-value"))
                MIN_VALUE = std::stod(argv[++i]);
            else if (!std::strcmp(argv[i], "--max-value"))
                MAX_VALUE = std::stod(argv[++i]);
            else if (!std::strcmp(argv[i], "--num-samples"))
                num_samples = std::stoul(argv[++i]);
            else if (!std::strcmp(argv[i], "--period"))
                period = std::stoul(argv[++i]);
            else if (!std::strcmp(argv[i], "--adc-resolution"))
                adc_resolution = std::stoul(argv[++i]);
            else if (!std::strcmp(argv[i], "--adc-noise"))
                adc_noise_lsb = std::stoul(argv[++i]);
            else if (!std::strcmp(argv[i], "--sensor-noise"))
                sensor_noise_c = std::stod(argv[++i]);
            else if (!std::strcmp(argv[i], "--window-size"))
                window_size = std::stoul(argv[++i]);
            else {
                fprintf(stderr, "Argumento invalido: %s\n", argv[i]);
                return 1;
            }
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Valor invalido: " << argv[i] << std::endl;
            return 1;
        }
    }

    // Step 1: Generate sensor data
    Sensor sensor(MIN_VALUE, MAX_VALUE, num_samples, period, adc_resolution, adc_noise_lsb, sensor_noise_c);
    const std::vector<double>& sensor_data = sensor.genData();

    // Step 2: Write sensor data to CSV file
    writeToCSV("sensor_data.csv", sensor_data);

    // Step 3: Apply noise reduction using NoiseReduction class
    NoiseReduction noise_reduction(window_size, sensor_data);
    const std::vector<double>& denoised_data = noise_reduction.denoise();

    // Step 4: Write denoised data to another CSV file
    writeToCSV("denoised_data.csv", denoised_data);

    return 0;
}
