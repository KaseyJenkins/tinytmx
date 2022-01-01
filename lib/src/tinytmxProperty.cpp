#include <string_view>
#include "tinyxml2.h"
#include "tinytmxProperty.hpp"
#include "tinytmxPropertySet.hpp"

namespace tinytmx {
    Property::Property(tinyxml2::XMLElement const *propertyElem)
            : type(tinytmx::PropertyType::TMX_PROPERTY_STRING), properties(nullptr) {
        Parse(propertyElem);
    }

    Property::~Property() {
        if (properties != nullptr) {
            delete properties;
            properties = nullptr;
        }
    }

    void Property::Parse(tinyxml2::XMLElement const *propertyElem) {
        tinyxml2::XMLAttribute const *typeAttribute = propertyElem->FindAttribute("type");

        if (typeAttribute != nullptr) {
            std::string_view typeAsCString = typeAttribute->Value();
            if (typeAsCString == "string") {
                type = tinytmx::PropertyType::TMX_PROPERTY_STRING;
            } else if (typeAsCString == "bool") {
                type = tinytmx::PropertyType::TMX_PROPERTY_BOOL;
            } else if (typeAsCString == "float") {
                type = tinytmx::PropertyType::TMX_PROPERTY_FLOAT;
            } else if (typeAsCString == "int") {
                type = tinytmx::PropertyType::TMX_PROPERTY_INT;
            } else if (typeAsCString == "color") {
                type = tinytmx::PropertyType::TMX_PROPERTY_COLOR;
            } else if (typeAsCString == "file") {
                type = tinytmx::PropertyType::TMX_PROPERTY_FILE;
            } else if (typeAsCString == "object") {
                type = tinytmx::PropertyType::TMX_PROPERTY_OBJECT;
            } else if (typeAsCString == "class") {
                type = tinytmx::PropertyType::TMX_PROPERTY_CLASS;
            }
        }

        char const *valueAsCString = propertyElem->Attribute("value");
        if (valueAsCString) {
            value = valueAsCString;
        } else {
            // The value of properties that contain newlines is stored in the element text.
            valueAsCString = propertyElem->GetText();
            value = valueAsCString ? valueAsCString : std::string();
        }

        char const *propertytypeAsCString = propertyElem->Attribute("propertytype");
        if (propertytypeAsCString) {
            propertytype = propertytypeAsCString;
        }


        if (type == tinytmx::PropertyType::TMX_PROPERTY_CLASS) {
            // Parse the properties if any.
            tinyxml2::XMLNode const *propertiesNode = propertyElem->FirstChildElement("properties");
            if (propertiesNode) {
                properties = new PropertySet(propertiesNode);
            }
        }

    }



    bool Property::GetBoolValue(bool defaultValue) const {
        if (!IsOfType(tinytmx::PropertyType::TMX_PROPERTY_BOOL)) { return defaultValue; }

        return (value == "true");
    }

    int Property::GetIntValue(int defaultValue) const {
        if (!IsOfType(tinytmx::PropertyType::TMX_PROPERTY_INT)) { return defaultValue; }

        return std::stoi(value);
    }

    float Property::GetFloatValue(float defaultValue) const {
        if (!IsOfType(tinytmx::PropertyType::TMX_PROPERTY_FLOAT)) { return defaultValue; }

        return std::stof(value);
    }

    tinytmx::Color Property::GetColorValue(tinytmx::Color defaultValue) const {
        if (!IsOfType(tinytmx::PropertyType::TMX_PROPERTY_COLOR)) {
            return defaultValue;
        }
        return tinytmx::Color(value);
    }

    int Property::GetObjectValue(int defaultValue) const {
        if (!IsOfType(tinytmx::PropertyType::TMX_PROPERTY_OBJECT)) {
            return defaultValue;
        }

        return std::stoi(value);
    }



}
