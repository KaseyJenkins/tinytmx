#include "tinytmxWangSetArray.hpp"
#include "tinytmxWangSet.hpp"
#include "tinyxml2.h"

namespace tinytmx {


    WangSetArray::WangSetArray(std::vector<tinytmx::WangSet *> *wangsets, const tinyxml2::XMLNode *wangsetsNode) {
        Parse(wangsets, wangsetsNode);
    }

    void WangSetArray::Parse(std::vector<tinytmx::WangSet *> *wangsets, tinyxml2::XMLNode const *wangsetsNode) {
        // Iterate through all of the wangsets nodes.
        tinyxml2::XMLNode const *wangsetNode = wangsetsNode->FirstChildElement("wangset");

        while (wangsetNode) {
            // Read the attributes of the wangset and add it the WangSet vector.
            auto wangset = new WangSet(wangsetNode);
            wangsets->push_back(wangset);

            wangsetNode = wangsetNode->NextSiblingElement("wangset");
        }
    }
}