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
    /// Class to store a Text of an Object.
    //-------------------------------------------------------------------------
    class Text
    {
    public:
        /// Construct text with the given options.
        Text();
        ~Text();

        std::string GetContents() const noexcept { return contents; }
        std::string GetFontFamily() const noexcept { return font_family; }
        int GetPixelSize() const noexcept { return pixel_size; }
        bool Wraps() const noexcept { return wrap; }
        Color* GetColor() const noexcept { return color; }
        bool IsBold() const noexcept { return bold; }
        bool IsItalic() const noexcept { return italic; }
        bool IsUnderline() const noexcept { return underline; }
        bool IsStrikeout() const noexcept { return strikeout; }
        bool UseKerning() const noexcept { return kerning; }
        HorizontalAlignment GetHorizontalAlignment() const noexcept { return horizontal_alignment; }
        VerticalAlignment GetVerticalAlignment() const noexcept { return vertical_alignment; }

        /// Parse the text node.
        void Parse(const tinyxml2::XMLNode *textNode);

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

