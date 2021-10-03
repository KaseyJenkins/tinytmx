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


    void Terrain::Parse(const tinyxml2::XMLNode *terrainNode) {
        const tinyxml2::XMLElement *terrainElem = terrainNode->ToElement();

        // Parse the attributes.
        name = std::string(terrainElem->Attribute("name"));

        tileID = terrainElem->IntAttribute("tile");

        // Parse the properties if any.
        const tinyxml2::XMLNode *propertiesNode = terrainNode->FirstChildElement("properties");
        if (propertiesNode) {
            properties = new PropertySet();
            properties->Parse(propertiesNode);
        }
    }

}
