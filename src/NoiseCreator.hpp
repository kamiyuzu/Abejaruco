#include "PluginInterface.hpp"

class NoiseCreator : public PluginInterface {
    public:
        // Constructor with default parameters
        NoiseCreator();
        ~NoiseCreator();
        std::vector<double> execute();
        const std::vector<std::string> getParameters();
        int setParameter(const std::string& key, const ParamType& value);
    private:
        std::vector<double> input;
        double range;
};
