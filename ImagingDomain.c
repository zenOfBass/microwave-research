/*
ImagingDomain.c
Revised 7/21/2023
Nathan Wiley - nwiley@uco.edu
*/

#include "ImagingDomain.h"

int index = 0;

int generateImagingDomain(long double imaging_domain[MAX_SIZE][3])
{
    for (double x = -0.07; x < 0.07; x += RESOLUTION)
    {
        
        for (double y = -0.07; y < 0.07; y += RESOLUTION)
        {
            imaging_domain[index][0] = x;
            imaging_domain[index][1] = y;
            imaging_domain[index][2] = 0.0;
            index++;
        }
    }
    
// If WRITE_TO_FILE defined in .h will write results to output.csv
#ifdef WRITE_TO_FILE
    FILE* fp;
    fp = fopen("output.csv", "w+");
    for (int i = 0; i < index; i++)
    {
        fprintf(fp, "%lf,", imaging_domain[i][0]);
        fprintf(fp, "%lf,", imaging_domain[i][1]);
        fprintf(fp, "%lf\n", imaging_domain[i][2]);
    }
    fclose(fp);
#endif

    return index;
}

void writeImageFile(long double imaging_domain[MAX_SIZE][3])
{
    FILE *fp;
    fp = fopen("output.csv", "w+");
    for (int i = 0; i < index; i++)
    {
        fprintf(fp, "%Lf,", imaging_domain[i][0]);
        fprintf(fp, "%Lf,", imaging_domain[i][1]);
        fprintf(fp, "%Lf\n", imaging_domain[i][2]);
    }
    fclose(fp);
}