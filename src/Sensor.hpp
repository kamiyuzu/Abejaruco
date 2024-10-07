#include <vector>
class Sensor {
    public:
        // Constructor with default parameters
        Sensor(double MIN_VALUE = 0.0,
                double MAX_VALUE = 50.0,
                unsigned int num_samples = 10000,
                unsigned int period = 10000,
                unsigned int adc_resolution = 10,
                unsigned int adc_noise_lsb = 2,
                double sensor_noise_c = 2.0);
        ~Sensor();
        std::vector<double> genData();
    private:
        double min_value;
        double max_value;
        unsigned int num_samples;
        unsigned int period;
        unsigned int adc_noise_lsb;
        double sensor_noise_c;
        double adc_step_size;
};
