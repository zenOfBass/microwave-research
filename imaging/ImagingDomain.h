#ifndef IMAGING_DOMAIN
#define IMAGING_DOMAIN

#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Config.h"


int generateImagingDomain(long double imaging_domain[IMAGING_DOMAIN_POINTS][3]);
void writeImageFile(long double imaging_domain[IMAGING_DOMAIN_POINTS][3]);
int writeImagingDomainFile(const char* filename);

#endif