#ifndef TINYTMX_TINYTMXGRID_HPP
#define TINYTMX_TINYTMXGRID_HPP

#include <cstdint>

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {

    enum class GridOrientation {
        TMX_GO_ORTHOGONAL,
        TMX_GO_ISOMETRIC
    };


    /// This element is only used in case of isometric orientation,
    /// and determines how tile overlays for terrain and collision information are rendered.

    class Grid {
    public:

        explicit Grid(tinyxml2::XMLNode const *);

        /// Get the grid's orientation.
        [[nodiscard]] tinytmx::GridOrientation GetOrientation() const { return grid_orientation; }

        /// Get the value of the width attribute of the grid element.
        [[nodiscard]] uint32_t GetWidth() const { return width; }

        /// Get the value of the height attribute of the grid element.
        [[nodiscard]] uint32_t GetHeight() const { return height; }

    private:
        tinytmx::GridOrientation grid_orientation;
        // TODO maybe Vector2?
        uint32_t width;
        uint32_t height;

        void Parse(tinyxml2::XMLNode const *gridNode);
    };

}

#endif //TINYTMX_TINYTMXGRID_HPP
