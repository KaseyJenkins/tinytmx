#include "tinyxml2.h"
#include <cstdlib>
#include "tinytmxPropertySet.hpp"


namespace tinytmx {

    PropertySet::PropertySet() : properties() {}

    PropertySet::~PropertySet() {
        properties.clear();
    }

//
//    void PropertySet::Parse(const tinyxml2::XMLNode *propertiesNode) {
//        // Iterate through all of the property nodes.
//        const tinyxml2::XMLElement *propertyElem = propertiesNode->FirstChildElement("property");
//
//        while (propertyElem) {
//
//            auto nameAttrib = propertyElem->FindAttribute("name");
//
//            if (nameAttrib == nullptr || nameAttrib->Value()[0] == 0) {
//                propertyElem = propertyElem->NextSiblingElement("property");
//                continue;
//            }
//
//            // Read the attributes of the property and add it to the map
//            Property property;
//            property.Parse(propertyElem);
//            properties[nameAttrib->Value()] = property;
//
//            propertyElem = propertyElem->NextSiblingElement("property");
//        }
//    }



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

            // Read the attributes of the property and add it to the map
            Property property;
            property.Parse(propertyElem);
            properties[nameAttrib->Value()] = property;

            propertyNode = propertyNode->NextSiblingElement("property");
        }
    }

    std::string PropertySet::GetStringProperty(const std::string &name, std::string defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end()) { return defaultValue; }

        return iter->second.GetValue();
    }

    int PropertySet::GetIntProperty(const std::string &name, int defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty()) { return defaultValue; }

        // Note that we convert the value here ourselves in order to maintain
        // compatibility with older versions of the TMX spec.
        return std::stoi(iter->second.GetValue());
    }

    float PropertySet::GetFloatProperty(const std::string &name, float defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty()) { return defaultValue; }

        // Note that we convert the value here ourselves in order to maintain
        // compatibility with older versions of the TMX spec.
        return std::stof(iter->second.GetValue());
    }

    bool PropertySet::GetBoolProperty(const std::string &name, bool defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty()) { return defaultValue; }

        // Note that we convert the value here ourselves in order to maintain
        // compatibility with older versions of the TMX spec.
        return (iter->second.GetValue() == "true");

    }

    tinytmx::Color PropertySet::GetColorProperty(const std::string &name, tinytmx::Color defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty()) {
            return defaultValue;
        }

        return iter->second.GetColorValue(defaultValue);
    }


    int PropertySet::GetObjectProperty(const std::string &name, int defaultValue) const {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty()) {
            return defaultValue;
        }

        return iter->second.GetObjectValue(defaultValue);
    }


    bool PropertySet::HasProperty(const std::string &name) const {
        if (properties.empty()) { return false; }
        return (properties.find(name) != properties.end());
    }

//    std::map<std::string, std::string> PropertySet::GetList() const {
//        std::map<std::string, std::string> orderedProperties;
//        for (auto &pair: properties) {
//            auto &property = pair.second;
//            orderedProperties[pair.first] = property.GetValue();
//        }
//        return orderedProperties;
//    }

}
