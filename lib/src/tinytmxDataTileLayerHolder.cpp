#include "tinytmxDataTileLayerHolder.hpp"

namespace tinytmx {


    DataTileLayerHolder::DataTileLayerHolder() : width(0), height(0), tile_map(nullptr) {

    }

    DataTileLayerHolder::DataTileLayerHolder(int _width, int _height) : width(_width), height(_height),
                                                                        tile_map(new MapTile[_width * _height]) {

    }

    DataTileLayerHolder::~DataTileLayerHolder() {
        if (tile_map) {
            delete[] tile_map;
            tile_map = nullptr;
        }
    }

}
