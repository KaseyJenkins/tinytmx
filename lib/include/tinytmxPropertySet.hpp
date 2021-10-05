#ifndef TINYTMX_TINYTMXPROPERTYSET_HPP
#define TINYTMX_TINYTMXPROPERTYSET_HPP

#include <unordered_map>
#include <string>

#include "tinytmxProperty.hpp"

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {
    class Property;

    class PropertySet {
    public:

        // Delete copy constructor.
        PropertySet(const PropertySet &) = delete;
        // Delete move constructor.
        PropertySet(PropertySet &&) = delete;
        // Delete copy assignment operator.
        PropertySet &operator=(const PropertySet &) = delete;
        // Delete move assignment operator.
        PropertySet &operator=(PropertySet &&) = delete;


        PropertySet();
        ~PropertySet();

        /// Parse a node containing all the property nodes.
        void Parse(const tinyxml2::XMLNode *propertiesNode);

        /// Get an int Property by its name.
        int GetIntProperty(const std::string &name, int defaultValue = 0) const;

        /// Get a float Property by its name.
        float GetFloatProperty(const std::string &name, float defaultValue = 0.0f) const;

        /// Get a string Property by its name.
        const std::string& GetStringProperty(const std::string &name, const std::string& defaultValue = "") const;

        /// Get a bool Property by its name.
        bool GetBoolProperty(const std::string &name, bool defaultValue = false) const;

        /// Get a color Property by its name.
        tinytmx::Color GetColorProperty(const std::string &name, tinytmx::Color defaultValue = tinytmx::Color()) const;

        /// Get an object Property by its name.
        int GetObjectProperty(const std::string &name, int defaultValue = 0) const;

        /// Get a File Property by its name.
        const std::string& GetFileProperty(const std::string& name, const std::string& defaultValue = "") const;

        /// Returns the number of properties.
        auto GetSize() const { return properties.size(); }

        /// Checks if a Property with a certain name exists in the set.
        bool HasProperty(const std::string &name) const;

        /// Returns the unordered map of properties.
        const std::unordered_map<std::string, Property> &GetPropertyMap() const { return properties; }

        /// Are there any properties at all? - returns 'true' if empty.
        bool Empty() const { return properties.empty(); }

    private:
        std::unordered_map<std::string, Property> properties;
    };
}

#endif //TINYTMX_TINYTMXPROPERTYSET_HPP

