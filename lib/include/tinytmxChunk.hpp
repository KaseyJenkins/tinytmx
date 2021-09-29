#ifndef TINYTMX_TINYTMXCHUNK_HPP
#define TINYTMX_TINYTMXCHUNK_HPP

#include "tinytmxMapTile.hpp"
#include "tinytmxDataTileLayerHolder.hpp"

namespace tinytmx {

    class Chunk : public tinytmx::DataTileLayerHolder {
    public:
        Chunk();

        //private:
        int m_x;
        int m_y;

    };

}
#endif //TINYTMX_TINYTMXCHUNK_HPP
