#include "tinyxml2.h"
#include "tinytmxWangColor.hpp"

namespace tinytmx {

    WangColor::WangColor() : color(nullptr), tileID(0), probability(0) {

    }

    WangColor::~WangColor() {
        if (color) {
            delete color;
            color = nullptr;
        }
    }

    void WangColor::Parse(const tinyxml2::XMLElement *wangColorElement) {
        // Parse the attributes.
        name = wangColorElement->Attribute("name");

        // Color
        color = new Color(wangColorElement->Attribute("color"));

        tileID = wangColorElement->IntAttribute("tile");
        probability = wangColorElement->FloatAttribute("probability");

        // Parse the properties if any.
        const tinyxml2::XMLElement *propertiesElement = wangColorElement->FirstChildElement("properties");
        if (propertiesElement) {
            properties.Parse(propertiesElement);
        }
    }
}
