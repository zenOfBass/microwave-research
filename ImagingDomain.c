/*
ImagingDomain.c
Revised 8/2/2023
Nathan Wiley - nwiley@uco.edu
*/

#include "ImagingDomain.h"

int index = 0; // The number of points in the image domain

int generateImagingDomain(long double imaging_domain[MAX_SIZE][3])
{
    for (double x = -0.07; x < 0.07; x += RESOLUTION) // Loop over x coordinates
    {

        for (double y = -0.07; y < 0.07; y += RESOLUTION) // Loop over y coordinates
        {
            imaging_domain[index][0] = x;   // Set point's x coordinate
            imaging_domain[index][1] = y;   // Set point's y coordinate
            imaging_domain[index][2] = 0.0; // Set point's IQ data
            index++;
        }
    }
    return index; // Return the number of points in the image domain
}

void writeImageFile(long double imaging_domain[MAX_SIZE][3])
{
    // Open output file
    FILE *fp;
    fp = fopen("output.csv", "w+");

    // Write the data for the image domain from array to file
    for (int i = 0; i < index; i++)
    {
        fprintf(fp, "%Lf,", imaging_domain[i][0]);  // Write x coordinate
        fprintf(fp, "%Lf,", imaging_domain[i][1]);  // Write y coordinate
        fprintf(fp, "%Lf\n", imaging_domain[i][2]); // Wrtie IQ data
    }
    fclose(fp); // Close file
}