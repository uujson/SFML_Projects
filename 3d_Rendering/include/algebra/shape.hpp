#pragma once

#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "SFML/Graphics.hpp"
#include "linalg.hpp"
#include <algorithm>
#include <vector>
#include <cmath>

const double ISQRT2 = 1/sqrt(2);
const double SQRT2 = sqrt(2);


const double N = -1;
const double P = 1;

/*
     0---1
    /|   |\    
   2-------3
   | 4---5 |
   |/     \|
   6-------7
*/


vec3 CUBE[8] = {
       {N,N,P},{P,N,P},
    {N,P,P},      {P,P,P},

       {N,N,N},{P,N,N},
    {N,P,N},      {P,P,N}
};

class triangle{
    public:
        vec3 normal;
        vec3 points[3];
        vec3 midpoint;
        sf::Color color;
        triangle() : triangle(vec3(1,0,0), vec3(0,0,0), vec3(0,1,0)){}
        triangle(vec3 p0, vec3 p1, vec3 p2){
            points[0] = p0;
            points[1] = p1;
            points[2] = p2;
            color = sf::Color::White;
            updateNormal();
            updateMidpoint();
        }
        void updateNormal(){ normal = cross((points[2]-points[1]),(points[0]-points[1])); }
        void updateMidpoint(){ midpoint = (points[0]+points[1]+points[2])/3; }
        triangle& operator=(const triangle o){
            for (int i = 0; i < 3; i++){ points[i] = o.points[i]; }
            normal = o.normal;
            midpoint = o.midpoint;
            return *this;
        }
        triangle& operator*=(mat4 m){
            for (int i = 0; i < 3; i++){ points[i] = m*vec4(points[i]);}
            midpoint = m*vec4(midpoint);
            updateNormal();
            return *this;
        }
        double operator*(vec3 v){
            return normal*v;
        }
};

bool tcsort(triangle a, triangle b, vec3 cp, vec3 cn){
    double ca = buffer(cp-a.midpoint)*(b*cn);
    double cb = buffer(cp-b.midpoint)*(b*cn);
    return (((ca) < (cb)));
}

class cube{
    private:
        void translateCube(vec3 t){ translate += t; update(); }
        void scaleCube(const double d){ scale *= d; update(); }
    public:
        std::vector<triangle> triangles;
        vec3 points[36];
        vec3 translate;
        vec3 rotate;
        vec3 scale;
        cube() : cube(ZERO3, ZERO3, vec3(1,1,1)){}

        cube(vec3 t, vec3 r, vec3 s){
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
            
            update();
        }
        cube& operator=(const cube o){
            for (int i = 0; i < 12; i++){ triangles[i] = o.triangles[i]; }
            translate = o.translate;
            rotate = o.rotate;
            scale = o.scale;
            return *this;
        }
        cube& operator+=(const double d[3]){ translateCube(vec3(d[0], d[1], d[2])); return *this; }
        cube& operator-=(const double d[3]){ translateCube(vec3(d[0], d[1], d[2])); return *this; }
        cube& operator+=(const vec3 d){ translateCube(d); return *this; }
        cube& operator-=(const vec3 d){ translateCube(d); return *this; }
        cube& operator/=(const double d){ scaleCube(d); return *this; }
        cube& operator*=(const double d){ scaleCube(d); return *this; }
        mat4 model(){ return (scale4(scale)*rotate4(rotate)*translate4(translate)); }
        void setTranslate(vec3 t){ translate = t; update(); }
        void setScale(const double d){ scale = vec3(d,d,d); update(); }
        void rotateCube(vec3 r){ rotate += r; update(); }
        void setRotate(vec3 r){ rotate = r; update(); }
        void update(){
            mat4 m = model();
            for (int i = 0; i < 12; i++){ triangles[i] *= m; }
        }
        void updatePoints(vec3 cameraP, vec3 cameraN){
            std::sort(triangles.begin(), triangles.end(),
                std::bind(tcsort, std::placeholders::_1,std::placeholders::_2, cameraP, cameraN));
            for (int i = 0; i < 12; i++){
                int temp = i*3;
                if(triangles[i]*cameraN > 0){
                    points[temp] = triangles[i].points[2];
                    points[temp+1] = triangles[i].points[1];
                    points[temp+2] = triangles[i].points[0];
                }
                else{
                    points[temp] = ZERO3;
                    points[temp+1] = ZERO3;
                    points[temp+2] = ZERO3;
                }
            }
            // for (int i = 0; i < 12; i++){
            //     int temp = i*3;
            //     points[temp] = triangles[i].points[0];
            //     points[temp+1] = triangles[i].points[1];
            //     points[temp+2] = triangles[i].points[2];
            // }
        }
};


#endif