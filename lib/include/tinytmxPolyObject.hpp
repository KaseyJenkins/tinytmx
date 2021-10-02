#ifndef TINYTMX_TINYTMXPOLYOBJECT_HPP
#define TINYTMX_TINYTMXPOLYOBJECT_HPP

#include <vector>
#include "tinytmxVector2.hpp"

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {
    //-------------------------------------------------------------------------
    /// A class to store a Polyline or a Polygon.
    //-------------------------------------------------------------------------

    class PolyObject {
    public:
        PolyObject() = default;

        /// Parse the polyline node.
        void Parse(const tinyxml2::XMLNode *polyObjectNode);

        /// Get all of the points.
        [[nodiscard]] const std::vector<tinytmx::Vector2f > &GetPoints() const { return points; }

        /// Get one of the vertices.
        [[nodiscard]] const tinytmx::Vector2f &GetPoint(int index) const { return points.at(index); }

        /// Get the number of vertices.
        [[nodiscard]] auto GetNumPoints() const { return points.size(); }

    private:
        std::vector<tinytmx::Vector2f> points;
    };
}

#endif //TINYTMX_TINYTMXPOLYOBJECT_HPP

