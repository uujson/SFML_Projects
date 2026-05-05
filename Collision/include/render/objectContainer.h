#pragma once

#include "../settings/settings.h"
#include "../object/object.h"

class objectContainer : public sf::Drawable, public sf::Transformable{
    private:
        sf::VertexArray vertices;
        std::vector<object> objects;
    public:
        objectContainer();
        void update();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};