#include "NoiseCreator.hpp"
#include <random>

NoiseCreator::NoiseCreator() :
        range(2.0),
        input()
{}

extern "C" PluginInterface* createPlugin() {
    return new NoiseCreator();
}

NoiseCreator::~NoiseCreator(){}

std::vector<double> NoiseCreator::execute() {
    std::vector<double> data(this->input.size(), 0.0);
    // Initialize random seed for noise generation using random_device and mt19937
    std::random_device rd;
    std::mt19937 gen(rd());

    for (unsigned int i = 0; i < data.size(); i++) {
        std::uniform_real_distribution<> dis(-this->range, this->range);
        data[i] = this->input[i] + dis(gen);
    }

    return data;
}

const std::vector<std::string> NoiseCreator::getParameters() {
    return std::vector<std::string>{ "range", "input" };
}

int NoiseCreator::setParameter(const std::string& key, const unsigned int value) {
    return 1;
}
int NoiseCreator::setParameter(const std::string& key, const double value) {
    if (!key.compare("range"))
        this->range = value;
    else
        return 1;
    return 0;
}
int NoiseCreator::setParameter(const std::string& key, const std::vector<double>& value) {
    if (!key.compare("input"))
        this->input = value;
    else
        return 1;
    return 0;
}
