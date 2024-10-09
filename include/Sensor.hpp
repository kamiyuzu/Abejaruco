#include "PluginInterface.hpp"
#include <vector>

class Sensor : public PluginInterface {
    public:
        // Constructor with default parameters
        Sensor();
        ~Sensor();
        std::vector<double> execute();
        const std::vector<std::string> getParameters();
        int setParameter(const std::string& key, const ParamType& value);
    private:
        double min_value;
        double max_value;
        unsigned int num_samples;
        unsigned int period;
        unsigned int adc_noise_lsb;
        unsigned int adc_resolution;
        double sensor_noise_c;
        double adc_step_size;
};
