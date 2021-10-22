#include "tinyxml2.h"

#include "tinytmxTerrainArray.hpp"
#include "tinytmxTerrain.hpp"


namespace tinytmx {

    void TerrainArray::Parse(std::vector<tinytmx::Terrain *> *terrainTypes, tinyxml2::XMLNode const *terrainArrayNode) {
        // Iterate through all of the terrain nodes.
        tinyxml2::XMLNode const *terrainNode = terrainArrayNode->FirstChildElement("terrain");

        while (terrainNode) {
            // Read the attributes of the terrain and add it the terrainTypes vector.
            auto terrainType = new Terrain();
            terrainType->Parse(terrainNode);
            terrainTypes->push_back(terrainType);

            terrainNode = terrainNode->NextSiblingElement("terrain");
        }
    }
}
