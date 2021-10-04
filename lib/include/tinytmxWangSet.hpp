#ifndef TINYTMX_TINYTMXWANGSET_HPP
#define TINYTMX_TINYTMXWANGSET_HPP

#include <string>
#include <vector>
#include "tinytmxPropertySet.hpp"

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {

    class WangTile;
    class WangColor;


//    enum class WangSetType {
//        TMX_WST_CORNER,
//        TMX_WST_EDGE,
//        TMX_WST_MIXED
//    };

    //-------------------------------------------------------------------------
    /// A class to contain the information about every wangset in the
    /// wangsets element.
    //-------------------------------------------------------------------------
    class WangSet {
    public:

        // Delete copy constructor.
        WangSet(const WangSet &) = delete;
        // Delete move constructor.
        WangSet(WangSet &&) = delete;
        // Delete copy assignment operator.
        WangSet &operator=(const WangSet &) = delete;
        // Delete move assignment operator.
        WangSet &operator=(WangSet &&) = delete;

        WangSet();
        ~WangSet();

        /// Parse a wangset node.
        void Parse(const tinyxml2::XMLNode *wangsetNode);

        /// Get the name of the wangset.
        [[nodiscard]] const std::string &GetName() const { return name; }

        /// Get the tile ID of the tile representing this wangset.
        [[nodiscard]] int GetTileId() const { return tileID; }

//        /// Get the type.
//        tinytmx::WangSetType GetWangSetType() const { return wangSetType; }

        /// Returns the whole wangtile collection.
        [[nodiscard]] const std::vector< tinytmx::WangTile *> &GetWangTiles() const { return wangtiles; }

        /// Returns the whole wangtile collection.
        [[nodiscard]] const std::vector< tinytmx::WangColor *> &GetWangColor() const { return wangcolors; }

        /// Get a set of properties regarding the wangset.
        [[nodiscard]] const tinytmx::PropertySet* GetProperties() const { return properties; }

    private:
        int tileID;
        // WangSetType wangSetType; // FIXME probably not needed as it's not in the TMX Map Format documentation

        tinytmx::PropertySet* properties;

        std::vector<tinytmx::WangTile*> wangtiles;
        std::vector<tinytmx::WangColor*> wangcolors;

        std::string name;
    };
}

#endif //TINYTMX_TINYTMXWANGSET_HPP
