#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define MIN_VALUE 5.0
#define MAX_VALUE 40.0

int main() {
    // Parameters
    int num_samples=10000, noise_step=100;
    double noise_level = 10.0;  // Adjust this value to control the intensity of noise
    FILE *file;

    // Initialize random seed for noise generation
    srand(time(NULL));

    // Ask for user input
    printf("Enter the number of samples (minimum 10000): ");
    scanf("%d", &num_samples);

    if (num_samples < 10000) {
        printf("Number of samples must be at least 10000.\n");
        return 1;
    }

    printf("Enter the number of steps after which noise will be added: ");
    scanf("%d", &noise_step);

    // Open CSV file for writing
    file = fopen("sensor_data_with_noise.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write header to CSV file
    fprintf(file, "Sample,Value\n");

    // Generate sinusoidal values and write to the CSV file
    for (int i = 0; i < num_samples; i++) {
        // Generate a sinusoidal value in the range [0, 2*PI]
        double sine_value = sin(2 * M_PI * (double)i / num_samples);

        // Scale the value to fit between 5 and 40
        double scaled_value = MIN_VALUE + (sine_value + 1.0) * (MAX_VALUE - MIN_VALUE) / 2.0;

        // Add noise every 'noise_step' samples
        if (i % noise_step == 0) {
            // Random noise in the range [-noise_level, +noise_level]
            double noise = ((double)rand() / RAND_MAX) * 2 * noise_level - noise_level;
            scaled_value += noise;
        }

        // Write the sample index and value to the CSV file
        fprintf(file, "%d,%.5f\n", i + 1, scaled_value);
    }

    // Close the file
    fclose(file);

    printf("Sensor data with noise written to 'sensor_data_with_noise.csv'.\n");
    
    return 0;
}
