/*
ImagingDomain.c
Revised 6/22/2023 
Colton Cox - ccox60@uco.edu
*/

#ifndef IMAGING_DOMAIN
#define IMAGING_DOMAIN

#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 0.14
#define LENGTH 0.14
#define RESOLUTION 0.0025
#define Z 0
#define MAX_SIZE 231762


// #define WRITE_TO_FILE                 // Uncomment to write results to output.csv

int generateImagingDomain(long double imaging_domain[MAX_SIZE][3]);
void writeImageFile(long double imaging_domain[MAX_SIZE][3]);

#endif