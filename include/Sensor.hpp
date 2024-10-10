#include "PluginInterface.hpp"
#include <vector>

class Sensor : public PluginInterface {
    public:
        // Constructor with default parameters
        Sensor();
        ~Sensor();
        std::vector<double> execute();
        const std::vector<std::string> getParameters();
        int setParameter(const std::string& key, const unsigned int value);
        int setParameter(const std::string& key, const double value);
        int setParameter(const std::string& key, const std::vector<double>& value);
    private:
        double min_value;
        double max_value;
        unsigned int num_samples;
        unsigned int period;
};
