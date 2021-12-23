#include <string_view>
#include "tinytmxGrid.hpp"
#include "tinyxml2.h"

namespace tinytmx {

    Grid::Grid(tinyxml2::XMLNode const *gridNode) :
            grid_orientation(tinytmx::GridOrientation::TMX_GO_ORTHOGONAL),
            width(0), height(0) {
        Parse(gridNode);
    }

    void Grid::Parse(tinyxml2::XMLNode const *gridNode) {
        tinyxml2::XMLElement const *gridElement = gridNode->ToElement();

        // Read all the attributes into member variables.
        std::string_view orientationsCString = gridElement->Attribute("orientation");

        if (orientationsCString == "isometric") {
            grid_orientation = tinytmx::GridOrientation::TMX_GO_ISOMETRIC;
        } else if (orientationsCString == "orthogonal") {
            grid_orientation = tinytmx::GridOrientation::TMX_GO_ORTHOGONAL; // FIXME: probably redundant at the moment : This element is only used in case of isometric orientation
        }

        width = gridElement->UnsignedAttribute("width");
        height = gridElement->UnsignedAttribute("height");
    }

}