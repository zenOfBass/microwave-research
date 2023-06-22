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

#define SPHERE_RADIUS 5
#define RESOLUTION 0.25                 // Space between points on x, y, z axes
#define ANGULAR_RESOLUTION M_PI/180     // angle delta used to generate one circle
#define MAX_SIZE 231762                 // maximum number of points generated


//#define WRITE_TO_FILE                 // Uncomment to write results to output.csv

void GenerateImagingDomain(float imaging_domain[MAX_SIZE][3]);


#endif
