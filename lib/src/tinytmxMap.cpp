#include "tinyxml2.h"

#include "tinytmxMap.hpp"
#include "tinytmxTileset.hpp"
#include "tinytmxLayer.hpp"
#include "tinytmxTileLayer.hpp"
#include "tinytmxObjectGroup.hpp"
#include "tinytmxImageLayer.hpp"
#include "tinytmxGroupLayer.hpp"


namespace tinytmx {
    Map::Map()
            : has_error(false),
              is_infinite(false),
              error_code(0),
              orientation(MapOrientation::TMX_MO_ORTHOGONAL),
              render_order(MapRenderOrder::TMX_RIGHT_DOWN),
              stagger_axis(MapStaggerAxis::TMX_SA_NONE),
              stagger_index(MapStaggerIndex::TMX_SI_NONE),
              version(0.0f),
              background_color(),
              width(0),
              height(0),
              tile_width(0),
              tile_height(0),
              next_layer_id(0),
              next_object_id(0),
              hexside_length(0),
              compression_level(-1),
              properties(nullptr) {}

    Map::~Map() {

        // Delete 'properties'
        if (properties != nullptr) {
            delete properties;
            properties = nullptr;
        }

        // Iterate through all of the tilesets and delete each of them.
        for (auto tileset: tilesets) {
            delete tileset;
            tileset = nullptr;
        }

        // Iterate through all of the group layers and delete each of them.
        for (auto grouplayer: group_layers) {
            delete grouplayer;
            grouplayer = nullptr;
        }

        // Iterate through all of the object groups and delete each of them.
        for (auto objectGroup: object_groups) {
            delete objectGroup;
            objectGroup = nullptr;
        }

        // Iterate through all of the image layers and delete each of them.
        for (auto layer: image_layers) {
            delete layer;
            layer = nullptr;
        }

        // Iterate through all of the tile layers and delete each of them.
        for (auto layer: tile_layers) {
            if (layer) {
                delete layer;
                layer = nullptr;
            }
        }
    }

    void Map::ParseFile(std::string const &fileName) {
        file_name = fileName;

        auto const lastSlash = fileName.find_last_of('/');

        // Get the directory of the file using substring.
        if (lastSlash != std::string::npos) {
            file_path = fileName.substr(0, lastSlash + 1);
        } else {
            file_path = "";
        }

        // Create a tiny xml document and use it to parse the text.
        tinyxml2::XMLDocument doc;
        doc.LoadFile(fileName.c_str());

        // Check for parsing errors.
        if (doc.Error()) {
            has_error = true;
            error_code = static_cast<uint8_t>(MapError::TMX_PARSING_ERROR);
            error_text = doc.ErrorStr();
            return;
        }

        tinyxml2::XMLNode const *mapNode = doc.FirstChildElement("map");
        Parse(mapNode);
    }

    void Map::ParseText(std::string const &text) {
        // Create a tinyxml2 document and use it to parse the text.
        tinyxml2::XMLDocument doc;
        doc.Parse(text.c_str());

        // Check for parsing errors.
        if (doc.Error()) {
            has_error = true;
            error_code = static_cast<uint8_t>(MapError::TMX_PARSING_ERROR);
            error_text = doc.ErrorStr();
            return;
        }

        tinyxml2::XMLNode const *mapNode = doc.FirstChildElement("map");
        Parse(mapNode);
    }

    int Map::FindTilesetIndex(unsigned gid) const {
        gid &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);

