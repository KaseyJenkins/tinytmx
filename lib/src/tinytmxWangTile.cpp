#include "tinyxml2.h"

#include <charconv>
#include <string_view>
#include "tinytmxWangTile.hpp"

namespace tinytmx {
    namespace {
        void ParseCommaSeparatedUInts(std::string_view text, std::vector<uint32_t> &out) {
            while (!text.empty()) {
                auto const commaPos = text.find(',');
                std::string_view token = (commaPos == std::string_view::npos) ? text : text.substr(0, commaPos);

                // Trim leading/trailing spaces.
                while (!token.empty() && token.front() == ' ') {
                    token.remove_prefix(1);
                }
                while (!token.empty() && token.back() == ' ') {
                    token.remove_suffix(1);
                }

                if (!token.empty()) {
                    uint32_t value = 0;
                    auto const result = std::from_chars(token.data(), token.data() + token.size(), value);
                    if (result.ec == std::errc{}) {
                        out.emplace_back(value);
                    }
                }

                if (commaPos == std::string_view::npos) {
                    break;
                }
                text.remove_prefix(commaPos + 1);
            }
        }
    }

    WangTile::WangTile() : tileID(0) {

    }

    void WangTile::Parse(const tinyxml2::XMLElement *wangTileElement) {
        // Parse the attributes.
        tileID = wangTileElement->UnsignedAttribute("tileid");

        // FIXME put into a function?
        // Parse the wangid attribute.
        char const *wangidAttr = wangTileElement->Attribute("wangid");
        if (wangidAttr) {
            ParseCommaSeparatedUInts(wangidAttr, wangID);
        }
    }
}
