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
//    class Chunk;
    class DataChunkTile;

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
    /// Used to store the information about the tile ids for every tile layer.
    //-------------------------------------------------------------------------
    class TileLayer : public tinytmx::Layer
    {
    private:

    public:

        /// Construct a TileLayer on the given map.
        explicit TileLayer(tinytmx::Map const *_map);
        ~TileLayer() override;

        /// Parse a tile layer node.
        void Parse(tinyxml2::XMLNode const *tileLayerNode) override;

        /// Get the width of the layer, in tiles. Only used in tile layers.
        [[nodiscard]] uint32_t GetWidth() const { return width; }

        /// Get the height of the layer, in tiles. Only used in tile layers.
        [[nodiscard]] uint32_t GetHeight() const { return height; }

        /// Get the horizontal parallax factor for this layer.
        [[nodiscard]] float GetParallaxX() const { return parallax.x; }

        /// Get the vertical parallax factor for this layer.
        [[nodiscard]] float GetParallaxY() const { return parallax.y; }

        /// Get the type of encoding that was used for parsing the tile layer data.
        /// See: TileLayerEncodingType
        [[nodiscard]] tinytmx::TileLayerEncodingType GetEncoding() const { return encoding; }

        /// Get the type of compression that was used for parsing the tile layer data.
        /// See: TileLayerCompressionType
        [[nodiscard]] tinytmx::TileLayerCompressionType GetCompression() const { return compression; }

        /// Get the chunks for the infinite map.
        [[nodiscard]] std::vector<tinytmx::DataChunkTile *> const &GetChunks() const { return chunks; }
        /// Get the chunk at a particular index.
        [[nodiscard]] tinytmx::DataChunkTile const *GetChunk(std::vector<tinytmx::DataChunkTile *>::size_type index) const { return chunks.at(index); }
        /// Get the number of chunks.
        [[nodiscard]] auto GetNumChunks() { return chunks.size(); }

        /// Get the data tile for the finite map.
        [[nodiscard]] tinytmx::DataChunkTile const *GetDataTileFiniteMap () const { return  data_tile_finite_map; }


    private:


        // TODO these functions need a tad of redoing
        void ParseXML(tinyxml2::XMLNode const *dataNode, tinytmx::MapTile *m_tile_map = nullptr, std::string const &firstChildElement = "tile"); // Deprecated.
        void ParseBase64(std::string const &innerText, uint32_t m_width = 0, uint32_t m_height = 0,  tinytmx::MapTile *m_tile_map = nullptr);
        void ParseCSV(std::string const &innerText, tinytmx::MapTile *m_tile_map = nullptr);

        tinytmx::Vector2f parallax;

        tinytmx::TileLayerEncodingType encoding;
        tinytmx::TileLayerCompressionType compression;

        tinytmx::DataChunkTile *data_tile_finite_map;
        std::vector<tinytmx::DataChunkTile *> chunks;

    };
}

#endif //TINYTMX_TINYTMXTILELAYER_HPP

