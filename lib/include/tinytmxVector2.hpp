#ifndef TINYTMX_TINYTMXVECTOR2_HPP
#define TINYTMX_TINYTMXVECTOR2_HPP

namespace tinytmx {

    template<typename T>
    class Vector2 {
    public:
    Vector2() : x(0), y(0) {}
    Vector2(T _x, T _y) : x(_x), y(_y) {}

        T x;
        T y;
    };

    using Vector2i = tinytmx::Vector2<int>;
    using Vector2f = tinytmx::Vector2<float>;
}
#endif //TINYTMX_TINYTMXVECTOR2_HPP
