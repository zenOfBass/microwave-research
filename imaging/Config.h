/**********************************
/ Config.h
/ Colton Cox - ccox60@uco.edu
/ Nathan G Wiley - nwiley@uco.edu
/ University of Central Oklahoma
/ See changelog.md for detailed changes
**********************************/

#ifndef CONFIG_H
#define CONFIG_H

#define CHANNELS_FILE "configuration\\channel_names.csv"
#define FREQUENCIES_FILE "configuration\\frequencies_1.4-3.2.csv"
#define ANTENNA_LOCATIONS_FILE "configuration\\antenna_locations_cylinder.csv"
#define DATA_FILE_1 "data\\K003-KSample_1.4-3.2_200_8_0.csv"
#define DATA_FILE_2 "data\\K004-KSample_1.4-3.2_200_8_0.csv"

#define CHANNEL_ARRAY_SIZE 224  // 112 * 2 integers in channels
#define NUMBER_OF_CHANNELS 112
#define NUMBER_OF_FREQUENCIES 201
#define NUMBER_OF_ANTENNAS 8


//OPTIONS

// #define USE_PROPORTIONAL_PERMITTIVITY
#define IMAGE_SUBTRACTION


#define ANTENNA_RADIUS 0.0765
#define BOUNDARY_RADIUS 0.025
#define INNER_PERMITTIVITY 80
#define OUTER_PERMITTIVITY 8

#define RELATIVE_PERMITTIVITY 8 // Relative permittivity of subject

#define IMAGING_DOMAIN_RADIUS 0.0765
#define RESOLUTION 0.0025 // Resolution taken of the image based on the distance between sampled point

// Calculate as (2*IMAGING_DOMAIN_RADIUS)^2 / RESOLUTION^2;
#define IMAGING_DOMAIN_POINTS 4000

#define Z_HEIGHT 0.02
#define GLOBAL_Z 0.02
#define C 299792458.0       // Speed of light

//#define FREQ_MAX 1001            // Maximum number of frequencies

#define MAX_ROWS 1200            // Maximun rows for 2D channel names, frequencies, and 2D antenna locations arrays//
#define MAX_SIZE 231762         // Maximum number of points that can be in the image domain

#endif