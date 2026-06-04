#pragma once

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../../include/algebra/linalg.hpp"
#include "../../include/settings/settings.hpp"
#include "../../include/utils/utils.hpp"

enum SWITCH{NEGATIVE = -1, ZERO = 0, POSITIVE = 1};

struct STATE{
    SWITCH state;
}fovSwitch{.state = ZERO}, radiusSwitch{.state = ZERO}, rotateSwitch{.state = ZERO};

class renderer{
    private:
        vec3 cameraPosition;
        vec3 cameraTarget;
        mat4 projectionM;
        mat4 viewM;
        mat4 modelM;
        double radius;
        double fovDegrees;
    public:
        renderer() : renderer(vec3(1,1,1), 45.0){}
        renderer(vec3 pos, double fovD){
            projectionM = projectionMatrix(fovD, WINDOW_WIDTH/WINDOW_HEIGHT, 0.1, 100.0);
            radius = magnitude(pos);
            modelM = modelMatrix(vec3(1,1,1)/radius, vec3(0,0,0),pos);
            fovDegrees = fovD;
            lookAt(pos, vec3(0,0,0), vec3(0,1,0));
        }
        void setFOV(double fovD){ fovDegrees = fovD; }
        void lookAt(vec3 pos, vec3 target, vec3 up){
            cameraPosition = pos;
            cameraTarget = target;
            vec3 cameraDirection = normalize(cameraPosition - cameraTarget);
            vec3 cameraRight = normalize(cross(up, cameraDirection));
            vec3 cameraUp = normalize(cross(cameraDirection, cameraRight));
            vec3 npos = -pos;
            mat4 other = mat4(
                vec4(cameraRight,cameraRight*npos),
                vec4(cameraUp,cameraUp*npos),
                vec4(cameraDirection,cameraDirection*npos),
                vec4(0,0,0,1)
            );
            viewM = other;
        }
        void project(vec3 point){
            vec4 temp4 = projectionM*viewM*modelM*vec4(point);
            vec3 temp3 = vec3(temp4.x,temp4.y,temp4.z)/(2*temp4.w);
            // std::cout << temp3.x << ' ' << temp3.y << ' ' << temp3.z << std::endl;
            std::cout << temp3.x*WINDOW_WIDTH+WINDOW_WIDTH_HALF << ' ' << temp3.y*WINDOW_HEIGHT+WINDOW_HEIGHT_HALF << std::endl;
        }
};
#endif