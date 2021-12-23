#ifndef TINYTMX_TINYTMXTRANSFORMATIONS_HPP
#define TINYTMX_TINYTMXTRANSFORMATIONS_HPP


namespace tinyxml2 {
    class XMLNode;
}

namespace tinytmx {

        //-----------------------------------------------------------------------------
        /// This element is used to describe which transformations can be applied to the tiles
        /// (e.g. to extend a Wang set by transforming existing tiles).
        //-----------------------------------------------------------------------------


    class Transformations {
    public:

        explicit Transformations(tinyxml2::XMLNode const *);

        /// Get the value of the 'hflip' attribute of the Transformations element. (Defaults to 0).
        [[nodiscard]] bool GetHflip() const { return hflip; }

        /// Get the value of the 'vflip' attribute of the Transformations element. (Defaults to 0).
        [[nodiscard]] bool GetVflip() const { return vflip; }

        /// Get the value of the 'rotate' attribute of the Transformations element. (Defaults to 0).
        [[nodiscard]] bool GetRotate() const { return rotate; }

        /// Get the value of the 'preferuntransformed' attribute of the Transformations element. (Defaults to 0).
        [[nodiscard]] bool GetPreferUntransformed() const { return preferuntransformed; }

    private:
        bool hflip;
        bool vflip;
        bool rotate;
        bool preferuntransformed;

        void Parse(tinyxml2::XMLNode const *transformationsNode);
    };
}

#endif //TINYTMX_TINYTMXTRANSFORMATIONS_HPP
