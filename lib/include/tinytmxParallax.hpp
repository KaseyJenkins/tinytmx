#ifndef TINYTMX_TINYTMXPARALLAX_HPP
#define TINYTMX_TINYTMXPARALLAX_HPP

namespace tinytmx {

    class Parallax {
    public:

        Parallax():
        x(1.0f), y(1.0f) {}

        Parallax(float _x, float _y) :
        x(_x), y(_y) {}

        float x;
        float y;
    };
}
#endif //TINYTMX_TINYTMXPARALLAX_HPP
