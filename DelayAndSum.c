/*
CSVReader.h
Revised 7/11/2023
Nathan Wiley - nwiley@uco.edu
*/

#include "DelayAndSum.h"

float calculateDistance(float RXAntennaPoint[3], float TXAntennaPoint[3], double imagingDomainPoint[3])
{
    // Calculates total euclidean distance between 3 points (RX antenna -> Imaging Domain Point -> Tx antenna)
    // NOTE: Imaging domain point Z is constant Z_HEIGHT defined in CONFIGURATION_H

    // RX Antenna Point
    float Rx = RXAntennaPoint[0];
    float Ry = RXAntennaPoint[1];
    float Rz = RXAntennaPoint[2];

    // TX Antenna Point
    float Tx = TXAntennaPoint[0];
    float Ty = TXAntennaPoint[1];
    float Tz = TXAntennaPoint[2];

    // Imaging Domain Point
    double Ix = imagingDomainPoint[0];
    double Iy = imagingDomainPoint[1];
    double Iz = 0;

    //           Distance from RX -> Imaging Domain Point      +       Distance from TX -> Imaging Domain Point         
    return sqrt(pow(Rx-Ix, 2) + pow(Ry-Iy, 2) + pow(Rz-Iz, 2)) + sqrt(pow(Tx-Ix, 2) + pow(Ty-Iy, 2) + pow(Tz-Iz, 2));
}

double timeDelay(float distance)
{
    // Calculates the time for a signal with phase velocity = C/Relative Permittivity to travel given distance
    double phaseVelocity = C / sqrt(ER);
    return distance / phaseVelocity;
}

void delayAndSum(
                int channels[MAX_ROWS][MAX_COLS],
                double frequencies[MAX_ROWS],
                float antennaLocations[MAX_ROWS][MAX_COLS],
                long double complex** signalData,
                double imagingDomain[MAX_SIZE][3],
                int imagingDomainSize)
{

    FILE *fptr;
    fptr = fopen("DAS_data.csv", "w+");
     for (int r = 0; r < imagingDomainSize; r++)
    {
        //printf("point: %d = %lf\n", r, imagingDomain[r][2]);
        for (int m = 0; m < NUM_OF_CHANNELS; m++)
        {
            for (int f = 0; f < FREQ_MAX; f++)
            {
                long double complex IQData = signalData[f][m];
                int RxAntennaNumber = channels[m][1];
                int TXAntennaNumber = channels[m][0];

                float distance = calculateDistance(antennaLocations[RxAntennaNumber], antennaLocations[TXAntennaNumber], imagingDomain[r]);
                double time = timeDelay(distance);
                double intensity = creal(IQData * cexp(-1 * I * 2 * M_PI * time * frequencies[f]));
                imagingDomain[r][2] += intensity;
                //printf("%.10e\n", intensity);
                //printf("%.20Lf + %.20Lfi\n", creall(signalData[f][m]), cimagl(signalData[f][m]));
                
            }
        }
        //fprintf(fptr, "\n");
    }
}