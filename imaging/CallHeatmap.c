/*
CSVReader.h
Revised 2023-07-05
Colton Cox - ccox60@uco.edu
Nathan G Wiley - nwiley@uco.edu
*/

#include "CallHeatmap.h"

void callHeatmap()
{
    system("gnuplot -p PlotImage.p"); // Run the GNU script
}