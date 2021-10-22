#ifndef TINYTMX_TINYTMXMAPTILE_HPP
#define TINYTMX_TINYTMXMAPTILE_HPP


namespace tinytmx {
    //-------------------------------------------------------------------------
    // Flags that may be in the first three bits of the gid.
    //-------------------------------------------------------------------------
    const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
    const unsigned FLIPPED_VERTICALLY_FLAG   = 0x40000000;
    const unsigned FLIPPED_DIAGONALLY_FLAG   = 0x20000000;

    //-------------------------------------------------------------------------
    /// A struct to store the information about a specific tile in the map layer.
    //-------------------------------------------------------------------------
    struct MapTile {
        /// Default constructor.
        MapTile()
                : tilesetId(0), id(0), gid(0), flippedHorizontally(false), flippedVertically(false), flippedDiagonally(false) {}

        /// Take a gid and read the attributes from its first three bits.
        MapTile(unsigned _gid, int _tilesetFirstGid, int _tilesetId)
                : tilesetId(_tilesetId),
                  id(_gid & ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG)),
                  flippedHorizontally((_gid & FLIPPED_HORIZONTALLY_FLAG) != 0),
                  flippedVertically((_gid & FLIPPED_VERTICALLY_FLAG) != 0),
                  flippedDiagonally((_gid & FLIPPED_DIAGONALLY_FLAG) != 0) {
            gid = id;
            id -= _tilesetFirstGid;
        }

        /// True when the tile should be drawn flipped horizontally.
        bool flippedHorizontally;

        /// True when the tile should be drawn flipped vertically.
        bool flippedVertically;

        /// True when the tile should be drawn flipped diagonally.
        bool flippedDiagonally;

        /// Tileset id.
        int tilesetId;

        /// Id.
        unsigned id;

        /// Gid.
        unsigned gid;
    };
}

#endif //TINYTMX_TINYTMXMAPTILE_HPP

