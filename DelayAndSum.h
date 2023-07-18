/*
CSVReader.h
Revised 7/11/2023
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

float calculateDistance(float RXAntennaPoint[3], float TXAntennaPoint[3], double imagingDomainPoint[3]);
double timeDelay(float distance);
void delayAndSum(
                int channels[MAX_ROWS][MAX_COLS],
                double frequencies[MAX_ROWS],
                float antennaLocations[MAX_ROWS][MAX_COLS],
                long double complex** signalData,
                double imagingDomain[MAX_SIZE][3],
                int imagingDomainSize);
                

#endif