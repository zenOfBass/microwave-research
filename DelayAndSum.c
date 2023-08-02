/*
CSVReader.h
Revised 8/2/2023
Nathan Wiley - nwiley@uco.edu
*/

#include "DelayAndSum.h"

double timeDelay(float Tx, float Ty, float Tz, float Rx, float Ry, 
                float Rz, double IDx, double IDy, double IDz)
{
    return (sqrt(pow((Rx - IDx), 2) + pow((Ry - IDy), 2) + pow((Rz - IDz), 2)) + sqrt(pow((Tx - IDx), 2) + pow((Ty - IDy), 2) + pow((Tz - IDz), 2))) / (C / sqrt(RELATIVE_PERMITTIVITY));
}

void delayAndSum(int chan[MAX_ROWS][3],
                double freq[MAX_ROWS],
                float antLoc[MAX_ROWS][3],
                long double complex **iq,
                long double imagingDomain[MAX_SIZE][3],
                int imagingDomainSize)
{
    for (int r = 0; r < imagingDomainSize; r++) // Loop over number of points in image
    {
        for (int m = 0; m < NUM_OF_CHANNELS; m++) // Loop over the number of antenna channels
        {
            for (int f = 0; f < FREQ_MAX; f++) // Loop over the number of frequensies 
            {
                // Set image point coodinates and data
                double IDx = imagingDomain[r][0];      // x
                double IDy = imagingDomain[r][1];      // y
                double IDz = Z_HEIGHT;                 // z
                long double complex IQData = iq[f][m]; // IQ data for point over the channel and frequnecy

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

                // Run algorithm using data
                imagingDomain[r][2] += creall(IQData * cexp(-1 * I * 2 * M_PI * timeDelay(Tx, Ty, Tz, Rx, Ry, Rz, IDx, IDy, IDz) * freq[f]));
            }
        }
    }
}

void delayMultiplyAndSum(int chan[MAX_ROWS][3],
                double freq[MAX_ROWS],
                float antLoc[MAX_ROWS][3],
                long double complex **iq,
                long double imagingDomain[MAX_SIZE][3],
                int imagingDomainSize)
{
    for (int r = 0; r < imagingDomainSize; r++)
    {
        for (int m = 0; m < NUM_OF_CHANNELS; m++)
        {
            for (int f = 0; f < FREQ_MAX; f++)
            {
                double IDx = imagingDomain[r][0];
                double IDy = imagingDomain[r][1];
                double IDz = 0.03;
                long double complex IQData = iq[f][m];
                int RAnt = chan[m][0];
                int TAnt = chan[m][1];
                float Rx = antLoc[RAnt][0];
                float Ry = antLoc[RAnt][1];
                float Rz = antLoc[RAnt][2];
                float Tx = antLoc[TAnt][0];
                float Ty = antLoc[TAnt][1];
                float Tz = antLoc[TAnt][2];
                imagingDomain[r][2] += creall(IQData * cexp(-1 * I * 2 * M_PI * timeDelay(Tx, Ty, Tz, Rx, Ry, Rz, IDx, IDy, IDz) * freq[f]));
            }
        }
    }
}