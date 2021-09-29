#include "tinyxml2.h"
#include <algorithm>
#include <utility>

#ifdef USE_MINIZ
//#define MINIZ_HEADER_FILE_ONLY
#include "miniz.h"
#else

#include <zlib.h>

#endif

#include <stdlib.h>
#include <stdio.h>

#include "tinytmxLayer.hpp"
#include "tinytmxUtil.hpp"
#include "tinytmxMap.hpp"
#include "tinytmxTileset.hpp"

// Avoid nextParseOrder to be included in the documentation as it is an implementation detail
// that should not be considered as part of the API.

/// @cond INTERNAL
int tinytmx::Layer::nextParseOrder = 0;
/// @endcond

namespace tinytmx {
    Layer::Layer(const tinytmx::Map *_map, std::string _name, int _x, int _y, int _width, int _height, float _opacity,
                 bool _visible, LayerType _layerType)
            : map(_map), tile(nullptr), name(std::move(_name)), ID(0), x(_x), y(_y), width(_width), height(_height), opacity(_opacity),
              visible(_visible), tint_color(0), offsetX(0), offsetY(0), zOrder(nextParseOrder), parseOrder(nextParseOrder), layerType(_layerType),
              properties() {
        ++nextParseOrder;
    }

    Layer::Layer(const tinytmx::Tile *_tile,
                 const tinytmx::Map *_map
                 ,std::string _name, int _x, int _y, int _width,
                 int _height, float _opacity, bool _visible, LayerType _layerType)
            : map(_map), tile(_tile), name(std::move(_name)), ID(0), x(_x), y(_y), width(_width), height(_height), opacity(_opacity),
              visible(_visible), tint_color(0), offsetX(0), offsetY(0), zOrder(nextParseOrder), parseOrder(nextParseOrder), layerType(_layerType),
              properties() {
        ++nextParseOrder;
    }

}
