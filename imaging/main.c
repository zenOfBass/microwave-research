/*
main.c
Revised 2023-09-14
Colton Cox - ccox60@uco.edu
Nathan G Wiley - nwiley@uco.edu
*/

#include "ImagingDomain.h"
#include "CSVReader.h"
#include "CallHeatmap.h"
#include "DelayAndSum.h"
#include "Config.h"

long double ID[MAX_SIZE][3]; // Array for first image domain

int main()
{
    // Arrays
    // channel names
    int channels[NUMBER_OF_CHANNELS][2];
    // frequencies
    double freqArray[NUMBER_OF_FREQUENCIES];
    // antenna locations
    float antlocArray[MAX_ROWS][3];
    // first IQ data set (Sm(f) complex)
    long double complex **iqArray1 = malloc(MAX_ROWS_COMPLEX * sizeof(long double complex *)); // Allocate memory for array in heap
    // second IQ data set (Sm(f) complex)
    long double complex **iqArray2 = malloc(MAX_ROWS_COMPLEX * sizeof(long double complex *)); // Allocate memory for array in heap

    // Read CSV files in into memory
    readDataFiles(channels, freqArray, antlocArray, iqArray1, iqArray2);

    delayAndSum(channels, freqArray, antlocArray, iqArray1, ID, generateImagingDomain(ID)); 
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

    return 0; // Exit program
}