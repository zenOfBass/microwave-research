#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <string.h>

#define MAX_ROWS 300
#define MAX_COLS 3
#define MAX_LINE_LENGTH 1000
#define MAX_ROWS_COMPLEX 500
#define MAX_COMPLEX_NUMBERS 500
#define BUFFER_SIZE 4096

void chan_freq_antloc_reader(const char *chan, const char *freq, const char *antloc)
{
    // Declare arrays for each file type
    int intArray[MAX_ROWS][MAX_COLS];     // 2D array of channel names
    double doubleArray[MAX_ROWS];         // Array of frequencies
    float floatArray[MAX_ROWS][MAX_COLS]; // 2D array of antenna locations

    // Open first file (int array)
    FILE *file1 = fopen(chan, "r");
    if (file1 == NULL) // If the file isn't found...
    {
        printf("Error opening channel names CSV (%s).\n", chan); // Print error to terminal
        return 1; // Exception exit
    }

    // Read first file
    int rows1 = 0, cols1 = 0;
    while (fscanf(file1, "%d,%d,", &intArray[rows1][cols1], &intArray[rows1][cols1 + 1]) == 2)
    {
        /* Read two integers separated by a comma from file1
           Store the first integer in intArray[rows1][cols1]
           Store the second integer in intArray[rows1][cols1 + 1] */
        rows1++;
        if (rows1 >= MAX_ROWS) // If the number of rows read exceeds what is allowed for the array...
        {
            printf("Maximum number of rows exceeded (%s).\n", chan); // Print error to terminal
            break; // Break loop from error
        }
    }
    fclose(file1); // Close channel names file

    // Open second file (double array)
    FILE *file2 = fopen(freq, "r");
    if (file2 == NULL) // If the file isn't found...
    {
        printf("Error opening frequencies CSV (%s).\n", freq); // Print error to terminal
        return 1; // Exception exit
    }

    // Read second file
    int rows2 = 0;
    while (fscanf(file2, "%lf,", &doubleArray[rows2]) == 1)
    {
        /* Read a double value followed by a comma from file2
           Store the double value in doubleArray[rows2] */
        rows2++;
        if (rows2 >= MAX_ROWS) // If the number of rows read exceeds what is allowed for the array...
        {
            printf("Maximum number of rows exceeded (%s).\n", freq); // Print error to terminal
            break; // Break loop from error
        }
    }
    fclose(file2); // Close frequencies file

    // Open third file (array of x, y, z float coordinates)
    FILE *file3 = fopen(antloc, "r");
    if (file3 == NULL) // If the file isn't found...
    {
        printf("Error opening antenna locations CSV (%s).\n", antloc); // Print error to terminal
        return 1; // Exception exit
    }

    // Read third file
    int rows3 = 0;
    while (fscanf(file3, "%f,%f,%f,", &floatArray[rows3][0], &floatArray[rows3][1], &floatArray[rows3][2]) == 3)
    {
        /* Read three float values separated by commas from file3
           Store the float values in floatArray[rows3][0], floatArray[rows3][1], and floatArray[rows3][2] */
        rows3++;
        if (rows3 >= MAX_ROWS) // If the number of rows read exceeds what is allowed for the array...
        {
            printf("Maximum number of rows exceeded (%s).\n", antloc); // Print error to terminal
            break; // Break loop from error
        }
    }
    fclose(file3); // Close antenna locations file

    /* Print statements to terminal for debugging (legacy) */
    // // Print the contents of the arrays
    // printf("Data from file1.csv (2D int array):\n");
    // for (int i = 0; i < rows1; i++)
    // {
    //     printf("[%d, %d]\n", intArray[i][0], intArray[i][1]);
    // }
    // printf("\nData from file2.csv (double array):\n");
    // for (int i = 0; i < rows2; i++)
    // {
    //     printf("%lf\n", doubleArray[i]);
    // }
    // printf("\nData from file3.csv (float array):\n");
    // for (int i = 0; i < rows3; i++)
    // {
    //     printf("[%f, %f, %f]\n", floatArray[i][0], floatArray[i][1], floatArray[i][2]);
    // }
    // printf("\n");

    printf("chan_freq_antloc_reader() done. (%s, %s, %s)\n", chan, freq, antloc); // Print confirmation to terminal
}

void iq_reader(const char *iq)
{
    // Declare arrays and allocate memory
    long double complex **complexArray = malloc(MAX_ROWS_COMPLEX * sizeof(long double complex *)); // Allocate memory for array in heap
    for (int i = 0; i < MAX_ROWS_COMPLEX; i++)                                       // Loop over all elements
    {
        complexArray[i] = malloc(MAX_COMPLEX_NUMBERS * sizeof(long double complex)); // Allocate memory for each element in array in heap
    }
    int num_complex_numbers[MAX_ROWS_COMPLEX] = {0}; // Set all elements to zero

    // Read the CSV file
    FILE *file = fopen(iq, "r");
    if (file == NULL) // If the file isn't found...
    {
        printf("Error opening IQ CSV (%s).\n", iq); // Print error to terminal
        return 1; // Exception exit
    }

    char line[BUFFER_SIZE];
    int row = 0;
    while (fgets(line, sizeof(line), file)) // Read a line from 'file' and store it in 'line'
    {
        char *token;
        char *rest = line;
        while ((token = strtok_r(rest, ",", &rest))) // Split 'line' into tokens using the delimiter ',' and store each token in 'token'
        {
            // Extract the real and imaginary parts from 'token'
            char *endptr;
            long double real = strtold(token, &endptr);                    // Convert the token to a real number
            long double imag = strtold(endptr, &endptr);                   // Convert the remaining string to an imaginary number
            complexArray[row][num_complex_numbers[row]] = real + imag * I; // Store the complex number in the array by combining them and multiplying by 'i'
            num_complex_numbers[row]++;                                    // Increment the count of complex numbers for the current row
        }
        row++;

        if (row >= MAX_ROWS_COMPLEX) // If the number of rows read exceeds what is allowed for the array...
        {
            printf("Maximum number of rows exceeded (%s).\n", iq); // Print error to terminal
            break; // Break loop from error
        }
    }
    fclose(file); // Close iq file

    /* Print statements to terminal for debugging (legacy) */
    // // Print the contents of the arrays
    // printf("Data from the IQ file (long double complex):\n");
    // for (int i = 0; i < row; i++)
    // {
    //     for (int j = 0; j < num_complex_numbers[i]; j++)
    //     {
    //         long double complex c_num = complexArray[i][j];
    //         printf("%.18Lf + %.18Lfi\n", creal(c_num), cimag(c_num));
    //     }
    // }

    // Deallocation
    for (int i = 0; i < MAX_ROWS_COMPLEX; i++) // Loop over the array
    {
        free(complexArray[i]); // Deallocate the memory for each element in array in heap
    }
    free(complexArray);        // Deallocate memory for array in heap

    printf("iq_reader() done. (%s)\n", iq); // Print confirmation to terminal
}

int main()
{
    // Names of CSV files (change as needed)
    const char *chan = "file1.csv";   // Channel names
    const char *freq = "file2.csv";   // fi frequencies
    const char *antloc = "file3.csv"; // Antenna locations
    const char *iq1 = "file4.csv";    // First IQ data set (Sm(f) complex)
    const char *iq2 = "file5.csv";    // Second IQ data set (Sm(f) complex)

    // Function calls for reading CSV files into memory
    chan_freq_antloc_reader(chan, freq, antloc); // Read channel names, frequencies, and antenna locations
    iq_reader(iq1);                              // Read first IQ data set
    iq_reader(iq2);                              // Read second IQ data set

    return 0; // Exit
}