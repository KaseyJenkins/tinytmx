#ifndef TINYTMX_TINYTMXIMAGELAYER_HPP
#define TINYTMX_TINYTMXIMAGELAYER_HPP


#include "tinytmxLayer.hpp"
//#include "tinytmxPropertySet.hpp"

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
        ImageLayer(tinytmx::Map const *, tinyxml2::XMLNode const *);
        ~ImageLayer() override;

        /// Returns a variable containing the information
        /// about the image of the ImageLayer.
        [[nodiscard]] tinytmx::Image const *GetImage() const { return image; }


        /// Returns whether the image drawn by this layer is repeated along the X axis.
        [[nodiscard]] bool IsRepeatX() const { return repeatx; }
        /// Returns whether the image drawn by this layer is repeated along the Y axis.
        [[nodiscard]] bool IsRepeatY() const { return repeaty; }

    private:
        bool repeatx;
        bool repeaty;

        tinytmx::Image* image;

        void Parse(tinyxml2::XMLNode const *imageLayerNode) override;
    };
}

#endif //TINYTMX_TINYTMXIMAGELAYER_HPP

