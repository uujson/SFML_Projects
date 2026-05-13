#pragma once

#include "../settings/settings.h"
#include "vector2f.h"
#include "object.h"

class grid{
    private:
        int32_t firstObject;
        int32_t count;
        int32_t x;
        int32_t y;
        float size;
    public:
        grid();
        grid(float dim, int32_t X, int32_t Y);
        int32_t element();
        void insert();
        bool contains(float X, float Y);
        bool contains(vector2f xy);
        bool contains(object o);
        void clear();
};