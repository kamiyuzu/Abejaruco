#include <vector>
class NoiseReduction {
    public:
        // Constructor with default parameters
        NoiseReduction(unsigned int window_size = 5);
        ~NoiseReduction();
        std::vector<double> denoise(const std::vector<double>& input);
    private:
        unsigned int window_size;
};
