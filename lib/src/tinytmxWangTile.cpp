#include "tinyxml2.h"
#include <cstdlib>
#include "tinytmxWangTile.hpp"

namespace tinytmx {

    WangTile::WangTile() : tileID(0) {

    }

    void WangTile::Parse(const tinyxml2::XMLElement *wangTileElement) {
        // Parse the attributes.
        tileID = wangTileElement->UnsignedAttribute("tileid");

        // FIXME put into a function?
        // Parse the wangid attribute.
        char *wangidString = strdup(wangTileElement->Attribute("wangid"));
        char *token = strtok(wangidString, ",");
        while (token) {
            wangID.emplace_back(strtol(token, nullptr, 10));
            token = strtok(nullptr, ",");
        }
        free(wangidString);
    }
}
