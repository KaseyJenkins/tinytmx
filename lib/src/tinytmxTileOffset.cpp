#include "tinyxml2.h"
#include "tinytmxTileOffset.hpp"

namespace tinytmx {
    TileOffset::TileOffset(tinyxml2::XMLNode const *tileOffsetNode)
            : x(0), y(0) {
        Parse(tileOffsetNode);
    }


    void TileOffset::Parse(tinyxml2::XMLNode const *tileOffsetNode) {
        tinyxml2::XMLElement const *tileOffsetElem = tileOffsetNode->ToElement();

        // Read all the attributes into member variables.
        x = tileOffsetElem->IntAttribute("x");
        y = tileOffsetElem->IntAttribute("y");
    }
}
