#include "tinyxml2.h"
#include "tinytmxPropertySet.hpp"


namespace tinytmx {

    PropertySet::PropertySet(tinyxml2::XMLNode const *propertiesNode) : properties() {
        Parse(propertiesNode);
    }

    PropertySet::~PropertySet() {
        properties.clear();
    }

    void PropertySet::Parse(tinyxml2::XMLNode const *propertiesNode) {
        // Iterate through all of the property nodes.
        tinyxml2::XMLNode const *propertyNode = propertiesNode->FirstChildElement("property");
        while (propertyNode) {
            tinyxml2::XMLElement const *propertyElem = propertyNode->ToElement();

            auto nameAttrib = propertyElem->FindAttribute("name");
            // FIXME MAYBE - is the name attribute ever nullptr or an empty string?

            if (nameAttrib == nullptr || nameAttrib->Value()[0] == 0) {
                propertyNode = propertyNode->NextSiblingElement("property");
                continue;
            }

            // Read the attributes of the property and add it to the map.
            Property property(propertyElem);
            properties.insert({nameAttrib->Value(), property});
            propertyNode = propertyNode->NextSiblingElement("property");
        }
    }

    std::string const &PropertySet::GetStringProperty(std::string const &name, std::string const &defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end()) { return defaultValue; }

        return iter->second.GetValue();
    }

    int PropertySet::GetIntProperty(std::string const &name, int defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty()) { return defaultValue; }

        return iter->second.GetIntValue(defaultValue);
    }

    float PropertySet::GetFloatProperty(std::string const &name, float defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty()) { return defaultValue; }

        return iter->second.GetFloatValue(defaultValue);
    }

    bool PropertySet::GetBoolProperty(std::string const &name, bool defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty()) { return defaultValue; }

        return (iter->second.GetBoolValue(defaultValue));
    }

    tinytmx::Color PropertySet::GetColorProperty(std::string const &name, tinytmx::Color defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty()) { return defaultValue; }

        return iter->second.GetColorValue(defaultValue);
    }


    int PropertySet::GetObjectProperty(std::string const &name, int defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty()) { return defaultValue; }

        return iter->second.GetObjectValue(defaultValue);
    }

    std::string const &PropertySet::GetFileProperty(std::string const &name, std::string const &defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end()) { return defaultValue; }

        return iter->second.GetFileValue();
    }

    bool PropertySet::HasProperty(std::string const &name) const {
        if (properties.empty()) { return false; }
        return (properties.find(name) != properties.end());
    }



}
