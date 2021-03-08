#pragma once

// libraries
#include "nlohmann/json.hpp"

namespace dai {

struct Rect {
   public:
    Rect(float xmin, float ymin, float xmax, float ymax) {
        setRect(xmin, ymin, xmax, ymax);
    };
    Rect(){};

    void setRect(float xmin, float ymin, float xmax, float ymax) {
        this->xmin = xmin;
        this->xmax = xmax;
        this->ymin = ymin;
        this->ymax = ymax;
    }

    bool validRect() {
        if(xmin < 0 || xmin > 1) return false;
        if(xmax < 0 || xmax > 1) return false;
        if(ymin < 0 || ymin > 1) return false;
        if(ymax < 0 || ymax > 1) return false;
        if(xmin >= xmax) return false;
        if(ymin >= ymax) return false;
        return true;
    }

    // Normalized range 0-1
    float xmin = 0.0f, ymin = 0.0f, xmax = 0.0f, ymax = 0.0f;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Rect, xmin, ymin, xmax, ymax);

}  // namespace dai