#include "../settings/settings.h"
#include "../object/obj.h"

int main(){
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(0,0));
    obj test = obj({400.f,300.f},{133,100});
    sf::Clock clock;
    sf::Time elapsed;
    while(window.isOpen()){
        elapsed = clock.restart();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ window.close(); }
        if (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){ window.close(); }
        }
        test.update(elapsed.asSeconds());
        window.clear(sf::Color::Black);
        window.draw(test);
        window.display();
    }
}