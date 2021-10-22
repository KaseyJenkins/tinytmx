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

        void Parse(tinyxml2::XMLElement const *wangTileElement);

        /// Get the tile ID.
        [[nodiscard]] uint32_t GetTileId() const { return tileID; }

        /// Get the wang ID.
        [[nodiscard]] std::vector<uint32_t> const &GetWangID() const { return wangID; }

    private:

        uint32_t tileID;
        std::vector<uint32_t> wangID;

    };
}

#endif //TINYTMX_TINYTMXWANGTILE_HPP
