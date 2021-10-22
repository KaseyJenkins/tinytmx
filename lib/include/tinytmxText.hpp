#ifndef TINYTMX_TINYTMXTEXT_HPP
#define TINYTMX_TINYTMXTEXT_HPP

#include <vector>
#include <string>
#include "tinytmxColor.hpp"

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx
{

    //--------------------------------------------------------------------------
    /// Enum to denote Horizontal Alignment of Text
    //--------------------------------------------------------------------------
    enum class HorizontalAlignment : uint8_t {
        LEFT,
        HCENTER,
        RIGHT,
        JUSTIFY
    };

    //--------------------------------------------------------------------------
    /// Enum to denote Vertical Alignment of Text
    //--------------------------------------------------------------------------
    enum class VerticalAlignment : uint8_t {
        TOP,
        VCENTER,
        BOTTOM
    };

    //-------------------------------------------------------------------------
    /// A class to store a Text of an Object.
    //-------------------------------------------------------------------------
    class Text
    {
    public:
        /// Construct text with the given options.
        Text();

        /// Parse the text node.
        void Parse(tinyxml2::XMLNode const *textNode);

        [[nodiscard]] std::string const &GetContents() const noexcept { return contents; }
        [[nodiscard]] std::string const &GetFontFamily() const noexcept { return font_family; }
        [[nodiscard]] int GetPixelSize() const noexcept { return pixel_size; }
        [[nodiscard]] bool Wraps() const noexcept { return wrap; }
        [[nodiscard]] Color const &GetColor() const noexcept { return color; }
        [[nodiscard]] bool IsBold() const noexcept { return bold; }
        [[nodiscard]] bool IsItalic() const noexcept { return italic; }
        [[nodiscard]] bool IsUnderline() const noexcept { return underline; }
        [[nodiscard]] bool IsStrikeout() const noexcept { return strikeout; }
        [[nodiscard]] bool UseKerning() const noexcept { return kerning; }
        [[nodiscard]] HorizontalAlignment GetHorizontalAlignment() const noexcept { return horizontal_alignment; }
        [[nodiscard]] VerticalAlignment GetVerticalAlignment() const noexcept { return vertical_alignment; }

    private:
        bool bold;
        bool italic;
        bool underline;
        bool strikeout;
        bool kerning;
        bool wrap;

        HorizontalAlignment horizontal_alignment;
        VerticalAlignment vertical_alignment;

        int pixel_size;

        tinytmx::Color color;

        std::string contents;
        std::string font_family;
    };
}

#endif //TINYTMX_TINYTMXTEXT_HPP

