#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "Background.h"
#include "Color.h"
#include "Ray.h"

namespace rt {

    struct Background {
        virtual Color backgroundColor(const Ray &ray) = 0;
    };

}

#endif