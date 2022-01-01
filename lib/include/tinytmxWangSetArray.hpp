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
            WangSetArray(std::vector<tinytmx::WangSet *> *, tinyxml2::XMLNode const *);

        private:
            void Parse(std::vector<tinytmx::WangSet *> *, tinyxml2::XMLNode const *);
    };
}

#endif //TINYTMX_TINYTMXWANGSETARRAY_HPP
