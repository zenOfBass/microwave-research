/*
ImagingDomain.c
Revised 8/2/2023
Nathan G Wiley - nwiley@uco.edu
*/

#include "ImagingDomain.h"
#include "CSVReader.h"
#include "CallHeatmap.h"
#include "DelayAndSum.h"
#include "Config.h"

long double ID[MAX_SIZE][3];   // Array for first image domain
long double ID_2[MAX_SIZE][3]; // Array for second image domain

int main()
{
    // Files
    // channel names
    const char *chan = "C:\\Users\\kick_\\OneDrive\\Documents\\Work\\autosweep\\data\\old\\file1.csv";
    // frequencies
    const char *freq = "C:\\Users\\kick_\\OneDrive\\Documents\\Work\\autosweep\\data\\old\\file2.csv";
    // antenna locations
    const char *antloc = "C:\\Users\\kick_\\OneDrive\\Documents\\Work\\autosweep\\data\\old\\file3.csv";
    // first IQ data set (Sm(f) complex)
    const char *iq1 = "C:\\Users\\kick_\\OneDrive\\Documents\\Work\\autosweep\\data\\old\\file4.csv";
    // second IQ data set (Sm(f) complex)
    const char *iq2 = "C:\\Users\\kick_\\OneDrive\\Documents\\Work\\autosweep\\data\\[0012]SG_Center_22.5(1.4-3.2).csv";

    // Arrays
    // channel names
    int chanArray[MAX_ROWS][3];
    int chanNumRows = 0;

    // frequencies
    double freqArray[MAX_ROWS];
    int freqNumRows = 0;

    // antenna locations
    float antlocArray[MAX_ROWS][3];
    int antlocNumRows = 0;

    // first IQ data set (Sm(f) complex)
    long double complex **iqArray1 = malloc(MAX_ROWS_COMPLEX * sizeof(long double complex *)); // Allocate memory for array in heap
    for (int i = 0; i < MAX_ROWS_COMPLEX; i++)                                                 // Loop over all elements
    {
        iqArray1[i] = malloc(MAX_COMPLEX_NUMBERS * sizeof(long double complex)); // Allocate memory for each element in array in heap
    }
    int iqNums1[MAX_ROWS_COMPLEX] = {0}; // Set all elements to zero
    int iqNumRows1 = 0;

    // second IQ data set (Sm(f) complex)
    long double complex **iqArray2 = malloc(MAX_ROWS_COMPLEX * sizeof(long double complex *)); // Allocate memory for array in heap
    for (int i = 0; i < MAX_ROWS_COMPLEX; i++)                                                 // Loop over all elements
    {
        iqArray2[i] = malloc(MAX_COMPLEX_NUMBERS * sizeof(long double complex)); // Allocate memory for each element in array in heap
    }
    int iqNums2[MAX_ROWS_COMPLEX] = {0}; // Set all elements to zero
    int iqNumRows2 = 0;

    // third IQ data set for subtraction
    long double complex **iqData = malloc(MAX_ROWS_COMPLEX * sizeof(long double complex *)); // Allocate memory for array in heap
    for (int i = 0; i < MAX_ROWS_COMPLEX; i++)                                               // Loop over all elements
    {
        iqData[i] = malloc(MAX_COMPLEX_NUMBERS * sizeof(long double complex)); // Allocate memory for each element in array in heap
    }

    // Read CSV files in into memory
    readIntArray(chan, chanArray, &chanNumRows);           // channel names
    readDoubleArray(freq, freqArray, &freqNumRows);        // frequencies
    readFloatArray(antloc, antlocArray, &antlocNumRows);   // antenna locations
    readComplexArray(iq1, iqArray1, &iqNumRows1, iqNums1); // first IQ data set (Sm(f) complex)
    readComplexArray(iq2, iqArray2, &iqNumRows2, iqNums2); // second IQ data set (Sm(f) complex)

    int num_points = generateImagingDomain(ID);            // Get the number of points for the image domain
    delayMultiplyAndSum(chanArray, freqArray, antlocArray, iqArray1, ID, num_points); // Do the Delay and Sum algorithm

    #ifdef IMAGE_SUBTRACTION  // If defined in Config.h image subtraction will be applied
    delayMultiplyAndSum(chanArray, freqArray, antlocArray, iqArray2, ID_2, generateImagingDomain(ID_2)); // Do the Delay and Sum algorithm for second image

    for (int i = 0; i < num_points; i++) // Loop to subtract the two images
    {
        ID[i][2] -= ID_2[i][2];
    }
    #endif

    writeImageFile(ID); // Write the image domain array out the the output file
    callHeatmap();      // Call the GNUplot script to generate the heatmap image

    // Memory deallocation
    for (int i = 0; i < MAX_ROWS_COMPLEX; i++) // Loop over the array
    {
        free(iqArray1[i]);                     // Deallocate heap memory for each element in array
    }
    free(iqArray1);                            // Deallocate heap memory for array itself

    for (int i = 0; i < MAX_ROWS_COMPLEX; i++) // Loop over the array
    {
        free(iqArray2[i]);                     // Deallocate heap memory for each element in array
    }
    free(iqArray2);                            // Deallocate heap memory for array itself

    for (int i = 0; i < MAX_ROWS_COMPLEX; i++) // Loop over the array
    {
        free(iqData[i]);                       // Deallocate heap memory for each element in array
    }
    free(iqData);                              // Deallocate heap memory for array itself

    return 0; // Exit program
}