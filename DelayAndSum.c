/*
CSVReader.h
Revised 7/21/2023
Nathan Wiley - nwiley@uco.edu
*/

#include "DelayAndSum.h"

double timeDelay(float Rx, float RXy, float RXz, double IDx, double IDy, double IDz)
{
    return sqrt(pow((Rx - IDx), 2) + pow((RXy - IDy), 2) + pow((RXz - IDz), 2)) / C / sqrt(ER);
}

void delayAndSum(int chan[MAX_ROWS][MAX_COLS],
                double freq[MAX_ROWS],
                float antLoc[MAX_ROWS][MAX_COLS],
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
                double IDz = 0;
                long double complex IQData = iq[f][m];
                int RXAnt = chan[m][1];
                float Rx = antLoc[RXAnt][0];
                float Ry = antLoc[RXAnt][1];
                float Rz = antLoc[RXAnt][2];
                imagingDomain[r][2] += creall(IQData * cexp(-1 * I * 2 * M_PI * timeDelay(Rx, Ry, Rz, IDx, IDy, IDz) * freq[f]));
            }
        }
    }
}