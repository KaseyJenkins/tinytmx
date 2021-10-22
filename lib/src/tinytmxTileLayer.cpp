#include "tinyxml2.h"
#include <algorithm>

#ifdef USE_MINIZ
#include "miniz.h"
#else

#include <zlib.h>

#endif

#include <zstd.h>

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "tinytmxLayer.hpp"
#include "tinytmxTileLayer.hpp"
#include "tinytmxUtil.hpp"
#include "tinytmxMap.hpp"
#include "tinytmxTileset.hpp"

#include "tinytmxDataChunkTile.hpp"

namespace tinytmx {
    TileLayer::TileLayer(Map const *_map)
            : Layer(_map, std::string(), 0, 0, _map->GetWidth(), _map->GetHeight(), 1.0f, true,
                    LayerType::TMX_LAYERTYPE_TILE)
            //, tile_map(nullptr)  // Set the map to null to specify that it is not yet allocated.
            , parallax(1.0f, 1.0f), encoding(TileLayerEncodingType::TMX_ENCODING_XML),
              compression(TileLayerCompressionType::TMX_COMPRESSION_NONE),
              data_tile_finite_map(nullptr) {
    }

    TileLayer::~TileLayer() {

        for (auto chunk: chunks) {
            delete chunk;
            chunk = nullptr;
        }

        if (data_tile_finite_map) {
            delete data_tile_finite_map;
            data_tile_finite_map = nullptr;
        }
    }

    void TileLayer::Parse(tinyxml2::XMLNode const *tileLayerNode) {
        tinyxml2::XMLElement const *tileLayerElem = tileLayerNode->ToElement();

        // Read the attributes.
        ID = tileLayerElem->UnsignedAttribute("id");
        name = tileLayerElem->Attribute("name");

        tileLayerElem->QueryIntAttribute("x", &x);
        tileLayerElem->QueryIntAttribute("y", &y);

        tileLayerElem->QueryFloatAttribute("offsetx", &offsetX);
        tileLayerElem->QueryFloatAttribute("offsety", &offsetY);

        tileLayerElem->QueryFloatAttribute("opacity", &opacity);
        tileLayerElem->QueryBoolAttribute("visible", &visible);

        if (tileLayerElem->Attribute("tintcolor")) {
            tint_color = tinytmx::Color(tileLayerElem->Attribute("tintcolor"));
        }

        tileLayerElem->QueryFloatAttribute("parallaxx", &parallax.x);
        tileLayerElem->QueryFloatAttribute("parallaxy", &parallax.y);

        // Read the properties.
        tinyxml2::XMLNode const *propertiesNode = tileLayerNode->FirstChildElement("properties");
        if (propertiesNode) {
            properties = new PropertySet();
            properties->Parse(propertiesNode);
        }


        tinyxml2::XMLElement const *dataElem = tileLayerNode->FirstChildElement("data");
        char const *encodingStr = dataElem->Attribute("encoding");
        char const *compressionStr = dataElem->Attribute("compression");

        // Check for encoding.
        if (encodingStr) {
            if (!strcmp(encodingStr, "base64")) {
                encoding = TileLayerEncodingType::TMX_ENCODING_BASE64;
            } else if (!strcmp(encodingStr, "csv")) {
                encoding = TileLayerEncodingType::TMX_ENCODING_CSV;
            }
        }

        // Check for compression.
        if (compressionStr) {
            if (!strcmp(compressionStr, "gzip")) {
                compression = TileLayerCompressionType::TMX_COMPRESSION_GZIP;
            } else if (!strcmp(compressionStr, "zlib")) {
                compression = TileLayerCompressionType::TMX_COMPRESSION_ZLIB;
            } else if (!strcmp(compressionStr, "zstd")) {
                compression = TileLayerCompressionType::TMX_COMPRESSION_ZSTD;
            }
        }

        // If the map is infinite parse all the chunks
        if (map->IsInfinite()) {
            tinyxml2::XMLElement const *chunkElem = dataElem->FirstChildElement("chunk");
            // Iterate through all the chunks.
            while (chunkElem) {
                auto chunk = new DataChunkTile(
                        chunkElem->UnsignedAttribute("width"),
                        chunkElem->UnsignedAttribute("height"),
                        chunkElem->IntAttribute("x"),
                        chunkElem->IntAttribute("y")
                        );

                switch (encoding) {
                    case TileLayerEncodingType::TMX_ENCODING_XML:
                        ParseXML(chunkElem, chunk->GetMapTile());
                        break;

                    case TileLayerEncodingType::TMX_ENCODING_BASE64:
                        ParseBase64(chunkElem->GetText(),
                                    chunk->GetWidth(),
                                    chunk->GetHeight(),
                                    chunk->GetMapTile());
                        break;

                    case TileLayerEncodingType::TMX_ENCODING_CSV:
                        ParseCSV(chunkElem->GetText(),
                                 chunk->GetMapTile());
                        break;
                }

                chunks.push_back(chunk);

                chunkElem = chunkElem->NextSiblingElement("chunk");
            }


        } else {
            data_tile_finite_map = new DataChunkTile(width, height);

            // Decode.
            switch (encoding) {
                case TileLayerEncodingType::TMX_ENCODING_XML:
                    ParseXML(dataElem, data_tile_finite_map->GetMapTile());
                    break;

                case TileLayerEncodingType::TMX_ENCODING_BASE64:
                    ParseBase64(dataElem->GetText(),
                                data_tile_finite_map->GetWidth(),
                                data_tile_finite_map->GetHeight(),
                                data_tile_finite_map->GetMapTile());
                    break;

                case TileLayerEncodingType::TMX_ENCODING_CSV:
                    ParseCSV(dataElem->GetText(),
                             data_tile_finite_map->GetMapTile());
                    break;
            }
        }

    }

