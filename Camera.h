#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include <string>
#include <stdio.h>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ParsingUtility.h"

typedef struct Camera {
    glm::vec3 Location;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 Look_At;
    
    Camera(std::string cameraParams) {
        ParsingUtility::NamedBracketedParameterToVec3(cameraParams, "location", Location, 0, 1);
        ParsingUtility::NamedBracketedParameterToVec3(cameraParams, "up", Up, 0, 1);
        ParsingUtility::NamedBracketedParameterToVec3(cameraParams, "right", Right, 0, 1);
        ParsingUtility::NamedBracketedParameterToVec3(cameraParams, "look_at", Look_At, 0, 1);
    }
    
    Camera() {
        
    }
} Camera;

#endif