#ifndef TINYTMX_TINYTMXIMAGE_HPP
#define TINYTMX_TINYTMXIMAGE_HPP


#include <string>
#include <vector>
#include "tinytmxColor.hpp"

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {
    //-------------------------------------------------------------------------
    /// A class to store the information about an image within a tileset.
    /// Supports both external file references and embedded image data.
    //-------------------------------------------------------------------------
    class Image {
    public:
        explicit Image(tinyxml2::XMLNode const *);

        /// Get the path to the file of the image (relative to the map).
        /// Empty when the image data is embedded.
        [[nodiscard]] std::string const &GetSource() const { return source; }

        /// Get the width of the image.
        [[nodiscard]] uint32_t GetWidth() const { return width; }

        /// Get the height of the image.
        [[nodiscard]] uint32_t GetHeight() const { return height; }

        /// Get the transparent color used in the image. If none is set return a fully transparent color.
        [[nodiscard]] tinytmx::Color GetTransparentColor() const { return transparent_color; }

        /// Get the image format (e.g. "png", "bmp"). Only set for embedded images.
        [[nodiscard]] std::string const &GetFormat() const { return format; }

        /// Get the encoding of the embedded data (e.g. "base64"). Empty if unencoded.
        [[nodiscard]] std::string const &GetEncoding() const { return encoding; }

        /// Get the compression of the embedded data (e.g. "gzip", "zlib", "zstd"). Empty if uncompressed.
        [[nodiscard]] std::string const &GetCompression() const { return compression; }

        /// Get the raw (decoded and decompressed) embedded image bytes.
        /// Empty when the image is an external file reference.
        [[nodiscard]] std::vector<unsigned char> const &GetRawData() const { return raw_data; }

        /// Whether this image has embedded data (as opposed to an external source file).
        [[nodiscard]] bool HasEmbeddedData() const { return !raw_data.empty(); }

        /// Whether a parse error occurred (e.g. decompression failure).
        [[nodiscard]] bool HasParseError() const { return !parse_error.empty(); }

        /// Get the parse error message. Empty if no error.
        [[nodiscard]] std::string const &GetParseError() const { return parse_error; }

    private:
        uint32_t width;
        uint32_t height;
        tinytmx::Color transparent_color;
        std::string source;
        std::string format;
        std::string encoding;
        std::string compression;
        std::vector<unsigned char> raw_data;
        std::string parse_error;

        void Parse(tinyxml2::XMLNode const *imageNode);
    };
}

#endif //TINYTMX_TINYTMXIMAGE_HPP

