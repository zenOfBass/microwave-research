/*
ImagingDomain.c
Revised 6/22/2023 
Colton Cox - ccox60@uco.edu
*/


#include "ImagingDomain.h"


void GenerateImagingDomain(float imaging_domain[MAX_SIZE][3])
{
    int index = 0;
    for(float height=0; height < SPHERE_RADIUS * 2; height += RESOLUTION)
    {
        float circle_radius = sqrtf(powf(SPHERE_RADIUS, 2) - powf((SPHERE_RADIUS - height), 2));
        for (float angle = 0; angle < 2 * M_PI; angle += ANGULAR_RESOLUTION)
        {
            for (float r = 0; r < circle_radius; r += RESOLUTION)
            {
                imaging_domain[index][0] = r * cosf(angle);
                imaging_domain[index][1] = r * sinf(angle);
                imaging_domain[index][2] = height;
                index++;
            }
        }
    }

// If WRITE_TO_FILE defined in .h will write results to output.csv
#ifdef WRITE_TO_FILE
    FILE* fp;
    fp = fopen("output.csv", "w+");
    for (int i=0; i < index; i++)
    {
        fprintf(fp, "%f,", imaging_domain[i][0]);
        fprintf(fp, "%f,", imaging_domain[i][1]);
        fprintf(fp, "%f\n", imaging_domain[i][2]);
    }
    fclose(fp);
#endif

}

