#include "tinyxml2.h"
#include "tinytmxTransformations.hpp"

namespace tinytmx {
    Transformations::Transformations() :
            hflip(false), vflip(false), rotate(false), preferuntransformed(false) {}

    void Transformations::Parse(const tinyxml2::XMLNode *transformationsNode) {
        const tinyxml2::XMLElement *transformationsElement = transformationsNode->ToElement();

        // Read all the attributes into member variables.
        hflip = transformationsElement->BoolAttribute("hflip");
        vflip = transformationsElement->BoolAttribute("vflip");
        rotate = transformationsElement->BoolAttribute("rotate");
        preferuntransformed = transformationsElement->BoolAttribute("preferuntransformed");

    }

}

