Microwave Imaging System Readme
===============================

**Authors:** Colton Cox (<ccox60@uco.edu>), Nathan G Wiley (<nwiley@uco.edu>)

This system processes IQ data from a VNA system and generates a microwave image using the Delay-and-Sum algorithm.

## Prerequisites
- C Compiler (e.g., GCC)
- GNUplot
- C Standard Library

## Files
### main.c
This file contains the main program logic. It orchestrates the execution of the entire microwave imaging process.

### ImagingDomain.c and ImagingDomain.h
This file implements functions for generating the imaging domain, a critical component of the Delay-and-Sum algorithm.

### DelayAndSum.c and DelayAndSum.h
The Delay-and-Sum algorithm is implemented in this file. It computes the imaging based on the IQ data, channel configurations, and antenna locations.

### CSVReader.c and CSVReader.h
These files provide functions for reading data from CSV files. They handle the extraction of channel names, frequencies, antenna locations, and IQ data sets.

### CallHeatmap.c and CallHeatmap.h
These files facilitate the generation of a heatmap from the radar imaging data. The `callHeatmap` function invokes GNUplot to produce visual outputs.

### Config.h
This file contains various constants and configurations used throughout the program.

### makefile
This makefile automates the build process for the microwave imaging system.

### PlotImage.p
This GNUplot script is responsible for generating the heatmap visualization from the output CSV file.

## Functions
- `generateImagingDomain(long double imaging_domain[MAX_SIZE][3])`: Generates points in the imaging domain based on specified coordinates and resolution.
- `writeImageFile(long double imaging_domain[MAX_SIZE][3])`: Writes the imaging domain data to an output CSV file.
- `timeDelay(float Tx, float Ty, float Tz, float Rx, float Ry, float Rz, double IDx, double IDy, double IDz)`: Computes the time delay for a given set of coordinates.
- `delayAndSum(int chan[NUMBER_OF_CHANNELS][2], double freq[NUMBER_OF_FREQUENCIES], float antLoc[NUMBER_OF_ANTENNAS][3], long double complex **iq, long double imagingDomain[MAX_SIZE][3], int imagingDomainSize)`: Applies the Delay-and-Sum algorithm to generate the imaging.
- `readIntArray(const char *fileName, int channels[NUMBER_OF_CHANNELS][2])`, `readDoubleArray(const char *fileName, double doubleArray[NUMBER_OF_FREQUENCIES])`, `readFloatArray(const char *fileName, float floatArray[NUMBER_OF_ANTENNAS][3])`, `readComplexArray(const char *fileName, long double complex **complexArray, int *numRows, int numComplexNumbers[])`: Functions for reading data from CSV files.
- `readDataFiles(int channelsArray[NUMBER_OF_CHANNELS][2], double frequenciesArray[NUMBER_OF_FREQUENCIES] , float antennaLocationsArray[NUMBER_OF_ANTENNAS][3], long double complex **iqArray1, long double complex **iqArray2)`: Reads data from CSV files and allocates memory dynamically.
- `callHeatmap()`: Invokes GNUplot to generate a heatmap.

## Usage
1. Compile the code using a C compiler.
2. Ensure the necessary CSV files (`channels.csv`, `frequencies.csv`, `antenna_locations.csv`, `iq_data_1.csv`, `iq_data_2.csv`) are in the same directory as the executable.
3. Run the program. It will generate microwave imaging data in `output.csv`.
4. The program will generate a heatmap visualization as an image using the GNUplot script command `gnuplot -p PlotImage.p`.

## Notes
- Ensure the constants like `RESOLUTION`, `NUMBER_OF_CHANNELS`, `NUMBER_OF_FREQUENCIES`, etc., are correctly defined in `Config.h`.