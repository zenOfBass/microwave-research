/*
CSVReader.c
Revised 7/5/2023
Nathan Wiley - nwiley@uco.edu
*/

#include "CSVReader.h"

void readIntArray(const char *fileName, int intArray[MAX_ROWS][MAX_COLS], int *numRows)
{
    // Open file (channel names)
    FILE *file = fopen(fileName, "r");
    if (file == NULL) // If the file isn't found...
    {
        printf("Error opening file (%s).\n", fileName); // Print error to terminal
        *numRows = 0;                                   // Set the number of rows to 0
        return;                                         // Exception exit
    }

    // Read file
    int rows = 0, cols = 0;
    while (fscanf(file, "%d,%d,", &intArray[rows][cols], &intArray[rows][cols + 1]) == 2)
    {
        /* Read two integers separated by a comma from file
           Store the first integer in intArray[rows1][cols1]
           Store the second integer in intArray[rows1][cols1 + 1] */
        rows++;
        if (rows >= MAX_ROWS) // If the number of rows read exceeds what is allowed for the array...
        {
            printf("Maximum number of rows exceeded (%s).\n", fileName); // Print error to terminal
            break;                                                       // Break loop from error
        }
    }
    fclose(file); // Close channel names file

    *numRows = rows; // Update the number of rows
}

void readDoubleArray(const char *fileName, double doubleArray[MAX_ROWS], int *numRows)
{
    // Open file (frequencies)
    FILE *file = fopen(fileName, "r");
    if (file == NULL) // If the file isn't found...
    {
        printf("Error opening file (%s).\n", fileName); // Print error to terminal
        *numRows = 0;                                   // Set the number of rows to 0
        return;                                         // Exception exit
    }

    // Read file
    int rows = 0;
    while (fscanf(file, "%lf,", &doubleArray[rows]) == 1)
    {
        /* Read a double value followed by a comma from file
           Store the double value in doubleArray[rows2] */
        rows++;
        if (rows >= MAX_ROWS) // If the number of rows read exceeds what is allowed for the array...
        {
            printf("Maximum number of rows exceeded (%s).\n", fileName); // Print error to terminal
            break;                                                       // Break loop from error
        }
    }
    fclose(file); // Close frequencies file

    *numRows = rows; // Update the number of rows
}

void readFloatArray(const char *fileName, float floatArray[MAX_ROWS][MAX_COLS], int *numRows)
{
    // Open file (antenna x, y, z coordinates)
    FILE *file = fopen(fileName, "r");
    if (file == NULL) /// If the file isn't found...
    {
        printf("Error opening file (%s).\n", fileName); // Print error to terminal
        *numRows = 0;                                   // Set the number of rows to 0
        return;                                         // Exception exit
    }

    // Read file
    int rows = 0, cols = 0;
    while (fscanf(file, "%f,%f,%f,", &floatArray[rows][cols], &floatArray[rows][cols + 1], &floatArray[rows][cols + 2]) == 3)
    {
        /* Read three float values separated by commas from file
           Store the float values in floatArray[rows3][0], floatArray[rows3][1], and floatArray[rows3][2] */
        rows++;
        if (rows >= MAX_ROWS) // If the number of rows read exceeds what is allowed for the array...
        {
            printf("Maximum number of rows exceeded (%s).\n", fileName); // Print error to terminal
            break;                                                       // Break loop from error
        }
    }
    fclose(file); // Close antenna locations file

    *numRows = rows; // Update the number of rows
}

void readComplexArray(const char *fileName, long double complex **complexArray, int *numRows, int numComplexNumbers[])
{
    // Open file (IQ data)
    FILE *file = fopen(fileName, "r");
    if (file == NULL) // If the file isn't found...
    {
        printf("Error opening IQ CSV (%s).\n", fileName); // Print error to terminal
        *numRows = 0;                                     // Set the number of rows to 0
        return;                                           // Exception exit
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
            // Extract the real and imaginary parts from 'token'
            char *endptr;
            long double real = strtold(token, &endptr);  // Convert the token to a real number
            long double imag = strtold(endptr, &endptr); // Convert the remaining string to an imaginary number
            complexArray[row][numComplexNumbers[row]] = real + imag * I; // Store complex number in array by combining and multiplying by 'i'
            numComplexNumbers[row]++;                                    // Increment the count of complex numbers for the current row                               // Increment the count of complex numbers for the current row
        }
        row++;
        if (row >= MAX_ROWS_COMPLEX) // If the number of rows read exceeds what is allowed for the array...
        {
            printf("Maximum number of rows exceeded (%s).\n", fileName); // Print error to terminal
            break;                                                       // Break loop from error
        }
    }
    fclose(file); // Close IQ file

    *numRows = row; // Update the number of rows
}