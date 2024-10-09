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
        int setParameter(const std::string& key, const ParamType& value);
    private:
        unsigned int window_size;
        std::vector<double> input;
};

#endif // NOISEREDUCTION_H
