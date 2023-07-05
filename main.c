#include "ImagingDomain.h"
#include "CSVReader.h"
#include "CallHeatmap.h"

float ID[MAX_SIZE][3];

int main()
{

    generateImagingDomain(ID);

    // print first 20 for testing
    for (int i=0;i<20;i++)
    {
       printf("%f\n", ID[i][0]);
    }

    callHeatmap();

    return 0;
}