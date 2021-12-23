#include "tinyxml2.h"
#include "tinytmxTransformations.hpp"

namespace tinytmx {
    Transformations::Transformations(tinyxml2::XMLNode const *transformationsNode) :
            hflip(false), vflip(false), rotate(false), preferuntransformed(false) {
        Parse(transformationsNode);
    }

    void Transformations::Parse(tinyxml2::XMLNode const *transformationsNode) {
        tinyxml2::XMLElement const *transformationsElement = transformationsNode->ToElement();

        // Read all the attributes into member variables.
        hflip = transformationsElement->BoolAttribute("hflip");
        vflip = transformationsElement->BoolAttribute("vflip");
        rotate = transformationsElement->BoolAttribute("rotate");
        preferuntransformed = transformationsElement->BoolAttribute("preferuntransformed");

    }

}

