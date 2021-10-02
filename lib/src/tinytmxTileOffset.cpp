#include "tinyxml2.h"
#include "tinytmxTileOffset.hpp"

namespace tinytmx {
    TileOffset::TileOffset()
            : x(0), y(0) {}


    void TileOffset::Parse(const tinyxml2::XMLNode *tileOffsetNode) {
        const tinyxml2::XMLElement *tileOffsetElem = tileOffsetNode->ToElement();

        // Read all the attributes into member variables.
        x = tileOffsetElem->IntAttribute("x");
        y = tileOffsetElem->IntAttribute("y");
    }
}
