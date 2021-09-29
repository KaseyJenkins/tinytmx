#include "tinytmxEllipse.hpp"

namespace tinytmx {
    Ellipse::Ellipse(float _x, float _y, float width, float height)
            : x(_x + (width / 2)), y(_y + (height / 2)), radiusX(width / 2), radiusY(height / 2) {
    }
}
