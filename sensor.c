#include <stdio.h>
#include <math.h>

#define MIN_VALUE 5.0
#define MAX_VALUE 40.0

int main() {
    // Parameters
    int num_samples;
    FILE *file;

    // Ask for user input
    printf("Enter the number of samples (minimum 10000): ");
    scanf("%d", &num_samples);

    // Ensure minimum number of samples
    if (num_samples < 10000) {
        printf("Number of samples must be at least 10000.\n");
        return 1;
    }

    // Open CSV file for writing
    file = fopen("sinusoidal_data.csv", "w");
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

        // Write the sample index and value to the CSV file
        fprintf(file, "%d,%.5f\n", i + 1, scaled_value);
    }

    // Close the file
    fclose(file);

    printf("Sinusoidal data written to 'sinusoidal_data.csv'.\n");

    return 0;
}
