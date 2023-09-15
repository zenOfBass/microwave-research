/*
CSVReader.h
Revised 7/5/2023
Colton Cox - ccox60@uco.edu
Nathan G Wiley - nwiley@uco.edu
*/

#include "CallHeatmap.h"

void callHeatmap()
{
    system("gnuplot -p PlotImage.p"); // Run the GNU script
}