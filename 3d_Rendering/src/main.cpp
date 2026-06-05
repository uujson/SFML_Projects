#include "renderer/render.hpp"

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
                    position = {1,0,0};
                    break;
                case 'y':
                    vertices[0].color = sf::Color::Blue;
                    vertices[1].color = sf::Color::Blue;
                    position = {0,1,0};
                    break;
                case 'z':
                    vertices[0].color = sf::Color::Green;
                    vertices[1].color = sf::Color::Green;
                    position = {0,0,1};
                    break;
            }
        }
        void setPosition(vec3 pos){ vertices[1].position = sf::Vector2f(pos.x,pos.y); }
        vec3 getPoint(){ return position; }
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            target.draw(vertices);
        }
};


class line : public sf::Drawable {
    private:
        vec3 position[2];
        sf::VertexArray vertices;
    public:
        line(int p0, int p1, int i0, double i1){
            vertices.resize(2);
            vertices.setPrimitiveType(sf::Lines);
            set(p0, 0, i0);
            set(p1, 1, i1);
        }
        void set(int c, int n, double i){
            switch(c){
                case 0:
                    vertices[n].color = sf::Color::Red;
                    position[n] = {i,0,0};
                    break;
                case 1:
                    vertices[n].color = sf::Color::Blue;
                    position[n] = {0,i,0};
                    break;
                case 2:
                    vertices[n].color = sf::Color::Green;
                    position[n] = {0,0,i};
                    break;
            }
        }
        void setPosition(vec3 pos0, vec3 pos1){
            vertices[0].position = sf::Vector2f(pos0.x,pos0.y);
            vertices[1].position = sf::Vector2f(pos1.x,pos1.y);
        }
        vec3 operator[](const int index){ return position[index]; }
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            target.draw(vertices);
        }
};

int main(){
    double radians = 0.0;
    render r = render(vec3(2,2,0),15.0);
    /*
    | [-x -y] | [-y +x] | [-z -y] | [-y +z] |
    | [+z +x] | [+x -z] | [-z -x] | [-x +z] |
    | [+x +y] | [+y -x] | [-z +y] | [+y +z] |
    */
    line lines[12] = {
        line(0,1,-1,-1), line(1,0,-1,1), line(2,1,-1,-1), line(1,2,-1,1),
        line(2,0,1,1), line(0,2,1,-1), line(2,0,-1,-1), line(0,2,-1,1),
        line(0,1,1,1), line(1,0,1,-1), line(2,1,-1,1), line(1,2,1,1)
    };
    axisLine x = axisLine('x');
    axisLine y = axisLine('y');
    axisLine z = axisLine('z');
    window.setFramerateLimit(60.0);
    while (window.isOpen()){
        r.setCameraPosition(vec3(2.0*cos(radians),2.0*sin(radians),2));
        x.setPosition(r.project(x.getPoint()));
        y.setPosition(r.project(y.getPoint()));
        z.setPosition(r.project(z.getPoint()));
        for (int i = 0; i < 12; i++){
            lines[i].setPosition(r.project(lines[i][0]),r.project(lines[i][1]));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ window.close(); }
        if (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){ window.close(); }
        }
        window.clear(sf::Color::Black);
        for (int i = 0; i < 12; i++){
            window.draw(lines[i]);
        }
        window.draw(y);
        window.draw(x);
        window.draw(z);
        window.display();
        radians += 0.05;
    }
    return 0;
}