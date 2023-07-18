/*
CSVReader.h
Revised 7/12/2023
Nathan Wiley - nwiley@uco.edu
*/

#include "DelayAndSum.h"


double timeDelay(float RX_x, float RX_y, float RX_z, double ID_x, double ID_y, double ID_z)
{
    double phaseVelocity = C / sqrt(ER);
    double distance = sqrt(pow((RX_x - ID_x), 2) + pow((RX_y - ID_y), 2) + pow((RX_z - ID_z), 2));
    double time = distance / phaseVelocity;
    return time;
}

void delayAndSum(
                int intArray[MAX_ROWS][MAX_COLS],
                double frequencies[MAX_ROWS],
                float floatArray[MAX_ROWS][MAX_COLS],
                long double complex **complexArray,
                double imagingDomain[MAX_SIZE][3],
                int imagingDomainSize)
{
    for (int r = 0; r < imagingDomainSize; r++)
    {
        for (int m = 0; m < NUM_OF_CHANNELS; m++)
        {
            for (int f = 0; f < FREQ_MAX; f++)
            {
                double ID_x = imagingDomain[r][0];
                double ID_y = imagingDomain[r][1];
                double ID_z = 0;
                
                long double complex IQData = complexArray[f][m];
                int RXAnt = (intArray[m])[1];
                float RX_x = floatArray[RXAnt][0];
                
                float RX_y = (floatArray[RXAnt])[1];
                float RX_z = (floatArray[RXAnt])[2];

                // printf("Complex Value: %.20Lf + %.20Lfi\n", creall(IQData), cimagl(IQData));

                //printf("%.30e\n", creall(timeDelay(RX_x, RX_y, RX_z, ID_x, ID_y, ID_z)*I*2*3.141592));
                double intensity = creal(IQData * cexp(-1 * I * 2 * M_PI * timeDelay(RX_x, RX_y, RX_z, ID_x, ID_y, ID_z) * frequencies[f]));
                printf("%.lf\n", intensity);
                imagingDomain[r][2] += intensity;
                //printf("%.30e\n", imagingDomain[r][2]);
            }
        }
    }
}