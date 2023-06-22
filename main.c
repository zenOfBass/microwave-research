#include "ImagingDomain.h"
#include "csvreader.h"

float ID[MAX_SIZE][3];

int main()
{

    GenerateImagingDomain(ID);

    // print first 20 for testing
    for (int i=0;i<20;i++)
    {
       printf("%f\n", ID[i][0]);
    }
    return 0;
}