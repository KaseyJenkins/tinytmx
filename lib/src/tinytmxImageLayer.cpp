#include "tinyxml2.h"

#include "tinytmxLayer.hpp"
#include "tinytmxImageLayer.hpp"
#include "tinytmxImage.hpp"

using std::vector;
using std::string;

namespace tinytmx {
    ImageLayer::ImageLayer(const tinytmx::Map *_map)
            : Layer(_map, std::string(), 0, 0, 0, 0, 1.0f, true, LayerType::TMX_LAYERTYPE_IMAGE_LAYER),
              image(nullptr) {
    }

    ImageLayer::~ImageLayer() {
        delete image;
        image = nullptr;
    }

    void ImageLayer::Parse(const tinyxml2::XMLNode *imageLayerNode) {
        const tinyxml2::XMLElement *imageLayerElem = imageLayerNode->ToElement();

        // Read all the attributes into local variables.
        ID = imageLayerElem->UnsignedAttribute("id");
        name = imageLayerElem->Attribute("name");

        imageLayerElem->QueryFloatAttribute("offsetx", &offsetX);
        imageLayerElem->QueryFloatAttribute("offsety", &offsetY);

        imageLayerElem->QueryIntAttribute("x", &x); // Deprecated since 0.15.
        imageLayerElem->QueryIntAttribute("y", &y); // Deprecated since 0.15.

        imageLayerElem->QueryFloatAttribute("opacity", &opacity);
        imageLayerElem->QueryBoolAttribute("visible", &visible);

        if (imageLayerElem->Attribute("tintcolor")) {
            tint_color = tinytmx::Color(imageLayerElem->Attribute("tintcolor"));
        }

        // Parse the image if there is one.
        const tinyxml2::XMLNode *imageNode = imageLayerElem->FirstChildElement("image");
        if (imageNode) {
            image = new Image();
            image->Parse(imageNode);
        }

        // Parse the properties if any.
        const tinyxml2::XMLNode *propertiesNode = imageLayerElem->FirstChildElement("properties");
        if (propertiesNode) {
            properties = new PropertySet();
            properties->Parse(propertiesNode);
        }
    }

}
