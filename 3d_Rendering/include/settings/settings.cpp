#include "settings.hpp"

const double MAXFRAMERATE = 144.0;
const double TICKTIME = 1.f/MAXFRAMERATE;
const double WINDOW_WIDTH = 640.0;
const double WINDOW_HEIGHT = 640.0;
const double WINDOW_WIDTH_HALF = WINDOW_WIDTH/2.0;
const double WINDOW_HEIGHT_HALF = WINDOW_HEIGHT/2.0;
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "3D RENDERER");
sf::Event event;