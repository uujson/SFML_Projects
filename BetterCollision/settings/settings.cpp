#include "settings.h"

float MAXFRAMERATE = 24.f;
int MAXGRIDS = 8;
float tickTime = 1.f/MAXFRAMERATE;
float windowWidth = 1000;
float windowHeight = 1000;
sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Collision Simulation");
sf::Event event;

float dot(sf::Vector2f v1, sf::Vector2f v2){
    return v1.x*v2.x + v1.y*v2.y;
}

float sqd(sf::Vector2f p1, sf::Vector2f p2){
    sf::Vector2f p = p1-p2;
    return ((p.x * p.x)+(p.y * p.y));
}