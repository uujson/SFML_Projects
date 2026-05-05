#pragma once

#include "../settings/settings.h"

class obj: public sf::Drawable, public sf::Transformable{
    private:
        sf::Vector2f velocity;
        sf::CircleShape point;
        int inBounds(sf::Vector2f v);
    public:
        obj(sf::Vector2f pos, sf::Vector2f v);
        obj(sf::Vector2f pos);
        void setVelocity(sf::Vector2f v);
        void update(float dt);
        float dot(obj &other);
        sf::Vector2f getPos();
        sf::Vector2f getV();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};