#include "tinytmxDataChunkTile.hpp"

namespace tinytmx {


    DataChunkTile::DataChunkTile(uint32_t widthv, uint32_t heightv, int x, int y) :
                                                width(widthv),
                                                height(heightv),
                                                m_x(x), m_y(y),
                                                tile_map(new MapTile[widthv * heightv]) {}

    DataChunkTile::DataChunkTile(uint32_t widthv, uint32_t heightv) :
                                                width(widthv),
                                                height(heightv),
                                                m_x(0), m_y(0),
                                                tile_map(new MapTile[widthv * heightv]) {}

    DataChunkTile::~DataChunkTile() {
        delete[] tile_map;
    }

}
