#include "Sensor.hpp"
#include <string>
#include <variant>
#include <vector>
#include <cmath>

// Constructor with optional parameters, as they have default values
Sensor::Sensor() :
        min_value(0.0),
        max_value(50.0),
        num_samples(10000),
        period(10000),
        adc_noise_lsb(2),
        adc_resolution(10),
        sensor_noise_c(2.0),
        adc_step_size(50.0 / (1 << 10))
{}

Sensor::~Sensor(){}

std::vector<double> Sensor::execute() {
    std::vector<double> data(this->num_samples, 0.0);

    // Generate sinusoidal values
    for (unsigned int i = 0; i < this->num_samples; i++) {
        // Generate a sinusoidal value in the range [0, 2*PI]
        double sine_value = sin(2 * M_PI * static_cast<double>(i) / this->period);

        // Scale the value to fit between MIN and MAX
        data[i] = min_value + (sine_value + 1.0) * (max_value - min_value) / 2.0;
    }

    return data;
}

const std::vector<std::string> Sensor::getParameters() {
    return std::vector<std::string>{ "min_value", "max_value", "num_samples", "period", "adc_noise_lsb", "sensor_noise_c", "adc_resolution" };
}

int Sensor::setParameter(const std::string& key, const ParamType& value) {
    if (!key.compare("min_value")) {
        if (std::holds_alternative<double>(value)) {
            this->min_value = std::get<double>(value);
            this->adc_step_size = (this->max_value - this->min_value) / (1 << this->adc_resolution);
        }
        else
            return 1;
    }
    else if (!key.compare("max_value")) {
        if (std::holds_alternative<double>(value)) {
            this->max_value = std::get<double>(value);
            this->adc_step_size = (this->max_value - this->min_value) / (1 << this->adc_resolution);
        }
        else
            return 1;
    }
    else if (!key.compare("num_samples")) {
        if (std::holds_alternative<unsigned int>(value))
            this->num_samples = std::get<unsigned int>(value);
        else
            return 1;
    }
    else if (!key.compare("period")) {
        if (std::holds_alternative<unsigned int>(value))
            this->period = std::get<unsigned int>(value);
        else
            return 1;
    }
    else if (!key.compare("adc_noise_lsb")) {
        if (std::holds_alternative<unsigned int>(value))
            this->adc_noise_lsb = std::get<unsigned int>(value);
        else
            return 1;
    }
    else if (!key.compare("sensor_noise_c")) {
        if (std::holds_alternative<double>(value))
            this->sensor_noise_c = std::get<double>(value);
        else
            return 1;
    }
    else if (!key.compare("adc_resolution")) {
        if (std::holds_alternative<unsigned int>(value)) {
            this->adc_resolution = std::get<unsigned int>(value);
            this->adc_step_size = (this->max_value - this->min_value) / (1 << this->adc_resolution);
        }
        else
            return 1;
    }
    else
        return 2;

    return 0;
}
