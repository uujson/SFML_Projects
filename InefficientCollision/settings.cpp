#include "settings.h"

float tickTime = 1.f/60.f;
float windowWidth = 800;
float windowHeight = 800;
sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Collision Simulation");
sf::Event event;

float dot(sf::Vector2f v1, sf::Vector2f v2){
    return v1.x*v2.x + v1.y*v2.y;
}

float sqd(sf::Vector2f p1, sf::Vector2f p2){
    sf::Vector2f p = p1-p2;
    return ((p.x * p.x)+(p.y * p.y));
}