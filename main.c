/*
ImagingDomain.c
Revised 7/25/2023
Nathan Wiley - nwiley@uco.edu
*/

#include "ImagingDomain.h"
#include "CSVReader.h"
#include "CallHeatmap.h"
#include "DelayAndSum.h"
#include "Config.h"

long double ID[MAX_SIZE][3];

int main()
{
    // Files
    const char *chan = "Benchmarking\\channel_names.csv";                  // Channel names
    const char *freq = "Benchmarking\\frequencies_1.4-3.2.csv";           // fi frequencies
    const char *antloc = "Benchmarking\\antenna_locations_cylinder.csv"; // Antenna locations
    const char *iq1 = "Benchmarking\\0012SG_Center_01.4-3.2.csv"; // First IQ data set (Sm(f) complex)
    const char *iq2 = "Example_csv_files\\file5.csv";    // Second IQ data set (Sm(f) complex)

    // Arrays
    int chanArray[MAX_ROWS][3];
    int chanNumRows = 0;

    double freqArray[MAX_ROWS];
    int freqNumRows = 0;

    float antlocArray[MAX_ROWS][3];
    int antlocNumRows = 0;

    long double complex **iqArray1 = malloc(MAX_ROWS_COMPLEX * sizeof(long double complex *)); // Allocate memory for array in heap
    for (int i = 0; i < MAX_ROWS_COMPLEX; i++)                                                 // Loop over all elements
    {
        iqArray1[i] = malloc(MAX_COMPLEX_NUMBERS * sizeof(long double complex)); // Allocate memory for each element in array in heap
    }
    int iqNums1[MAX_ROWS_COMPLEX] = {0}; // Set all elements to zero
    int iqNumRows1 = 0;

    long double complex **iqArray2 = malloc(MAX_ROWS_COMPLEX * sizeof(long double complex *)); // Allocate memory for array in heap
    for (int i = 0; i < MAX_ROWS_COMPLEX; i++)                                                 // Loop over all elements
    {
        iqArray2[i] = malloc(MAX_COMPLEX_NUMBERS * sizeof(long double complex)); // Allocate memory for each element in array in heap
    }
    int iqNums2[MAX_ROWS_COMPLEX] = {0}; // Set all elements to zero
    int iqNumRows2 = 0;

    long double complex **iqData = malloc(MAX_ROWS_COMPLEX * sizeof(long double complex *)); // Allocate memory for array in heap
    for (int i = 0; i < MAX_ROWS_COMPLEX; i++)                                               // Loop over all elements
    {
        iqData[i] = malloc(MAX_COMPLEX_NUMBERS * sizeof(long double complex)); // Allocate memory for each element in array in heap
    }
    int iqDataNums[MAX_ROWS_COMPLEX] = {0}; // Set all elements to zero
    int iqDataNumRows = 0;

    // Read CSV files in into memory
    readIntArray(chan, chanArray, &chanNumRows);
    readDoubleArray(freq, freqArray, &freqNumRows);
    readFloatArray(antloc, antlocArray, &antlocNumRows);
    readComplexArray(iq1, iqArray1, &iqNumRows1, iqNums1);
    readComplexArray(iq2, iqArray2, &iqNumRows2, iqNums2);

    // Image subtraction
    // #ifdef IMAGE_SUBTRACTION
    // for (int i = 0; i < MAX_ROWS_COMPLEX; i++)
    // {
    //     for (int j = 0; j < MAX_COMPLEX_NUMBERS; j++)
    //     {
    //         iqData[i][j] = iqArray2[i][j] - iqArray1[i][j];
    //     }
    // }
    // #endif

    delayAndSum(chanArray, freqArray, antlocArray, iqArray1, ID, generateImagingDomain(ID));
    writeImageFile(ID);
    callHeatmap();

    // Memory deallocation
    for (int i = 0; i < MAX_ROWS_COMPLEX; i++) // Loop over the array
    {
        free(iqArray1[i]); // Deallocate heap memory for each element in array
    }
    free(iqArray1); // Deallocate heap memory for array itself

    for (int i = 0; i < MAX_ROWS_COMPLEX; i++) // Loop over the array
    {
        free(iqArray2[i]); // Deallocate heap memory for each element in array
    }
    free(iqArray2); // Deallocate heap memory for array itself

    for (int i = 0; i < MAX_ROWS_COMPLEX; i++) // Loop over the array
    {
        free(iqData[i]); // Deallocate heap memory for each element in array
    }
    free(iqData); // Deallocate heap memory for array itself

    return 0;
}