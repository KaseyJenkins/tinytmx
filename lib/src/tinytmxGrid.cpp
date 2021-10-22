#include <string>
#include "tinytmxGrid.hpp"
#include "tinyxml2.h"

namespace tinytmx {

    Grid::Grid() :
            grid_orientation(tinytmx::GridOrientation::TMX_GO_ORTHOGONAL),
            width(0), height(0) {}

    void Grid::Parse(tinyxml2::XMLNode const *gridNode) {
        tinyxml2::XMLElement const *gridElement = gridNode->ToElement();

        // Read all the attributes into member variables.
        char const *orientationsCString = gridElement->Attribute("orientation");

        if (std::strcmp(orientationsCString, "isometric") == 0) {
            grid_orientation = tinytmx::GridOrientation::TMX_GO_ISOMETRIC;
        } else if (std::strcmp(orientationsCString, "orthogonal") == 0) {
            grid_orientation = tinytmx::GridOrientation::TMX_GO_ORTHOGONAL; // FIXME: probably redundant at the moment : This element is only used in case of isometric orientation
        }

        width = gridElement->UnsignedAttribute("width");
        height = gridElement->UnsignedAttribute("height");
    }

}