#include "ImagingDomain.hpp"

ImagingDomain::ImagingDomain(){}

ImagingDomain::ImagingDomain(float height, float width, float depth, float resolution)
{
    if (height <= 0 || width <= 0 || depth <= 0 || resolution <= 0)
    {
        
        throw ImagingDomainParameterError();
    }
    
    for(float x = -1 * (depth/2.0); x < depth; x+=resolution)
    {
        for(float y = -1 * (width/2.0); y < width; y+=resolution)
        {
            for(float z = -1 * (height/2.0); z < height; z+=resolution)
            {
                points.push_back(point(x, y, z));
            }
        }
    }
}