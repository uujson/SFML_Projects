#pragma once

#include "../settings/settings.h"
#include "object.h"
#include "grid.h"
#include "vector2f.h"

class array: public sf::Drawable{
    private:
        grid *grids;
        std::vector<object> objects;
        sf::VertexArray vertices;
        float cellSize;
        int ngrids;
    public:
        array();
        array(int n);
        void update();
        void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
};