#include "ImagingDomain.h"

int idx = 0; // The number of points in the image domain

int generateImagingDomain(long double imaging_domain[IMAGING_DOMAIN_POINTS][3])
{
    for (double x = -IMAGING_DOMAIN_RADIUS; x < IMAGING_DOMAIN_RADIUS; x += RESOLUTION) // Loop over x coordinates
    {

        for (double y = -IMAGING_DOMAIN_RADIUS; y < IMAGING_DOMAIN_RADIUS; y += RESOLUTION) // Loop over y coordinates
        {
            imaging_domain[idx][0] = x;   // Set point's x coordinate
            imaging_domain[idx][1] = y;   // Set point's y coordinate
            imaging_domain[idx][2] = 0.0; // Set point's IQ data
            idx++;
        }
    }
    return idx; // Return the number of points in the image domain
}

int writeImagingDomainFile(const char* filename)
{
    FILE* imagingDomainFile;
    imagingDomainFile = fopen(filename, "w");

    for (long double x = -IMAGING_DOMAIN_RADIUS; x < IMAGING_DOMAIN_RADIUS; x += RESOLUTION) // Loop over x coordinates
    {
        for (long double y = -IMAGING_DOMAIN_RADIUS; y < IMAGING_DOMAIN_RADIUS; y += RESOLUTION) // Loop over y coordinates
        {
            fprintf(imagingDomainFile, "%Lf,%Lf,%Lf\n", x, y, 0.0L);
            idx++;
        }
    }
    return idx; // Return the number of points in the image domain

}



void writeImageFile(long double imaging_domain[IMAGING_DOMAIN_POINTS][3])
{
    // Open output file
    FILE *fp;
    fp = fopen("output.csv", "w+");

    // Write the data for the image domain from array to file
    for (int i = 0; i < IMAGING_DOMAIN_POINTS; i++)
    {
        fprintf(fp, "%Lf,", imaging_domain[i][0]);  // Write x coordinate
        fprintf(fp, "%Lf,", imaging_domain[i][1]);  // Write y coordinate
        fprintf(fp, "%.10Le\n", imaging_domain[i][2]); // Wrtie IQ data
    }
    fclose(fp); // Close file
}