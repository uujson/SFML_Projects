#pragma once

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../algebra/linalg.hpp"
#include <cmath>

const vec3 upDirection = vec3(0,0,1);
const double D2R = M_PI/180.0;
const double R2D = 1.0/D2R;


class camera{
    public:
        vec3 position, lookingAt, tNormal, uNormal, rNormal;
        double longitude;
        double latitude;
        double fov;
        camera() : camera({0,0,0}, 45.0){}
        camera(vec3 pos, double FOV){
            longitude = 180;
            latitude = 0;
            position = pos;
            fov = FOV;
            update();
        }
        void setPosition(vec3 v){
            position = v;
            update();
        }
        void setTarget(vec3 target){
            tNormal = -normalize(target-position);
            latitude = asin(tNormal.z)*R2D;
            longitude = acos(tNormal.z)*R2D;
            checkAngle();
            update();
        }
        void setFOV(double FOV){ fov = FOV; }
        void checkAngle(){
            if (longitude > 360.0){ longitude -= 360.0; }
            else if (longitude < 0){ longitude += 360.0; }
            if (latitude > 85){ latitude = 85; }
            else if (latitude < -85){ latitude = -85; }
            update();
        }
        void checkFOV(){
            if (fov > 89.0){ fov = 89.0; }
            else if (fov < 15.0){ fov = 15.0; }
        }
        camera& operator+=(vec3 d){
            if (d.x == 0 & d.y == 0 & d.z == 0){ return *this; }
            if (d.x != 0 || d.y != 0){
                vec3 temp = normalize(vec3(d.x,d.y,0))*0.01;
                position += vec3(temp.x*rNormal.y, -temp.x*rNormal.x, 0);
                position += vec3(temp.y*rNormal.x, temp.y*rNormal.y, 0);
            }
            position += vec3(0,0,d.z);
            update();
            return *this;
        }
        camera& operator+=(double angles[2]){
            longitude += angles[0];
            latitude += angles[1];
            checkAngle();
            update();
            return *this;
        }
        camera& operator+=(double FOV){
            fov += FOV;
            checkFOV();
            return *this;
        }
        camera& operator-=(double FOV){
            fov -= FOV;
            checkFOV();
            return *this;
        }
        mat4 viewMatrix(){
            vec3 temp = -position;
            return mat4(
                vec4(rNormal, rNormal*temp),
                vec4(uNormal, uNormal*temp),
                vec4(tNormal, tNormal*temp),
                vec4(0,0,0,1)
            );
        }
        void update(){
            tNormal = vec3(cos(latitude*D2R)*cos(longitude*D2R), cos(latitude*D2R)*sin(longitude*D2R), sin(latitude*D2R));
            lookingAt = position - tNormal;
            rNormal = normalize(cross(tNormal, upDirection));
            uNormal = normalize(cross(tNormal, rNormal));
        }
};

#endif