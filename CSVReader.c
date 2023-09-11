/*
CSVReader.c
Revised 8/2/2023
Nathan Wiley - nwiley@uco.edu
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
    for (int i=0;i<NUMBER_OF_FREQUENCIES;i++)
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
