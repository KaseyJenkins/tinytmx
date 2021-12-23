#ifndef TINYTMX_TINYTMXCOLOR_HPP
#define TINYTMX_TINYTMXCOLOR_HPP


#include <string>
#include <string_view>
#include <cstdint>

namespace tinytmx
{
    //-------------------------------------------------------------------------
    /// A class for storing the information about color.
    //-------------------------------------------------------------------------
    class Color
    {
    public:
        /// Default constructor for a fully transparent black color.
        Color();

        /// Initialize the Color with a 32 bit ARGB representation.
        explicit Color(uint32_t color);

        /// Initialize the Color with red, green, blue and optionally alpha values.
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

        /// Initialize the Color from a string hexadecimal representation in the format "#AARRGGBB" or "#RRGGBB".
        explicit Color(std::string_view str);

        /// Default copy ctor.
        Color(Color const &) = default;
        /// Default copy asignment operator.
        Color& operator=(Color const &) = default;
        /// Default move ctor.
        Color(Color &&) = default;
        /// Default move assignment operator.
        Color& operator=(Color &&) = default;

        /// Check if two colors have the exact same four components.
        bool operator==(Color const &o) const { return color == o.color; }

        /// Check if two colors are different.
        bool operator!=(Color const &o) const { return color != o.color; }

        //FIXME: should be free functions operating on color class:

        /// Get the alpha component of the color.
        [[nodiscard]] uint8_t GetAlpha() const;

        /// Get the red component of the color.
        [[nodiscard]] uint8_t GetRed() const;

        /// Get the green component of the color.
        [[nodiscard]] uint8_t GetGreen() const;

        /// Get the blue component of the color.
        [[nodiscard]] uint8_t GetBlue() const;

        /// Return true if the color is fully transparent (ie alpha value is 0).
        [[nodiscard]] bool IsTransparent() const;
      
        /// Get the 32 bits integer representing the color. The 8 highest bits are for the alpha channel, then the red, the green and the blue.
        [[nodiscard]] uint32_t ToInt() const { return color; }

        /// Get a string representation of the color in the format "#AARRGGBB".
        [[nodiscard]] std::string ToString() const;

    private:
        uint32_t color;
    };
}

#endif //TINYTMX_TINYTMXCOLOR_HPP
