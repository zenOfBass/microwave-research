/*
Colton Cox   - ccox60@uco.edu
Nathan Wiley - nwiley@uco.edu

University of Central OKlahoma - 2023
See changelog.md for detailed changes
*/

#ifndef CONFIG_H
#define CONFIG_H

#define CHANNELS_FILE "configuration\\channel_names.csv"
#define FREQUENCIES_FILE "configuration\\frequencies_3.588-3.656_68.csv"
#define ANTENNA_LOCATIONS_FILE "configuration\\antenna_locations_cylinder.csv"
#define DATA_FILE_1 "data\\0001-RectangularParallelpiped5_3.588-3.656_68_8_0.csv"
#define DATA_FILE_2 "data\\0000-EmptyFieldOrangeDisk_3.588-3.656_68_8_0.csv"

#define CHANNEL_ARRAY_SIZE 224  // 112 * 2 integers in channels
#define NUMBER_OF_CHANNELS 112
#define NUMBER_OF_FREQUENCIES 69
#define NUMBER_OF_ANTENNAS 8


//OPTIONS

// #define USE_PROPORTIONAL_PERMITTIVITY
#define IMAGE_SUBTRACTION


#define ANTENNA_RADIUS 0.0775
#define BOUNDARY_RADIUS 0.025
#define INNER_PERMITTIVITY 80
#define OUTER_PERMITTIVITY 1

#define RELATIVE_PERMITTIVITY 1 // Relative permittivity of subject

#define IMAGING_DOMAIN_RADIUS 0.0775
#define RESOLUTION 0.0025 // Resolution taken of the image based on the distance between sampled point

// Calculate as (2*IMAGING_DOMAIN_RADIUS)^2 / RESOLUTION^2;
#define IMAGING_DOMAIN_POINTS 3844

#define Z_HEIGHT 0.0
#define GLOBAL_Z 0.0
#define C 299792458.0       // Speed of light

//#define FREQ_MAX 1001            // Maximum number of frequencies

#define MAX_ROWS 1200            // Maximun rows for 2D channel names, frequencies, and 2D antenna locations arrays//
#define MAX_SIZE 231762         // Maximum number of points that can be in the image domain



#endif