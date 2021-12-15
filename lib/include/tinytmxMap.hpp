#ifndef TINYTMX_TINYTMXMAP_HPP
#define TINYTMX_TINYTMXMAP_HPP


#include <vector>
#include <string>
#include <string_view>
#include <memory>

#include "tinytmxColor.hpp"

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {

    class Layer;
    class TileLayer;
    class ImageLayer;
    class ObjectGroup;
    class GroupLayer;
    class Tileset;
    class PropertySet;

    //-------------------------------------------------------------------------
    /// Error in handling of the Map class.
    //-------------------------------------------------------------------------
    enum class MapError : uint8_t {
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
    enum class MapOrientation : uint8_t {
        /// This map is an orthogonal map.
        TMX_MO_ORTHOGONAL = 0x01,

        /// This map is an isometric map.
        TMX_MO_ISOMETRIC = 0x02,

        /// This map is an isometric staggered map.
        TMX_MO_STAGGERED = 0x03,

        /// This map is a hexagonal staggered map.
        TMX_MO_HEXAGONAL = 0x04
    };

    //-------------------------------------------------------------------------
    /// The order in which tiles on tile layers are rendered.
    /// The default is TMX_RIGHT_DOWN.
    //-------------------------------------------------------------------------
    enum class MapRenderOrder : uint8_t {
        TMX_RIGHT_DOWN = 0x01,
        TMX_RIGHT_UP = 0x02,
        TMX_LEFT_DOWN = 0x03,
        TMX_LEFT_UP = 0x04
    };

    //-------------------------------------------------------------------------
    /// For staggered and hexagonal maps, determines which axis ("x" or "y") is staggered.
    //-------------------------------------------------------------------------
    enum class MapStaggerAxis : uint8_t {
        TMX_SA_NONE = 0x00,  // if the map is not hexagonal or staggered
        TMX_SA_X = 0x01,
        TMX_SA_Y = 0x02
    };

    //-------------------------------------------------------------------------
    /// For staggered and hexagonal maps, determines whether
    /// the “even” or “odd” indexes along the staggered axis are shifted.
    //-------------------------------------------------------------------------
    enum class MapStaggerIndex :uint8_t {
        TMX_SI_NONE = 0x00,  // if the map is not hexagonal
        TMX_SI_EVEN = 0x01,
        TMX_SI_ODD = 0x02
    };

    //-------------------------------------------------------------------------
    /// This class is the root class of the tinytmx.
    /// It contains all of the information regarding the TMX file.
    //-------------------------------------------------------------------------
    class Map {

    public:
        // Delete copy constructor.
        Map(Map const &) = delete;
        // Delete move constructor.
        Map(Map &&) = delete;
        // Delete assignment operator.
        Map &operator=(Map const &) = delete;
        // Delete move assignment operator.
        Map &operator=(Map &&) = delete;

        Map();
        ~Map();

        /// Read the file and parse it.
        /// Note: use '/' instead of '\\' as it is using '/' to find the path.
        void ParseFile(std::string const &fileName);

        /// Parse the text containing TMX formatted XML.
        void ParseText(std::string const &text);

        /// Get the filename used to read the map.
        [[nodiscard]] std::string const &GetFilename() const { return file_name; }

        /// Get the path to the directory of the map file if any.
        [[nodiscard]] std::string const &GetFilepath() const { return file_path; }

        /// Get the background color of the map file. If unset, return a fully transparent color.
        [[nodiscard]] tinytmx::Color const &GetBackgroundColor() const { return background_color; }

        /// Get the TMX format version.
        [[nodiscard]] float GetVersion() const { return version; }

        /// Get the Tiled version used to save the file.
        [[nodiscard]] std::string const &GetTiledVersion() const { return tiled_version; }

        /// Get the map orientation.
        [[nodiscard]] tinytmx::MapOrientation GetOrientation() const { return orientation; }

        /// Get the order in which tiles on tile layers are rendered.
        [[nodiscard]] tinytmx::MapRenderOrder GetRenderOrder() const { return render_order; }

        /// Get the compression level to use for tile layer data
        /// (defaults to -1, which means to use the algorithm default).
        [[nodiscard]] int GetCompressionLevel() const { return compression_level; }

        /// Is the map infinite? - returns 'true' if it is.
        [[nodiscard]] bool IsInfinite() const { return is_infinite; }

        /// Get the stagger axis of the map.
        [[nodiscard]] tinytmx::MapStaggerAxis GetStaggerAxis() const { return stagger_axis; }

        /// Get the stagger index of the map.
        [[nodiscard]] tinytmx::MapStaggerIndex GetStaggerIndex() const { return stagger_index; }

        /// Get the map width in tiles.
        [[nodiscard]] uint32_t GetWidth() const { return width; }

        /// Get the map height in tiles.
        [[nodiscard]] uint32_t GetHeight() const { return height; }

        /// Get the width of a tile in pixels.
        [[nodiscard]] uint32_t GetTileWidth() const { return tile_width; }

        /// Get the height of a tile in pixels.
        [[nodiscard]] uint32_t GetTileHeight() const { return tile_height; }

        /// Get the next available ID for new layers.
        [[nodiscard]] int GetNextLayerID() const { return next_layer_id; }

        /// Get the next available ID for new objects.
        [[nodiscard]] int GetNextObjectID() const { return next_object_id; }

        /// Get the hexside length. (Only for hexagonal maps.)
        [[nodiscard]] uint32_t GetHexsideLength() const { return hexside_length; }

        /// Get the layer at a certain index.
        [[nodiscard]] tinytmx::Layer const *GetLayer(int index) const { return layers.at(index); }

        /// Get the number of layers.
        [[nodiscard]] auto GetNumLayers() const { return layers.size(); }

        /// Get the whole layers collection.
        [[nodiscard]] std::vector<tinytmx::Layer *> const &GetLayers() const { return layers; }

        /// Get the tile layer at a certain index.
        [[nodiscard]] tinytmx::TileLayer const *GetTileLayer(int index) const { return tile_layers.at(index); }

        /// Get the number of tile layers.
        [[nodiscard]] auto GetNumTileLayers() const { return tile_layers.size(); }

        /// Get the whole collection of tile layers.
        [[nodiscard]] std::vector<tinytmx::TileLayer *> const &GetTileLayers() const { return tile_layers; }

        /// Get the object group at a certain index.
        [[nodiscard]] tinytmx::ObjectGroup const *GetObjectGroup(int index) const { return object_groups.at(index); }

        /// Get the number of object groups.
        [[nodiscard]] auto GetNumObjectGroups() const { return object_groups.size(); }

        /// Get the whole collection of object groups.
        [[nodiscard]] std::vector<tinytmx::ObjectGroup *> const &GetObjectGroups() const { return object_groups; }

        /// Get the image layer at a certain index.
        [[nodiscard]] tinytmx::ImageLayer const *GetImageLayer(int index) const { return image_layers.at(index); }

        /// Get the number of image layers.
        [[nodiscard]] auto GetNumImageLayers() const { return image_layers.size(); }

        /// Get the whole collection of image layers.
        [[nodiscard]] std::vector<tinytmx::ImageLayer *> const &GetImageLayers() const { return image_layers; }

        /// Get the group layer at a certain index.
        [[nodiscard]] tinytmx::GroupLayer const *GetGroupLayer(int index) const { return group_layers.at(index); }

        /// Get the number of group layers.
        [[nodiscard]] auto GetNumGroupLayers() const { return group_layers.size(); }

        /// Get the whole collection of group layers
        [[nodiscard]] std::vector<tinytmx::GroupLayer *> const &GetGroupLayers() const { return group_layers; }

        /// Find the tileset index for a tileset using a tile gid.
        [[nodiscard]] int FindTilesetIndex(unsigned gid) const;

        /// Find the tileset for a specific gid.
        [[nodiscard]] tinytmx::Tileset const *FindTileset(unsigned gid) const;

        /// Get a tileset by an index.
        [[nodiscard]] tinytmx::Tileset const *GetTileset(int index) const { return tilesets.at(index); }

        /// Get the number of tilesets.
        [[nodiscard]] auto GetNumTilesets() const { return tilesets.size(); }

        /// Get the whole collection of tilesets.
        [[nodiscard]] std::vector<tinytmx::Tileset *> const &GetTilesets() const { return tilesets; }

        /// Was there an error? - get the bool value.
        [[nodiscard]] bool HasError() const { return has_error; }

        /// Get an error string containing the error in text format.
        [[nodiscard]] std::string const &GetErrorText() const { return error_text; }

        /// Get a number that identifies the error. (TMX_ preceded constants)
        [[nodiscard]] uint8_t GetErrorCode() const { return error_code; }

        /// Get the property set.
        [[nodiscard]] tinytmx::PropertySet const *GetProperties() const { return properties; }

    private:

        bool has_error;
        bool is_infinite;
        uint8_t error_code;

        tinytmx::MapOrientation orientation;
        tinytmx::MapRenderOrder render_order;
        tinytmx::MapStaggerAxis stagger_axis;
        tinytmx::MapStaggerIndex stagger_index;

        float version;

        tinytmx::Color background_color;

        uint32_t width;
        uint32_t height;
        uint32_t tile_width;
        uint32_t tile_height;
        int next_layer_id;  // FIXME: can be unsigned?
        int next_object_id; // FIXME: can be unsigned?
        uint32_t hexside_length;
        int compression_level;

        tinytmx::PropertySet* properties;

        std::vector<tinytmx::Layer *> layers;
        std::vector<tinytmx::TileLayer *> tile_layers;
        std::vector<tinytmx::ImageLayer *> image_layers;
        std::vector<tinytmx::ObjectGroup *> object_groups;
        std::vector<tinytmx::GroupLayer *> group_layers;
        std::vector<tinytmx::Tileset *> tilesets;

        std::string error_text;
        std::string tiled_version;
        std::string file_name;
        std::string file_path;

        // Parse a 'map' node.
        void Parse(tinyxml2::XMLNode const *mapNode);
    };
}

#endif //TINYTMX_TINYTMXMAP_HPP
