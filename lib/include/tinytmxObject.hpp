#ifndef TINYTMX_TINYTMXOBJECT_HPP
#define TINYTMX_TINYTMXOBJECT_HPP


#include <string>

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
    class PropertySet;


    enum class ObjectType : uint8_t {
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
        // Delete copy constructor.
        Object(const Object &) = delete;
        // Delete move constructor.
        Object(Object &&) = delete;
        // Delete copy assignment operator.
        Object &operator=(const Object &) = delete;
        // Delete move assignment operator.
        Object &operator=(Object &&) = delete;

        Object();
        ~Object();

        /// Parse an object node.
        void Parse(const tinyxml2::XMLNode *objectNode, const tinytmx::Map *_map = nullptr);

        /// Get the name of the object.
        [[nodiscard]] const std::string &GetName() const { return name; }

        /// Get the type of the object. An arbitrary string. (defaults to "")
        [[nodiscard]] const std::string &GetType() const { return type; }

        /// Get the left side of the object, in pixels.
        [[nodiscard]] float GetX() const { return x; }

        /// Get the top side of the object, in pixels.
        [[nodiscard]] float GetY() const { return y; }

        /// Get the width of the object, in pixels.
        [[nodiscard]] float GetWidth() const { return width; }

        /// Get the height of the object, in pixels.
        [[nodiscard]] float GetHeight() const { return height; }

        /// Get the rotation of the object, in degrees.
        [[nodiscard]] float GetRot() const { return rotation; }

        /// Get the Global ID of the tile associated with this object.
        /// This is a raw value, hence GetTile->gid should be used instead.
        [[nodiscard]] unsigned GetGid() const { return gid; }

        /// Get the ID of this object.
        [[nodiscard]] int GetID() const { return id; }

        /// Get the visibility of the object.
        [[nodiscard]] bool IsVisible() const { return visible; }

        /// Get the object type. (Rectangle, Ellipse, Point... etc)
        [[nodiscard]] const tinytmx::ObjectType& GetObjectType() const { return objectType; }

        /// Get the Template.
        [[nodiscard]] const std::string &GetTemplate() const { return t_template; }

        /// Get the Ellipse.
        [[nodiscard]] const tinytmx::Ellipse *GetEllipse() const { return ellipse; }

        /// Get the Point.
        [[nodiscard]] const tinytmx::Vector2f *GetPoint() const { return point; }

        /// Get the Polygon.
        [[nodiscard]] const tinytmx::PolyObject *GetPolygon() const { return polygon; }

        /// Get the Polyline.
        [[nodiscard]] const tinytmx::PolyObject *GetPolyline() const { return polyline; }

        /// Get the Text.
        [[nodiscard]] const tinytmx::Text *GetText() const { return text; }

        /// Get the property set.
        [[nodiscard]] const tinytmx::PropertySet *GetProperties() const { return properties; }

        /// Get the tile for a tile object.
        [[nodiscard]] const tinytmx::MapTile *GetTile() const { return mapTile; }

        /// Get the templated tileset.
        [[nodiscard]] const tinytmx::Tileset *GetTileset() const { return tileset; }

        /// Is it a template? -- get the bool value.
        [[nodiscard]] bool IsTemplate() const { return isTemplate; }

    private:
        /// @cond INTERNAL
        bool isTemplate;
        ObjectType objectType;
        /// @endcond

        bool visible;

        int id;

        float x;
        float y;
        float width;
        float height;
        float rotation;
        unsigned gid;

        /// @cond INTERNAL
        /// @endcond

        tinytmx::Ellipse *ellipse;
        tinytmx::Vector2f *point;
        tinytmx::PolyObject *polygon;
        tinytmx::PolyObject *polyline;
        tinytmx::Text *text;

        tinytmx::MapTile *mapTile;

        tinytmx::PropertySet* properties;

        tinytmx::Tileset* tileset; // If a templated object uses a templated tileset...

        std::string name;
        std::string type;
        std::string t_template;

        /// @cond INTERNAL
        void setObjectType();
        void ParseObject(const tinyxml2::XMLNode *objectNode, const tinytmx::Map *_map = nullptr);
        /// @endcond
    };
}

#endif //TINYTMX_TINYTMXOBJECT_HPP

