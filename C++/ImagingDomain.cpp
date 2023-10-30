#include "ImagingDomain.hpp"


ImagingDomain::ImagingDomain(float height, float width, float depth, float resolution)
{
    for(float x = -1 * (depth/2.0); x < depth; x+=resolution)
    {
        for(float y = -1 * (width/2.0); y < width; y+=resolution)
        {
            for(float z = -1 * (height/2.0); z < height; z+=resolution)
            {
                domain.push_back(point(x, y, z));
            }
        }
    }
}