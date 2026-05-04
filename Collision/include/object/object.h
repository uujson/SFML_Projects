#pragma once

#include "../settings/settings.h"

class object{
    private:
        int npoints;
        float height;
        float width;
        float elasticity;
        float friction;
        float mass;
        float angv;
        float angle;
        sf::Vector2f velocity;
        sf::Vector2f position;
    public:
        object(int n, float h, float w, float e, float f, float m, float av, float a, sf::Vector2f v, sf::Vector2f pos);
        object(int n, float r, sf::Vector2f pos);
        object(float r, sf::Vector2f pos);
        object(int n, float r);
        object(int n);
        object();
        void rotate(float degrees);
        void move(sf::Vector2f v);
        float dot(object &o);
        void update();
};