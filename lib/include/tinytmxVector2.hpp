#ifndef TINYTMX_TINYTMXVECTOR2_HPP
#define TINYTMX_TINYTMXVECTOR2_HPP

#include <cstdint>

namespace tinytmx {

    template<typename T>
    class Vector2 {
    public:
        Vector2() : x(0), y(0) {}
        Vector2(T xvalue, T yvalue) : x(xvalue), y(yvalue) {}

        T x;
        T y;
    };

    using Vector2i = tinytmx::Vector2<int>;
    using Vector2f = tinytmx::Vector2<float>;
    using Vector2ui = tinytmx::Vector2<uint32_t>;
}
#endif //TINYTMX_TINYTMXVECTOR2_HPP
