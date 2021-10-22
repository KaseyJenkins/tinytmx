#include "tinyxml2.h"
#include <algorithm>


#ifdef USE_MINIZ
#include "miniz.h"
#else
#include "zlib.h"
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
    Layer::Layer(const tinytmx::Map *_map, std::string const &_name, int _x, int _y, uint32_t _width, uint32_t _height, float _opacity,
                 bool _visible, LayerType _layerType)
            : visible(_visible),
              layerType(_layerType),
              ID(0),
              x(_x),
              y(_y),
              width(_width),
              height(_height),
              opacity(_opacity),
              offsetX(0),
              offsetY(0),
              zOrder(nextParseOrder),
              parseOrder(nextParseOrder),
              tint_color(0),
              map(_map),
              tile(nullptr),
              properties(nullptr),
              name(_name) {
        ++nextParseOrder;
    }

    Layer::Layer(tinytmx::Tile const *_tile,
                 tinytmx::Map  const *_map,
                 std::string   const &_name, int _x, int _y, uint32_t _width,
                 uint32_t _height, float _opacity, bool _visible, LayerType _layerType)
            : visible(_visible),
              layerType(_layerType),
              ID(0),
              x(_x),
              y(_y),
              width(_width),
              height(_height),
              opacity(_opacity),
              offsetX(0),
              offsetY(0),
              zOrder(nextParseOrder),
              parseOrder(nextParseOrder),
              tint_color(0),
              map(_map),
              tile(_tile),
              properties(nullptr),
              name(_name) {
        ++nextParseOrder;
    }

    Layer::~Layer() {
        if (properties != nullptr) {
            delete properties;
            properties = nullptr;
        }
    }

}
