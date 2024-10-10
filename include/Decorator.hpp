#ifndef DECORATOR_H
#define DECORATOR_H

#include "PluginInterface.hpp"
#include <memory>

// Interfaz basica de cada decorador
class Decorator : public PluginInterface {
protected:
    std::unique_ptr<PluginInterface> component;  // Store the component we're decorating

public:
    // Constructor that takes ownership of a unique_ptr<PluginInterface>
    Decorator(std::unique_ptr<PluginInterface> comp) : component(std::move(comp)) {}

    // Constructor that takes a raw pointer and converts it into a unique_ptr
    Decorator(PluginInterface* plugin) : component(std::unique_ptr<PluginInterface>(plugin)) {}

    // Delegate the functionality to the wrapped component
    virtual std::vector<double> execute() override {
        return component->execute();
    }

    virtual int setParameter(const std::string& key, const ParamType& value) override {
        return component->setParameter(key, value);
    }

    virtual const std::vector<std::string> getParameters() override {
        return component->getParameters();
    }
};

#endif // DECORATOR_H
