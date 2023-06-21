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

void chan_freq_antloc_reader()
{
    // Declare arrays for each file type
    int intArray[MAX_ROWS][MAX_COLS];
    double doubleArray[MAX_ROWS];
    float floatArray[MAX_ROWS][MAX_COLS];

    // Read first file (int array)
    FILE *file1 = fopen("file1.csv", "r");
    if (file1 == NULL)
    {
        printf("Error opening file1.csv\n");
        return 1;
    }
    int rows1 = 0, cols1 = 0;
    while (fscanf(file1, "%d,%d,", &intArray[rows1][cols1], &intArray[rows1][cols1 + 1]) == 2)
    {
        rows1++;
        if (rows1 >= MAX_ROWS)
        {
            printf("Maximum number of rows exceeded.\n");
            break;
        }
    }
    fclose(file1);

    // Read second file (double array)
    FILE *file2 = fopen("file2.csv", "r");
    if (file2 == NULL)
    {
        printf("Error opening file2.csv\n");
        return 1;
    }
    int rows2 = 0;
    while (fscanf(file2, "%lf,", &doubleArray[rows2]) == 1)
    {
        rows2++;
        if (rows2 >= MAX_ROWS)
        {
            printf("Maximum number of rows exceeded.\n");
            break;
        }
    }
    fclose(file2);

    // Read third file (array of x, y, z float coordinates)
    FILE *file3 = fopen("file3.csv", "r");
    if (file3 == NULL)
    {
        printf("Error opening file3.csv\n");
        return 1;
    }
    int rows3 = 0;
    while (fscanf(file3, "%f,%f,%f,", &floatArray[rows3][0], &floatArray[rows3][1], &floatArray[rows3][2]) == 3)
    {
        rows3++;
        if (rows3 >= MAX_ROWS)
        {
            printf("Maximum number of rows exceeded (file 3).\n");
            break;
        }
    }
    fclose(file3);

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

    printf("chan_freq_antloc_reader() done\n");
}

void iq_reader()
{
    long double complex **complexArray1 = malloc(MAX_ROWS_COMPLEX * sizeof(long double complex *));
    for (int i = 0; i < MAX_ROWS_COMPLEX; i++)
    {
        complexArray1[i] = malloc(MAX_COMPLEX_NUMBERS * sizeof(long double complex));
    }
    int num_complex_numbers1[MAX_ROWS_COMPLEX] = {0};

    long double complex **complexArray2 = malloc(MAX_ROWS_COMPLEX * sizeof(long double complex *));
    for (int i = 0; i < MAX_ROWS_COMPLEX; i++)
    {
        complexArray2[i] = malloc(MAX_COMPLEX_NUMBERS * sizeof(long double complex));
    }
    int num_complex_numbers2[MAX_ROWS_COMPLEX] = {0};

    // Read fourth file (complex numbers)
    FILE *file4 = fopen("file4.csv", "r");
    if (file4 == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }
    else
    {
        printf("file4 read.\n");
    }

    char line4[BUFFER_SIZE];
    int row4 = 0;
    while (fgets(line4, sizeof(line4), file4))
    {
        char *token;
        char *rest = line4;
        while ((token = strtok_r(rest, ",", &rest)))
        {
            // Extract the real and imaginary parts
            char *endptr;
            long double real = strtold(token, &endptr);
            long double imag = strtold(endptr, &endptr);
            complexArray1[row4][num_complex_numbers1[row4]] = real + imag * I;
            num_complex_numbers1[row4]++;
        }
        row4++;

        if (row4 >= MAX_ROWS_COMPLEX)
        {
            printf("Maximum number of rows exceeded.\n");
            break;
        }
    }
    fclose(file4);

    // Read fifth file (complex double array)
    FILE *file5 = fopen("file5.csv", "r");
    if (file5 == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }
    else
    {
        printf("file5 read.\n");
    }

    char line[BUFFER_SIZE];
    int row5 = 0;
    while (fgets(line, sizeof(line), file5))
    {
        char *token;
        char *rest = line;
        while ((token = strtok_r(rest, ",", &rest)))
        {
            // Extract the real and imaginary parts
            char *endptr;
            long double real = strtold(token, &endptr);
            long double imag = strtold(endptr, &endptr);
            complexArray2[row5][num_complex_numbers2[row5]] = real + imag * I;
            num_complex_numbers2[row5]++;
        }
        row5++;

        if (row5 >= MAX_ROWS_COMPLEX)
        {
            printf("Maximum number of rows exceeded.\n");
            break;
        }
    }
    fclose(file5);

    // printf("\nData from file4.csv (complex double array):\n");
    // for (int i = 0; i < row4; i++)
    // {
    //     for (int j = 0; j < num_complex_numbers1[i]; j++)
    //     {
    //         long double complex c_num = complexArray1[i][j];
    //         printf("%.18Lf + %.18Lfi\n", creal(c_num), cimag(c_num));
    //     }
    // }

    // printf("\nData from file5.csv (complex double array):\n");
    // for (int i = 0; i < row5; i++)
    // {
    //     for (int j = 0; j < num_complex_numbers2[i]; j++)
    //     {
    //         long double complex c_num = complexArray2[i][j];
    //         printf("%.18Lf + %.18Lfi\n", creal(c_num), cimag(c_num));
    //     }
    // }
    // printf("\n");

    for (int i = 0; i < MAX_ROWS_COMPLEX; i++)
    {
        free(complexArray1[i]);
    }
    free(complexArray1);

    for (int i = 0; i < MAX_ROWS_COMPLEX; i++)
    {
        free(complexArray2[i]);
    }
    free(complexArray2);

    printf("iq_reader() done\n");
}

int main()
{
    chan_freq_antloc_reader();
    iq_reader();

    return 0;
}