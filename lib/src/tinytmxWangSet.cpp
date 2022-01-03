#include "tinyxml2.h"
#include "tinytmxWangSet.hpp"
#include "tinytmxWangTile.hpp"
#include "tinytmxWangColor.hpp"

namespace tinytmx {

    WangSet::WangSet(tinyxml2::XMLNode const *wangsetNode): tileID(0), properties(nullptr) {
        Parse(wangsetNode);
    }

    WangSet::~WangSet() {

        delete properties;

        for (auto &wangtile : wangtiles) {
            delete wangtile;
        }

        for (auto &wangcolor : wangcolors) {
            delete wangcolor;
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

            auto wangColor = new WangColor(wangColorElement);
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