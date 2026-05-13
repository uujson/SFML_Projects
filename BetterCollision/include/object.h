#pragma once

#include "../settings/settings.h"
#include "vector2f.h"

class object{
    private:
        int32_t index;
        int32_t next;
        float radius;
        float mass;
        vector2f position;
        vector2f velocity;
        vector2f newVelocity;
    public:
        object();
        object(int32_t n);
        object(int32_t n, vector2f pos);
        object(int32_t n, float x, float y);
        vector2f getPosition();
        vector2f getVelocity();
        float getRadius();
        float getMass();
        int32_t getIndex();
        int32_t getNext();
        bool intersect(object other);
        vector2f collide(object &other);
        void setVelocity(vector2f v);
        void velocityChange(vector2f v);
        void setNext(int32_t n);
        void update();
        void clear();
};

float randFloat(){
    return float(rand()%10)+1.0;
}