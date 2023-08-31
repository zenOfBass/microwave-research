/*
ImagingDomain.h
Revised 8/3/2023
Nathan G Wiley - nwiley@uco.edu
*/

#ifndef IMAGING_DOMAIN
#define IMAGING_DOMAIN

#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Config.h"

#define WIDTH 0.14        // Width of image
#define LENGTH 0.14       // Height of image
#define RESOLUTION 0.0025 // Resolution taken of the image based on the distance between sampled point

int generateImagingDomain(long double imaging_domain[MAX_SIZE][3]);
void writeImageFile(long double imaging_domain[MAX_SIZE][3]);

#endif