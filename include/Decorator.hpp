#ifndef DECORATOR_H
#define DECORATOR_H

#include "PluginInterface.hpp"

//Interfaz basica de cada decorador
class Decorator : public PluginInterface {
    public:
        virtual ~Decorator() = default;
        virtual std::vector<double> execute();
        virtual int setParameter(const std::string& key, const unsigned int value);
        virtual int setParameter(const std::string& key, const double value);
        virtual int setParameter(const std::string& key, const std::vector<double>& value);
        virtual const std::vector<std::string> getParameters();
};

#endif //DECORATOR_H
