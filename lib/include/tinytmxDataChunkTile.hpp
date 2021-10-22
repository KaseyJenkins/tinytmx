#ifndef TINYTMX_TINYTMXDATATILELAYERHOLDER_HPP
#define TINYTMX_TINYTMXDATATILELAYERHOLDER_HPP

#include "tinytmxMapTile.hpp"
#include "tinytmxVector2.hpp"
#include <cstdint>

namespace tinytmx {

    class DataChunkTile {
    public:

        // Delete copy constructor.
        DataChunkTile(DataChunkTile const &) = delete;
        // Delete move constructor.
        DataChunkTile(DataChunkTile &&) = delete;
        // Delete copy assignment operator.
        DataChunkTile &operator=(DataChunkTile const &) = delete;
        // Delete move assignment operator.
        DataChunkTile &operator=(DataChunkTile &&) = delete;


        /// Constructor for Chunk
        DataChunkTile(uint32_t _width, uint32_t _height, int _x, int _y);
        /// Constructor for TileLayer Data
        explicit DataChunkTile(uint32_t _width, uint32_t _height);

        ~DataChunkTile();


        /// Get the x coordinate of the chunk in tiles.
        [[nodiscard]] int GetX() const { return m_x; }

        /// Get the y coordinate of the chunk in tiles.
        [[nodiscard]] int GetY() const { return m_y; }

        /// Get the width of the layer, in tiles.
        [[nodiscard]] uint32_t GetWidth() const { return width; }

        /// Get the height of the layer, in tiles.
        [[nodiscard]] uint32_t GetHeight() const { return height; }

        /// Get a MapTile
        [[nodiscard]] tinytmx::MapTile* GetMapTile() const { return tile_map; }


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
        [[nodiscard]] tinytmx::MapTile const &GetTile(int x, int y) const { return tile_map[y * width + x]; }

        /// Get a tile by its index.
        [[nodiscard]] tinytmx::MapTile const &GetTile(int index) const { return tile_map[index]; }


    private:
        uint32_t width;
        uint32_t height;

        int m_x;
        int m_y;
        tinytmx::MapTile *tile_map;
    };
}

#endif //TINYTMX_TINYTMXDATATILELAYERHOLDER_HPP
