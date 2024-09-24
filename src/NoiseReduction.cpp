#include "NoiseReduction.hpp"
#include <vector>

// Constructor with optional parameters, as they have default values
NoiseReduction::NoiseReduction(unsigned int window_size, const std::vector<double>& input) :
    window_size(window_size),
    input(input),
    output(input.size(), 0)
{}

NoiseReduction::~NoiseReduction(){}

// TODO: Implement noise reduction algorithm
const std::vector<double>& NoiseReduction::denoise() {
    return this->output;
}
