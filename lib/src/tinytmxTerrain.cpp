#include "tinyxml2.h"
#include "tinytmxTerrain.hpp"

namespace tinytmx {
    Terrain::Terrain() :
            tileID(), properties(nullptr) {
    }

    Terrain::~Terrain() {
        if (properties != nullptr) {
            delete properties;
            properties = nullptr;
        }
    }


    void Terrain::Parse(tinyxml2::XMLNode const *terrainNode) {
        tinyxml2::XMLElement const *terrainElem = terrainNode->ToElement();

        // Parse the attributes.
        name = std::string(terrainElem->Attribute("name"));

        tileID = terrainElem->IntAttribute("tile");

        // Parse the properties if any.
        tinyxml2::XMLNode const *propertiesNode = terrainNode->FirstChildElement("properties");
        if (propertiesNode) {
            properties = new PropertySet();
            properties->Parse(propertiesNode);
        }
    }

}
