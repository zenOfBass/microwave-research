/*
DelayAndSum.c
Revised 9/14/2023
Colton Cox - ccox60@uco.edu
Nathan G Wiley - nwiley@uco.edu
*/

#include "DelayAndSum.h"

double timeDelay(float Tx, float Ty, float Tz, 
                float Rx, float Ry, float Rz, 
                double IDx, double IDy, double IDz)
{
    #ifdef USE_PROPORTIONAL_PERMITTIVITY
    return (sqrt(pow((Rx - IDx), 2) + pow((Ry - IDy), 2) + pow((Rz - IDz), 2)) + sqrt(pow((Tx - IDx), 2) + pow((Ty - IDy), 2) + pow((Tz - IDz), 2)))
            / (C / (BOUNDARY_RADIUS * sqrt(INNER_PERMITTIVITY)/(ANTENNA_RADIUS * sqrt(OUTER_PERMITTIVITY))));
    #else
    return (sqrt(pow((Rx - IDx), 2) + pow((Ry - IDy), 2) + pow((Rz - IDz), 2)) + sqrt(pow((Tx - IDx), 2) + pow((Ty - IDy), 2) + pow((Tz - IDz), 2))) 
            / (C / (sqrt(RELATIVE_PERMITTIVITY)));
    #endif
}

void delayAndSum(int chan[NUMBER_OF_CHANNELS][2],
                double freq[NUMBER_OF_FREQUENCIES],
                float antLoc[NUMBER_OF_ANTENNAS][3],
                long double complex **iq,
                long double imagingDomain[MAX_SIZE][3],
                int imagingDomainSize)
{
    for (int r = 0; r < imagingDomainSize; r++) // Loop over number of points in image
    {
        for (int m = 0; m < NUMBER_OF_CHANNELS; m++) // Loop over the number of antenna channels
        {
            for (int f = 0; f < FREQ_MAX; f++) // Loop over the number of frequensies 
            {
                // Set image point coodinates and data
                long double complex IQData = iq[f][m]; // IQ data for point over the channel and frequnecy
                double IDx = imagingDomain[r][0];      // x
                double IDy = imagingDomain[r][1];      // y
                double IDz = Z_HEIGHT;                 // z
                
                // Receiving antenna coodinates
                int RAnt = chan[m][0];      // Antenna ID
                float Rx = antLoc[RAnt][0]; // x
                float Ry = antLoc[RAnt][1]; // y
                float Rz = antLoc[RAnt][2]; // z

                // Transmitting antenna coodinates
                int TAnt = chan[m][1];      // Antenna ID
                float Tx = antLoc[TAnt][0]; // x
                float Ty = antLoc[TAnt][1]; // y
                float Tz = antLoc[TAnt][2]; // z

                // Calculate the time delay
                double delay = timeDelay(Tx, Ty, Tz, Rx, Ry, Rz, IDx, IDy, IDz);

                // Calculate phase shift and sum
                imagingDomain[r][2] += creall(IQData * cexp(-1 * I * 2 * M_PI * delay * freq[f]));
            }
        }
    }
}