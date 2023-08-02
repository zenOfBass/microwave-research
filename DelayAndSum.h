/*
CSVReader.h
Revised 8/2/2023
Nathan Wiley - nwiley@uco.edu
*/

#ifndef DELAY_AND_SUM
#define DELAY_AND_SUM

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "Config.h"

#define C 299792458.0       // Speed of light
#define MAX_ROWS 300        // Maximun rows for 2D channel names, frequencies, and 2D antenna locations arrays//
#define MAX_SIZE 231762     // Maximum number of points that can be in the image domain
#define NUM_OF_CHANNELS 112 // Number of antenna channels
#define FREQ_MAX 201        // Maximum number of frequencies

double timeDelay(float Tx, float Ty, float Tz, 
                float Rx, float Ry, float Rz, 
                double IDx, double IDy, double IDz);
void delayAndSum(int chan[MAX_ROWS][3],
                double freq[MAX_ROWS],
                float antLoc[MAX_ROWS][3],
                long double complex **iq,
                long double imagingDomain[MAX_SIZE][3],
                int imagingDomainSize);
void delayMultiplyAndSum(int chan[MAX_ROWS][3],
                        double freq[MAX_ROWS],
                        float antLoc[MAX_ROWS][3],
                        long double complex **iq,
                        long double imagingDomain[MAX_SIZE][3],
                        int imagingDomainSize);

#endif