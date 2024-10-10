#include "Sensor.hpp"
#include <string>
#include <variant>
#include <vector>
#include <cmath>

Sensor::Sensor() :
        min_value(0.0),
        max_value(50.0),
        num_samples(10000),
        period(10000)
{}

extern "C" PluginInterface* createPlugin() {
    return new Sensor();
}

Sensor::~Sensor(){}

std::vector<double> Sensor::execute() {
    std::vector<double> data(this->num_samples, 0.0);

    // Generate sinusoidal values
    for (unsigned int i = 0; i < this->num_samples; i++) {
        // Generate a sinusoidal value in the range [0, 2*PI]
        double sine_value = sin(2 * M_PI * static_cast<double>(i) / this->period);

        // Scale the value to fit between MIN and MAX
        data[i] = this->min_value + (sine_value + 1.0) * (this->max_value - this->min_value) / 2.0;
    }

    return data;
}

const std::vector<std::string> Sensor::getParameters() {
    return std::vector<std::string>{ "min_value", "max_value", "num_samples", "period" };
}

int Sensor::setParameter(const std::string& key, const unsigned int value) {
    if (!key.compare("num_samples"))
        this->num_samples = value;
    else if (!key.compare("period"))
        this->period = value;
    else
        return 1;
    return 0;
}
int Sensor::setParameter(const std::string& key, const double value) {
    if (!key.compare("min_value"))
        this->min_value = value;
    else if (!key.compare("max_value"))
        this->max_value = value;
    else
        return 1;
    return 0;
}
int Sensor::setParameter(const std::string& key, const std::vector<double>& value) {
    return 1;
}
