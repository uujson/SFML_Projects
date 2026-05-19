#include "../settings/settings.h"
#include "../include/vector2f.h"
#include "../include/object.h"
#include "../include/grid.h"
#include "../include/array.h"

int main(){
    window.setFramerateLimit(MAXFRAMERATE);
    window.setPosition(sf::Vector2i(0,0));
    array *thing = new array(69);
    sf::Clock clock;
    sf::Time elapsed;
    while(window.isOpen()){
        window.clear(sf::Color::Black);
        elapsed = clock.restart();
        std::cout << 1.f/elapsed.asSeconds() << std::endl;
        thing->update();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ window.close(); }
        if (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){ window.close(); }
        }
        window.draw(*thing);
        window.display();
    }
}