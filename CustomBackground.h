#ifndef _CUSTOM_BACKGROUND_H_
#define _CUSTOM_BACKGROUND_H_

#include "./CustomBackground.h"
#include "./Color.h"
#include "./Ray.h"

namespace rt {

    struct MyBackground : public Background {

        Color backgroundColor(const Ray &ray) {
            Color result;
            float z = ray.direction.at(2);
            if (z >= 0.0 && z <= 0.5) {
                return Color(1.0f - 2.0f * z, 1.0f - 2.0f * z, 1.0f);
            } else if (z > 0.5f && z <= 1.0f) {
                return Color(0.0f, 0.0f, 1.0f - (z - 0.5f) * 2.0f);
            } else {
                Real x = -0.5f * ray.direction[0] / ray.direction[2];
                Real y = -0.5f * ray.direction[1] / ray.direction[2];
                Real d = sqrt(x * x + y * y);
                Real t = std::min(d, 30.0f) / 30.0f;
                x -= floor(x);
                y -= floor(y);
                if (((x >= 0.5f) && (y >= 0.5f)) || ((x < 0.5f) && (y < 0.5f)))
                    result += (1.0f - t) * Color(0.2f, 0.2f, 0.2f) + t * Color(1.0f, 1.0f, 1.0f);
                else
                    result += (1.0f - t) * Color(0.4f, 0.4f, 0.4f) + t * Color(1.0f, 1.0f, 1.0f);
                return result;
            }
        }

    };

}

#endif