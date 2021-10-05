#include <cstring>
#include "tinyxml2.h"
#include "tinytmxProperty.hpp"

namespace tinytmx {
    Property::Property()
            : type(tinytmx::PropertyType::TMX_PROPERTY_STRING) {
    }

    void Property::Parse(const tinyxml2::XMLElement *propertyElem) {
        const tinyxml2::XMLAttribute *typeAttribute = propertyElem->FindAttribute("type");

        if (typeAttribute != nullptr) {
            const char *typeAsCString = typeAttribute->Value();
            if (std::strcmp(typeAsCString, "string") == 0) {
                type = tinytmx::PropertyType::TMX_PROPERTY_STRING;
            } else if (std::strcmp(typeAsCString, "bool") == 0) {
                type = tinytmx::PropertyType::TMX_PROPERTY_BOOL;
            } else if (std::strcmp(typeAsCString, "float") == 0) {
                type = tinytmx::PropertyType::TMX_PROPERTY_FLOAT;
            } else if (std::strcmp(typeAsCString, "int") == 0) {
                type = tinytmx::PropertyType::TMX_PROPERTY_INT;
            } else if (std::strcmp(typeAsCString, "color") == 0) {
                type = tinytmx::PropertyType::TMX_PROPERTY_COLOR;
            } else if (std::strcmp(typeAsCString, "file") == 0) {
                type = tinytmx::PropertyType::TMX_PROPERTY_FILE;
            } else if (std::strcmp(typeAsCString, "object") == 0) {
                type = tinytmx::PropertyType::TMX_PROPERTY_OBJECT;
            }
        }

        const char *valueAsCString = propertyElem->Attribute("value");
        if (valueAsCString) {
            value = valueAsCString;
        } else {
            // The value of properties that contain newlines is stored in the element text.
            valueAsCString = propertyElem->GetText();
            value = valueAsCString ? valueAsCString : std::string();
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
