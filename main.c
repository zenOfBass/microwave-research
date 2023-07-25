/*
ImagingDomain.c
Revised 7/21/2023
Nathan Wiley - nwiley@uco.edu
*/

#include "ImagingDomain.h"
#include "CSVReader.h"
#include "CallHeatmap.h"
#include "DelayAndSum.h"

long double ID[MAX_SIZE][3];

int main()
{
    // Files
    const char *chan = "Example_csv_files\\file1.csv";   // Channel names
    const char *freq = "Example_csv_files\\file2.csv";   // fi frequencies
    const char *antloc = "Example_csv_files\\file3.csv"; // Antenna locations
    const char *iq1 = "Example_csv_files\\file4.csv";    // First IQ data set (Sm(f) complex)
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

    readIntArray(chan, chanArray, &chanNumRows);
    readDoubleArray(freq, freqArray, &freqNumRows);
    readFloatArray(antloc, antlocArray, &antlocNumRows);
    readComplexArray(iq1, iqArray1, &iqNumRows1, iqNums1); 

    // #ifdef IMAGE_SUBTRACTION
    // iqData = iqArray1 - iqArray2;
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

    // for (int i = 0; i < MAX_ROWS_COMPLEX; i++) // Loop over the array
    // {
    //    free(iqData[i]); // Deallocate heap memory for each element in array
    // }
    // free(iqData); // Deallocate heap memory for array itself

    return 0;
}