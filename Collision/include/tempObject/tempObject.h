#pragma once

#include "../settings/settings.h"

class obj: sf::Drawable, sf::Transformable{
    private:
        sf::Vector2f position;
        sf::Vector2f velocity;
    public:
        obj(sf::Vector2f pos);
        void setVelocity(sf::Vector2f v);
        void update(float dt);
        float dot(obj &other);
        sf::Vector2f getPos();
        sf::Vector2f getV();
};