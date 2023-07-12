/*
CSVReader.h
Revised 7/12/2023
Nathan Wiley - nwiley@uco.edu
*/

#include "DelayAndSum.h"

double timeDelay(float RX_x, float RX_y, float RX_z, double ID_x, double ID_y, double ID_z)
{
    double numerator = (sqrt(pow(((double)(RX_x - ID_x)), 2) + pow(((double)(RX_y - ID_y)), 2) + pow(((double)(RX_z - ID_z)), 2)));
    double denominator = (C / sqrt(ER));
    return numerator / denominator;
}

void delayAndSum(int intArray[MAX_ROWS][MAX_COLS],
                double doubleArray[MAX_ROWS],
                float floatArray[MAX_ROWS][MAX_COLS],
                long double complex **complexArray,
                double imagingDomain[MAX_SIZE][3])
{
    for (int r = 0; r < MAX_SIZE; r++)
    {
        double ID_x = imagingDomain[r][0];
        double ID_y = imagingDomain[r][1];
        double ID_z = 0;
        for (int m = 0; m < NUM_OF_CHANNELS; m++)
        {
            for (int f = 0; f < FREQ_MAX; f++)
            {
                long double complex IQData = complexArray[f][m];
                int channel = intArray[m][1];
                double freq = doubleArray[f];
                int RXAnt = (intArray[m])[1];
                float RX_x = (floatArray[RXAnt])[0];
                float RX_y = (floatArray[RXAnt])[1];
                float RX_z = (floatArray[RXAnt])[2];
                // printf("%f\n", RX_x);
                // printf("%f\n", RX_y);
                // printf("%f\n", RX_z);
                // imagingDomain[r][2] += creal(IQData * exp(I * 2 * M_PI * timeDelay(RX_x, RX_y, RX_z, ID_x, ID_y, ID_z)));
                printf("%lf\n", timeDelay(RX_x, RX_y, RX_z, ID_x, ID_y, ID_z));
                // printf("%lf\n", (C / sqrt(ER)));
            }
        }
    }
}