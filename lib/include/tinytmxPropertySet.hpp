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
        PropertySet(PropertySet const &) = delete;
        // Delete move constructor.
        PropertySet(PropertySet &&) = delete;
        // Delete copy assignment operator.
        PropertySet &operator=(PropertySet const &) = delete;
        // Delete move assignment operator.
        PropertySet &operator=(PropertySet &&) = delete;


        explicit PropertySet(tinyxml2::XMLNode const *);
        ~PropertySet();

        /// Parse a node containing all the property nodes.
//        void Parse(tinyxml2::XMLNode const *propertiesNode);

        /// Get an int Property by its name.
        int GetIntProperty(std::string const &name, int defaultValue = 0) const;

        /// Get a float Property by its name.
        float GetFloatProperty(std::string const &name, float defaultValue = 0.0f) const;

        /// Get a string Property by its name.
        std::string const &GetStringProperty(std::string const &name, std::string const &defaultValue = "") const;

        /// Get a bool Property by its name.
        bool GetBoolProperty(std::string const &name, bool defaultValue = false) const;

        /// Get a color Property by its name.
        tinytmx::Color GetColorProperty(std::string const &name, tinytmx::Color defaultValue = tinytmx::Color()) const;

        /// Get an object Property by its name.
        int GetObjectProperty(std::string const &name, int defaultValue = 0) const;

        /// Get a File Property by its name.
        std::string const &GetFileProperty(std::string const &name, std::string const &defaultValue = "") const;

        /// Returns the number of properties.
        auto GetSize() const { return properties.size(); }

        /// Checks if a Property with a certain name exists in the set.
        bool HasProperty(std::string const &name) const;

        /// Returns the unordered map of properties.
        std::unordered_map<std::string, Property> const &GetPropertyMap() const { return properties; }

        /// Are there any properties at all? - returns 'true' if empty.
        bool Empty() const { return properties.empty(); }

    private:
        std::unordered_map<std::string, Property> properties;

        void Parse(tinyxml2::XMLNode const *propertiesNode);
    };
}

#endif //TINYTMX_TINYTMXPROPERTYSET_HPP

