#ifndef TINYTMX_TINYTMXTILESET_HPP
#define TINYTMX_TINYTMXTILESET_HPP

#include <string>
#include <vector>

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
    class PropertySet;

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
    /// A class to store the information about each of the tilesets.
    /// A tileset is a collection of tiles, of whom each may contain properties.
    //-------------------------------------------------------------------------
    class Tileset 
    {
    public:

        // Delete copy constructor.
        Tileset(Tileset const &) = delete;
        // Delete move constructor.
        Tileset(Tileset &&) = delete;
        // Delete copy assignment operator.
        Tileset &operator=(Tileset const &) = delete;
        // Delete move assignment operator.
        Tileset &operator=(Tileset &&) = delete;

        Tileset();
        ~Tileset();

        /// Parse a tileset element.
        void Parse(tinyxml2::XMLNode const *tilesetNode, std::string const &file_path, tinytmx::Map const *_map);

        /// Returns the global id of the first tile.
        [[nodiscard]] int GetFirstGid() const { return first_gid; }

        /// Returns the name of the tileset.
        [[nodiscard]] std::string const &GetName() const { return name; }

        /// Get the width of a single tile.
        [[nodiscard]] uint32_t GetTileWidth() const { return tile_width; }

        /// Get the height of a single tile.
        [[nodiscard]] uint32_t GetTileHeight() const { return tile_height; }

        /// Get the spacing of the tileset.
        [[nodiscard]] uint32_t GetSpacing() const { return spacing; }

        /// Get the margin of the tileset.
        [[nodiscard]] uint32_t GetMargin() const { return margin; }

        /// Get the number of tiles in this tileset.
        [[nodiscard]] uint32_t GetTileCount() const { return tile_count; }

        /// Get the number of columns in the tileset.
        [[nodiscard]] uint32_t GetColumns() const { return columns;}

        /// Get Object Alignment.
        [[nodiscard]] tinytmx::ObjectAlignment GetObjectAlignment() const { return object_alignment; }

        /// Get the grid.
        [[nodiscard]] tinytmx::Grid const *GetGrid() const { return grid; }

        /// Get the offset of tileset
        [[nodiscard]] tinytmx::TileOffset const *GetTileOffset() const { return tileOffset; }

        /// Returns a variable containing information
        /// about the image of the tileset.
        [[nodiscard]] tinytmx::Image const *GetImage() const { return image; }

        /// Get the transformations.
        [[nodiscard]] tinytmx::Transformations const *GetTransformations() const { return transformations; }

        /// Returns a single tile of the set.
        [[nodiscard]] tinytmx::Tile const *GetTile(int index) const;

        /// Returns the whole tile collection.
        [[nodiscard]] std::vector< tinytmx::Tile *> const &GetTiles() const { return tiles; }

        /// Returns the whole wangsets collection.
        [[nodiscard]] std::vector<tinytmx::WangSet*> const &GetWangSets() const { return wangsets; }

        /// Get a wangset by an index.
        [[nodiscard]] tinytmx::WangSet const *GetWangSet(int index) const { return wangsets.at(index); }
        
        /// Get a set of properties regarding the tile.
        [[nodiscard]] tinytmx::PropertySet const *GetProperties() const { return properties; }

    private:
        int first_gid;

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

        tinytmx::PropertySet* properties;

//        std::vector< tinytmx::Terrain* > terrainTypes; // Deprecated
        std::vector<tinytmx::Tile * > tiles;
        std::vector<tinytmx::WangSet*> wangsets;

        std::string name;

    };
}

#endif //TINYTMX_TINYTMXTILESET_HPP

