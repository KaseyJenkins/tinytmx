#include "tinyxml2.h"
#include <cassert> //RJCB
#include <iostream>

#include "tinytmxTileset.hpp"
#include "tinytmxTileOffset.hpp"
#include "tinytmxGrid.hpp"
//#include "tinytmxTerrainArray.hpp" // Deprecated
//#include "tinytmxTerrain.hpp"
#include "tinytmxImage.hpp"
#include "tinytmxTile.hpp"
#include "tinytmxMap.hpp"
#include "tinytmxTransformations.hpp"
#include "tinytmxWangSetArray.hpp"
#include "tinytmxWangSet.hpp"


namespace tinytmx {
    Tileset::Tileset()
            : first_gid(0), tile_width(0), tile_height(0), spacing(0), margin(0), tile_count(0), columns(0),
              object_alignment(tinytmx::ObjectAlignment::TMX_OA_UNSPECIFIED), grid(nullptr), tileOffset(nullptr), image(nullptr),
              transformations(nullptr), properties(nullptr) {
    }

    Tileset::~Tileset() {

        // Delete the properties if any.
        if (properties != nullptr) {
            delete properties;
            properties = nullptr;
        }

        // Delete the grid from memory if allocated.
        if (grid != nullptr) {
            delete grid;
            grid = nullptr;
        }

        // Delete the tile offset from memory if allocated.
        if (tileOffset != nullptr) {
            delete tileOffset;
            tileOffset = nullptr;
        }

        // Delete the image from memory if allocated.
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }

        if (transformations != nullptr) {
            delete transformations;
            transformations = nullptr;
        }

        // Deprecated
        // Iterate through all of the terrain types in the tileset and delete each of them.
//        for (auto terrainType: terrainTypes) {
//            delete terrainType;
//            terrainType = nullptr;
//        }

        // Iterate through all of the tiles in the tileset and delete each of them.
        for (auto tile: tiles) {
            delete tile;
            tile = nullptr;
        }

        // Iterate through all of the wangsets in the wangset and delete each of them.
        for (auto wangset : wangsets) {
            delete wangset;
            wangset = nullptr;
        }

    }

    void Tileset::Parse(tinyxml2::XMLNode const *tilesetNode, std::string const &file_path, tinytmx::Map const *_map) {
        tinyxml2::XMLElement const *tilesetElem = tilesetNode->ToElement();

        // Read all the attributes into local variables.

        // The firstgid and source attribute are kept in the TMX map,
        // since they are map specific.
        first_gid = tilesetElem->IntAttribute("firstgid");

        // If the <tileset> node contains a 'source' tag,
        // the tileset config should be loaded from an external
        // TSX (Tile Set XML) file. That file has the same structure
        // as the <tileset> element in the TMX map.
        char const *source_name = tilesetElem->Attribute("source");
        tinyxml2::XMLDocument tileset_doc;
        if (source_name) {
            std::string const &fileName = file_path + source_name;
            tileset_doc.LoadFile(fileName.c_str());

            if (tileset_doc.ErrorID() != 0) {
                fprintf(stderr, "failed to load tileset file '%s'\n", fileName.c_str());
                return;
            }

            // Update node and element references to the new node
            tilesetNode = tileset_doc.FirstChildElement("tileset");
            assert(tilesetNode); //RJCB

            tilesetElem = tilesetNode->ToElement();
        }

        name = tilesetElem->Attribute("name");
        tile_width = tilesetElem->UnsignedAttribute("tilewidth");
        tile_height = tilesetElem->UnsignedAttribute("tileheight");
        spacing = tilesetElem->UnsignedAttribute("spacing");
        margin = tilesetElem->UnsignedAttribute("margin");
        tile_count = tilesetElem->UnsignedAttribute("tilecount");
        columns = tilesetElem->UnsignedAttribute("columns");

        // Read Object Alignment
        if (tilesetElem->Attribute("objectalignment")) {
            std::string const &objectAlignment = tilesetElem->Attribute("objectalignment");
            if (objectAlignment == "topleft") {
                object_alignment = tinytmx::ObjectAlignment::TMX_OA_TOPLEFT;
            } else if (objectAlignment == "top") {
                object_alignment = tinytmx::ObjectAlignment::TMX_OA_TOP;
            } else if (objectAlignment == "topright") {
                object_alignment = tinytmx::ObjectAlignment::TMX_OA_TOPRIGHT;
            } else if (objectAlignment == "left") {
                object_alignment = tinytmx::ObjectAlignment::TMX_OA_LEFT;
            } else if (objectAlignment == "center") {
                object_alignment = tinytmx::ObjectAlignment::TMX_OA_CENTER;
            } else if (objectAlignment == "right") {
                object_alignment = tinytmx::ObjectAlignment::TMX_OA_RIGHT;
            } else if (objectAlignment == "bottomleft") {
                object_alignment = tinytmx::ObjectAlignment::TMX_OA_BOTTOMLEFT;
            } else if (objectAlignment == "bottom") {
                object_alignment = tinytmx::ObjectAlignment::TMX_OA_BOTTOM;
            } else if (objectAlignment == "bottomright") {
                object_alignment = tinytmx::ObjectAlignment::TMX_OA_BOTTOMRIGHT;
            }
        }

        // Parse the tile offset, if it exists.
        tinyxml2::XMLNode const *tileOffsetNode = tilesetNode->FirstChildElement("tileoffset");
        if (tileOffsetNode) {
            tileOffset = new TileOffset(tileOffsetNode);
        }

        // Parse the terrain types if any. // Deprecated
//        tinyxml2::XMLNode const *terrainTypesNode = tilesetNode->FirstChildElement("terraintypes");
//        if (terrainTypesNode) {
//            TerrainArray terrainArray;
//            terrainArray.Parse(&terrainTypes, terrainTypesNode);
//        }

        // Parse the image.
        tinyxml2::XMLNode const *imageNode = tilesetNode->FirstChildElement("image");
        if (imageNode) {
            image = new Image(imageNode);
        }

        // Parse the grid.
        tinyxml2::XMLNode const *gridNode = tilesetNode->FirstChildElement("grid");
        if (gridNode) {
            grid = new Grid(gridNode);
        }

        // Parse the transformations.
        tinyxml2::XMLNode const *transformationsNode = tilesetNode->FirstChildElement("transformations");
        if (transformationsNode) {
            transformations = new Transformations(transformationsNode);
        }

        // Iterate through all of the tile elements and parse each.
        tinyxml2::XMLNode const *tileNode = tilesetNode->FirstChildElement("tile");
        for (int tId = 0; tileNode; ++tId) {
            auto tile = new Tile(tId);
            tile->Parse(tileNode, _map);
            tiles.push_back(tile);

            tileNode = tileNode->NextSiblingElement("tile");
        }

        // Iterate through all of the wangsets if any.
        tinyxml2::XMLNode const *wangsetsNode = tilesetNode->FirstChildElement("wangsets");
        if (wangsetsNode) {
            WangSetArray wangSetArray; // FIXME on the stack or heap?
            wangSetArray.Parse(&wangsets, wangsetsNode);
        }

        // Parse the properties if any.
        tinyxml2::XMLNode const *propertiesNode = tilesetNode->FirstChildElement("properties");
        if (propertiesNode) {
            properties = new PropertySet(propertiesNode);
        }
    }

    Tile const *Tileset::GetTile(int index) const {
        for (auto tile: tiles) {
            if (tile->GetId() == index)
                return tile;
        }
        return nullptr;
    }
}
