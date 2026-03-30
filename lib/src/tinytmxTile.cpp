#include "tinyxml2.h"

#include <charconv>
#include <string_view>

#include "tinytmxTile.hpp"
#include "tinytmxObject.hpp"

namespace tinytmx {
    namespace {
        void ParseCommaSeparatedInts(std::string_view text, std::vector<int> &out) {
            while (!text.empty()) {
                auto const commaPos = text.find(',');
                std::string_view token = (commaPos == std::string_view::npos) ? text : text.substr(0, commaPos);

                // Trim leading/trailing spaces.
                while (!token.empty() && token.front() == ' ') {
                    token.remove_prefix(1);
                }
                while (!token.empty() && token.back() == ' ') {
                    token.remove_suffix(1);
                }

                if (!token.empty()) {
                    int value = 0;
                    auto const result = std::from_chars(token.data(), token.data() + token.size(), value);
                    if (result.ec == std::errc{}) {
                        out.emplace_back(value);
                    }
                }

                if (commaPos == std::string_view::npos) {
                    break;
                }
                text.remove_prefix(commaPos + 1);
            }
        }
    }
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

    void Tile::Parse(tinyxml2::XMLNode const *tileNode, tinytmx::Map const *_map) {
        tinyxml2::XMLElement const *tileElem = tileNode->ToElement();

        // Parse the attributes.
        id = tileElem->IntAttribute("id");

        // Parse the terrain attribute.
        if (tileElem->Attribute("terrain")) {
            ParseCommaSeparatedInts(tileElem->Attribute("terrain"), terrain);
        }

        // Parse the probability value.
        tileElem->QueryAttribute("probability", &probability);

        // Parse tile type if it has one.
        if (tileElem->FindAttribute("type")) {
            type = std::string(tileElem->Attribute("type"));
        }

        // Parse the properties if any.
        tinyxml2::XMLNode const *propertiesNode = tileNode->FirstChildElement("properties");
        if (propertiesNode) {
            properties = new PropertySet(propertiesNode);
        }

        // Parse the animation if there is one.
        tinyxml2::XMLNode const *animationNode = tileNode->FirstChildElement("animation");
        if (animationNode) {
            isAnimated = true;

            tinyxml2::XMLNode const *frameNode = animationNode->FirstChildElement("frame");
            unsigned int durationSum = 0;
            while (frameNode != nullptr) {

                tinyxml2::XMLElement const *frameElement = frameNode->ToElement();

                int const          tileID   = frameElement->IntAttribute("tileid");
                unsigned int const duration = frameElement->UnsignedAttribute("duration");

                frames.emplace_back(tileID, duration);
                durationSum += duration;

                frameNode = frameNode->NextSiblingElement("frame");
            }

            totalDuration = durationSum;
        }

        tinyxml2::XMLNode const *objectGroupNode = tileNode->FirstChildElement("objectgroup");
        if (objectGroupNode) {
            hasObjectGroup = true;
            objectGroup = new ObjectGroup(this, _map);
            objectGroup->Parse(objectGroupNode);
            if (objectGroup->GetNumObjects() > 0) { hasObjects = true; }

        }

        tinyxml2::XMLNode const *imageNode = tileNode->FirstChildElement("image");
        if (imageNode) {
            image = new Image(imageNode);
        }

    }
}
