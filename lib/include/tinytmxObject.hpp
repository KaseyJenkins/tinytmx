#ifndef TINYTMX_TINYTMXOBJECT_HPP
#define TINYTMX_TINYTMXOBJECT_HPP


#include <string>

#include "tinytmxPropertySet.hpp"
#include "tinytmxVector2.hpp"

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx
{
    class Ellipse;
    class PolyObject;
    class Text;
    class Map;
    class Tileset;
    class MapTile;


    enum class ObjectType {
        TMX_OT_UNDEFINED,
        TMX_OT_TILE,
        TMX_OT_ELLIPSE,
        TMX_OT_POINT,
        TMX_OT_POLYGON,
        TMX_OT_POLYLINE,
        TMX_OT_TEXT,
        TMX_OT_RECTANGLE
    };


    //-------------------------------------------------------------------------
    /// A class for representing a single object from the objectgroup.
    //-------------------------------------------------------------------------
    class Object
    {
    public:
        Object();
        ~Object();

        /// Parse an object node.
        void Parse(const tinyxml2::XMLNode *objectNode, const tinytmx::Map *_map = nullptr);

        /// Get the name of the object.
        const std::string &GetName() const { return name; }

        /// Get the type of the object. An arbitrary string. (defaults to "")
        const std::string &GetType() const { return type; }

        /// Get the left side of the object, in pixels.
        float GetX() const { return x; }

        /// Get the top side of the object, in pixels.
        float GetY() const { return y; }

        /// Get the width of the object, in pixels.
        float GetWidth() const { return width; }

        /// Get the height of the object, in pixels.
        float GetHeight() const { return height; }

        /// Get the rotation of the object, in degrees.
        float GetRot() const { return rotation; }

        /// Get the Global ID of the tile associated with this object.
        /// This is a raw value, hence GetTile->gid should be used instead.
        unsigned GetGid() const { return gid; }

        /// Get the ID of this object.
        int GetID() const { return id; }

        /// Get the visibility of the object.
        bool IsVisible() const { return visible; }

        /// Get the object type. (Rectangle, Ellipse, Point... etc)
        const tinytmx::ObjectType& GetObjectType() const { return objectType; }

        /// Get the Template.
        const std::string &GetTemplate() const { return t_template; }

        /// Get the Ellipse.
        const tinytmx::Ellipse *GetEllipse() const { return ellipse; }

        /// Get the Point.
        const tinytmx::Vector2f *GetPoint() const { return point; }

        /// Get the Polygon.
        const tinytmx::PolyObject *GetPolygon() const { return polygon; }

        /// Get the Polyline.
        const tinytmx::PolyObject *GetPolyline() const { return polyline; }

        /// Get the Text.
        const tinytmx::Text *GetText() const { return text; }

        /// Get the property set.
        const tinytmx::PropertySet &GetProperties() const { return properties; }

        /// Get the tile for a tile object.
        const tinytmx::MapTile *GetTile() const { return mapTile; }

        /// Get the templated tileset.
        const tinytmx::Tileset *GetTileset() const { return tileset; }

        /// Is it a template? -- get the bool value.
        bool IsTemplate() const { return isTemplate; }

    private:
        std::string name;
        std::string type;

        float x;
        float y;
        float width;
        float height;
        unsigned gid;

        int id;

        float rotation;
        bool visible;

        std::string t_template;

        tinytmx::Ellipse *ellipse;
        tinytmx::Vector2f *point;
        tinytmx::PolyObject *polygon;
        tinytmx::PolyObject *polyline;
        tinytmx::Text *text;

        tinytmx::MapTile *mapTile;

        tinytmx::PropertySet properties;


        /// @cond INTERNAL

        ObjectType objectType;
        void setObjectType();

        void ParseObject(const tinyxml2::XMLNode *objectNode, const tinytmx::Map *_map = nullptr);

        bool isTemplate;

        /// @endcond

        tinytmx::Tileset* tileset; // If a templated object uses a templated tileset...

    };
}

#endif //TINYTMX_TINYTMXOBJECT_HPP

