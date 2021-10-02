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
    /// A class to store the information about a background image.
    //-------------------------------------------------------------------------
    class ImageLayer : public tinytmx::Layer
    {
    public:
        /// Construct an ImageLayer on the given map.
        explicit ImageLayer(const tinytmx::Map *_map);
        ~ImageLayer() override;

        /// Parse an ImageLayer element.
        void Parse(const tinyxml2::XMLNode *imageLayerNode) override;

        /// Returns a variable containing the information
        /// about the image of the ImageLayer.
        [[nodiscard]] const tinytmx::Image* GetImage() const { return image; }

    private:
        tinytmx::Image* image;
    };
}

#endif //TINYTMX_TINYTMXIMAGELAYER_HPP

