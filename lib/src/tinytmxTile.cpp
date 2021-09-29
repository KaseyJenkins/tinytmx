#include "tinyxml2.h"

#include "tinytmxTile.hpp"
#include "tinytmxObject.hpp"

namespace tinytmx {
    Tile::Tile() :
            id(0), probability(0.0f), properties(), isAnimated(false), hasObjects(false), hasObjectGroup(false), objectGroup(nullptr),
            totalDuration(0), image(nullptr), type() {
    }

    Tile::Tile(int id) :
            id(id), probability(0.0f), properties(), isAnimated(false), hasObjects(false), hasObjectGroup(false), objectGroup(nullptr),
            totalDuration(0), image(nullptr), type() {
    }

    Tile::~Tile() {
        if (image) {
            delete image;
            image = nullptr;
        }
        if (objectGroup) {
            delete objectGroup;
            objectGroup = nullptr;
        }
    }

    void Tile::Parse(const tinyxml2::XMLNode *tileNode, const tinytmx::Map *_map) {
        const tinyxml2::XMLElement *tileElem = tileNode->ToElement();

        // Parse the attributes.
        id = tileElem->IntAttribute("id");

        // Parse the terrain attribute.
        if (tileElem->Attribute("terrain")) {
            char *terrainString = strdup(tileElem->Attribute("terrain"));
            char *token = strtok(terrainString, ",");
            while (token) {
                //int val = strtol(token, nullptr, 10);
                terrain.emplace_back(strtol(token, nullptr, 10));
                token = strtok(nullptr, ",");
            }
            free(terrainString);
        }

        // Parse the probability value.
        tileElem->QueryAttribute("probability", &probability);

        // Parse tile type if it has one.
        if (tileElem->FindAttribute("type")) {
            type = std::string(tileElem->Attribute("type"));
        }

        // Parse the properties if any.
        const tinyxml2::XMLNode *propertiesNode = tileNode->FirstChildElement("properties");
        if (propertiesNode) {
            properties.Parse(propertiesNode);
        }

        // Parse the animation if there is one.
        const tinyxml2::XMLNode *animationNode = tileNode->FirstChildElement("animation");
        if (animationNode) {
            isAnimated = true;

            const tinyxml2::XMLNode *frameNode = animationNode->FirstChildElement("frame");
            unsigned int durationSum = 0;
            while (frameNode != nullptr) {
//            for (const tinyxml2::XMLNode *frameNode = animationNode->FirstChildElement("frame");
//                 frameNode != nullptr; frameNode = frameNode->NextSiblingElement("frame")) {

                const tinyxml2::XMLElement *frameElement = frameNode->ToElement();

                const int tileID = frameElement->IntAttribute("tileid");
                const unsigned int duration = frameElement->IntAttribute("duration");

                frames.emplace_back(tileID, duration);
                durationSum += duration;

                frameNode = frameNode->NextSiblingElement("frame");
            }

            totalDuration = durationSum;
        }

        const tinyxml2::XMLNode *objectGroupNode = tileNode->FirstChildElement("objectgroup");
        if (objectGroupNode) {
            hasObjectGroup = true;
            objectGroup = new ObjectGroup(this, _map);
            objectGroup->Parse(objectGroupNode);
            if (objectGroup->GetNumObjects() > 0) { hasObjects = true; }

        }

        const tinyxml2::XMLNode *imageNode = tileNode->FirstChildElement("image");
        if (imageNode) {
            image = new Image();
            image->Parse(imageNode);
        }

    }
}
