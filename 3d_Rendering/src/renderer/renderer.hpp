#pragma once

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../../include/algebra/linalg.hpp"
#include "../../include/settings/settings.hpp"
#include "../../include/utils/utils.hpp"

class renderer{
    private:
        vec3 cameraPosition;
        vec3 cameraTarget;
        mat4 projection;
        mat4 view;
        mat4 model;
        double radius;
        double fovDegrees;
    public:
        renderer() : renderer(vec3(0,0,1), 45.0){}
        renderer(vec3 pos, double fovD){
            projection = perspectiveMatrix(fovD, WINDOW_WIDTH/WINDOW_HEIGHT, 0.1, 100.0);
            // model = mat4(
            //     vec4(1,0,0,0),
            //     vec4(0,cos(-45*PERSPECTIVE_CONST),-sin(-45*PERSPECTIVE_CONST),0),
            //     vec4(0,cos(-45*PERSPECTIVE_CONST),cos(-45*PERSPECTIVE_CONST),0),
            //     vec4(0,0,0,1)
            // );
            model = mat4(1.0);
            radius = magnitude(pos);
            fovDegrees = fovD;
            lookAt(pos, vec3(0,0,0), vec3(0,1,0));
        }
        void lookAt(vec3 pos, vec3 target, vec3 up){
            cameraPosition = pos;
            cameraTarget = target;
            vec3 cameraDirection = normalize(cameraPosition - cameraTarget);
            vec3 cameraRight = normalize(cross(up, cameraDirection));
            vec3 cameraUp = cross(cameraDirection, cameraRight);
            mat4 pos4 = mat4(1.0);
            pos4.m03 = -pos.x;
            pos4.m13 = -pos.y;
            pos4.m23 = -pos.z;
            mat4 other = mat4(
                vec4(cameraRight,0.0),
                vec4(cameraUp,0.0),
                vec4(cameraDirection,0.0),
                vec4(0,0,0,1)
            );
            view = other*pos4;
        }
        void project(vec3 point){
            vec4 temp4 = (projection*view*model*vec4(point));
            std::cout << temp4.x << ' ' << temp4.y << ' ' << temp4.z << ' ' << temp4.w << std::endl;
            // vec3 temp3 = vec3(temp4[0],temp4[1],temp4[2])/temp4[3];
            // std::cout << temp3.x << ' ' << temp3.y << ' ' << temp3.z << std::endl;
            vec2 temp2 = vec2(temp4[0],temp4[1])/(temp4[3]);
            // std::cout << temp2.x << ' ' << temp2.y << std::endl;
            // std::cout << temp2.x*WINDOW_WIDTH+WINDOW_WIDTH_HALF << ' ' << temp2.y*WINDOW_HEIGHT+WINDOW_HEIGHT_HALF << std::endl;

        }

};
#endif