#pragma once

#include "../settings/settings.h"
#include "vector2f.h"

class object{
    private:
        float radius;
        float mass;
        vector2f position;
        vector2f velocity;
        vector2f newVelocity;
    public:
        object();
        object(vector2f pos);
        object(float x, float y);
        vector2f getPosition();
        vector2f getVelocity();
        float getRadius();
        float getMass();
        bool intersect(object other);
        void collide(object &other);
        void setVelocity(vector2f v);
        void velocityChange(vector2f v);
        void update();
        void clear();
        void bounce(int n);
};

float randFloat();