#ifndef TINYTMX_TINYTMXDATATILELAYERHOLDER_HPP
#define TINYTMX_TINYTMXDATATILELAYERHOLDER_HPP

#include "tinytmxMapTile.hpp"
#include <cstdint>

namespace tinytmx {

    class DataTileLayerHolder {
    public:
        /// Constructor for Chunk
        DataTileLayerHolder();
        /// Constructor for TileLayer Data Holder
        explicit DataTileLayerHolder(uint32_t _width, uint32_t _height);

        virtual ~DataTileLayerHolder();

        /// Pick a specific tile id from the list.
        [[nodiscard]] unsigned GetTileId(int x, int y) const { return tile_map[y * width + x].id; }

        /// Pick a specific tile gid from the list.
        [[nodiscard]] unsigned GetTileGid(int x, int y) const { return tile_map[y * width + x].gid; }

        /// Get the tileset index for a tileset from the list.
        [[nodiscard]] int GetTileTilesetIndex(int x, int y) const { return tile_map[y * width + x].tilesetId; }

        /// Returns true if a tile is flipped horizontally.
        [[nodiscard]] bool IsTileFlippedHorizontally(int x, int y) const { return tile_map[y * width + x].flippedHorizontally; }

        /// Returns true if a tile is flipped vertically.
        [[nodiscard]] bool IsTileFlippedVertically(int x, int y) const { return tile_map[y * width + x].flippedVertically; }

        /// Returns true if a tile is flipped diagonally.
        [[nodiscard]] bool IsTileFlippedDiagonally(int x, int y) const { return tile_map[y * width + x].flippedDiagonally; }

        /// Get a tile at the given position.
        [[nodiscard]] const tinytmx::MapTile &GetTile(int x, int y) const { return tile_map[y * width + x]; }

        /// Get a tile by its index.
        [[nodiscard]] const tinytmx::MapTile &GetTile(int index) const { return tile_map[index]; }

        uint32_t width;
        uint32_t height;
        tinytmx::MapTile *tile_map;
    };
}

#endif //TINYTMX_TINYTMXDATATILELAYERHOLDER_HPP
