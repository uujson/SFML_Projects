#pragma once

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <SFML/Graphics.hpp>
#include "../algebra/linalg.hpp"
#include "../camera/camera.hpp"
#include "../renderer/renderer.hpp"
#include <algorithm>
#include <vector>
#include <cmath>

/*
     0---1
    /|   |\    
   2-------3
   | 4---5 |
   |/     \|
   6-------7
*/


const double N = -1;
const double P = 1;

vec3 CUBE[8] = {
       {N,N,P},{P,N,P},
    {N,P,P},      {P,P,P},

       {N,N,N},{P,N,N},
    {N,P,N},      {P,P,N}
};

class triangle{
    public:
        vec3 normal;
        vec3 midpoint;
        sf::Color color;
        vec3 points[3];
        triangle(){}
        triangle(vec3 p0, vec3 p1, vec3 p2){}
        void updateNormal(){
            normal = normalize(cross((points[1]-points[2]),(points[1]-points[0])));
        }
        void updateMidpoint(){ midpoint = (points[0]+points[1]+points[2])/3; }
        triangle& operator=(const triangle o){
            return *this;
        }
        bool operator*(camera c){
            return (normal*c.tNormal > 0);
        }  
};

bool tsort(triangle a, triangle b, camera c){
    return ((c.tNormal*(c.position - a.midpoint)) <= (c.tNormal*(c.position - b.midpoint)));
}

class cube : public sf::Drawable{
    public:
        std::vector<triangle> triangles;
        vec3 translate;
        vec3 rotate;
        vec3 scale;
        sf::VertexArray verts;
        vec3 points[36];
        cube() : cube(ZERO3, ZERO3, vec3(1,1,1)){}
        cube(vec3 t,vec3 r, vec3 s){
            verts.resize(36);
            triangles.reserve(12);
            translate = t;
            rotate = r;
            scale = s;
            // bottom
            triangles[0] = triangle(CUBE[6],CUBE[7],CUBE[5]);
            triangles[1] = triangle(CUBE[5],CUBE[4],CUBE[6]);
            triangles[0].color = sf::Color::Green;
            triangles[1].color = sf::Color::Green;
            
            // top
            triangles[2] = triangle(CUBE[0],CUBE[1],CUBE[3]);
            triangles[3] = triangle(CUBE[3],CUBE[2],CUBE[0]);
            triangles[2].color = sf::Color::Green;
            triangles[3].color = sf::Color::Green;
            
            // back
            triangles[4] = triangle(CUBE[4],CUBE[5],CUBE[1]);
            triangles[5] = triangle(CUBE[1],CUBE[0],CUBE[4]);
            triangles[4].color = sf::Color::Magenta;
            triangles[5].color = sf::Color::Magenta;

            // front
            triangles[10] = triangle(CUBE[7],CUBE[6],CUBE[2]);
            triangles[11] = triangle(CUBE[2],CUBE[3],CUBE[7]);
            triangles[10].color = sf::Color::Blue;
            triangles[11].color = sf::Color::Blue;
            
            // right
            triangles[6] = triangle(CUBE[1],CUBE[5],CUBE[7]);
            triangles[7] = triangle(CUBE[7],CUBE[3],CUBE[1]);
            triangles[6].color = sf::Color::Yellow;
            triangles[7].color = sf::Color::Yellow;
            
            // left
            triangles[8] = triangle(CUBE[6],CUBE[4],CUBE[0]);
            triangles[9] = triangle(CUBE[0],CUBE[2],CUBE[6]);
            triangles[8].color = sf::Color::Red;
            triangles[9].color = sf::Color::Red;
        }
        void update(renderer r){
            std::sort(triangles.begin(), triangles.end(),
                        std::bind(tsort, std::placeholders::_1,std::placeholders::_2, r.Camera));
            for (int i = 0; i < 12; i++){
                int temp = i*3;
                if (triangles[i]*r.Camera){
                    points[temp] = triangles[i].points[0];
                    points[temp+1] = triangles[i].points[1];
                    points[temp+2] = triangles[i].points[2];
                }
                else{
                    points[temp] = ZERO3;
                    points[temp+1] = ZERO3;
                    points[temp+2] = ZERO3;
                }
            }
            for (int i = 0; i < 36; i++){
                vec3 temp = r.project(points[i]);
                verts[i].position = sf::Vector2f(temp.x, temp.y);
                verts[i].color = triangles[i/3].color;
            }
        }
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override{
            target.draw(verts);
        }


};

#endif 