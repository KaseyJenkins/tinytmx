#ifndef TINYTMX_TINYTMXMAP_HPP
#define TINYTMX_TINYTMXMAP_HPP


#include <vector>
#include <string>
#include <memory>

#include "tinytmxPropertySet.hpp"

namespace tinytmx {
    class Layer;

    class TileLayer;

    class ImageLayer;

    class ObjectGroup;

    class GroupLayer;

    class Tileset;

    //-------------------------------------------------------------------------
    /// Error in handling of the Map class.
    //-------------------------------------------------------------------------
    enum class MapError {
        /// A file could not be opened. (usually due to permission problems)
        TMX_COULDNT_OPEN = 0x01,

        /// There was an error in parsing the TMX file.
        /// This is being caused by TinyXML parsing problems.
        TMX_PARSING_ERROR = 0x02,

        /// The size of the file is invalid.
        TMX_INVALID_FILE_SIZE = 0x04
    };

    //-------------------------------------------------------------------------
    /// The way the map is viewed.
    //-------------------------------------------------------------------------
    enum class MapOrientation {
        /// This map is an orthogonal map.
        TMX_MO_ORTHOGONAL = 0x01,

        /// This map is an isometric map.
        TMX_MO_ISOMETRIC = 0x02,

        /// This map is an isometric staggered map.
        TMX_MO_STAGGERED = 0x03,

        /// This map is an hexagonal staggered map.
        TMX_MO_HEXAGONAL = 0x04
    };

    //-------------------------------------------------------------------------
    /// The order in which tiles on tile layers are rendered.
    /// The default is TMX_RIGHT_DOWN.
    //-------------------------------------------------------------------------
    enum class MapRenderOrder {
        TMX_RIGHT_DOWN = 0x01,
        TMX_RIGHT_UP = 0x02,
        TMX_LEFT_DOWN = 0x03,
        TMX_LEFT_UP = 0x04
    };

    //-------------------------------------------------------------------------
    /// The stagger axis for the map. (only applies to hexagonal and staggered maps)
    //-------------------------------------------------------------------------
    enum class MapStaggerAxis {
        TMX_SA_NONE = 0x00,  // if the map is not hexagonal or staggered
        TMX_SA_X = 0x01,
        TMX_SA_Y = 0x02
    };

    //-------------------------------------------------------------------------
    /// The stagger index for the map. (applies to hexagonal AND isometric staggered maps)
    //-------------------------------------------------------------------------
    enum class MapStaggerIndex {
        TMX_SI_NONE = 0x00,  // if the map is not hexagonal
        TMX_SI_EVEN = 0x01,
        TMX_SI_ODD = 0x02
    };

    //-------------------------------------------------------------------------
    /// This class is the root class of the parser.
    /// It has all of the information in regard to the TMX file.
    /// This class has a property set.
    //-------------------------------------------------------------------------
    class Map {

    public:
        // Delete copy constructor.
        Map(const Map &) = delete;

        // Delete assignment operator.
        Map &operator=(const Map &) = delete;

        Map();

        ~Map();

        /// Read a file and parse it.
        /// Note: use '/' instead of '\\' as it is using '/' to find the path.
        void ParseFile(const std::string &fileName);

        /// Parse text containing TMX formatted XML.
        void ParseText(const std::string &text);

        /// Get the filename used to read the map.
        const std::string &GetFilename() const { return file_name; }

        /// Get a path to the directory of the map file if any.
        const std::string &GetFilepath() const { return file_path; }

        /// Get the background color of the map file. If unset, return a fully transparent color.
        tinytmx::Color GetBackgroundColor() const { return background_color; }

        /// Get the version of the map.
        float GetVersion() const { return version; }

        /// Get the Tiled version.
        const std::string& GetTiledVersion() const { return tiled_version; }

        /// Get the orientation of the map.
        tinytmx::MapOrientation GetOrientation() const { return orientation; }

        /// Get the render order of the map.
        tinytmx::MapRenderOrder GetRenderOrder() const { return render_order; }

        /// Get the compression level.
        int GetCompressionLevel() const { return compression_level; }

        /// Get the infinite bool value.
        bool IsInfinite() const { return is_infinite; }

        /// Get the stagger axis of the map.
        tinytmx::MapStaggerAxis GetStaggerAxis() const { return stagger_axis; }

        /// Get the stagger index of the map.
        tinytmx::MapStaggerIndex GetStaggerIndex() const { return stagger_index; }

        /// Get the width of the map, in tiles.
        uint32_t GetWidth() const { return width; }

        /// Get the height of the map, in tiles.
        uint32_t GetHeight() const { return height; }

        /// Get the width of a tile, in pixels.
        uint32_t GetTileWidth() const { return tile_width; }

