#ifndef TINYTMX_TINYTMXGROUPLAYER_HPP
#define TINYTMX_TINYTMXGROUPLAYER_HPP


#include <string>
#include <vector>

#include "tinytmxLayer.hpp"
#include "tinytmxPropertySet.hpp"

namespace tinytmx
{
    class Map;

    //-------------------------------------------------------------------------
    /// A class to hold groups of layers to create a layer hierarchy.
    //-------------------------------------------------------------------------
    class GroupLayer : public tinytmx::Layer
    {
    public:
        /// Construct a GroupLayer on the given map.
        explicit GroupLayer(const tinytmx::Map *_map);
        ~GroupLayer() override;

        /// Parse a GroupLayer element.
        void Parse(const tinyxml2::XMLNode *groupLayerNode) override;

        /// Adds a Child Layer to the group.
        void AddChild(tinytmx::Layer* childLayer);

        /// Get a Child Layer.
        [[nodiscard]] tinytmx::Layer* GetChild(int index) const;

        /// Get all Child layers.
        [[nodiscard]] std::vector<tinytmx::Layer*> GetChildren() const noexcept;

        /// Get the number of Child Layers.
        [[nodiscard]] auto GetNumChildren() const noexcept;

    private:
        std::vector<tinytmx::Layer*> children;
    };
}

#endif //TINYTMX_TINYTMXGROUPLAYER_HPP
