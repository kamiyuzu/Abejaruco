#include "PluginInterface.hpp"

//Interfaz basica de cada decorador
class Decorator : public PluginInterface {
    public:
        virtual ~Decorator() = default;
        virtual std::vector<double> execute();
        virtual int setParameter(const std::tuple<std::string, ParamType>& value);
        virtual const std::vector<std::string> getParameters();
};
