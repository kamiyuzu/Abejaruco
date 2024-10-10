#ifndef NOISEREDUCTION_H
#define NOISEREDUCTION_H

#include <string>
#include <vector>
#include "PluginInterface.hpp"

class NoiseReduction : public PluginInterface {
    public:
        // Constructor with default parameters
        NoiseReduction(unsigned int window_size = 5);
        ~NoiseReduction();

        std::vector<double> execute();
        const std::vector<std::string> getParameters();
        int setParameter(const std::string& key, const unsigned int value);
        int setParameter(const std::string& key, const double value);
        int setParameter(const std::string& key, const std::vector<double>& value);
    private:
        unsigned int window_size;
        std::vector<double> input;
};

#endif // NOISEREDUCTION_H
