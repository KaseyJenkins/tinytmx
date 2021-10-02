#ifndef TINYTMX_TINYTMXTERRAIN_HPP
#define TINYTMX_TINYTMXTERRAIN_HPP

#include <vector>
#include "tinytmxPropertySet.hpp"

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {
    //-------------------------------------------------------------------------
    /// A class to contain the information about every terrain in the
    /// tileset/terraintypes element.
    /// DEPRECATED since 1.5.
    //-------------------------------------------------------------------------
    class Terrain {
    public:
        Terrain();

        /// Parse a terrain type node.
        void Parse(const tinyxml2::XMLNode *terrainNode);

        /// Get the name of the terrain type.
        const std::string &GetName() const { return name; }

        /// Get the local tile-id of the tile that represents the terrain type visually.
        int GetTileID() const { return tileID; }

        /// Get a set of properties re the terrain type.
        const tinytmx::PropertySet &GetProperties() const { return properties; }

    private:
        std::string name;
        int tileID;

        tinytmx::PropertySet properties;
    };
}

#endif //TINYTMX_TINYTMXTERRAIN_HPP