        /// Get the height of a tile, in pixels.
        uint32_t GetTileHeight() const { return tile_height; }

        /// Get the next layer id.
        int GetNextLayerId() const { return next_layer_id; }

        /// Get the next object id.
        int GetNextObjectId() const { return next_object_id; }

        /// Get the hexside length.
        uint32_t GetHexsideLength() const { return hexside_length; }

        /// Get the layer at a certain index.
        const tinytmx::Layer *GetLayer(int index) const { return layers.at(index); }

        /// Get the amount of layers.
        auto GetNumLayers() const { return layers.size(); }

        /// Get the whole layers collection.
        const std::vector<tinytmx::Layer *> &GetLayers() const { return layers; }

        /// Get the tile layer at a certain index.
        const tinytmx::TileLayer *GetTileLayer(int index) const { return tile_layers.at(index); }

        /// Get the amount of tile layers.
        auto GetNumTileLayers() const { return tile_layers.size(); }

        /// Get the whole collection of tile layers.
        const std::vector<tinytmx::TileLayer *> &GetTileLayers() const { return tile_layers; }

        /// Get the object group at a certain index.
        const tinytmx::ObjectGroup *GetObjectGroup(int index) const { return object_groups.at(index); }

        /// Get the amount of object groups.
        auto GetNumObjectGroups() const { return object_groups.size(); }

        /// Get the whole collection of object groups.
        const std::vector<tinytmx::ObjectGroup *> &GetObjectGroups() const { return object_groups; }

        /// Get the image layer at a certain index.
        const tinytmx::ImageLayer *GetImageLayer(int index) const { return image_layers.at(index); }

        /// Get the amount of image layers.
        auto GetNumImageLayers() const { return image_layers.size(); }

        /// Get the whole collection of image layers.
        const std::vector<tinytmx::ImageLayer *> &GetImageLayers() const { return image_layers; }

        const tinytmx::GroupLayer *GetGroupLayer(int index) const { return group_layers.at(index); }

        auto GetNumGroupLayers() const { return group_layers.size(); }

        const std::vector<tinytmx::GroupLayer *> &GetGroupLayers() const { return group_layers; }

        /// Find the tileset index for a tileset using a tile gid.
        int FindTilesetIndex(unsigned gid) const;

        /// Find a tileset for a specific gid.
        const tinytmx::Tileset *FindTileset(unsigned gid) const;

        /// Get a tileset by an index.
        const tinytmx::Tileset *GetTileset(int index) const { return tilesets.at(index); }

        /// Get the amount of tilesets.
        auto GetNumTilesets() const { return tilesets.size(); }

        /// Get the collection of tilesets.
        const std::vector<tinytmx::Tileset *> &GetTilesets() const { return tilesets; }

        /// Get whether there was an error or not.
        bool HasError() const { return has_error; }

        /// Get an error string containing the error in text format.
        const std::string &GetErrorText() const { return error_text; }

        /// Get a number that identifies the error. (TMX_ preceded constants)
        unsigned char GetErrorCode() const { return error_code; }

        /// Get the property set.
        const tinytmx::PropertySet &GetProperties() const { return properties; }

    private:


        std::string tiled_version;

        std::string file_name;
        std::string file_path;

        tinytmx::Color background_color;

        float version;
        tinytmx::MapOrientation orientation;
        tinytmx::MapRenderOrder render_order;
        tinytmx::MapStaggerAxis stagger_axis;
        tinytmx::MapStaggerIndex stagger_index;

        uint32_t width;
        uint32_t height;
        uint32_t tile_width;
        uint32_t tile_height;
        int next_layer_id; /*! 'nextlayerid': Auto-increments for each layer */ // FIXME: can be unsigned?
        int next_object_id; // FIXME: can be unsigned?
        uint32_t hexside_length;
        int compression_level; /*!
                               * 'compressionlevel': The compression level to use for tile layer
							   *     data (defaults to -1, which means to use the algorithm default)
							   *     Introduced in Tiled 1.3
							   *     */
        bool is_infinite;

        std::vector<tinytmx::Layer *> layers;
        std::vector<tinytmx::TileLayer *> tile_layers;
        std::vector<tinytmx::ImageLayer *> image_layers;
        std::vector<tinytmx::ObjectGroup *> object_groups;
        std::vector<tinytmx::GroupLayer *> group_layers;
        std::vector<tinytmx::Tileset *> tilesets;

        bool has_error;
        uint8_t error_code;
        std::string error_text;

        tinytmx::PropertySet properties;

        // Parse a 'map' node.
        void Parse(tinyxml2::XMLNode *mapNode);
    };
}

#endif //TINYTMX_TINYTMXMAP_HPP
