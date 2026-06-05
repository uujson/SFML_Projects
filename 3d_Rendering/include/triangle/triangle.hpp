#pragma once

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "SFML/Graphics.hpp"
#include "../algebra/linalg.hpp"

class triangle : public sf::Drawable{
    private:
        vec3 normal;
        vec3 points[3];
        sf::VertexArray tri;
};


#endif