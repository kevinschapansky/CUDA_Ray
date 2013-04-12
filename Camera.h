#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include <string>
#include <stdio.h>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ParsingUtility.h"

class Camera {
public:
    glm::vec3* Location;
    glm::vec3* Up;
    glm::vec3* Right;
    glm::vec3* Look_At;
    
    Camera(std::string cameraParams);
    Camera();
};

#endif