/*
CSVReader.c
Revised 9/14/2023
Colton Cox - ccox60@uco.edu
Nathan G Wiley - nwiley@uco.edu
*/

#include "CSVReader.h"

void readIntArray(const char *fileName, int channels[NUMBER_OF_CHANNELS][2])
{
    FILE *file = fopen(fileName, "r"); // Open file
    if (file == NULL)                  // If the file isn't found...
    {
        printf("Error opening file (%s).\n", fileName); // Print error to terminal
        exit(1);
    }

    for (int i=0;i<NUMBER_OF_CHANNELS;i++)
    {
        fscanf(file, "%u,%u,\n", &channels[i][0], &channels[i][1]);
    }

    fclose(file); // Close file
}

void readDoubleArray(const char *fileName, double doubleArray[NUMBER_OF_FREQUENCIES])
{
    FILE *file = fopen(fileName, "r"); // Open file
    if (file == NULL)                  // If the file isn't found...
    {
        printf("Error opening file (%s).\n", fileName); // Print error to terminal
        exit(1); // Exit
    }

    // Read file
    for (int i = 0; i < NUMBER_OF_FREQUENCIES; i++)
    {
        fscanf(file, "%lf,", &doubleArray[i]);
    }
    fclose(file); // Close file
}

void readFloatArray(const char *fileName, float floatArray[NUMBER_OF_ANTENNAS][3])
{
    FILE *file = fopen(fileName, "r"); // Open file
    if (file == NULL)                  // If the file isn't found...
    {
        printf("Error opening file (%s).\n", fileName); // Print error to terminal
        exit(1); // Exit
    }

    // Read file
    for (int i=0;i<NUMBER_OF_ANTENNAS;i++)
    {
        fscanf(file, "%f,%f,%f,", &floatArray[i][0], &floatArray[i][1], &floatArray[i][3]);
    }
    fclose(file); // Close file
}

void readComplexArray(const char *fileName, long double complex **complexArray, int *numRows, int numComplexNumbers[])
{
    FILE *file = fopen(fileName, "r"); // Open file
    if (file == NULL)                  // If the file isn't found...
    {
        printf("Error opening IQ CSV (%s).\n", fileName); // Print error to terminal
        *numRows = 0;
        exit(1); // Exit
    }

    // Read file
    char line[BUFFER_SIZE];
    int row = 0;
    while (fgets(line, sizeof(line), file)) // Read a line from 'file' and store it in 'line'
    {
        char *token;
        char *rest = line;
        while ((token = strtok_r(rest, ",", &rest))) // Split 'line' into tokens using the delimiter ',' and store each 'token'
        {
            char *endptr;                                                // Extract the real and imaginary parts from 'token'
            long double real = strtold(token, &endptr);                  // Convert the token to a real number
            long double imag = strtold(endptr, &endptr);                 // Convert the remaining string to an imaginary number
            complexArray[row][numComplexNumbers[row]] = real + imag * I; // Store complex number in array by adding and multiplying by 'i'
            numComplexNumbers[row]++;                                    // Increment the count of complex numbers for the current row
        }
        row++;
        if (row >= MAX_ROWS_COMPLEX) // If the number of rows read exceeds what is allowed for the array...
        {
            printf("Maximum number of rows exceeded (%s).\n", fileName); // Print error to terminal
            break;                                                       // Break loop from error
        }
    }
    fclose(file); // Close file
    *numRows = row;
}

void readDataFiles(int channelsArray[NUMBER_OF_CHANNELS][2], 
                double frequenciesArray[NUMBER_OF_FREQUENCIES], 
                float antennaLocationsArray[NUMBER_OF_ANTENNAS][3], 
                long double complex **iqArray1, 
                long double complex **iqArray2)
{
    for (int i = 0; i < MAX_ROWS_COMPLEX; i++) // Loop over all elements
    {
        iqArray1[i] = malloc(MAX_COMPLEX_NUMBERS * sizeof(long double complex)); // Allocate memory for each element in array in heap
    }
    int iqNums1[MAX_ROWS_COMPLEX] = {0}; // Set all elements to zero
    int iqNumRows1 = 0;

    for (int i = 0; i < MAX_ROWS_COMPLEX; i++) // Loop over all elements
    {
        iqArray2[i] = malloc(MAX_COMPLEX_NUMBERS * sizeof(long double complex)); // Allocate memory for each element in array in heap
    }
    int iqNums2[MAX_ROWS_COMPLEX] = {0}; // Set all elements to zero
    int iqNumRows2 = 0;
    
    readIntArray(CHANNELS_FILE, channelsArray);                    // channel names
    readDoubleArray(FREQUENCIES_FILE, frequenciesArray);           // frequencies
    readFloatArray(ANTENNA_LOCATIONS_FILE, antennaLocationsArray); // antenna locations
    readComplexArray(DATA_FILE_1, iqArray1, &iqNumRows1, iqNums1); // first IQ data set (Sm(f) complex)
    readComplexArray(DATA_FILE_2, iqArray2, &iqNumRows2, iqNums2); // second IQ data set (Sm(f) complex)
}