#include "Sensor.hpp"
#include <algorithm>
#include <vector>
#include <random>

// Constructor with optional parameters, as they have default values
Sensor::Sensor(double MIN_VALUE, double MAX_VALUE, unsigned int num_samples, unsigned int period,
    unsigned int adc_resolution, unsigned int adc_noise_lsb, double sensor_noise_c) :
        min_value(MIN_VALUE),
        max_value(MAX_VALUE),
        num_samples(num_samples),
        period(period),
        adc_noise_lsb(adc_noise_lsb),
        sensor_noise_c(sensor_noise_c),
        adc_step_size((MAX_VALUE - MIN_VALUE) / (1 << adc_resolution))
{}

Sensor::~Sensor(){}

/*  El ruido en las mediciones proviene de dos fuentes:
        1. Ruido y resolución del ADC: Podemos tomar como referencia el ADC del Arduino UNO
           Tiene una resolución de 10-bits con una precisión absoluta de +-2 LSB.
        2. Ruido típico del sensor de temperatura: Como referencia se puede usar el DHT11 que
           viene incluido con el Arduino UNO, tiene un rango de medición de 0ºC a 50ºC con el
           mismo voltaje que el ADC, con una precisión de +-2ºC.
    Esto significa que el ADC tiene una resolución de 50 / 2¹⁰ = 0,048828125ºC
    y un error de +-0,09765625ºC.

    Entonces el ruido se puede calcular como:
        Temp + (+-2 * 0,048...) + (floor(+-2 / 0,048...) * 0,048...)
    Que significa que la temperatura medida es la real + la precisión del ADC +
    la precisión del sensor (con un tamaño de paso igual a la resolución del sensor)
*/
std::vector<double> Sensor::genData() {
    std::vector<double> data(this->num_samples, 0.0);
    // Initialize random seed for noise generation using random_device and mt19937
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generate sinusoidal values
    for (unsigned int i = 0; i < this->num_samples; i++) {
        // Generate a sinusoidal value in the range [0, 2*PI]
        double sine_value = sin(2 * M_PI * static_cast<double>(i) / this->period);

        // Scale the value to fit between MIN and MAX
        double scaled_value = min_value + (sine_value + 1.0) * (max_value - min_value) / 2.0;

        // Noise from ADC
        std::uniform_int_distribution<> adc_dis(-this->adc_noise_lsb, this->adc_noise_lsb);
        double adc_noise = static_cast<double>(adc_dis(gen)) * this->adc_step_size;

        // Noise from sensor
        std::uniform_real_distribution<> sensor_dis(-this->sensor_noise_c, this->sensor_noise_c);
        double sensor_noise = std::floor(sensor_dis(gen) / this->adc_step_size) * this->adc_step_size;

        // Clamp and assign the value
        scaled_value += adc_noise + sensor_noise;
        data[i] = std::clamp(scaled_value, this->min_value, this->max_value);
    }

    return data;
}
