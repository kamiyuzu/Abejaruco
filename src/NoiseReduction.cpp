#include "NoiseReduction.hpp"
#include <vector>
#include <numeric> // For std::accumulate
#include <algorithm> // For std::min, std::max

// Constructor with optional parameters, as they have default values
NoiseReduction::NoiseReduction(unsigned int window_size) :
    window_size(window_size)
{}

extern "C" PluginInterface* createPlugin() {
    return new NoiseReduction();
}

// Destructor
NoiseReduction::~NoiseReduction(){}

std::vector<double> NoiseReduction::execute(){
    unsigned int half_window = this->window_size / 2;
    size_t input_size = input.size();
    std::vector<double> output(input_size, 0.0);

    // Iterate over each element of the input vector
    for (size_t i = 0; i < input_size; ++i) {
        // Define the start and end indices for the window
        size_t window_start = (i >= half_window) ? i - half_window : 0;
        size_t window_end = std::min(i + half_window + 1, input_size); // end is exclusive

        // Calculate the average within the window
        double sum = std::accumulate(input.begin() + window_start, input.begin() + window_end, 0.0);
        size_t window_length = window_end - window_start;
        output[i] = sum / window_length;
    }

    return output;
}

const std::vector<std::string> NoiseReduction::getParameters() {
    return std::vector<std::string>{ "window_size", "input" };
}

int NoiseReduction::setParameter(const std::string& key, const ParamType& value) {
    if (!key.compare("window_size")) {
        if (std::holds_alternative<unsigned int>(value)) {
            this->window_size = std::get<unsigned int>(value);
        }
        else
            return 1;
    }
    else if (!key.compare("input")) {
        if (std::holds_alternative<const std::vector<double>>(value)) {
            this->input = std::get<const std::vector<double>>(value);
        }
        else
            return 1;
    }
    else
        return 2;

    return 0;
}
