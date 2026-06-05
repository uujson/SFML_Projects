#include "renderer/renderer.hpp"

const double sqrt2 = sqrt(2);

class axisLine : public sf::Drawable {
    private:
        vec3 position;
        sf::VertexArray vertices;
    public:
        axisLine(char code){
            vertices.resize(2);
            vertices.setPrimitiveType(sf::Lines);
            vertices[0].position = {(float)WINDOW_WIDTH_HALF,(float)WINDOW_HEIGHT_HALF};
            setColor(code);
        }
        void setColor(char code){
            switch(code){
                case 'x':
                    vertices[0].color = sf::Color::Red;
                    vertices[1].color = sf::Color::Red;
                    position = {2,0,0};
                    break;
                case 'y':
                    vertices[0].color = sf::Color::Blue;
                    vertices[1].color = sf::Color::Blue;
                    position = {0,2,0};
                    break;
                case 'z':
                    vertices[0].color = sf::Color::Green;
                    vertices[1].color = sf::Color::Green;
                    position = {0,0,2};
                    break;
            }
        }
        void setPosition(vec3 pos){ vertices[1].position = sf::Vector2f(pos.x,pos.y); }
        vec3 getPoint(){ return position; }
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            target.draw(vertices);
        }
};

int main(){
    double radians = 0.0;
    renderer r = renderer(vec3(2,2,0),110.0);
    axisLine x = axisLine('x');
    axisLine y = axisLine('y');
    axisLine z = axisLine('z');
    window.setFramerateLimit(60.0);
    while (window.isOpen()){
        r.setCameraPosition(vec3(4*cos(radians),4,4*sin(radians)));
        r.printM();
        x.setPosition(r.project(x.getPoint()));
        y.setPosition(r.project(y.getPoint()));
        z.setPosition(r.project(z.getPoint()));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ window.close(); }
        if (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){ window.close(); }
        }
        window.clear(sf::Color::Black);
        window.draw(y);
        window.draw(x);
        window.draw(z);
        window.display();
        radians += 0.01;
    }
    return 0;
}