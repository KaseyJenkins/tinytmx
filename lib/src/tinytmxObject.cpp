#include "tinyxml2.h"

#include "tinytmxObject.hpp"
#include "tinytmxPolyObject.hpp"
#include "tinytmxEllipse.hpp"
#include "tinytmxText.hpp"
#include "tinytmxTileset.hpp"
#include "tinytmxPropertySet.hpp"

#include <iostream>
#include "tinytmxImage.hpp"
#include "tinytmxMapTile.hpp"

#include "tinytmxVector2.hpp"
#include "tinytmxMap.hpp"

namespace tinytmx {
    Object::Object()
            : isTemplate(false),
              objectType(tinytmx::ObjectType::TMX_OT_UNDEFINED),
              visible(true),
              id(0),
              x(0),
              y(0),
              width(0),
              height(0),
              rotation(0.0f),
              gid(0),
              ellipse(nullptr), point(nullptr), polygon(nullptr), polyline(nullptr), text(nullptr),
              mapTile(nullptr), properties(nullptr), tileset(nullptr) {}

    Object::~Object() {
        if (properties != nullptr) {
            delete properties;
            properties = nullptr;
        }

        if (ellipse != nullptr) {
            delete ellipse;
            ellipse = nullptr;
        }
        if (point != nullptr) {
            delete point;
            point = nullptr;
        }
        if (polygon != nullptr) {
            delete polygon;
            polygon = nullptr;
        }
        if (polyline != nullptr) {
            delete polyline;
            polyline = nullptr;
        }
        if (text != nullptr) {
            delete text;
            text = nullptr;
        }
        if (tileset != nullptr) {
            delete tileset;
            tileset = nullptr;
        }
        if (mapTile != nullptr) {
            delete mapTile;
            mapTile = nullptr;
        }

    }

    void Object::Parse(tinyxml2::XMLNode const *objectNode, tinytmx::Map const *_map) {
        tinyxml2::XMLElement const *objectElem = objectNode->ToElement();

        if (objectElem->Attribute("template")) {
            isTemplate = true;
            t_template = objectElem->Attribute("template");
            std::string const &file_path = _map->GetFilepath();
            std::string const fileName = file_path + t_template;

            // Let's parse the template.
            tinyxml2::XMLDocument template_doc;
            template_doc.LoadFile(fileName.c_str());

            tinyxml2::XMLNode const *mapNode = template_doc.FirstChildElement("template");

            for (tinyxml2::XMLNode const *node = mapNode->FirstChild(); node != nullptr; node = node->NextSibling()) {
                // Read the properties. Can contain at most one: <tileset>, <object>

                if (std::strcmp(node->Value(), "tileset") == 0) {
                    tileset = new Tileset();
                    tileset->Parse(node, file_path, _map);
                }

                if (std::strcmp(node->Value(), "object") == 0) {
                    ParseObject(node, _map); // go through a template object
                    ParseObject(objectNode, _map); // go through a normal object
                    setObjectType();
                }
            }

        } else {
            // Parse a non-templated object.
            ParseObject(objectNode, _map);
            // Set ObjectType
            setObjectType();
        }

    }

    void Object::setObjectType() {
        if (objectType == tinytmx::ObjectType::TMX_OT_UNDEFINED) {
            if (gid > 0) {
                objectType = tinytmx::ObjectType::TMX_OT_TILE;
            } else if (ellipse != nullptr) {
                objectType = tinytmx::ObjectType::TMX_OT_ELLIPSE;
            } else if (point != nullptr) {
                objectType = tinytmx::ObjectType::TMX_OT_POINT;
            } else if (polygon != nullptr) {
                objectType = tinytmx::ObjectType::TMX_OT_POLYGON;
            } else if (polyline != nullptr) {
                objectType = tinytmx::ObjectType::TMX_OT_POLYLINE;
            } else if (text != nullptr) {
                objectType = tinytmx::ObjectType::TMX_OT_TEXT;
            } else {
                objectType = tinytmx::ObjectType::TMX_OT_RECTANGLE;
            }
        }
    }

    void Object::ParseObject(tinyxml2::XMLNode const *objectNode, tinytmx::Map const *_map) {
        tinyxml2::XMLElement const *objectElem = objectNode->ToElement();

        // Read the attributes of the object.

        if (objectElem->UnsignedAttribute("gid")) {

            gid = objectElem->UnsignedAttribute("gid");

            // Find the tileset index.
            int const tilesetIndex = _map->FindTilesetIndex(gid);
            if (tilesetIndex != -1) {
                // If valid, set up the object tile with the tileset.
                tinytmx::Tileset const *_tileset = _map->GetTileset(tilesetIndex);
                delete mapTile;
                mapTile = new MapTile(gid, _tileset->GetFirstGid(), tilesetIndex);
            } else {
                // Otherwise, make it null.
                mapTile = new MapTile(gid, 0, -1);
            }

        }

        if (objectElem->Attribute("name")) {
            name = objectElem->Attribute("name");
        }

        if (objectElem->Attribute("type")) {
            type = objectElem->Attribute("type");
        }

        if (objectElem->Attribute("class")) {
            class_ = objectElem->Attribute("class");
        }

        objectElem->QueryIntAttribute("id", &id);
        objectElem->QueryFloatAttribute("x", &x);
        objectElem->QueryFloatAttribute("y", &y);
        objectElem->QueryFloatAttribute("width", &width);
        objectElem->QueryFloatAttribute("height", &height);

        objectElem->QueryFloatAttribute("rotation", &rotation);
        objectElem->QueryBoolAttribute("visible", &visible);

        // Read the ellipse of the object if there is any.
        tinyxml2::XMLNode const *ellipseNode = objectNode->FirstChildElement("ellipse");
        if (ellipseNode) {
            delete ellipse;
            ellipse = new Ellipse(x, y, width, height);
        }

        // Read the point of the object if there is any.
        tinyxml2::XMLNode const *pointNode = objectNode->FirstChildElement("point");
        if (pointNode) {
            delete point;
            point = new Vector2f();
            point->x = x;
            point->y = y;
        }

        // Read the Polygon and Polyline of the object if there are any.
        tinyxml2::XMLNode const *polygonNode = objectNode->FirstChildElement("polygon");
        if (polygonNode) {
            delete polygon;
            polygon = new PolyObject();
            polygon->Parse(polygonNode);
        }
        tinyxml2::XMLNode const *polylineNode = objectNode->FirstChildElement("polyline");
        if (polylineNode) {
            delete polyline;
            polyline = new PolyObject();
            polyline->Parse(polylineNode);
        }
        tinyxml2::XMLNode const *textNode = objectNode->FirstChildElement("text");
        if (textNode) {
            delete text;
            text = new Text();
            text->Parse(textNode);
        }

        // Read the properties of the object.
        tinyxml2::XMLNode const *propertiesNode = objectNode->FirstChildElement("properties");
        if (propertiesNode) {
            delete properties;
            properties = new PropertySet(propertiesNode);
        }

    }
}
