#ifndef TINYTMX_TINYTMXIMAGE_HPP
#define TINYTMX_TINYTMXIMAGE_HPP


#include <string>
#include "tinytmxColor.hpp"

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {
    //-------------------------------------------------------------------------
    /// A class to store the information about an image within a tileset.
    /// Note that it is not currently possible to use Tiled to create maps
    /// with embedded image data <data>, even though the TMX format supports this.
    //-------------------------------------------------------------------------
    class Image {
    public:
        explicit Image(tinyxml2::XMLNode const *);

        /// Get the path to the file of the image (relative to the map)
        [[nodiscard]] std::string const &GetSource() const { return source; }

        /// Get the width of the image.
        [[nodiscard]] uint32_t GetWidth() const { return width; }

        /// Get the height of the image.
        [[nodiscard]] uint32_t GetHeight() const { return height; }

        /// Get the transparent color used in the image. If none is set return a fully transparent color.
        [[nodiscard]] tinytmx::Color GetTransparentColor() const { return transparent_color; }

    private:
        // std::string format - for when it's possible to use Tiled to create maps with embedded image data
        uint32_t width;
        uint32_t height;
        tinytmx::Color transparent_color;
        std::string source;

        void Parse(tinyxml2::XMLNode const *imageNode);
    };
}

#endif //TINYTMX_TINYTMXIMAGE_HPP

