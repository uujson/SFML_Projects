#pragma once

#include "../settings/settings.h"
#include "vector2f.h"
#include "object.h"

class grid: public sf::Drawable{
    private:
        int32_t firstObject;
        int32_t count;
        int32_t x;
        int32_t y;
    public:
        grid();
        grid(int32_t x, int32_t y);
        int32_t element();
        void insert(object &o);
        bool contains(object& o);
        void update();
        void clear();
};