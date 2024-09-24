#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*  El ruido en las mediciones proviene de dos fuentes:
        1. Ruido y resolución del ADC: Podemos tomar como referencia el ADC del Arduino UNO
           Tiene una resolución de 10-bits con una precisión absoluta de +-2 LSB.
        2. Ruido típico del sensor de temperatura: Como referencia se puede usar el DHT11 que
           viene incluido con el Arduino UNO, tiene un rango de medición de 0ºC a 50ºC con el
           mismo voltaje que el ADC, con una precisión de +-2ºC.
    Esto significa que el ADC tiene una resolución de 50 / 2¹⁰ = 0,048828125ºC
    y un error de +-0,09765625ºC.

    Entonces el ruido se puede calcular como:
        Temp + (+-2 * 0,048...) + (floor(+-2 / 0,048...) * 0,048...)
    Que significa que la temperatura medida es la real + la precisión del ADC +
    la precisión del sensor (con un tamaño de paso igual a la resolución del sensor)
*/

int main(int argc, char** argv) {
    // Parameters
    double MIN_VALUE = 0.0;
    double MAX_VALUE = 50.0;
    unsigned int num_samples = 10000;
    unsigned int period = 10000;
    unsigned int adc_resolution = 10;
    unsigned int adc_noise_lsb = 2;
    double sensor_noise_c = 2.0;

    double adc_step_size;

    FILE *file;

    //Arguments parsing
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--help")) {
            fprintf(stderr, "Modo de empleo: %s [OPCIONES]\n\t--min-value NUM\tValor minimo de temperatura\n\t--max-value NUM\tValor maximo de temperatura\n\t--num-samples NUM\tNumero de muestras a generar\n\t--period NUM\tNumero de muestras en un dia\n\t--adc-resolution NUM\tResolucion en bits del ADC\n\t--adc-noise NUM\tRuido caracteristico del ADC en LSBs\n\t--sensor-noise NUM\tRuido caracteristico del sensor en ºC\n", argv[0]);
            return 0;
        }
        else if (!strcmp(argv[i], "--min-value")) {
            if (sscanf(argv[++i], "%lf", &MIN_VALUE) < 1) {
                fprintf(stderr, "Valor invalido: %s\n", argv[i]);
                return 1;
            }
        }
        else if (!strcmp(argv[i], "--max-value")) {
            if (sscanf(argv[++i], "%lf", &MAX_VALUE) < 1) {
                fprintf(stderr, "Valor invalido: %s\n", argv[i]);
                return 1;
            }
        }
        else if (!strcmp(argv[i], "--num-samples")) {
            if (sscanf(argv[++i], "%u", &num_samples) < 1) {
                fprintf(stderr, "Valor invalido: %s\n", argv[i]);
                return 1;
            }
        }
        else if (!strcmp(argv[i], "--period")) {
            if (sscanf(argv[++i], "%u", &period) < 1) {
                fprintf(stderr, "Valor invalido: %s\n", argv[i]);
                return 1;
            }
        }
        else if (!strcmp(argv[i], "--adc-resolution")) {
            if (sscanf(argv[++i], "%u", &adc_resolution) < 1) {
                fprintf(stderr, "Valor invalido: %s\n", argv[i]);
                return 1;
            }
        }
        else if (!strcmp(argv[i], "--adc-noise")) {
            if (sscanf(argv[++i], "%u", &adc_noise_lsb) < 1) {
                fprintf(stderr, "Valor invalido: %s\n", argv[i]);
                return 1;
            }
        }
        else if (!strcmp(argv[i], "--sensor-noise")) {
            if (sscanf(argv[++i], "%lf", &sensor_noise_c) < 1) {
                fprintf(stderr, "Valor invalido: %s\n", argv[i]);
                return 1;
            }
        }
        else {
            fprintf(stderr, "Argumento invalido: %s\n", argv[i]);
            return 1;
        }
    }

    if (num_samples < 10000) {
        fprintf(stderr, "Number of samples must be at least 10000.\n");
        return 1;
    }

    adc_step_size = (MAX_VALUE - MIN_VALUE) / (1 << adc_resolution);

    // Initialize random seed for noise generation
    srand(time(NULL));

    // Open CSV file for writing
    file = fopen("sensor_data_with_noise.csv", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file!\n");
        return 1;
    }

    // Write header to CSV file
    fprintf(file, "Sample,Value\n");

    // Generate sinusoidal values and write to the CSV file
    for (int i = 0; i < num_samples; i++) {
        // Generate a sinusoidal value in the range [0, 2*PI]
        double sine_value = sin(2 * M_PI * (double)i / period);

        // Scale the value to fit between MIN and MAX
        double scaled_value = MIN_VALUE + (sine_value + 1.0) * (MAX_VALUE - MIN_VALUE) / 2.0;

        // Noise from ADC
        double adc_noise =
            (floor(
                ((double)rand() / RAND_MAX) * 2.0 * adc_noise_lsb - adc_noise_lsb
            )) * adc_step_size;
        // Noise from sensor
        double sensor_noise =
            floor(
                (((double)rand() / RAND_MAX) * 2.0 * sensor_noise_c - sensor_noise_c)
                / adc_step_size
            ) * adc_step_size;

        // Clamp the value
        scaled_value += adc_noise + sensor_noise;
        scaled_value = fmax(MIN_VALUE, fmin(MAX_VALUE, scaled_value));

        // Write the sample index and value to the CSV file
        fprintf(file, "%d,%.5f\n", i + 1, scaled_value);
    }

    // Close the file
    fclose(file);

    fprintf(stderr, "Sensor data with noise written to 'sensor_data_with_noise.csv'.\n");

    return 0;
}