        for (int i = tilesets.size() - 1; i > -1; --i) {
            // If the gid is beyond the tileset gid return its index.
            if (gid >= tilesets[i]->GetFirstGid()) {
                return i;
            }
        }
        return -1;
    }

    Tileset const *Map::FindTileset(unsigned gid) const {
        for (int i = tilesets.size() - 1; i > -1; --i) {
            // If the gid is beyond the tileset gid return the tileset.
            if (gid >= tilesets[i]->GetFirstGid()) {
                return tilesets[i];
            }
        }
        return nullptr;
    }

    void Map::Parse(tinyxml2::XMLNode const *mapNode) {
        tinyxml2::XMLElement const *mapElem = mapNode->ToElement();

        // Read the map attributes.
        version = mapElem->FloatAttribute("version");
        if (mapElem->Attribute("tiledversion")) {
            tiled_version = mapElem->Attribute("tiledversion");
        }
        width = mapElem->UnsignedAttribute("width");
        height = mapElem->UnsignedAttribute("height");
        tile_width = mapElem->UnsignedAttribute("tilewidth");
        tile_height = mapElem->UnsignedAttribute("tileheight");
        next_layer_id = mapElem->IntAttribute("nextlayerid");
        next_object_id = mapElem->IntAttribute("nextobjectid");
        is_infinite = mapElem->BoolAttribute("infinite");

        mapElem->QueryIntAttribute("compressionlevel", &compression_level);


        if (mapElem->Attribute("backgroundcolor")) {
            background_color = tinytmx::Color(mapElem->Attribute("backgroundcolor"));
        }

        // Read the orientation
        std::string_view orientationCString = mapElem->Attribute("orientation");

        if (orientationCString == "orthogonal") {
            orientation = MapOrientation::TMX_MO_ORTHOGONAL;
        } else if (orientationCString == "isometric") {
            orientation = MapOrientation::TMX_MO_ISOMETRIC;
        } else if (orientationCString == "staggered") {
            orientation = MapOrientation::TMX_MO_STAGGERED;
        } else if (orientationCString == "hexagonal") {
            orientation = MapOrientation::TMX_MO_HEXAGONAL;
        }


        // Read the render order
        if (mapElem->Attribute("renderorder")) {
            std::string_view renderOrderCString = mapElem->Attribute("renderorder");

            if (renderOrderCString == "right-down") {
                render_order = MapRenderOrder::TMX_RIGHT_DOWN;
            } else if (renderOrderCString == "right-up") {
                render_order = MapRenderOrder::TMX_RIGHT_UP;
            } else if (renderOrderCString == "left-down") {
                render_order = MapRenderOrder::TMX_LEFT_DOWN;
            } else if (renderOrderCString == "left-up") {
                render_order = MapRenderOrder::TMX_LEFT_UP;
            }
        }

        // Read the stagger axis
        if (mapElem->Attribute("staggeraxis")) {
            std::string_view staggerAxisCString = mapElem->Attribute("staggeraxis");

            if (staggerAxisCString == "x") {
                stagger_axis = MapStaggerAxis::TMX_SA_X;
            } else if (staggerAxisCString == "y") {
                stagger_axis = MapStaggerAxis::TMX_SA_Y;
            }
        }

        // Read the stagger index
        if (mapElem->Attribute("staggerindex")) {
            std::string_view staggerIndexCString = mapElem->Attribute("staggerindex");

            if (staggerIndexCString == "even") {
                stagger_index = MapStaggerIndex::TMX_SI_EVEN;
            } else if (staggerIndexCString == "odd") {
                stagger_index = MapStaggerIndex::TMX_SI_ODD;
            }
        }

        // read the hexside length
        mapElem->QueryUnsignedAttribute("hexsidelength", &hexside_length);

        // read all other attributes
        for (tinyxml2::XMLNode const *node = mapElem->FirstChild(); node != nullptr; node = node->NextSibling()) {
            // Read the map properties.
            if (std::strcmp(node->Value(), "properties") == 0) {
                properties = new PropertySet(node);
            }

            // Iterate through all of the tileset elements.
            if (std::strcmp(node->Value(), "tileset") == 0) {
                // Allocate a new tileset and parse it.
                auto tileset = new Tileset();
                tileset->Parse(node, file_path, this);

                // Add the tileset to the list.
                tilesets.push_back(tileset);
            }

            // Iterate through all of the "layer" (tile layer) elements.
            if (std::strcmp(node->Value(), "layer") == 0) {
                // Allocate a new tile layer and parse it.
                auto tileLayer = new TileLayer(this);
                tileLayer->Parse(node);

                // Add the tile layer to the lists.
                tile_layers.push_back(tileLayer);
                layers.push_back(tileLayer);
            }

            // Iterate through all of the "imagelayer" (image layer) elements.
            if (std::strcmp(node->Value(), "imagelayer") == 0) {
                // Allocate a new image layer and parse it.
                auto imageLayer = new ImageLayer(this);
                imageLayer->Parse(node);

                // Add the image layer to the lists.
                image_layers.push_back(imageLayer);
                layers.push_back(imageLayer);
            }

            // Iterate through all of the "objectgroup" (object layer) elements.
            if (std::strcmp(node->Value(), "objectgroup") == 0) {
                // Allocate a new object group and parse it.
                auto objectGroup = new ObjectGroup(this);
                objectGroup->Parse(node);

                // Add the object group to the lists.
                object_groups.push_back(objectGroup);
                layers.push_back(objectGroup);
            }

            if (std::strcmp(node->Value(), "group") == 0) {
                auto groupLayer = new GroupLayer(this);
                groupLayer->Parse(node);

                // Add the group layer to the lists.
                group_layers.push_back(groupLayer);
                layers.push_back(groupLayer);
            }
        }
    }
}
