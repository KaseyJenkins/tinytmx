#include "tinyxml2.h"

#include "tinytmxTile.hpp"
#include "tinytmxObject.hpp"

namespace tinytmx {
    Tile::Tile() :
            isAnimated(false),
            hasObjects(false),
            hasObjectGroup(false),
            id(0),
            totalDuration(0),
            probability(0.0f),
            objectGroup(nullptr),
            image(nullptr),
            properties(nullptr) {}

    Tile::Tile(int id) :
            isAnimated(false),
            hasObjects(false),
            hasObjectGroup(false),
            id(id),
            totalDuration(0),
            probability(0.0f),
            objectGroup(nullptr),
            image(nullptr),
            properties(nullptr) {}

    Tile::~Tile() {
        if (properties != nullptr) {
            delete properties;
            properties = nullptr;
        }
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
        if (objectGroup != nullptr) {
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
            properties = new PropertySet();
            properties->Parse(propertiesNode);
        }

        // Parse the animation if there is one.
        const tinyxml2::XMLNode *animationNode = tileNode->FirstChildElement("animation");
        if (animationNode) {
            isAnimated = true;

            const tinyxml2::XMLNode *frameNode = animationNode->FirstChildElement("frame");
            unsigned int durationSum = 0;
            while (frameNode != nullptr) {

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
