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


//-------------------------------------------------------------------------
/// A class to contain the information about every wangset in the
/// wangsets element.
//-------------------------------------------------------------------------
    class WangSet {
    public:

        // Delete copy constructor.
        WangSet(WangSet const &) = delete;

        // Delete move constructor.
        WangSet(WangSet &&) = delete;

        // Delete copy assignment operator.
        WangSet &operator=(WangSet const &) = delete;

        // Delete move assignment operator.
        WangSet &operator=(WangSet &&) = delete;

        WangSet();

        ~WangSet();

        /// Parse a wangset node.
        void Parse(tinyxml2::XMLNode const *wangsetNode);

        /// Get the name of the wangset.
        [[nodiscard]] std::string const &GetName() const { return name; }

        /// Get the tile ID of the tile representing this wangset.
        [[nodiscard]] int GetTileId() const { return tileID; }

        /// Returns the whole wangtile collection.
        [[nodiscard]] std::vector<tinytmx::WangTile *> const &GetWangTiles() const { return wangtiles; }

        /// Returns the whole wangtile collection.
        [[nodiscard]] std::vector<tinytmx::WangColor *> const &GetWangColor() const { return wangcolors; }

        /// Get a set of properties regarding the wangset.
        [[nodiscard]] tinytmx::PropertySet const *GetProperties() const { return properties; }

    private:
        int tileID;

        tinytmx::PropertySet *properties;

        std::vector<tinytmx::WangTile *> wangtiles;
        std::vector<tinytmx::WangColor *> wangcolors;

        std::string name;
    };
}

#endif //TINYTMX_TINYTMXWANGSET_HPP
