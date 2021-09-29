#include "tinyxml2.h"
#include <cstdlib>

#include "tinytmxPolyObject.hpp"

namespace tinytmx {

    void PolyObject::Parse(const tinyxml2::XMLNode *polyObjectNode) {
        char *pointsLine = strdup(polyObjectNode->ToElement()->Attribute("points"));

        char *token = strtok(pointsLine, " ");
        while (token) {
            tinytmx::Vector2f point;
            sscanf(token, "%f,%f", &point.x, &point.y);

            points.push_back(point);

            token = strtok(nullptr, " ");
        }

        free(pointsLine);
    }
}
