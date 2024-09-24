#include "Sensor.hpp"
#include <vector>

// Constructor with optional parameters, as they have default values
Sensor::Sensor(double MIN_VALUE, double MAX_VALUE, unsigned int num_samples, unsigned int period,
    unsigned int adc_resolution, unsigned int adc_noise_lsb, double sensor_noise_c) :
        MIN_VALUE(MIN_VALUE),
        MAX_VALUE(MAX_VALUE),
        num_samples(num_samples),
        period(period),
        adc_resolution(adc_resolution),
        adc_noise_lsb(adc_noise_lsb),
        sensor_noise_c(sensor_noise_c),
        adc_step_size((MAX_VALUE - MIN_VALUE) / (1 << adc_resolution)),
        data(num_samples, 0.0)
{}

// TODO: Implement data generation algorithm
const std::vector<double>& Sensor::genData() {
    return this->data;
}
