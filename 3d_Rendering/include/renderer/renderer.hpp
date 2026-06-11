#pragma once

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../algebra/linalg.hpp"
#include "../camera/camera.hpp"
#include "../utils/utils.hpp"
#include "../settings/settings.hpp"

mat4 projectionMatrix(double degrees, double aspectRatio, double nearPlane, double farPlane){
    double fov = 1.0/tan(degrees*DEG2RADS*0.5);
    mat4 perspective = mat4(
        vec4(fov, 0, 0, 0),
        vec4(0, fov*aspectRatio, 0, 0),
        vec4(0, 0, (farPlane)/(farPlane-nearPlane), -(farPlane*nearPlane)/(farPlane-nearPlane)),
        vec4(0,0,1, 0)
    );
    return perspective;
}

class renderer{
    public:
        camera Camera;
        mat4 projection, view, model;
        renderer() : renderer(vec3(0,0,0)){}
        renderer(vec3 cameraPosition) : renderer(cameraPosition, 45.0){}
        renderer(vec3 cameraPosition, double FOV) : renderer(cameraPosition, FOV, vec3(1,0,0)){}
        renderer(vec3 cameraPosition, double FOV, vec3 target){
            Camera = camera(cameraPosition, FOV);
            Camera.setTarget(target);
            updateFOV();
            update();
        }
        void setCameraPosition(vec3 pos){
            Camera.setPosition(pos);
            update();
        }
        void setCameraTarget(vec3 target){
            Camera.setTarget(target);
            update();
        }
        void setFOV(double FOV){
            Camera.setFOV(FOV);
            updateFOV();
            update();
        }
        vec3 getCameraNormal(){ return Camera.tNormal; }
        vec3 getCameraTarget(){ return Camera.lookingAt; }
        vec3 getCameraPosition(){ return Camera.position; }
        double getFOV(){ return Camera.fov; }
        renderer& operator+=(vec3 d){
            Camera += d;
            update();
            return *this;
        }
        renderer& operator+=(double angles[2]){
            Camera += angles;
            update();
            return *this;
        }
        renderer& operator+=(double FOV){
            Camera += FOV;
            updateFOV();
            update();
            return *this;
        }
        renderer& operator-=(double FOV){
            Camera -= FOV;
            updateFOV();
            update();
            return *this;
        }
        void updateFOV(){
            projection = projectionMatrix(Camera.fov, WINDOW_WIDTH/WINDOW_HEIGHT, 0, 500.0);
        }
        void update(){
            model = modelMatrix(vec3(1,1,1), vec3(0,0,0), vec3(0,0,0));
            view = Camera.viewMatrix();
        }
        vec3 project(vec3 v){
            vec4 v4 = projection*view*model*vec4(v);
            vec3 v3 = vec3(v4)/(4.0*v4.w);
            v3.x = v3.x * WINDOW_WIDTH + WINDOW_WIDTH_HALF;
            v3.y = v3.y * WINDOW_HEIGHT + WINDOW_HEIGHT_HALF;
            return v3;
        }
};



#endif