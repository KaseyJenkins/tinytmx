#ifndef TINYTMX_TINYTMXIMAGELAYER_HPP
#define TINYTMX_TINYTMXIMAGELAYER_HPP


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
        explicit ImageLayer(tinytmx::Map const *_map);
        ~ImageLayer() override;

        /// Parse an ImageLayer element.
        void Parse(tinyxml2::XMLNode const *imageLayerNode) override;

        /// Returns a variable containing the information
        /// about the image of the ImageLayer.
        [[nodiscard]] tinytmx::Image const *GetImage() const { return image; }

        /// Get the horizontal parallax factor for this image layer.
        [[nodiscard]] float GetParallaxX() const { return parallax.x; }

        /// Get the vertical parallax factor for this image layer.
        [[nodiscard]] float GetParallaxY() const { return parallax.y; }

        /// Whether the image should repeat on the X axis.
        [[nodiscard]] bool GetRepeatX() const { return repeatX; }

        /// Whether the image should repeat on the Y axis.
        [[nodiscard]] bool GetRepeatY() const { return repeatY; }

    private:
        tinytmx::Vector2f parallax;
        bool repeatX;
        bool repeatY;
        tinytmx::Image* image;
    };
}

#endif //TINYTMX_TINYTMXIMAGELAYER_HPP

