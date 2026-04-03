#ifndef TINYTMX_TINYTMXPROPERTY_HPP
#define TINYTMX_TINYTMXPROPERTY_HPP


#include <string>
#include <memory>
#include "tinytmxColor.hpp"

namespace tinyxml2 {
    class XMLElement;
}

namespace tinytmx {
    class PropertySet;

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

        /// A class Property with optional nested member properties.
        TMX_PROPERTY_CLASS
    };

    //-------------------------------------------------------------------------
    /// A class to store a (typed) property.
    //-------------------------------------------------------------------------
    class Property {
    public:
        explicit Property(tinyxml2::XMLElement const *);

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

        /// Get the class name (from propertytype) for class properties.
        [[nodiscard]] std::string const &GetClassName() const { return class_name; }

        /// Get nested member properties for class properties.
        [[nodiscard]] tinytmx::PropertySet const *GetClassProperties() const { return class_properties.get(); }

    private:
        PropertyType type;
        std::string value;
        std::string class_name;
        std::unique_ptr<tinytmx::PropertySet> class_properties;

        void Parse(tinyxml2::XMLElement const *propertyElem);
    };

}

#endif //TINYTMX_TINYTMXPROPERTY_HPP



