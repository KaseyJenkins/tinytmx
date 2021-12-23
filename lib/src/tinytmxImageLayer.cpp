#include <string>
#include "tinyxml2.h"

#include "tinytmxLayer.hpp"
#include "tinytmxImageLayer.hpp"
#include "tinytmxImage.hpp"


namespace tinytmx {
    ImageLayer::ImageLayer(tinytmx::Map const *_map)
            : Layer(_map, std::string(), 0, 0, 0, 0, 1.0f, true, LayerType::TMX_LAYERTYPE_IMAGE_LAYER),
              image(nullptr) {
    }

    ImageLayer::~ImageLayer() {
        delete image;
        image = nullptr;
    }

    void ImageLayer::Parse(tinyxml2::XMLNode const *imageLayerNode) {
        tinyxml2::XMLElement const *imageLayerElem = imageLayerNode->ToElement();

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
        tinyxml2::XMLNode const *imageNode = imageLayerElem->FirstChildElement("image");
        if (imageNode) {
            image = new Image(imageNode);
        }

        // Parse the properties if any.
        tinyxml2::XMLNode const *propertiesNode = imageLayerElem->FirstChildElement("properties");
        if (propertiesNode) {
            properties = new PropertySet(propertiesNode);
        }
    }

}
