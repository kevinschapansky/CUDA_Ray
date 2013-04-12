#ifndef SPHERE_H
#define SPHERE_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ParsingUtility.h"
#include "Pigment.h"
#include "Finish.h"
#include "Transformations.h"

class Sphere {
public:
    glm::vec3* Position;
    float Radius;
    Pigment* Pig;
    Transformations* Trans;
    Finish* Fin;
    
    Sphere(std::string sphereParams);
    Sphere();
};

#endif