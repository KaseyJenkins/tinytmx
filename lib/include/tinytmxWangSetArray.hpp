#ifndef TINYTMX_TINYTMXWANGSETARRAY_HPP
#define TINYTMX_TINYTMXWANGSETARRAY_HPP

#include <vector>

namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {

    class WangSet;

    //-----------------------------------------------------------------------------
    /// Class to parse wangsets.
    //-----------------------------------------------------------------------------

    class WangSetArray {
    public:
        WangSetArray() = default;

        /// Parse a node containing all the wangsets.
        void Parse(std::vector<tinytmx::WangSet *> *wangsets, tinyxml2::XMLNode const *wangsetsNode);

    };
}

#endif //TINYTMX_TINYTMXWANGSETARRAY_HPP
