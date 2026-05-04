#include "../include/settings/settings.h"

int main(){
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(0,0));
    while(window.isOpen()){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ window.close(); }
        if (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){ window.close(); }
        }
        window.clear(sf::Color::Black);
        window.display();
    }
}