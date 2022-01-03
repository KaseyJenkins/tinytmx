#include "tinyxml2.h"
#include "tinytmxWangColor.hpp"

namespace tinytmx {

    WangColor::WangColor(tinyxml2::XMLElement const *wangColorElement) : tileID(0), probability(0), color(), properties(nullptr) {
        Parse(wangColorElement);
    }

    WangColor::~WangColor() {
        delete properties;
    }

    void WangColor::Parse(tinyxml2::XMLElement const *wangColorElement) {
        // Parse the attributes.
        name = wangColorElement->Attribute("name");

        // Color
        color = tinytmx::Color(wangColorElement->Attribute("color"));

        tileID = wangColorElement->IntAttribute("tile");
        probability = wangColorElement->FloatAttribute("probability");

        // Parse the properties if any.
        tinyxml2::XMLElement const *propertiesElement = wangColorElement->FirstChildElement("properties");
        if (propertiesElement) {
            properties = new PropertySet(propertiesElement);
        }
    }

}
