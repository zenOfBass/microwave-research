/*
CSVReader.h
Revised 7/11/2023
Nathan Wiley - nwiley@uco.edu
*/

#include "DelayAndSum.h"

double timeDelay(float RX_x, float RX_y, float RX_z, float ID_x, float ID_y, float ID_z)
{
    return (sqrt(pow((RX_x - ID_x), 2) + pow((RX_y - ID_y), 2) + pow((RX_z - ID_z), 2))) / (C/sqrt(ER));
}

void delayAndSum(int intArray[MAX_ROWS][MAX_COLS],
                double doubleArray[MAX_ROWS],
                float floatArray[MAX_ROWS][MAX_COLS],
                long double complex **complexArray,
                float imagingDomain[MAX_SIZE][3],
                double targetArray[MAX_ROWS][3])
{
    for (int r = 0; r < MAX_SIZE; r++)
    {
        float ID_x = (imagingDomain[r])[0];
        float ID_y = (imagingDomain[r])[1];
        float ID_z = (imagingDomain[r])[2];
        for (int m = 0; m < NUM_OF_CHANNELS; m++)
        {
            for (int f = 0; f < FREQ_MAX; f++)
            {
                long double complex IQData = complexArray[f][m];
                int channel = intArray[m][1];
                double freq = doubleArray[f];
                int RXAnt = (intArray[m])[1];
                float RX_x = (intArray[RXAnt])[0];
                float RX_y = (intArray[RXAnt])[1];
                float RX_z = (intArray[RXAnt])[2];
                targetArray[r][0] = ID_x;
                targetArray[r][1] = ID_y;
                targetArray[r][2] += creal(IQData * exp(I * 2 * M_PI * timeDelay(RX_x, RX_y, RX_z, ID_x, ID_y, ID_z)));
            }
        }
    }
}