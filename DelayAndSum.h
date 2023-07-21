/*
CSVReader.h
Revised 7/21/2023
Nathan Wiley - nwiley@uco.edu
*/

#ifndef DELAY_AND_SUM
#define DELAY_AND_SUM

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define C 299792458.0
#define ER 1
#define MAX_ROWS 300
#define MAX_COLS 3
#define MAX_SIZE 231762
#define NUM_OF_CHANNELS 112
#define FREQ_MAX 201

double timeDelay(float RX_x, float RX_y, float RX_z, double ID_x, double ID_y, double ID_z);
void delayAndSum(int intArray[MAX_ROWS][MAX_COLS],
                double doubleArray[MAX_ROWS],
                float floatArray[MAX_ROWS][MAX_COLS],
                long double complex **complexArray,
                long double imagingDomain[MAX_SIZE][3],
                int imagingDomainSize);

#endif