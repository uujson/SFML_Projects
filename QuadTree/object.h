#pragma once

#include "settings.h"

#define RADIUS 5.f

class object{
    private:
        sf::Vector2f position;
        sf::Vector2f velocity;
        float mass;
    public:
        object(sf::Vector2f pos);
        void update();
        void rotate(float degrees);
        bool collision(object &other);
        void collide(int wall);
        void collide(object &other);
        void setPosition(sf::Vector2f pos);
        void setVelocity(sf::Vector2f v);
        sf::Vector2f getPosition();
        sf::Vector2f getVelocity();
        float getMass();
        operator sf::Vector2f() const;
};