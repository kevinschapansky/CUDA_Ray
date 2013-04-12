#ifndef CONE_H
#define CONE_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ParsingUtility.h"
#include "Pigment.h"
#include "Finish.h"
#include "Transformations.h"

class Cone {
public:
    glm::vec3* End1;
    float Radius1;
    glm::vec3* End2;
    float Radius2;
    Pigment* Pig;
    Transformations* Trans;
    Finish* Fin;
    
    Cone(std::string coneParams);
    Cone();
};

#endif