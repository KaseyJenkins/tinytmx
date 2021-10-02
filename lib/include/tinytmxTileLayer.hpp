#ifndef TINYTMX_TINYTMXTILELAYER_HPP
#define TINYTMX_TINYTMXTILELAYER_HPP

#include <string>
#include <vector>

#include "tinytmxLayer.hpp"
#include "tinytmxPropertySet.hpp"
#include "tinytmxMapTile.hpp"
#include "tinytmxVector2.hpp"


namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx
{
    class Map;
    class Chunk;
    class DataTileLayerHolder;

    //-------------------------------------------------------------------------
    /// Type used for the encoding of the tile layer data.
    //-------------------------------------------------------------------------
    enum class TileLayerEncodingType
    {
        TMX_ENCODING_XML,
        TMX_ENCODING_BASE64,
        TMX_ENCODING_CSV
    };

    //-------------------------------------------------------------------------
    /// Type used for the compression of the tile layer data.
    //-------------------------------------------------------------------------
    enum class TileLayerCompressionType
    {
        TMX_COMPRESSION_NONE,
        TMX_COMPRESSION_ZLIB,
        TMX_COMPRESSION_GZIP,
        TMX_COMPRESSION_ZSTD
    };

    //-------------------------------------------------------------------------
    /// Used for storing information about the tile ids for every tile layer.
    /// This class also has a property set.
    //-------------------------------------------------------------------------
    class TileLayer : public tinytmx::Layer
    {
    private:

    public:

        // Delete copy constructor.
        TileLayer(const TileLayer&) = delete;
        // Delete assignment constructor.
        TileLayer& operator=(const TileLayer&) = delete;

        /// Construct a TileLayer on the given map.
        explicit TileLayer(const tinytmx::Map *_map);
        ~TileLayer() override;

        /// Parse a tile layer node.
        void Parse(const tinyxml2::XMLNode *tileLayerNode) override;

//        /// Pick a specific tile id from the list.
//        unsigned GetTileID(int x, int y) const { return tile_map[y * width + x].id; }
//
//        /// Pick a specific tile gid from the list.
//        unsigned GetTileGid(int x, int y) const { return tile_map[y * width + x].gid; }
//
//        /// Get the tileset index for a tileset from the list.
//        int GetTileTilesetIndex(int x, int y) const { return tile_map[y * width + x].tilesetId; }
//
//        /// Get whether a tile is flipped horizontally.
//        bool IsTileFlippedHorizontally(int x, int y) const
//        { return tile_map[y * width + x].flippedHorizontally; }
//
//        /// Get whether a tile is flipped vertically.
//        bool IsTileFlippedVertically(int x, int y) const
//        { return tile_map[y * width + x].flippedVertically; }
//
//        /// Get whether a tile is flipped diagonally.
//        bool IsTileFlippedDiagonally(int x, int y) const
//        { return tile_map[y * width + x].flippedDiagonally; }
//
//        /// Get the tile at the given position.
//        const tinytmx::MapTile& GetTile(int x, int y) const { return tile_map[y * width + x]; }
//
//        /// Get a tile by its index.
//        const tinytmx::MapTile& GetTile(int index) const { return tile_map[index]; }

        /// Get the parallax.
        const tinytmx::Vector2f& GetParallax() const { return parallax; }

        /// Get the type of encoding that was used for parsing the tile layer data.
        /// See: TileLayerEncodingType
        tinytmx::TileLayerEncodingType GetEncoding() const { return encoding; }

        /// Get the type of compression that was used for parsing the tile layer data.
        /// See: TileLayerCompressionType
        tinytmx::TileLayerCompressionType GetCompression() const { return compression; }

        /// Get the chunks for the infinite map.
        const std::vector<tinytmx::Chunk *>& GetChunks() const { return chunks; }

        /// Get the data tile for the finite map.
        const tinytmx::DataTileLayerHolder* GetDataTileFiniteMap () const { return  data_tile_finite_map; }


    private:

        // TODO these functions need a tad of redoing
        void ParseXML(const tinyxml2::XMLNode *dataNode, tinytmx::MapTile *m_tile_map = nullptr, const std::string& firstChildElement = "tile"); // Deprecated.
        void ParseBase64(const std::string &innerText, uint32_t m_width = 0, uint32_t m_height = 0,  tinytmx::MapTile *m_tile_map = nullptr);
        void ParseCSV(const std::string &innerText, tinytmx::MapTile *m_tile_map = nullptr);

//        tinytmx::MapTile *tile_map;

        tinytmx::Vector2f parallax;

        tinytmx::TileLayerEncodingType encoding;
        tinytmx::TileLayerCompressionType compression;

        std::vector<tinytmx::Chunk *> chunks;
        tinytmx::DataTileLayerHolder *data_tile_finite_map;

    };
}

#endif //TINYTMX_TINYTMXTILELAYER_HPP

