#ifndef NOISE_REDUCTION_DECORATOR_H
#define NOISE_REDUCTION_DECORATOR_H

#include "Decorator.hpp"
#include <algorithm>

// Clase concreta que aplica reducción de ruido
class NoiseReductionDecorator : public Decorator {
public:
    NoiseReductionDecorator(std::unique_ptr<PluginInterface> comp) : Decorator(std::move(comp)) {}

    // Redefine la ejecución para aplicar el filtro de ruido
    std::vector<double> execute() override {
        std::vector<double> data = Decorator::execute();  // Obtiene los datos del plugin envuelto
        filterNoise(data);  // Aplica el filtro de ruido
        return data;
    }

private:
    void filterNoise(std::vector<double>& data) {
        // Lógica simple para reducir ruido (p. ej., media móvil)
        if (data.size() < 3) return;
        for (size_t i = 1; i < data.size() - 1; ++i) {
            data[i] = (data[i - 1] + data[i] + data[i + 1]) / 3.0;  // Ejemplo de filtrado básico
        }
    }
};

#endif // NOISE_REDUCTION_DECORATOR_H
