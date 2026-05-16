#pragma once

#include "../settings/settings.h"
#include "vector2f.h"
#include "object.h"

class grid{
    private:
        std::vector<std::shared_ptr<object>> objects;
        int32_t x;
        int32_t y;
        vector2f xy;
        float size;
    public:
        grid();
        grid(float dim, int32_t X, int32_t Y);
        std::vector<std::shared_ptr<object>> update();
        void insert(std::shared_ptr<object> o);
        bool contains(float X, float Y);
        bool contains(vector2f xy);
        bool contains(object o);
        bool contains(std::shared_ptr<object> o);
        bool isEmpty();
        void clear();
};