/*
CSVReader.h
Revised 7/5/2023
Nathan Wiley - nwiley@uco.edu
*/

#include "CallHeatmap.h"

void callHeatmap()
{
    system("gnuplot -p PlotImage.p"); // Run the GNU script using the system() function
}