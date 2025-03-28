/*
ImagingDomain.c
Revised 8/3/2023
Nathan Wiley - nwiley@uco.edu
*/

#ifndef CONFIG_H
#define CONFIG_H

// #define IMAGE_SUBTRACTION

#define NUM_OF_CHANNELS 112     // Number of antenna channels
#define FREQ_MAX 201            // Maximum number of frequencies
#define RELATIVE_PERMITTIVITY 1 // Relative permittivity of subject
#define Z_HEIGHT 0              // Z coordinate of image taken of subject
#define MAX_ROWS 300            // Maximun rows for 2D channel names, frequencies, and 2D antenna locations arrays//
#define MAX_SIZE 231762         // Maximum number of points that can be in the image domain

#endif