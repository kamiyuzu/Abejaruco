#include "PluginInterface.hpp"
#include <cstdlib>
#include <cstring>
#include <forward_list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <dlfcn.h>
#include <iostream>
#include <algorithm>

typedef PluginInterface* (*create_t)();

std::forward_list<void*> dl_handles;

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

void cleanDlHandles() {
     std::for_each(dl_handles.begin(), dl_handles.end(), [](void* e) { dlclose(e); });
}

PluginInterface* getPlugin(const char* libName) {
    void* handle = dlopen(libName, RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << '\n';
        return NULL;
    }

    dl_handles.push_front(handle);

    create_t create_plugin = (create_t)dlsym(handle, "createPlugin");
    if (!create_plugin) {
        std::cerr << "Cannot load symbol 'createPlugin': " << dlerror() << '\n';
        dlclose(handle);
        return NULL;
    }

    PluginInterface* res = create_plugin();
    return res;
}

int main(int argc, char** argv) {
    //Load and create the plugins
    PluginInterface* sensor = getPlugin("lib/libSensor.so");
    PluginInterface* noise_creator = getPlugin("lib/libNoiseCreator.so");
    PluginInterface* denoise_creator = getPlugin("lib/libNoiseReduction.so");
    atexit(cleanDlHandles);

    //Arguments parsing
    for (int i = 1; i < argc; i++) {
        try {
            if (!std::strcmp(argv[i], "--help")) {
                std::cerr << "Modo de empleo: " << argv[0] <<" [OPCIONES]\n\t--min-value NUM\t\tValor minimo de temperatura\n\t--max-value NUM\t\tValor maximo de temperatura\n\t--num-samples NUM\tNumero de muestras a generar\n\t--period NUM\t\tNumero de muestras en un dia\n\t--range NUM\t\tRango del ruido del sensor\n\t--window-size NUM\tTamaño de la ventana para la reduccion del ruido\n";
                return 0;
            }
            else if (!std::strcmp(argv[i], "--min-value"))
                sensor->setParameter("min_value", std::stod(argv[++i]));
            else if (!std::strcmp(argv[i], "--max-value"))
                sensor->setParameter("max_value", std::stod(argv[++i]));
            else if (!std::strcmp(argv[i], "--num-samples"))
                sensor->setParameter("num_samples", (unsigned int)std::stoul(argv[++i]));
            else if (!std::strcmp(argv[i], "--period"))
                sensor->setParameter("period", (unsigned int)std::stoul(argv[++i]));
            else if (!std::strcmp(argv[i], "--range"))
                noise_creator->setParameter("range", std::stod(argv[++i]));
            else if (!std::strcmp(argv[i], "--window-size"))
                denoise_creator->setParameter("window_size", (unsigned int)std::stoul(argv[++i]));
            else {
                fprintf(stderr, "Argumento invalido: %s\n", argv[i]);
                delete sensor;
                delete noise_creator;
                delete denoise_creator;
                return 1;
            }
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Valor invalido: " << argv[i] << std::endl;
            delete sensor;
            delete noise_creator;
            delete denoise_creator;
            return 1;
        }
    }

    // Step 1: Generate sensor data
    std::vector<double> sensor_data = sensor->execute();

    // Step 2: Write sensor data to CSV file
    writeToCSV("sensor_data.csv", sensor_data);

    // Step 3: Apply noise
    noise_creator->setParameter("input", sensor_data);
    std::vector<double> noised_data = noise_creator->execute();

    // Step 4: Write data to another CSV file
    writeToCSV("noise_data.csv", noised_data);

    // Step 5: Apply denoise
    noise_creator->setParameter("input", noised_data);
    std::vector<double> denoised_data = denoise_creator->execute();

    // Step 6: Write data to another CSV file
    writeToCSV("denoised_data.csv", denoised_data);

    delete sensor;
    delete noise_creator;
    delete denoise_creator;
    return 0;
}
