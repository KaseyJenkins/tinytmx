#ifndef TINYTMX_TINYTMXPROPERTY_HPP
#define TINYTMX_TINYTMXPROPERTY_HPP


#include <string>
#include "tinytmxColor.hpp"

namespace tinyxml2 {
    class XMLElement;
}

namespace tinytmx {
    class PropertySet;
}

namespace tinytmx {
    //-------------------------------------------------------------------------
    /// The type of a property.
    //-------------------------------------------------------------------------
    enum class PropertyType {
        /// A string Property (default).
        TMX_PROPERTY_STRING,

        /// A boolean Property.
        TMX_PROPERTY_BOOL,

        /// An integer Property.
        TMX_PROPERTY_INT,

        /// A floating point Property.
        TMX_PROPERTY_FLOAT,

        /// A color Property.
        TMX_PROPERTY_COLOR,

        /// A file Property.
        TMX_PROPERTY_FILE,

        /// An object Property.
        TMX_PROPERTY_OBJECT,

        /// A class Property
        TMX_PROPERTY_CLASS,
    };

    //-------------------------------------------------------------------------
    /// A class to store a (typed) property.
    //-------------------------------------------------------------------------
    class Property {
    public:

        // Delete copy constructor.
        Property(Property const &) = delete;
        // Delete move constructor.
        Property(Property &&) = delete;
        // Delete copy assignment operator.
        Property &operator=(Property const &) = delete;
        // Delete move assignment operator.
        Property &operator=(Property &&) = delete;

        explicit Property(tinyxml2::XMLElement const *);

        ~Property();

        /// Get the type of the Property (default: TMX_PROPERTY_STRING)
        [[nodiscard]] PropertyType GetType() const { return type; }

        /// Check if the Property is of a certain type.
        [[nodiscard]] bool IsOfType(PropertyType propertyType) const { return (GetType() == propertyType); }

        /// Return the value of the Property.
        [[nodiscard]] std::string const &GetValue() const { return value; }

        /// Return whether the value is empty or was not specified.
        [[nodiscard]] bool IsValueEmpty() const { return value.empty(); }

        /// Convert the value to a boolean and return it (or the default value if not a boolean.)
        [[nodiscard]] bool GetBoolValue(bool defaultValue = false) const;

        /// Convert the value to an integer and return it (or the default value if not an integer).
        [[nodiscard]] int GetIntValue(int defaultValue = 0) const;

        /// Convert the value to a float and return it (or the default value if not a float).
        [[nodiscard]] float GetFloatValue(float defaultValue = 0.0f) const;

        /// Convert the value to a color and return it (or the default value if not a color).
        [[nodiscard]] tinytmx::Color GetColorValue(tinytmx::Color defaultValue = tinytmx::Color()) const;

        /// Convert the value into an objectID and return it (or -1 if no object is referenced).
        // Object properties can reference any object on the same map and are stored as an integer
        // (the ID of the referenced object, or 0 when no object is referenced).

        [[nodiscard]] int GetObjectValue(int defaultValue = -1) const;

        /// Get the value to a file and return it (or the default if not a file).
        [[nodiscard]] std::string const &GetFileValue() const { return value; }

        /// Get he name of the custom property type, when applicable (since 1.8).
        [[nodiscard]] std::string const &GetPropertyType() const { return propertytype; }

        /// Get the property set.
        [[nodiscard]] tinytmx::PropertySet const *GetProperties() const { return properties; }

    private:
        PropertyType type;

        tinytmx::PropertySet* properties;

        std::string value;

        std::string propertytype;

        void Parse(tinyxml2::XMLElement const *propertyElem);
    };

}

#endif //TINYTMX_TINYTMXPROPERTY_HPP



