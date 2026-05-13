#pragma once

#include "../settings/settings.h"

class vector2f{
    public:
        float x;
        float y;
        vector2f();
        vector2f(float X, float Y);
        vector2f operator+(vector2f other);
        vector2f operator-(vector2f other);
        vector2f operator/(const float f);
        vector2f operator*(const float f);
        vector2f &operator=(const vector2f other);
        vector2f &operator=(const int other);
        vector2f &operator/=(const float other);
        vector2f &operator*=(const float other);
        vector2f &operator+=(const vector2f other);
        vector2f &operator-=(const vector2f other);
        float operator*(vector2f other);
        bool operator==(const vector2f other);
        bool operator==(const float f);
        bool operator!=(const vector2f other);
        bool operator!=(const float f);
        float dot(vector2f other);
        float sqd();
        void zero();
};