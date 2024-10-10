#ifndef NOISECREATOR_H
#define NOISECREATOR_H

#include "PluginInterface.hpp"

class NoiseCreator : public PluginInterface {
    public:
        // Constructor with default parameters
        NoiseCreator();
        ~NoiseCreator();
        std::vector<double> execute();
        const std::vector<std::string> getParameters();
        int setParameter(const std::string& key, const unsigned int value);
        int setParameter(const std::string& key, const double value);
        int setParameter(const std::string& key, const std::vector<double>& value);
    private:
        std::vector<double> input;
        double range;
};

#endif //NOISECREATOR_H
