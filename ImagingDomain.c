/*
ImagingDomain.c
Revised 6/22/2023 
Colton Cox - ccox60@uco.edu
*/

#include "ImagingDomain.h"


int generateImagingDomain(float imaging_domain[MAX_SIZE][3])
{

    int index = 0;

    for (float x=0;x<LENGTH;x+=RESOLUTION)
    {
        
        for (float y=0;y<WIDTH;y+=RESOLUTION)
        {
            imaging_domain[index][0] = x;
            imaging_domain[index][1] = y;
            imaging_domain[index][2] = rand();
            index++;
        }
    }
    
// If WRITE_TO_FILE defined in .h will write results to output.csv
#ifdef WRITE_TO_FILE
    FILE* fp;
    fp = fopen("output.csv", "w+");
    for (int i = 0; i < index; i++)
    {
        fprintf(fp, "%f,", imaging_domain[i][0]);
        fprintf(fp, "%f,", imaging_domain[i][1]);
        fprintf(fp, "%f\n", imaging_domain[i][2]);
    }
    fclose(fp);
#endif

    return index;
}