#include <vector>
class NoiseReduction {
    public:
        // Constructor with default parameters
        NoiseReduction(unsigned int window_size = 5,
                        const std::vector<double>& input = {});
        ~NoiseReduction();
        const std::vector<double>& denoise();
    private:
        unsigned int window_size;
        const std::vector<double>& input; // Read-only reference to input data
        std::vector<double> output;
};
