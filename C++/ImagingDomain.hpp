#ifndef IMAGING_DOMAIN_H
#define IMAGING_DOMAIN_H

#include <vector>
#include "Util.h"

using namespace std;

struct point 
{
    float x, y, z; 
    double intensity;
    point(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->intensity = 0.0;
    }
    
};

class ImagingDomain
{
private:

    float height, width, depth;    // dimensions in meters
    float resolution;              // spacing between points in meters

public:

    vector<point> points;

    ImagingDomain();
    ImagingDomain(float, float, float, float);
    float getHeight(){return this->height;}
    float getWidth(){return this->width;}
    float getDepth(){return this->depth;}
    float getResolution(){return this->resolution;}


};



#endif