#ifndef TINYTMX_TINYTMXTEXT_HPP
#define TINYTMX_TINYTMXTEXT_HPP

#include <vector>
#include <string>

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx
{

    class Color;
    //--------------------------------------------------------------------------
    /// Enum to denote Horizontal Alignment of Text
    //--------------------------------------------------------------------------
    enum class HorizontalAlignment
    {
      LEFT,
      HCENTER,
      RIGHT,
      JUSTIFY
    };

    //--------------------------------------------------------------------------
    /// Enum to denote Vertical Alignment of Text
    //--------------------------------------------------------------------------
    enum class VerticalAlignment
    {
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
        ~Text();

        /// Parse the text node.
        void Parse(const tinyxml2::XMLNode *textNode);

        [[nodiscard]] const std::string& GetContents() const noexcept { return contents; }
        [[nodiscard]] const std::string& GetFontFamily() const noexcept { return font_family; }
        [[nodiscard]] int GetPixelSize() const noexcept { return pixel_size; }
        [[nodiscard]] bool Wraps() const noexcept { return wrap; }
        [[nodiscard]] const Color* GetColor() const noexcept { return color; }
        [[nodiscard]] bool IsBold() const noexcept { return bold; }
        [[nodiscard]] bool IsItalic() const noexcept { return italic; }
        [[nodiscard]] bool IsUnderline() const noexcept { return underline; }
        [[nodiscard]] bool IsStrikeout() const noexcept { return strikeout; }
        [[nodiscard]] bool UseKerning() const noexcept { return kerning; }
        [[nodiscard]] HorizontalAlignment GetHorizontalAlignment() const noexcept { return horizontal_alignment; }
        [[nodiscard]] VerticalAlignment GetVerticalAlignment() const noexcept { return vertical_alignment; }

    private:
        std::string contents;
        std::string font_family;
        int pixel_size;
        bool wrap;
        Color* color;
        bool bold;
        bool italic;
        bool underline;
        bool strikeout;
        bool kerning;
        HorizontalAlignment horizontal_alignment;
        VerticalAlignment vertical_alignment;
    };
}

#endif //TINYTMX_TINYTMXTEXT_HPP

