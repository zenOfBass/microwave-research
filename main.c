#include "ImagingDomain.h"
#include "CSVReader.h"
#include "CallHeatmap.h"
#include "DelayAndSum.h"

float ID[MAX_SIZE][3];

int main()
{
    // CSVReader
    // Files
    const char *chan = "Example_csv_files\\file1.csv"; // Channel names
    const char *freq = "Example_csv_files\\file2.csv"; // fi frequencies
    const char *antloc = "file3.csv";                  // Antenna locations
    const char *iq1 = "file4.csv";                     // First IQ data set (Sm(f) complex)
    const char *iq2 = "file5.csv";                     // Second IQ data set (Sm(f) complex)

    // Arrays
    int intArray[MAX_ROWS][MAX_COLS];
    int chanNumRows;

    double doubleArray[MAX_ROWS];
    float floatArray[MAX_ROWS][MAX_COLS];
    
    long double complex **complexArray1 = malloc(MAX_ROWS_COMPLEX * sizeof(long double complex *)); // Allocate memory for array in heap
    for (int i = 0; i < MAX_ROWS_COMPLEX; i++)                                                      // Loop over all elements
    {
        complexArray1[i] = malloc(MAX_COMPLEX_NUMBERS * sizeof(long double complex)); // Allocate memory for each element in array in heap
    }
    int numComplexNumbers1[MAX_ROWS_COMPLEX] = {0}; // Set all elements to zero

    long double complex **complexArray2 = malloc(MAX_ROWS_COMPLEX * sizeof(long double complex *)); // Allocate memory for array in heap
    for (int i = 0; i < MAX_ROWS_COMPLEX; i++)                                                      // Loop over all elements
    {
        complexArray2[i] = malloc(MAX_COMPLEX_NUMBERS * sizeof(long double complex)); // Allocate memory for each element in array in heap
    }
    int numComplexNumbers2[MAX_ROWS_COMPLEX] = {0}; // Set all elements to zero

    // readIntArray();
    // readDoubleArray();
    // readFloatArray();
    // readComplexArray();
    // readComplexArray();

    generateImagingDomain(ID);

    // print first 20 for testing
    for (int i=0;i<20;i++)
    {
       printf("%f\n", ID[i][0]);
    }

    // Delay and Sum

    callHeatmap();

    // Memory deallocation
    for (int i = 0; i < MAX_ROWS_COMPLEX; i++) // Loop over the array
    {
       free(complexArray1[i]); // Deallocate heap memory for each element in array
    }
    free(complexArray1); // Deallocate memory heap for array itself
    for (int i = 0; i < MAX_ROWS_COMPLEX; i++) // Loop over the array
    {
       free(complexArray2[i]); // Deallocate heap memory for each element in array
    }
    free(complexArray2); // Deallocate memory heap for array itself

    return 0;
}