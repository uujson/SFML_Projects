#pragma once

#include "../settings/settings.h"
#include "object.h"
#include "grid.h"
#include "vector2f.h"

class array: public sf::Drawable{
    private:
        grid **grids;
        std::vector<std::shared_ptr<object>> objects;
        sf::VertexArray vertices;
        int number;
        float cellSize;
        void initialize(int n);
        void gridUpdate(std::shared_ptr<object> o);
    public:
        array();
        array(int n);
        void update();
        void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
};