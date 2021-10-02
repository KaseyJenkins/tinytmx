#ifndef TINYTMX_TINYTMXGRID_HPP
#define TINYTMX_TINYTMXGRID_HPP

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

        Grid();

        /// Parse a grid element.
        void Parse(const tinyxml2::XMLNode *gridNode);

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
    };

}

#endif //TINYTMX_TINYTMXGRID_HPP
