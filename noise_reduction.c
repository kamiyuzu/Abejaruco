#include <stdio.h>
#include <stdlib.h>

#define MAX_SAMPLES 1000000  // Define a max limit for sample storage (adjust if needed)

// Function to apply a moving average filter
void moving_average(double *input, double *output, int num_samples, int window_size) {
    double sum = 0.0;
    int half_window = window_size / 2;

    // Initialize the first sum
    for (int i = 0; i < window_size; i++) {
        sum += input[i];
    }

    // Start applying the moving average
    for (int i = 0; i < num_samples; i++) {
        // Calculate the average for the current window
        if (i >= half_window && i < num_samples - half_window) {
            output[i] = sum / window_size;
        } else {
            output[i] = input[i];  // Keep edge values unchanged (no enough neighbors)
        }

        // Update the sum for the next window
        if (i < num_samples - half_window - 1) {
            sum = sum - input[i - half_window] + input[i + half_window + 1];
        }
    }
}

int main() {
    // Parameters
    char input_filename[] = "sensor_data_with_noise.csv";
    char output_filename[] = "smoothed_data.csv";
    int window_size;

    // Ask the user for window size
    printf("Enter the window size for the moving average filter (odd number, recommended 3, 5, 7...): ");
    scanf("%d", &window_size);

    // Ensure window size is an odd number
    if (window_size % 2 == 0) {
        printf("Please enter an odd number for the window size.\n");
        return 1;
    }

    FILE *input_file = fopen(input_filename, "r");
    FILE *output_file = fopen(output_filename, "w");

    if (input_file == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    if (output_file == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    // Arrays to hold the sample data
    double samples[MAX_SAMPLES];
    double smoothed_samples[MAX_SAMPLES];
    int num_samples = 0;

    // Skip the header line of the CSV
    char buffer[100];
    fgets(buffer, 100, input_file);

    // Read the CSV data into the array
    while (fscanf(input_file, "%*d,%lf", &samples[num_samples]) != EOF) {
        num_samples++;
        if (num_samples >= MAX_SAMPLES) {
            printf("Reached maximum sample limit.\n");
            break;
        }
    }

    // Apply the moving average filter
    moving_average(samples, smoothed_samples, num_samples, window_size);

    // Write the smoothed data to the new CSV file
    fprintf(output_file, "Sample,Smoothed Value\n");
    for (int i = 0; i < num_samples; i++) {
        fprintf(output_file, "%d,%.5f\n", i + 1, smoothed_samples[i]);
    }

    // Close the files
    fclose(input_file);
    fclose(output_file);

    printf("Smoothed data written to '%s'.\n", output_filename);

    return 0;
}
