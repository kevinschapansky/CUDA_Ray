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
        Location = *ParsingUtility::NamedBracketedParameterToVec3(cameraParams, "location", 0, 1);
        Up = *ParsingUtility::NamedBracketedParameterToVec3(cameraParams, "up", 0, 1);
        Right = *ParsingUtility::NamedBracketedParameterToVec3(cameraParams, "right", 0, 1);
        Look_At = *ParsingUtility::NamedBracketedParameterToVec3(cameraParams, "look_at", 0, 1);
    }
    
    Camera() {
        
    }
} Camera;

#endif