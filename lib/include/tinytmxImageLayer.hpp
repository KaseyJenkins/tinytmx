#ifndef TINYTMX_TINYTMXIMAGELAYER_HPP
#define TINYTMX_TINYTMXIMAGELAYER_HPP


#include <string>
#include <vector>

#include "tinytmxLayer.hpp"
#include "tinytmxPropertySet.hpp"

namespace tinytmx
{
    class Map;
    class Image;

    //-------------------------------------------------------------------------
    /// A class used for holding information about a background image.
    /// This class has a property set.
    //-------------------------------------------------------------------------
    class ImageLayer : public tinytmx::Layer
    {
    public:
        /// Construct an ImageLayer on the given map.
        explicit ImageLayer(const tinytmx::Map *_map);
        ~ImageLayer() override;

        /// Parse a ImageLayer element.
        void Parse(const tinyxml2::XMLNode *imageLayerNode) override;

        /// Returns a variable containing information
        /// about the image of the ImageLayer.
        const tinytmx::Image* GetImage() const { return image; }


    private:
        tinytmx::Image* image;
    };
}

#endif //TINYTMX_TINYTMXIMAGELAYER_HPP

