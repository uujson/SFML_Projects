#include "settings.h"

float MAXFRAMERATE = 144.f;
int MAXGRIDS = 16;
float tickTime = 1.f/MAXFRAMERATE;
float windowWidth = 800;
float windowHeight = 800;
float SQRT_TWO = float(sqrt(2));
float SQRT_TWO_INVERSE = float(1/sqrt(2));
sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Collision Simulation");
sf::Event event;

float dot(sf::Vector2f v1, sf::Vector2f v2){
    return v1.x*v2.x + v1.y*v2.y;
}

float sqd(sf::Vector2f p1, sf::Vector2f p2){
    sf::Vector2f p = p1-p2;
    return ((p.x * p.x)+(p.y * p.y));
}