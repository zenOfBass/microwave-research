/*
Colton Cox   - ccox60@uco.edu
Nathan Wiley - nwiley@uco.edu

University of Central OKlahoma - 2023
See changelog.md for detailed changes
*/
#include <time.h>
#include "ImagingDomain.h"
#include "CSVReader.h"
#include "CallHeatmap.h"
#include "DelayAndSum.h"
#include "Config.h"

int main()
{
    clock_t start, stop;
    double cpu_time_used;
    start = clock();

    // Array declarations for Imaging Domain, channels, frequencies, and antenna locations
    long double ID[IMAGING_DOMAIN_POINTS][3]; 
    long double ID2[IMAGING_DOMAIN_POINTS][3];   
    int channels[NUMBER_OF_CHANNELS][2];
    double freqArray[NUMBER_OF_FREQUENCIES];
    float antlocArray[MAX_ROWS][3];

    // Array declarations for complex IQ Data
    long double complex **iqArray1 = malloc(MAX_ROWS_COMPLEX * sizeof(long double complex *)); // Allocate memory for array in heap
    long double complex **iqArray2 = malloc(MAX_ROWS_COMPLEX * sizeof(long double complex *)); // Allocate memory for array in heap

    

    // Read data from files
    readDataFiles(channels, freqArray, antlocArray, iqArray1, iqArray2);

    /*
    Optionally generate an imaging domain in memory at runtime, read an imaging domain from a file, 
    write an imaging domain to file which can be read from later
    */


    //generateImagingDomain(ID);                        // Generate an imaging domain at runtime in memory
    //writeImagingDomainFile("Imaging_Domain.csv");     // Write an imaging domain file
    readImagingDomainFile("Imaging_Domain.csv", ID);    // Read imaging domain from a file

    /*!!IMPORTANT!!
    Note that if IMAGE_SUBTRACTION is defined, a unique imaging domain will need to be used for 
    each delay and sum computed. If reading from a file, two unique imaging domain arrays can read from
    the same file. 
    Example: 
    readImagingDomainFile("Imaging_Domain.csv", ID);
    readImagingDomainFile("Imaging_Domain.csv", ID2);
    */


    // DELAY AND SUM
    delayAndSum(channels, freqArray, antlocArray, iqArray1, ID, IMAGING_DOMAIN_POINTS); 
    
    #ifdef IMAGE_SUBTRACTION
    delayAndSum(channels, freqArray, antlocArray, iqArray2, ID2, generateImagingDomain(ID2));

    for (int i=0;i<IMAGING_DOMAIN_POINTS;i++)
    {
        ID[i][2] -= ID2[i][2];
    }
    #endif


    // Pixel intensity data is written to the third column of the imaging domain file
    writeImageFile(ID);
    callHeatmap();      // Call the GNUplot script to generate the heatmap image



    cleanUp(iqArray1, iqArray2); // De-allocate heap memory used


    stop = clock();
    cpu_time_used = ((double) (stop - start)) / CLOCKS_PER_SEC;
    printf("Runtime: %f s", cpu_time_used);

    return 0; // Exit program
}