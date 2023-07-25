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
#define MAX_SIZE 231762
#define NUM_OF_CHANNELS 112
#define FREQ_MAX 201

double timeDelay(float Rx, float Ry, float Rz, double IDx, double IDy, double IDz);
void delayAndSum(int chan[MAX_ROWS][3],
                double freq[MAX_ROWS],
                float antLoc[MAX_ROWS][3],
                long double complex **iq,
                long double imagingDomain[MAX_SIZE][3],
                int imagingDomainSize);

#endif