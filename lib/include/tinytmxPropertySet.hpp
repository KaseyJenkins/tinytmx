#ifndef TINYTMX_TINYTMXPROPERTYSET_HPP
#define TINYTMX_TINYTMXPROPERTYSET_HPP

#include <unordered_map>
#include <map>
#include <string>

#include "tinytmxProperty.hpp"

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {
    class Property;

    //-----------------------------------------------------------------------------
    /// This class contains a map of properties.
    //-----------------------------------------------------------------------------
    class PropertySet {
    public:
        PropertySet();

        ~PropertySet();

        /// Parse a node containing all the property nodes.
        void Parse(const tinyxml2::XMLNode *propertiesNode);

        /// Get a int property.
        int GetIntProperty(const std::string &name, int defaultValue = 0) const;

        /// Get a float property.
        float GetFloatProperty(const std::string &name, float defaultValue = 0.0f) const;

        /// Get a string property.
        std::string GetStringProperty(const std::string &name, std::string defaultValue = "") const;

        /// Get a bool property.
        bool GetBoolProperty(const std::string &name, bool defaultValue = false) const;

        /// Get a color property.
        tinytmx::Color GetColorProperty(const std::string &name, tinytmx::Color defaultValue = tinytmx::Color()) const;

        /// Get an object property.
        int GetObjectProperty(const std::string &name, int defaultValue = 0) const;

        /// Returns the amount of properties.
        auto GetSize() const { return properties.size(); }

        /// Checks if a property exists in the set.
        bool HasProperty(const std::string &name) const;

        /// Returns the unordered map of properties.
        const std::unordered_map<std::string, Property> &GetPropertyMap() const { return properties; }

        /// Returns the STL map of the properties.
        /// Deprecated, please use GetPropertyMap() instead.
        //std::map<std::string, std::string> GetList() const;

        /// Returns whether there are no properties.
        bool Empty() const { return properties.empty(); }

    private:
        std::unordered_map<std::string, Property> properties;
    };
}

#endif //TINYTMX_TINYTMXPROPERTYSET_HPP

