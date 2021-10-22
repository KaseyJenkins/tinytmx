#include "tinytmxWangSetArray.hpp"
#include "tinytmxWangSet.hpp"
#include "tinyxml2.h"

namespace tinytmx {

    void WangSetArray::Parse(std::vector<tinytmx::WangSet *> *wangsets, tinyxml2::XMLNode const *wangsetsNode) {
        // Iterate through all of the wangsets nodes.
        tinyxml2::XMLNode const *wangsetNode = wangsetsNode->FirstChildElement("wangset");

        while (wangsetNode) {
            // Read the attributes of the wangset and add it the WangSet vector.
            auto wangset = new WangSet();
            wangset->Parse(wangsetNode);
            wangsets->push_back(wangset);

            wangsetNode = wangsetNode->NextSiblingElement("wangset");
        }
    }
}