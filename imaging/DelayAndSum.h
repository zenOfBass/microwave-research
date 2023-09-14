/*
CSVReader.h
Revised 8/3/2023
Nathan Wiley - nwiley@uco.edu
*/

#ifndef DELAY_AND_SUM
#define DELAY_AND_SUM

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "Config.h"


double timeDelay(float Tx, float Ty, float Tz, 
                float Rx, float Ry, float Rz, 
                double IDx, double IDy, double IDz);
void delayAndSum(int chan[NUMBER_OF_CHANNELS][2],
                double freq[NUMBER_OF_FREQUENCIES],
                float antLoc[NUMBER_OF_ANTENNAS][3],
                long double complex **iq,
                long double imagingDomain[MAX_SIZE][3],
                int imagingDomainSize);

#endif