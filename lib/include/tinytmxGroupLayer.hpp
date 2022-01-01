#ifndef TINYTMX_TINYTMXGROUPLAYER_HPP
#define TINYTMX_TINYTMXGROUPLAYER_HPP


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
        GroupLayer(tinytmx::Map const *, tinyxml2::XMLNode const *);
        ~GroupLayer() override;

        /// Get a Child Layer.
        [[nodiscard]] tinytmx::Layer const *GetChild(int index) const;

        /// Get all Child layers.
        [[nodiscard]] std::vector<tinytmx::Layer*> const &GetChildren() const noexcept;

    private:
        std::vector<tinytmx::Layer*> children;

        void Parse(tinyxml2::XMLNode const *groupLayerNode) override;
        void AddChild(tinytmx::Layer *childLayer);
    };
}

#endif //TINYTMX_TINYTMXGROUPLAYER_HPP
