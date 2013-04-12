#ifndef PLANE_H
#define PLANE_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ParsingUtility.h"
#include "Pigment.h"
#include "Finish.h"
#include "Transformations.h"

class Plane {
public:
    glm::vec3* Normal;
    float Distance;
    Pigment* Pig;
    Transformations* Trans;
    Finish* Fin;
    
    Plane(std::string triangleParams);
    Plane();
};

#endif