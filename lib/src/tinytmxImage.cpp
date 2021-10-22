#include "tinyxml2.h"

#include "tinytmxImage.hpp"

namespace tinytmx
{   
    Image::Image() 
        : width(0)
        , height(0)
        , transparent_color()
    {}


    void Image::Parse(tinyxml2::XMLNode const *imageNode)
    {
        tinyxml2::XMLElement const *imageElem = imageNode->ToElement();
        
        // Read all the attribute into member variables.
        source = imageElem->Attribute("source");

        width = imageElem->UnsignedAttribute("width");
        height = imageElem->UnsignedAttribute("height");

        char const *trans = imageElem->Attribute("trans");
        if (trans) 
        {
            transparent_color = tinytmx::Color(trans);
        }
    }
}
