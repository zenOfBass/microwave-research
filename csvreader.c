#include "csvReader.h"

#define MAX_ROWS 300            // Maximun rows for 2D channel names, frequencies, and 2D antenna locations arrays
#define MAX_COLS 3              // Maximun comlumns for 2D channel names and 2D antenna locations arrays
#define MAX_ROWS_COMPLEX 500    // Maximun rows for 2D complex number array (IQ data)
#define MAX_COMPLEX_NUMBERS 500 // Maximun comlumns for 2D complex number array (IQ data)
#define BUFFER_SIZE 4096        // Maximum buffer size for line when reading complex number CSV data file

void readIntArray(const char *fileName, int intArray[MAX_ROWS][MAX_COLS], int *numRows)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Error opening file (%s).\n", fileName);
        *numRows = 0;
        return;
    }

    int rows = 0, cols = 0;
    while (fscanf(file, "%d,%d,", &intArray[rows][cols], &intArray[rows][cols + 1]) == 2)
    {
        rows++;
        if (rows >= MAX_ROWS)
        {
            printf("Maximum number of rows exceeded (%s).\n", fileName);
            break;
        }
    }
    fclose(file);

    *numRows = rows;
}

void readDoubleArray(const char *fileName, double doubleArray[MAX_ROWS], int *numRows)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Error opening file (%s).\n", fileName);
        *numRows = 0;
        return;
    }

    int rows = 0;
    while (fscanf(file, "%lf,", &doubleArray[rows]) == 1)
    {
        rows++;
        if (rows >= MAX_ROWS)
        {
            printf("Maximum number of rows exceeded (%s).\n", fileName);
            break;
        }
    }
    fclose(file);

    *numRows = rows;
}

void readFloatArray(const char *fileName, float floatArray[MAX_ROWS][MAX_COLS], int *numRows)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Error opening file (%s).\n", fileName);
        *numRows = 0;
        return;
    }

    int rows = 0, cols = 0;
    while (fscanf(file, "%f,%f,%f,", &floatArray[rows][cols], &floatArray[rows][cols + 1], &floatArray[rows][cols + 2]) == 3)
    {
        rows++;
        if (rows >= MAX_ROWS)
        {
            printf("Maximum number of rows exceeded (%s).\n", fileName);
            break;
        }
    }
    fclose(file);

    *numRows = rows;
}

void readComplexArray(const char *fileName, long double complex **complexArray, int *numRows, int numComplexNumbers[])
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Error opening IQ CSV (%s).\n", fileName);
        *numRows = 0;
        return;
    }

    char line[BUFFER_SIZE];
    int row = 0;
    while (fgets(line, sizeof(line), file))
    {
        char *token;
        char *rest = line;
        while ((token = strtok_r(rest, ",", &rest)))
        {
            char *endptr;
            long double real = strtold(token, &endptr);
            long double imag = strtold(endptr, &endptr);
            complexArray[row][numComplexNumbers[row]] = real + imag * I;
            numComplexNumbers[row]++;
        }
        row++;
        if (row >= MAX_ROWS_COMPLEX)
        {
            printf("Maximum number of rows exceeded (%s).\n", fileName);
            break;
        }
    }
    fclose(file);

    *numRows = row;
}
