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

int NoiseCreator::setParameter(const std::string& key, const ParamType& value) {
    if (!key.compare("range")) {
        if (std::holds_alternative<double>(value))
            this->range = std::get<double>(value);
        else
            return 1;
    }
    else if (!key.compare("input")) {
        if (std::holds_alternative<const std::vector<double>>(value))
            this->input = std::get<const std::vector<double>>(value);
        else
            return 1;
    }
    else
        return 2;

    return 0;
}
