#ifndef TINYTMX_TINYTMXTERRAINARRAY_HPP
#define TINYTMX_TINYTMXTERRAINARRAY_HPP

#include <vector>

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {
    class Terrain;

    //-----------------------------------------------------------------------------
    /// A class to parse terrain types, which can be referenced from the
    /// terrain attribute of the tileset/tile element.
    //-----------------------------------------------------------------------------
    class [[deprecated]] TerrainArray {
    public:
        TerrainArray() = default;

        /// Parse a node containing all the terrain nodes.
        void Parse(std::vector<tinytmx::Terrain *> *terrainTypes, tinyxml2::XMLNode const *terrainArrayNode);
    };
}

#endif //TINYTMX_TINYTMXTERRAINARRAY_HPP

