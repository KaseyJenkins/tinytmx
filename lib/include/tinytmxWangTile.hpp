#ifndef TINYTMX_TINYTMXWANGTILE_HPP
#define TINYTMX_TINYTMXWANGTILE_HPP

#include <vector>

namespace tinyxml2 {
    class XMLElement;
}

namespace tinytmx {

    class WangTile {
    public:
        WangTile();

        void Parse(const tinyxml2::XMLElement *wangTileElement);

        /// Get the tile ID.
        [[nodiscard]] uint32_t GetTileId() const { return tileID; }

        /// Get the wang ID.
        [[nodiscard]] const std::vector<uint32_t> &GetWangID() const { return wangID; }

    private:

        uint32_t tileID;
        std::vector<uint32_t> wangID;

    };
}

#endif //TINYTMX_TINYTMXWANGTILE_HPP
