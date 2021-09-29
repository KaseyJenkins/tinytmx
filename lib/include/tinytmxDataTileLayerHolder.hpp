#ifndef TINYTMX_TINYTMXDATATILELAYERHOLDER_HPP
#define TINYTMX_TINYTMXDATATILELAYERHOLDER_HPP

#include "tinytmxMapTile.hpp"


namespace tinytmx {

    class DataTileLayerHolder {
    public:
        /// Constructor for Chunk
        DataTileLayerHolder();
        /// Constructor for TileLayer Data Holder
        explicit DataTileLayerHolder(int _width, int _height);

        virtual ~DataTileLayerHolder();

        /// Pick a specific tile id from the list.
        unsigned GetTileId(int x, int y) const { return tile_map[y * width + x].id; }

        /// Pick a specific tile gid from the list.
        unsigned GetTileGid(int x, int y) const { return tile_map[y * width + x].gid; }

        /// Get the tileset index for a tileset from the list.
        int GetTileTilesetIndex(int x, int y) const { return tile_map[y * width + x].tilesetId; }

        /// Get whether a tile is flipped horizontally.
        bool IsTileFlippedHorizontally(int x, int y) const { return tile_map[y * width + x].flippedHorizontally; }

        /// Get whether a tile is flipped vertically.
        bool IsTileFlippedVertically(int x, int y) const { return tile_map[y * width + x].flippedVertically; }

        /// Get whether a tile is flipped diagonally.
        bool IsTileFlippedDiagonally(int x, int y) const { return tile_map[y * width + x].flippedDiagonally; }

        /// Get the tile at the given position.
        const tinytmx::MapTile &GetTile(int x, int y) const { return tile_map[y * width + x]; }

        /// Get a tile by its index.
        const tinytmx::MapTile &GetTile(int index) const { return tile_map[index]; }

        int width;
        int height;
        tinytmx::MapTile *tile_map;
    };
}

#endif //TINYTMX_TINYTMXDATATILELAYERHOLDER_HPP
