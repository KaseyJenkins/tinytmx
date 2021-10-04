#include "tinytmxDataChunkTile.hpp"

namespace tinytmx {


    DataChunkTile::DataChunkTile(uint32_t _width, uint32_t _height, int _x, int _y) :
                                                width(_width),
                                                height(_height),
                                                m_x(_x), m_y(_y),
                                                tile_map(new MapTile[_width * _height]) {}

    DataChunkTile::DataChunkTile(uint32_t _width, uint32_t _height) : width(_width),
                                                                      height(_height),
                                                                      m_x(0), m_y(0),
                                                                      tile_map( new MapTile[_width * _height]) {}

    DataChunkTile::~DataChunkTile() {
        if (tile_map) {
            delete[] tile_map;
            tile_map = nullptr;
        }
    }

}
