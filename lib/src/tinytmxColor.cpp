#include "tinytmxColor.hpp"
#include <cstdio>
#include <cstdlib>

namespace tinytmx {
    Color::Color()
            : color(0) {
    }

    Color::Color(uint32_t c)
            : color(c) {
    }

    Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        color = 0;

        color |= a;
        color <<= 8;
        color |= r;
        color <<= 8;
        color |= g;
        color <<= 8;
        color |= b;

        //uint32_t color1 = (a & 0xff) << 24 | (r & 0xff) << 16 | (g & 0xff) << 8 | (b & 0xff);

    }

    Color::Color(const std::string &str) {
        // We skip the first # character and then read directly the hexadecimal value
        color = std::strtoul((str.c_str() + 1), nullptr, 16);
        // If the input has the short format #RRGGBB without alpha channel we set it to 255
        if (str.length() == 7) { color |= 0xff000000; }
    }

    uint8_t Color::GetAlpha() const {
        return (color & 0xff000000) >> 24;
    }

    uint8_t Color::GetRed() const {
        return (color & 0x00ff0000) >> 16;
    }

    uint8_t Color::GetGreen() const {
        return (color & 0x0000ff00) >> 8;
    }

    uint8_t Color::GetBlue() const {
        return (color & 0x000000ff);
    }

    bool Color::IsTransparent() const {
        return GetAlpha() == 0;
    }

    std::string Color::ToString() const {
        char strRep[10];
        std::sprintf(strRep, "#%.8x", color);
        return strRep;
    }
}
