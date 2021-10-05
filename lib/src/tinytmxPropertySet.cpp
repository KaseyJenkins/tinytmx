#include "tinyxml2.h"
#include <cstdlib>
#include "tinytmxPropertySet.hpp"


namespace tinytmx {

    PropertySet::PropertySet() : properties() {}

    PropertySet::~PropertySet() {
        properties.clear();
    }

    void PropertySet::Parse(const tinyxml2::XMLNode *propertiesNode) {
        // Iterate through all of the property nodes.
        const tinyxml2::XMLNode *propertyNode = propertiesNode->FirstChildElement("property");
        while (propertyNode) {
            const tinyxml2::XMLElement *propertyElem = propertyNode->ToElement();

            auto nameAttrib = propertyElem->FindAttribute("name");
            // FIXME MAYBE - is the name attribute ever nullptr or an empty string?

            if (nameAttrib == nullptr || nameAttrib->Value()[0] == 0) {
                propertyNode = propertyNode->NextSiblingElement("property");
                continue;
            }

            // Read the attributes of the property and add it to the map.
            Property property;
            property.Parse(propertyElem);
            properties[nameAttrib->Value()] = property;

            propertyNode = propertyNode->NextSiblingElement("property");
        }
    }

    const std::string& PropertySet::GetStringProperty(const std::string &name, const std::string& defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end()) { return defaultValue; }

        return iter->second.GetValue();
    }

    int PropertySet::GetIntProperty(const std::string &name, int defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty()) { return defaultValue; }

        return iter->second.GetIntValue(defaultValue);
    }

    float PropertySet::GetFloatProperty(const std::string &name, float defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty()) { return defaultValue; }

        return iter->second.GetFloatValue(defaultValue);
    }

    bool PropertySet::GetBoolProperty(const std::string &name, bool defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty()) { return defaultValue; }

        return (iter->second.GetBoolValue(defaultValue));
    }

    tinytmx::Color PropertySet::GetColorProperty(const std::string &name, tinytmx::Color defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty()) { return defaultValue; }

        return iter->second.GetColorValue(defaultValue);
    }


    int PropertySet::GetObjectProperty(const std::string &name, int defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty()) { return defaultValue; }

        return iter->second.GetObjectValue(defaultValue);
    }

    const std::string &PropertySet::GetFileProperty(const std::string &name, const std::string &defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end()) { return defaultValue; }

        return iter->second.GetFileValue();
    }

    bool PropertySet::HasProperty(const std::string &name) const {
        if (properties.empty()) { return false; }
        return (properties.find(name) != properties.end());
    }



}