    void TileLayer::ParseXML(tinyxml2::XMLNode const *dataNode, tinytmx::MapTile *m_tile_map,
                             std::string const &firstChildElement) {
        tinyxml2::XMLNode const *tileNode = dataNode->FirstChildElement(firstChildElement.c_str());
        int tileCount = 0;
        while (tileNode) {
            tinyxml2::XMLElement const *tileElem = tileNode->ToElement();

            unsigned gid = 0;

            // Read the Global-ID of the tile.
            char const *gidText = tileElem->Attribute("gid");

            // Convert to an unsigned.
            //sscanf(gidText, "%u", &gid);
            gid = std::strtoul(gidText, nullptr, 10);

            // Find the tileset index.
            int const tilesetIndex = map->FindTilesetIndex(gid);
            if (tilesetIndex != -1) {
                // If valid, set up the map tile with the tileset.
                tinytmx::Tileset const *tileset = map->GetTileset(tilesetIndex);
                m_tile_map[tileCount] = MapTile(gid, tileset->GetFirstGid(), tilesetIndex);
            } else {
                // Otherwise, make it null.
                m_tile_map[tileCount] = MapTile(gid, 0, -1);
            }

            tileNode = tileNode->NextSiblingElement(firstChildElement.c_str());
            tileCount++;
        }
    }

    void TileLayer::ParseBase64(std::string const &innerText, uint32_t m_width, uint32_t m_height, tinytmx::MapTile *m_tile_map) {
        std::string testText = innerText;
        Util::Trim(testText);

        std::string const &text = Util::DecodeBase64(testText);

        // Temporary array of gids to be converted to map tiles.
        unsigned *out = nullptr;

        if (compression == TileLayerCompressionType::TMX_COMPRESSION_ZLIB) {
            // Use zlib to uncompress the tile layer into the temporary array of tiles.
            uLongf outlen = m_width * m_height * 4;
            out = (unsigned *) malloc(outlen);
            uncompress((Bytef *) out, &outlen, (const Bytef *) text.c_str(), text.size());

        } else if (compression == TileLayerCompressionType::TMX_COMPRESSION_ZSTD) {
            // Use zstd to uncompress the tile layer into the temporary array of tiles.
            uLongf outlen = m_width * m_height * 4;
            out = (unsigned *) malloc(outlen);
            ZSTD_decompress(out, outlen, text.c_str(), text.size());

        } else if (compression == TileLayerCompressionType::TMX_COMPRESSION_GZIP) {
            // Use the utility class for decompressing (which uses zlib)
            out = (unsigned *) Util::DecompressGZIP(text.c_str(), text.size(), m_width * m_height * 4);
        } else {
            out = (unsigned *) malloc(text.size());

            // Copy every gid into the temporary array since
            // the decoded string is an array of 32-bit integers.
            memcpy(out, text.c_str(), text.size());
        }

        // Convert the gids to map tiles.
        for (int x = 0; x < m_height; x++) {
            for (int y = 0; y < m_width; y++) {
                unsigned gid = out[x * m_height + y];

                // Find the tileset index.
                int const tilesetIndex = map->FindTilesetIndex(gid);
                if (tilesetIndex != -1) {
                    // If valid, set up the map tile with the tileset.
                    tinytmx::Tileset const *tileset = map->GetTileset(tilesetIndex);
                    m_tile_map[x * m_height + y] = MapTile(gid, tileset->GetFirstGid(), tilesetIndex);
                } else {
                    // Otherwise, make it null.
                    m_tile_map[x * m_height + y] = MapTile(gid, 0, -1);
                }
            }
        }

        // Free the temporary array from memory.
        free(out);
    }

    void TileLayer::ParseCSV(std::string const &innerText, tinytmx::MapTile *m_tile_map) {
        // Duplicate the string for use with C stdio.
        char *csv = strdup(innerText.c_str());

        // Iterate through every token of ';' in the CSV string.
        char *pch = std::strtok(csv, ",");
        int tileCount = 0;

        while (pch) {
            unsigned gid;

            // Convert to an unsigned.
            //sscanf(pch, "%u", &gid);
            gid = std::strtoul(pch, nullptr, 10);

            // Find the tileset index.
            int const tilesetIndex = map->FindTilesetIndex(gid);
            if (tilesetIndex != -1) {
                // If valid, set up the map tile with the tileset.
                tinytmx::Tileset const *tileset = map->GetTileset(tilesetIndex);
                m_tile_map[tileCount] = MapTile(gid, tileset->GetFirstGid(), tilesetIndex);
            } else {
                // Otherwise, make it null.
                m_tile_map[tileCount] = MapTile(gid, 0, -1);
            }

            pch = std::strtok(nullptr, ",");
            tileCount++;
        }

        free(csv);
    }


}
