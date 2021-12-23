#include "tinyxml2.h"
#include <cassert> //RJCB
#include <cstring>
#include <string>

#include "tinytmxLayer.hpp"
#include "tinytmxGroupLayer.hpp"
#include "tinytmxTileLayer.hpp"
#include "tinytmxObjectGroup.hpp"
#include "tinytmxImageLayer.hpp"

namespace tinytmx {

    GroupLayer::GroupLayer(tinytmx::Map const *_map)
            : Layer(_map, std::string(), 0, 0, 0, 0, 1.0f, true, LayerType::TMX_LAYERTYPE_GROUP_LAYER) {
    }

    GroupLayer::~GroupLayer() {
        for (auto c : children) {
            delete c;
            c = nullptr;
        }
    }

    void GroupLayer::Parse(tinyxml2::XMLNode const *groupLayerNode) {
        tinyxml2::XMLElement const *groupLayerElem = groupLayerNode->ToElement();

        // Read all the attributes into local variables.
        ID = groupLayerElem->UnsignedAttribute("id");
        name = groupLayerElem->Attribute("name");

        groupLayerElem->QueryIntAttribute("x", &x);
        groupLayerElem->QueryIntAttribute("y", &y);

        groupLayerElem->QueryFloatAttribute("offsetx", &offsetX);
        groupLayerElem->QueryFloatAttribute("offsety", &offsetY);

        groupLayerElem->QueryFloatAttribute("opacity", &opacity);
        groupLayerElem->QueryBoolAttribute("visible", &visible);

        if (groupLayerElem->Attribute("tintcolor")) {
            tint_color = tinytmx::Color(groupLayerElem->Attribute("tintcolor"));
        }

        // Parse the group.
        tinyxml2::XMLNode const *child = groupLayerElem->FirstChild();
        assert(child); //RJCB

        while (child != nullptr) {
            if (std::strcmp(child->Value(), "group") == 0) {
                auto groupLayer = new GroupLayer(map);
                groupLayer->Parse(child);
                AddChild(groupLayer);
            } else if (std::strcmp(child->Value(), "layer") == 0) {
                auto tileLayer = new TileLayer(map);
                tileLayer->Parse(child);
                AddChild(tileLayer);
            } else if (std::strcmp(child->Value(), "objectgroup") == 0) {
                auto objectGroup = new ObjectGroup(map);
                objectGroup->Parse(child);
                AddChild(objectGroup);
            } else if (std::strcmp(child->Value(), "imagelayer") == 0) {
                auto imageLayer = new ImageLayer(map);
                imageLayer->Parse(child);
                AddChild(imageLayer);
            }
            child = child->NextSiblingElement();
        }

        // Parse the properties if any.
        tinyxml2::XMLNode const *propertiesNode = groupLayerElem->FirstChildElement("properties");
        if (propertiesNode) {
            properties = new PropertySet(propertiesNode);
        }
    }

    void GroupLayer::AddChild(tinytmx::Layer *childLayer) {
        children.push_back(childLayer);
    }

    tinytmx::Layer const *GroupLayer::GetChild(int const index) const {
        return children.at(index);
    }

    std::vector<tinytmx::Layer *> const &GroupLayer::GetChildren() const noexcept {
        return children;
    }

    auto GroupLayer::GetNumChildren() const noexcept {
        return children.size();
    }

}
