#ifndef TINYTMX_TINYTMXLAYER_HPP
#define TINYTMX_TINYTMXLAYER_HPP


#include <string>
#include "tinytmxPropertySet.hpp"
#include "tinytmxVector2.hpp"

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {
    class Map;

    class Tile;

    enum class LayerType : uint8_t {
        TMX_LAYERTYPE_TILE = 0X01,
        TMX_LAYERTYPE_OBJECTGROUP = 0X02,
        TMX_LAYERTYPE_IMAGE_LAYER = 0X04,
        TMX_LAYERTYPE_GROUP_LAYER = 0X08
    };

    //-------------------------------------------------------------------------
    /// Base class for other layer types.
    //-------------------------------------------------------------------------
    class Layer {
    private:

    public:

        // Delete copy constructor.
        Layer(Layer const &) = delete;
        // Delete move constructor.
        Layer(Layer &&) = delete;
        // Delete copy assignment operator.
        Layer &operator=(Layer const &) = delete;
        // Delete move assignment operator.
        Layer &operator=(Layer &&) = delete;

        /// Construct a new Layer used by a map's objectgroup
        Layer(tinytmx::Map const *_map, std::string const &_name, int _x, int _y,
              uint32_t _width, uint32_t _height, float _opacity, bool _visible,
              LayerType _layerType);

        /// Construct a new layer used by a tile's objectgroup
        Layer(tinytmx::Tile const *_tile,
              tinytmx::Map const *_map, std::string const &_name, int _x, int _y,
              uint32_t _width, uint32_t _height, float _opacity, bool _visible,
              LayerType _layerType);

        virtual ~Layer();

        /// Parse a layer element.
        virtual void Parse(tinyxml2::XMLNode const *layerNode) = 0;

        /// Get the pointer to the parent map.
        [[nodiscard]] tinytmx::Map const *mapGetMap() const { return map; }

        /// Get the name of the layer.
        [[nodiscard]] std::string const &GetName() const { return name; }

        /// Get the ID.
        [[nodiscard]] uint32_t GetID() const { return ID; }

        /// Get the value of the x attribute of the layer. Means different things for different layer types.
        [[nodiscard]] int GetX() const { return x; }

        /// Get the value of the y attribute of the layer. Means different things for different layer types.
        [[nodiscard]] int GetY() const { return y; }

        /// Get the opacity of the layer.
        [[nodiscard]] float GetOpacity() const { return opacity; }

        /// Get the visibility of the layer
        [[nodiscard]] bool IsVisible() const { return visible; }

        /// Get the tint color.
        [[nodiscard]] tinytmx::Color const &GetTintColor() const { return tint_color; }

        // FIXME should probably be deprecated.
//        /// Sets the offset for this GroupLayer
//        void SetOffset(float offsetXv, float offsetYv) {
//            offsetX = offsetXv;
//            offsetY = offsetYv;
//        }

        /// Returns the x offset.
        [[nodiscard]] float GetOffsetX() const noexcept { return offsetX; }

        /// Returns the y offset.
        [[nodiscard]] float GetOffsetY() const noexcept { return offsetY; }

        /// Get the property set.
        [[nodiscard]] tinytmx::PropertySet const *GetProperties() const { return properties; }

        /// Get the zorder of the layer.
        [[nodiscard]] int GetZOrder() const { return zOrder; }

        /// Set the zorder of the layer.
        void SetZOrder(int z) { zOrder = z; }
//        int& SetZOrder() { return zOrder; }

        /// Get the parse order of the layer.
        [[nodiscard]] int GetParseOrder() const { return parseOrder; }

        /// Get the type of the layer.
        [[nodiscard]] tinytmx::LayerType GetLayerType() const { return layerType; }


    protected:
        /// @cond INTERNAL
        bool visible;
        const tinytmx::LayerType layerType;

        uint32_t ID;
        int x;
        int y;

        uint32_t width;
        uint32_t height;

//        tinytmx::Vector2ui size;

        float opacity;

        float offsetX;
        float offsetY;

        int zOrder;
        const int parseOrder;
        static int nextParseOrder;

        tinytmx::Color tint_color;

        const tinytmx::Map *map;
        const tinytmx::Tile *tile;

        tinytmx::PropertySet* properties;

        std::string name;

        /// @endcond
    };
}

#endif //TINYTMX_TINYTMXLAYER_HPP
