/*
csvreader.c
Revised 6/22/2023 
Nathan Wiley - nwiley @uco.edu
*/

//////////////////////////////////////////////////////
// Imports

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <string.h>

//////////////////////////////////////////////////////
// Define constants

#define MAX_ROWS 300            // Maximun rows for 2D channel names, frequencies, and 2D antenna locations arrays
#define MAX_COLS 3              // Maximun comlumns for 2D channel names and 2D antenna locations arrays
#define MAX_ROWS_COMPLEX 500    // Maximun rows for 2D complex number array (IQ data)
#define MAX_COMPLEX_NUMBERS 500 // Maximun comlumns for 2D complex number array (IQ data)
#define BUFFER_SIZE 4096        // Maximum buffer size for line when reading complex number CSV data file

// Function definitions
void chan_freq_antloc_reader(const char *chan, const char *freq, const char *antloc);
void iq_reader(const char *iq);