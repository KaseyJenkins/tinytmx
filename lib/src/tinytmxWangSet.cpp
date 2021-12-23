#include "tinyxml2.h"
#include "tinytmxWangSet.hpp"
#include "tinytmxWangTile.hpp"
#include "tinytmxWangColor.hpp"

namespace tinytmx {

    WangSet::WangSet(): tileID(0), properties(nullptr) {}

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

    void WangSet::Parse(tinyxml2::XMLNode const *wangsetNode) {
        tinyxml2::XMLElement const *wangsetElem = wangsetNode->ToElement();

        // Parse the attributes.
        name = wangsetElem->Attribute("name");
        tileID = wangsetElem->IntAttribute("tile");

        // Iterate through all of the wangcolor elements and parse them.
        tinyxml2::XMLElement const *wangColorElement = wangsetNode->FirstChildElement("wangcolor");
        while (wangColorElement) {

            auto wangColor = new WangColor();
            wangColor->Parse(wangColorElement);
            wangcolors.push_back(wangColor);

            wangColorElement = wangColorElement->NextSiblingElement("wangcolor");
        }
        // Iterate through all of the wangtile elements and parse each.
        tinyxml2::XMLElement const *wangTileElement = wangsetNode->FirstChildElement("wangtile");
        while(wangTileElement) {

            auto wangTile = new WangTile();
            wangTile->Parse(wangTileElement);
            wangtiles.push_back(wangTile);

            wangTileElement = wangTileElement->NextSiblingElement("wangtile");
        }

        // Parse the properties if any.
        tinyxml2::XMLNode const *propertiesNode = wangsetNode->FirstChildElement("properties");
        if (propertiesNode) {
            properties = new PropertySet(propertiesNode);
        }

    }

}