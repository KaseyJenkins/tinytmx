#include "tinyxml2.h"

#include "tinytmxImage.hpp"

namespace tinytmx
{   
    Image::Image() 
        : width(0)
        , height(0)
        , transparent_color()
    {}


    void Image::Parse(const tinyxml2::XMLNode *imageNode) 
    {
        const tinyxml2::XMLElement* imageElem = imageNode->ToElement();
        
        // Read all the attribute into member variables.
        source = imageElem->Attribute("source");

        width = imageElem->UnsignedAttribute("width");
        height = imageElem->UnsignedAttribute("height");

        const char *trans = imageElem->Attribute("trans");
        if (trans) 
        {
            transparent_color = tinytmx::Color(trans);
        }
    }
}
