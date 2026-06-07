#include "renderer/render.hpp"
#include "../include/algebra/shape.hpp"


class line : public sf::Drawable {
    public:
        vec3 position[2];
        sf::VertexArray vertices;
        line(){
            vertices.resize(2);
            vertices.setPrimitiveType(sf::Lines);
            vertices[0].color = sf::Color::White;
            vertices[1].color = sf::Color::White;
            vertices[0].position = {(float)WINDOW_WIDTH_HALF, (float)WINDOW_HEIGHT_HALF};
        }
        void setPosition(vec3 pos){
            vertices[1].position = sf::Vector2f(pos.x, pos.y);
        }
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            target.draw(vertices);
        }
};


int main(){
    double radians = 0.0;
    render r = render(vec3(0,0,0),45.0);
    cube testCube = cube({2,1,0},{0,0,0},{2,2,1});
    line lines[12];
    // cube testCube;
    // testCube;
    sf::VertexArray verts;
    verts.resize(36);
    verts.setPrimitiveType(sf::Triangles);
    window.setFramerateLimit(60.0);
    while (window.isOpen()){
        r.setCameraPosition(vec3(6.0*cos(radians),6.0*sin(radians),6));
        testCube.updatePoints(r.getCameraPosition(),r.getCameraNormal(),r.getCameraTarget());
        for (int i = 0; i < 36; i++){
            vec3 temp = r.project(testCube.points[i]);
            verts[i].position = sf::Vector2f(temp.x,temp.y);
            verts[i].color = testCube.triangles[(i)/3].color;
        }
        for (int i = 0; i < 12; i++){
            vec3 temp = r.project(testCube.triangles[i].midpoint);
            vec3 temp2 = r.project(testCube.triangles[i].midpoint + testCube.triangles[i].normal);
            lines[i].vertices[0].position = sf::Vector2f(temp2.x, temp2.y);
            lines[i].setPosition(temp);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ window.close(); }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){ radians -= 0.01; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){ radians += 0.01; }
        if (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){ window.close(); }
        }
        window.clear(sf::Color::Black);
        window.draw(verts);
        for (int i = 0; i < 12; i++){
            window.draw(lines[i]);
        }
        window.display();
        // radians += 0.01;
    }
    return 0;
}