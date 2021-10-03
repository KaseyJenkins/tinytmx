#include "tinyxml2.h"
#include "tinytmxWangColor.hpp"

namespace tinytmx {

    WangColor::WangColor() : tileID(0), probability(0), color(), properties(nullptr) {}

    WangColor::~WangColor() {
        if (properties != nullptr) {
            delete properties;
            properties = nullptr;
        }
    }

    void WangColor::Parse(const tinyxml2::XMLElement *wangColorElement) {
        // Parse the attributes.
        name = wangColorElement->Attribute("name");

        // Color
        color = tinytmx::Color(wangColorElement->Attribute("color"));

        tileID = wangColorElement->IntAttribute("tile");
        probability = wangColorElement->FloatAttribute("probability");

        // Parse the properties if any.
        const tinyxml2::XMLElement *propertiesElement = wangColorElement->FirstChildElement("properties");
        if (propertiesElement) {
            properties = new PropertySet();
            properties->Parse(propertiesElement);
        }
    }

}
