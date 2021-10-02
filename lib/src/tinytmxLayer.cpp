#include "tinyxml2.h"
#include <algorithm>
#include <utility>

#ifdef USE_MINIZ
#include "miniz.h"
#else
#include <zlib.h>
#endif


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
    Layer::Layer(const tinytmx::Map *_map, std::string _name, int _x, int _y, uint32_t _width, uint32_t _height, float _opacity,
                 bool _visible, LayerType _layerType)
            : map(_map), tile(nullptr), name(std::move(_name)), ID(0), x(_x), y(_y), width(_width), height(_height), opacity(_opacity),
              visible(_visible), tint_color(0), offsetX(0), offsetY(0), zOrder(nextParseOrder), parseOrder(nextParseOrder), layerType(_layerType),
              properties(nullptr) {
        ++nextParseOrder;
    }

    Layer::Layer(const tinytmx::Tile *_tile,
                 const tinytmx::Map *_map,
                 std::string _name, int _x, int _y, uint32_t _width,
                 uint32_t _height, float _opacity, bool _visible, LayerType _layerType)
            : map(_map), tile(_tile), name(std::move(_name)), ID(0), x(_x), y(_y), width(_width), height(_height), opacity(_opacity),
              visible(_visible), tint_color(0), offsetX(0), offsetY(0), zOrder(nextParseOrder), parseOrder(nextParseOrder), layerType(_layerType),
              properties(nullptr) {
        ++nextParseOrder;
    }

    Layer::~Layer() {
        if (properties != nullptr) {
            delete properties;
            properties = nullptr;
        }
    }

}
