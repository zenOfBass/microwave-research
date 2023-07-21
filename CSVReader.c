/*
CSVReader.c
Revised 7/21/2023
Nathan Wiley - nwiley@uco.edu
*/

#include "CSVReader.h"

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

    // // Print the contents of the arrays
    // printf("Data from the IQ file (long double complex):\n");
    // int ok;
    // for (int i = 0; i < row; i++)
    // {
    //     for (int j = 0; j < numComplexNumbers[i]; j++)
    //     {
    //         long double complex c_num = complexArray[i][j];
    //         printf("[%d][%d] %.18Lf + %.18Lfi\n", i, j, creall(c_num), cimagl(c_num));
    //         scanf("%d", &ok);
    //     }
    // }

    *numRows = row;
}
