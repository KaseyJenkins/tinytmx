#ifndef TINYTMX_TINYTMXPROPERTY_HPP
#define TINYTMX_TINYTMXPROPERTY_HPP


#include <string>
#include "tinytmxColor.hpp"

namespace tinyxml2 {
    class XMLElement;
}

namespace tinytmx {
    //-------------------------------------------------------------------------
    /// The type of a property.
    //-------------------------------------------------------------------------
    enum class PropertyType {
        /// A string property (default)
        TMX_PROPERTY_STRING,

        /// A boolean property
        TMX_PROPERTY_BOOL,

        /// An integer property
        TMX_PROPERTY_INT,

        /// A floating point property
        TMX_PROPERTY_FLOAT,

        /// A color property
        TMX_PROPERTY_COLOR,

        /// A file property
        TMX_PROPERTY_FILE,

        /// An object property
        TMX_PROPERTY_OBJECT
    };

    //-------------------------------------------------------------------------
    /// Used to store a (typed) property.
    //-------------------------------------------------------------------------
    class Property {
    public:
        Property();

        /// Parse the property element.
        void Parse(const tinyxml2::XMLElement *propertyElem);

        /// Get the type of the property (default: TMX_PROPERTY_STRING)
        PropertyType GetType() const { return type; }

        /// Check if the property is of a certain type.
        bool IsOfType(PropertyType propertyType) const { return (GetType() == propertyType); }

        /// Return the value of the property.
        const std::string &GetValue() const { return value; }

        /// Return whether the value is empty or was not specified.
        bool IsValueEmpty() const { return value.empty(); }

        /// Convert the value to a boolean and return it (or the default value if not a boolean.)
        bool GetBoolValue(bool defaultValue = false) const;

        /// Convert the value to an integer and return it (or the default value if not an integer).
        int GetIntValue(int defaultValue = 0) const;

        /// Convert the value to a float and return it (or the default value if not a float).
        float GetFloatValue(float defaultValue = 0.0f) const;

        /// Convert the value to a color and return it (or the default value if not a color).
        tinytmx::Color GetColorValue(tinytmx::Color defaultValue = tinytmx::Color()) const;

        /// Convert the value into an objectID and return it (or 0 if no object is referenced).
        // Object properties can reference any object on the same map and are stored as an integer
        // (the ID of the referenced object, or 0 when no object is referenced).

        int GetObjectValue(int defaultValue = 0) const;

    private:
        PropertyType type;
        std::string value;
    };

}

#endif //TINYTMX_TINYTMXPROPERTY_HPP



