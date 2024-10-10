#ifndef FILTERING_DECORATOR_HPP
#define FILTERING_DECORATOR_HPP

#include "Decorator.hpp"
#include <vector>
#include <algorithm>
#include <numeric>

class FilteringDecorator : public Decorator {
public:
    FilteringDecorator(PluginInterface* component)
        : Decorator(component), window_size(5) {} // Default window size for filtering

    // Override execute method to apply filtering
    std::vector<double> execute() override {
        // Get the original data by calling the base component
        std::vector<double> data = component->execute();
        
        // Apply moving average filter on the data
        std::vector<double> filtered_data = applyMovingAverageFilter(data);
        
        return filtered_data;
    }

    // Set parameter for window size
    int setParameter(const std::string& key, const ParamType& value) override {
        if (key == "window_size") {
            window_size = std::get<int>(value); // Cast value to int
            return 0;
        }
        return component->setParameter(key, value); // Call base method for other parameters
    }

private:
    int window_size; // Window size for the moving average filter

    // Function to apply a moving average filter
    std::vector<double> applyMovingAverageFilter(const std::vector<double>& data) {
        std::vector<double> filtered_data;

        // Apply moving average
        for (size_t i = 0; i < data.size(); ++i) {
            int start = std::max(0, static_cast<int>(i) - window_size / 2);
            int end = std::min(static_cast<int>(data.size()), static_cast<int>(i) + window_size / 2 + 1);
            double average = std::accumulate(data.begin() + start, data.begin() + end, 0.0) / (end - start);
            filtered_data.push_back(average);
        }

        return filtered_data;
    }
};

#endif // FILTERING_DECORATOR_HPP