/*
ImagingDomain.c
Revised 2023-09-14
Colton Cox - ccox60@uco.edu
Nathan G Wiley - nwiley@uco.edu
*/

#ifndef CONFIG_H
#define CONFIG_H

#define CHANNELS_FILE "configuration\\channel_names.csv"
#define FREQUENCIES_FILE "configuration\\frequencies_1.4-3.2.csv"
#define ANTENNA_LOCATIONS_FILE "configuration\\antenna_locations_cylinder.csv"
#define DATA_FILE_1 "data\\benchmarking\\[0014]SW_Left_SG_Right_0(1.4-3.2).csv"
#define DATA_FILE_2 "data\\benchmarking\\[0014]SW_Left_SG_Right_22.5(1.4-3.2).csv"

//#define USE_PROPORTIONAL_PERMITTIVITY
#define ANTENNA_RADIUS 0.077
#define BOUNDARY_RADIUS 0.05
#define INNER_PERMITTIVITY 8
#define OUTER_PERMITTIVITY 1

#define RELATIVE_PERMITTIVITY 1 // Relative permittivity of subject

// #define IMAGE_SUBTRACTION
#define CHANNEL_ARRAY_SIZE 224  // 112 * 2 integers in channels
#define NUMBER_OF_CHANNELS 112
#define NUMBER_OF_FREQUENCIES 201
#define NUMBER_OF_ANTENNAS 8

#define GLOBAL_Z 0
#define C 299792458.0           // Speed of light

#define FREQ_MAX 201            // Maximum number of frequencies

#define Z_HEIGHT 0              // Z coordinate of image taken of subject
#define MAX_ROWS 300            // Maximun rows for 2D channel names, frequencies, and 2D antenna locations arrays//
#define MAX_SIZE 231762         // Maximum number of points that can be in the image domain

#endif