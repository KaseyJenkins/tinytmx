#include "tinyxml2.h"
#include "tinytmxWangSet.hpp"
#include "tinytmxWangTile.hpp"
#include "tinytmxWangColor.hpp"

namespace tinytmx {

    WangSet::WangSet(): tileID(0), //wangSetType(WangSetType::TMX_WST_CORNER),
    properties(nullptr) {}

    WangSet::~WangSet() {

        // Delete properties
        if (properties != nullptr) {
            delete properties;
            properties = nullptr;
        }

        // Iterate through all of the wangtiles in the wangtiles vector and delete each of them.
        for (auto wangtile : wangtiles) {
            delete wangtile;
            wangtile = nullptr;
        }

        // Iterate through all of the colors in the wangcolors vector and delete each of them.
        for (auto wangcolor : wangcolors) {
            delete wangcolor;
            wangcolor = nullptr;
        }

    }

    void WangSet::Parse(const tinyxml2::XMLNode *wangsetNode) {
        const tinyxml2::XMLElement *wangsetElem = wangsetNode->ToElement();

        // Parse the attributes.
        name = wangsetElem->Attribute("name");
        tileID = wangsetElem->IntAttribute("tile");

//        // Read the type.
//        std::string typeStr = wangsetElem->Attribute("type");
//        if (typeStr == "corner") {
//            wangSetType = WangSetType::TMX_WST_CORNER;
//        } else if (typeStr == "edge") {
//            wangSetType = WangSetType::TMX_WST_EDGE;
//        } else if (typeStr == "mixed") {
//            wangSetType = WangSetType::TMX_WST_MIXED;
//        }

        // Iterate through all of the wangcolor elements and parse them.
        const tinyxml2::XMLElement *wangColorElement = wangsetNode->FirstChildElement("wangcolor");
        while (wangColorElement) {

            auto wangColor = new WangColor();
            wangColor->Parse(wangColorElement);
            wangcolors.push_back(wangColor);

            wangColorElement = wangColorElement->NextSiblingElement("wangcolor");
        }
        // Iterate through all of the wangtile elements and parse each.
        const tinyxml2::XMLElement *wangTileElement = wangsetNode->FirstChildElement("wangtile");
        while(wangTileElement) {

            auto wangTile = new WangTile();
            wangTile->Parse(wangTileElement);
            wangtiles.push_back(wangTile);

            wangTileElement = wangTileElement->NextSiblingElement("wangtile");
        }

        // Parse the properties if any.
        const tinyxml2::XMLNode *propertiesNode = wangsetNode->FirstChildElement("properties");
        if (propertiesNode) {
            properties = new PropertySet();
            properties->Parse(propertiesNode);
        }

    }

}