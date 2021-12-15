#include "tinytmxText.hpp"
#include "tinytmxColor.hpp"
#include "tinyxml2.h"
#include <string_view>


namespace tinytmx {
    Text::Text()
            : bold(false),
              italic(false),
              underline(false),
              strikeout(false),
              kerning(true),
              wrap(false),
              horizontal_alignment(HorizontalAlignment::LEFT),
              vertical_alignment(VerticalAlignment::TOP),
              pixel_size(16),
              color("#000000"),
              font_family("sans-serif") {}

    void Text::Parse(tinyxml2::XMLNode const *textNode) {
        tinyxml2::XMLElement const *textElement = textNode->ToElement();

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
            std::string_view halignAsCString = textElement->Attribute("halign");

            if (halignAsCString == "left") {
                horizontal_alignment = HorizontalAlignment::LEFT;
            } else if (halignAsCString == "center") {
                horizontal_alignment = HorizontalAlignment::HCENTER;
            } else if (halignAsCString == "right") {
                horizontal_alignment = HorizontalAlignment::RIGHT;
            } else if (halignAsCString == "justify") {
                horizontal_alignment = HorizontalAlignment::JUSTIFY;
            }
        }

        if (textElement->FindAttribute("valign")) {
            std::string_view valignAsCString = textElement->Attribute("valign");

            if (valignAsCString == "top") {
                vertical_alignment = VerticalAlignment::TOP;
            } else if (valignAsCString == "center") {
                vertical_alignment = VerticalAlignment::VCENTER;
            } else if (valignAsCString == "bottom") {
                vertical_alignment = VerticalAlignment::BOTTOM;
            }
        }

        if (textElement->FindAttribute("color"))
            color = tinytmx::Color(textElement->Attribute("color"));
    }
}
