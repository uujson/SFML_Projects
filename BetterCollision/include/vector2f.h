#pragma once

#include "../settings/settings.h"

class vector2f{
    public:
        float x;
        float y;
        vector2f();
        vector2f(float x, float y);
        vector2f(float *xy);
        vector2f operator+(vector2f &other);
        vector2f operator=(vector2f &other);
        vector2f operator=(float *farray);
        vector2f operator/(float f);
        vector2f operator+=(vector2f &other);
        vector2f operator-=(vector2f &other);
        vector2f operator/=(vector2f &other);
        vector2f operator*=(vector2f &other);
        float dot(vector2f &other);
        float sqd();
};