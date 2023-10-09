#ifndef CSV_READER
#define CSV_READER

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <string.h>
#include "Config.h"


#define MAX_ROWS_COMPLEX 500    // Maximun rows for 2D complex number array (IQ data)
#define MAX_COMPLEX_NUMBERS 500 // Maximun comlumns for 2D complex number array (IQ data)
#define BUFFER_SIZE 6000        // Maximum buffer size for line when reading complex number CSV data file

void readImagingDomainFile(const char *fileName, long double imaging_domain[IMAGING_DOMAIN_POINTS][3]);
void readIntArray(const char *fileName, int channels[NUMBER_OF_CHANNELS][2]);
void readDoubleArray(const char *fileName, double doubleArray[NUMBER_OF_FREQUENCIES]);
void readFloatArray(const char *fileName, float floatArray[NUMBER_OF_ANTENNAS][3]);
void readComplexArray(const char *fileName, long double complex **complexArray, int *numRows, int numComplexNumbers[]);
void readDataFiles(int channelsArray[NUMBER_OF_CHANNELS][2], double frequenciesArray[NUMBER_OF_FREQUENCIES] , float antennaLocationsArray[NUMBER_OF_ANTENNAS][3], long double complex **iqArray1, long double complex **iqArray2);


void cleanUp(long double complex **complexArray1, long double complex **complexArray2);
#endif
