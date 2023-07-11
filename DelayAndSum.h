/*
CSVReader.h
Revised 7/11/2023
Nathan Wiley - nwiley@uco.edu
*/

#ifndef DELAY_AND_SUM
#define DELAY_AND_SUM

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define C 299792458.0
#define ER 1
#define MAX_ROWS 300
#define MAX_COLS 3
#define MAX_SIZE 231762
#define NUM_OF_CHANNELS 201
#define FREQ_MAX 112

double timeDelay(float RX_x, float RX_y, float RX_z, float ID_x, float ID_y, float ID_z);
void readDoubleArray(const char *fileName, double doubleArray[MAX_ROWS], int *numRows);

#endif