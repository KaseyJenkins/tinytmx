#ifndef TINYTMX_TINYTMXELLIPSE_HPP
#define TINYTMX_TINYTMXELLIPSE_HPP

#include <vector>

namespace tinytmx
{
    //-------------------------------------------------------------------------
    /// Class to store an Ellipse of an Object.
    //-------------------------------------------------------------------------
    class Ellipse
    {
    public:
        /// Construct an ellipse at the given top left position with the given size.
        Ellipse( float x, float y, float width, float height );

        /// Get the center of the object, in pixels.
        [[nodiscard]] float GetCenterX() const { return x; }

        /// Get the center of the object, in pixels.
        [[nodiscard]] float GetCenterY() const { return y; }
        
        /// Get the RadiusX of the object, in pixels.
        [[nodiscard]] float GetRadiusX() const { return radiusX; }
        
        /// Get the RadiusY of the object, in pixels.
        [[nodiscard]] float GetRadiusY() const { return radiusY; }

    private:
        float x;
        float y;
        float radiusX;
        float radiusY;
    };
}

#endif //TINYTMX_TINYTMXELLIPSE_HPP
