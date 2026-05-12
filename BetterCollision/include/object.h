#pragma once

#include "../settings/settings.h"
#include "vector2f.h"

class object: public sf::Drawable{
    private:
        int32_t index;
        int32_t next;
        float radius;
        vector2f position;
        vector2f velocity;
        vector2f newVelocity;
        bool collided;
    public:
        object();
        object(int32_t n);
        object(int32_t n, vector2f pos);
        object(int32_t n, float x, float y);
        vector2f position();
        vector2f velocity();
        float x();
        float y();
        float radius();
        int32_t index();
        int32_t next();
        void update();
        bool intersect(object &other);
        void collide(object &other);
        void next(int32_t n);
};