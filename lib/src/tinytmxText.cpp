#include "tinytmxText.hpp"
#include "tinytmxColor.hpp"
#include "tinyxml2.h"
#include <cstdlib>


namespace tinytmx {
    Text::Text()
            : font_family("sans-serif"), pixel_size(16), wrap(false), color(new Color("#000000")), bold(false),
              italic(false), underline(false), strikeout(false), kerning(true),
              horizontal_alignment(HorizontalAlignment::LEFT), vertical_alignment(VerticalAlignment::TOP) {
    }

    Text::~Text() {
        if (color) {
            delete color;
            color = nullptr;
        }
    }

    void Text::Parse(const tinyxml2::XMLNode *textNode) {
        const tinyxml2::XMLElement *textElement = textNode->ToElement();

        contents = std::string(textElement->GetText() ? textElement->GetText() : "");
        if (textElement->FindAttribute("fontfamily")) {
            font_family = std::string(textElement->Attribute("fontfamily"));
        }
        textElement->QueryIntAttribute("pixelsize", &pixel_size);
        textElement->QueryBoolAttribute("wrap", &wrap);
        textElement->QueryBoolAttribute("bold", &bold);
        textElement->QueryBoolAttribute("italic", &italic);
        textElement->QueryBoolAttribute("underline", &underline);
        textElement->QueryBoolAttribute("strikeout", &strikeout);
        textElement->QueryBoolAttribute("kerning", &kerning);

        if (textElement->FindAttribute("halign")) {
            auto ha_str = std::string(textElement->Attribute("halign"));
            if (ha_str == "left") { horizontal_alignment = HorizontalAlignment::LEFT; }
            else if (ha_str == "center") { horizontal_alignment = HorizontalAlignment::HCENTER; }
            else if (ha_str == "right") { horizontal_alignment = HorizontalAlignment::RIGHT; }
            else if (ha_str == "justify") { horizontal_alignment = HorizontalAlignment::JUSTIFY; }
        }

        if (textElement->FindAttribute("valign")) {
            auto va_str = std::string(textElement->Attribute("valign"));
            if (va_str == "top") { vertical_alignment = VerticalAlignment::TOP; }
            else if (va_str == "center") { vertical_alignment = VerticalAlignment::VCENTER; }
            else if (va_str == "bottom") { vertical_alignment = VerticalAlignment::BOTTOM; }
        }

        if (textElement->FindAttribute("color"))
            color = new Color(textElement->Attribute("color"));
    }
}
