#include "tinyxml2.h"

#include "tinytmxLayer.hpp"
#include "tinytmxObjectGroup.hpp"
#include "tinytmxObject.hpp"

namespace tinytmx {
    ObjectGroup::ObjectGroup(const tinytmx::Map *_map)
            : Layer(_map, std::string(), 0, 0, 0, 0, 1.0f, true, LayerType::TMX_LAYERTYPE_OBJECTGROUP),
              draw_order(tinytmx::DrawOrder::TMX_DRAWORDER_TOPDOWN),
              color("#a0a0a4") {}

    ObjectGroup::ObjectGroup(const tinytmx::Tile *_tile, const tinytmx::Map *_map)
            : Layer(_tile, _map, std::string(), 0, 0, 0, 0, 1.0f, true, LayerType::TMX_LAYERTYPE_OBJECTGROUP),
              draw_order(tinytmx::DrawOrder::TMX_DRAWORDER_TOPDOWN),
              color("#a0a0a4") {}

    ObjectGroup::~ObjectGroup() {
        for (auto obj: objects) {
            delete obj;
            obj = nullptr;
        }
    }

    void ObjectGroup::Parse(const tinyxml2::XMLNode *objectGroupNode) {
        const tinyxml2::XMLElement *objectGroupElem = objectGroupNode->ToElement();

        // Read the object group attributes, set to unknown if not defined in XML
        //objectGroupElem->Attribute("name") != nullptr ? name = objectGroupElem->Attribute("name") : name = "unknown";
        ID = objectGroupElem->UnsignedAttribute("id");

        if (objectGroupElem->Attribute("name")) {
            name = objectGroupElem->Attribute("name");
        }

        objectGroupElem->QueryFloatAttribute("offsetx", &offsetX);
        objectGroupElem->QueryFloatAttribute("offsety", &offsetY);

        if (objectGroupElem->Attribute("color")) {
            color = tinytmx::Color(objectGroupElem->Attribute("color"));
        }

        objectGroupElem->QueryFloatAttribute("opacity", &opacity);
        objectGroupElem->QueryBoolAttribute("visible", &visible);

        if (objectGroupElem->Attribute("tintcolor")) {
            tint_color = tinytmx::Color(objectGroupElem->Attribute("tintcolor"));
        }

        if (objectGroupElem->Attribute("draworder")) {
            const char* draworderAsCString = objectGroupElem->Attribute("draworder");

            if (std::strcmp(draworderAsCString, "index") == 0) {
                draw_order = tinytmx::DrawOrder::TMX_DRAWORDER_INDEX;
            } else if (std::strcmp(draworderAsCString, "topdown") == 0) {
                draw_order = tinytmx::DrawOrder::TMX_DRAWORDER_TOPDOWN;
            }
        }

        // Read the properties.
        const tinyxml2::XMLNode *propertiesNode = objectGroupNode->FirstChildElement("properties");
        if (propertiesNode) {
            properties = new PropertySet();
            properties->Parse(propertiesNode);
        }

        // Iterate through all of the object elements.
        const tinyxml2::XMLNode *objectNode = objectGroupNode->FirstChildElement("object");
        while (objectNode) {
            // Allocate a new object and parse it.
            auto object = new Object();
            object->Parse(objectNode, map);

            // Add the object to the list.
            objects.push_back(object);

            objectNode = objectNode->NextSiblingElement("object");
        }
    }

}
