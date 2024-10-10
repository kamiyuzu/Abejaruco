#ifndef LOGGINGDECORATOR_HPP
#define LOGGINGDECORATOR_HPP

#include "Decorator.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>

class LoggingDecorator : public Decorator {
public:
    // Constructor takes a PluginInterface to wrap
    LoggingDecorator(std::unique_ptr<PluginInterface> comp) : Decorator(std::move(comp)) {}

    // Override the execute method to add logging
    std::vector<double> execute() override {
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << "[LOG] Starting execution...\n";

        // Call the wrapped component's execute method
        std::vector<double> result = component->execute();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "[LOG] Execution finished in " << std::fixed << std::setprecision(3) << elapsed.count() << " seconds.\n";

        return result;
    }

    // Override the setParameter method to log parameter changes
    int setParameter(const std::string& key, const ParamType& value) override {
        std::cout << "[LOG] Setting parameter '" << key << "'...\n";
        return component->setParameter(key, value);
    }
};

#endif // LOGGINGDECORATOR_HPP