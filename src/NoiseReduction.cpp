#include "NoiseReduction.hpp"
#include <vector>
#include <numeric> // For std::accumulate
#include <algorithm> // For std::min, std::max

// Constructor with optional parameters, as they have default values
NoiseReduction::NoiseReduction(unsigned int window_size, const std::vector<double>& input) :
    window_size(window_size),
    input(input),
    output(input.size(), 0)
{}

// Destructor
NoiseReduction::~NoiseReduction(){}

const std::vector<double>& NoiseReduction::denoise() {
    int half_window = window_size / 2;
    size_t input_size = input.size();

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

    return this->output;
}