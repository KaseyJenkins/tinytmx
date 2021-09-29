#include <string>
#include "tinytmxGrid.hpp"
#include "tinyxml2.h"

namespace tinytmx {

    Grid::Grid() :
            grid_orientation(tinytmx::GridOrientation::TMX_GO_ORTHOGONAL),
            width(0), height(0) {}

    void Grid::Parse(const tinyxml2::XMLNode *gridNode) {
        const tinyxml2::XMLElement *gridElement = gridNode->ToElement();

        // Read all the attributes into member variables.
        std::string orientationStr = gridElement->Attribute("orientation");
        if (orientationStr == "isometric") {
            grid_orientation = tinytmx::GridOrientation::TMX_GO_ISOMETRIC;
        } else if (orientationStr == "orthogonal") {
            grid_orientation = tinytmx::GridOrientation::TMX_GO_ORTHOGONAL; // FIXME: probably redundant at the moment : This element is only used in case of isometric orientation
        }

        width = gridElement->UnsignedAttribute("width");
        height = gridElement->UnsignedAttribute("height");
    }

}