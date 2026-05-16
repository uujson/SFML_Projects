#pragma once

#ifndef SETTINGS
#define SETTINGS

#include <string>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <time.h>
#include <vector>
#include <ctime>
#include <map>
#include <cstring>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <bits/stdc++.h>
#include <memory>

float dot(sf::Vector2f v1, sf::Vector2f v2);
float sqd(sf::Vector2f p1, sf::Vector2f p2);

extern float MAXFRAMERATE;
extern int MAXGRIDS;
extern float windowWidth;
extern float windowHeight;
extern float tickTime;
extern float SQRT_TWO;
extern float SQRT_TWO_INVERSE;
extern sf::RenderWindow window;
extern sf::Event event;

#endif