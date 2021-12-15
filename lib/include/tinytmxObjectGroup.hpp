#ifndef TINYTMX_TINYTMXOBJECTGROUP_HPP
#define TINYTMX_TINYTMXOBJECTGROUP_HPP


#include <vector>

#include "tinytmxLayer.hpp"
#include "tinytmxPropertySet.hpp"

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {
    class Object;

    enum class DrawOrder {
        TMX_DRAWORDER_TOPDOWN,
        TMX_DRAWORDER_INDEX
    };

    //-------------------------------------------------------------------------
    /// The object group is in fact a map layer, and is hence called “object layer” in Tiled.
    /// A class used for holding a list of objects.
    //-------------------------------------------------------------------------
    class ObjectGroup : public tinytmx::Layer {
    public:

        /// Construct a new ObjectGroup
        explicit ObjectGroup(tinytmx::Map const *_map);

        /// Construct a new ObjectGroup used by a Tile
        ObjectGroup(tinytmx::Tile const *_tile, tinytmx::Map const *_map);

        ~ObjectGroup() override;

        /// Parse an objectgroup node.
        void Parse(tinyxml2::XMLNode const *objectGroupNode) override;

        /// Get a single object.
        [[nodiscard]] tinytmx::Object const *GetObject(int index) const { return objects.at(index); }

        /// Get the number of objects in the list.
        [[nodiscard]] auto GetNumObjects() const { return objects.size(); }

        /// Get the color used to display the objects in this group.
        [[nodiscard]] tinytmx::Color const &GetColor() const { return color; }

        /// Get the whole list of objects.
        [[nodiscard]] std::vector<tinytmx::Object *> const &GetObjects() const { return objects; }

        /// Get the draworder.
        [[nodiscard]] tinytmx::DrawOrder GetDrawOrder() const { return draw_order; }

    private:
        DrawOrder draw_order;
        tinytmx::Color color; // defaults to gray (“#a0a0a4”)
        std::vector<tinytmx::Object *> objects;
    };
}

#endif //TINYTMX_TINYTMXOBJECTGROUP_HPP

