#ifndef TINYTMX_TINYTMXTILESET_HPP
#define TINYTMX_TINYTMXTILESET_HPP

#include <string>
#include <vector>

#include "tinytmxPropertySet.hpp"

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx
{
    class Grid;
    class Image;
    class TileOffset;
    class Terrain;
    class Tile;
    class Transformations;
    class WangSet;
    class Map;

    //-------------------------------------------------------------------------
    /// Controls the alignment for tile objects.
    //-------------------------------------------------------------------------

    enum class ObjectAlignment {
        TMX_OA_UNSPECIFIED,
        TMX_OA_TOPLEFT,
        TMX_OA_TOP,
        TMX_OA_TOPRIGHT,
        TMX_OA_LEFT,
        TMX_OA_CENTER,
        TMX_OA_RIGHT,
        TMX_OA_BOTTOMLEFT,
        TMX_OA_BOTTOM,
        TMX_OA_BOTTOMRIGHT
    };


    //-------------------------------------------------------------------------
    /// A class used for storing information about each of the tilesets.
    /// A tileset is a collection of tiles, of whom each may contain properties.
    /// This class has a property set.
    //-------------------------------------------------------------------------
    class Tileset 
    {
    public:
        Tileset();
        ~Tileset();

        /// Parse a tileset element.
        void Parse(const tinyxml2::XMLNode *tilesetNode, const std::string& file_path, const tinytmx::Map* _map);

        /// Returns the global id of the first tile.
        int GetFirstGid() const { return first_gid; }

        /// Returns the name of the tileset.
        const std::string &GetName() const { return name; }

        /// Get the width of a single tile.
        uint32_t GetTileWidth() const { return tile_width; }

        /// Get the height of a single tile.
        uint32_t GetTileHeight() const { return tile_height; }

        /// Get the spacing of the tileset.
        uint32_t GetSpacing() const { return spacing; }

        /// Get the margin of the tileset.
        uint32_t GetMargin() const { return margin; }

        /// Get the number of tiles in this tileset.
        uint32_t GetTileCount() const { return tile_count; }

        /// Get the number of columns in the tileset.
        uint32_t GetColumns() const { return columns;}

        /// Get Object Alignment.
        tinytmx::ObjectAlignment GetObjectAlignment() const { return object_alignment; }

        /// Get the grid.
        const tinytmx::Grid* GetGrid() const { return grid; }

        /// Get the offset of tileset
        const tinytmx::TileOffset* GetTileOffset() const { return tileOffset; }

        /// Returns a variable containing information
        /// about the image of the tileset.
        const tinytmx::Image* GetImage() const { return image; }

        /// Get the transformations.
        const tinytmx::Transformations* GetTransformations() const { return transformations; }

        /// Returns a single tile of the set.
        const tinytmx::Tile *GetTile(int index) const;

        /// Returns the whole tile collection.
        const std::vector< tinytmx::Tile *> &GetTiles() const { return tiles; }

        /// Returns the whole wangsets collection.
        const std::vector<tinytmx::WangSet*> &GetWangSets() const { return wangsets; }

        /// Get a wangset by an index.
        const tinytmx::WangSet* GetWangSet(int index) const { return wangsets.at(index); }
        
        /// Get a set of properties regarding the tile.
        const tinytmx::PropertySet &GetProperties() const { return properties; }

    private:
        int first_gid;
        
        std::string name;
        
        uint32_t tile_width;
        uint32_t tile_height;
        uint32_t spacing;
        uint32_t margin;
        uint32_t tile_count;
        uint32_t columns;

        tinytmx::ObjectAlignment object_alignment;
        
        tinytmx::Grid* grid;
        tinytmx::TileOffset* tileOffset;
        tinytmx::Image* image;
        tinytmx::Transformations* transformations;

        std::vector< tinytmx::Terrain* > terrainTypes;
        std::vector< tinytmx::Tile* > tiles;

        std::vector<tinytmx::WangSet*> wangsets;
        
        tinytmx::PropertySet properties;

    };
}

#endif //TINYTMX_TINYTMXTILESET_HPP

