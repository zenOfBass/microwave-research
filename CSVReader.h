/*
CSVReader.h
Revised 7/21/2023
Nathan Wiley - nwiley@uco.edu
*/

#ifndef CSV_READER
#define CSV_READER

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <string.h>

#define MAX_ROWS 300            // Maximun rows for 2D channel names, frequencies, and 2D antenna locations arrays
#define MAX_ROWS_COMPLEX 500    // Maximun rows for 2D complex number array (IQ data)
#define MAX_COMPLEX_NUMBERS 500 // Maximun comlumns for 2D complex number array (IQ data)
#define BUFFER_SIZE 5000        // Maximum buffer size for line when reading complex number CSV data file

void readIntArray(const char *fileName, int intArray[MAX_ROWS][3], int *numRows);
void readDoubleArray(const char *fileName, double doubleArray[MAX_ROWS], int *numRows);
void readFloatArray(const char *fileName, float floatArray[MAX_ROWS][3], int *numRows);
void readComplexArray(const char *fileName, long double complex **complexArray, int *numRows, int numComplexNumbers[]);

#endif
