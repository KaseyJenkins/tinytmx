#ifndef TINYTMX_TINYTMXIMAGE_HPP
#define TINYTMX_TINYTMXIMAGE_HPP


#include <string>
#include "tinytmxColor.hpp"

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {
    //-------------------------------------------------------------------------
    /// A class used for storing information about an image within a tileset.
    /// Note that it is not currently possible to use Tiled to create maps
    /// with embedded image data <data>, even though the TMX format supports this.
    //-------------------------------------------------------------------------
    class Image {
    public:
        Image();

        /// Parses an image element.
        void Parse(const tinyxml2::XMLNode *imageNode);

        /// Get the path to the file of the image (relative to the map)
        const std::string &GetSource() const { return source; }

        /// Get the width of the image.
        uint32_t GetWidth() const { return width; }

        /// Get the height of the image.
        uint32_t GetHeight() const { return height; }

        /// Get the transparent color used in the image. If none is set return a fully transparent color
        tinytmx::Color GetTransparentColor() const { return transparent_color; }

    private:
        // std::string format - for when it's possible to use Tiled to create maps with embedded image data
        std::string source;
        uint32_t width;
        uint32_t height;
        tinytmx::Color transparent_color;
    };
}

#endif //TINYTMX_TINYTMXIMAGE_HPP

