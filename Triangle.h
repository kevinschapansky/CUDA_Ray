#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ParsingUtility.h"
#include "Pigment.h"
#include "Finish.h"
#include "Transformations.h"

class Triangle {
public:
    glm::vec3* Corner1;
    glm::vec3* Corner2;
    glm::vec3* Corner3;
    Pigment* Pig;
    Transformations* Trans;
    Finish* Fin;
    
    Triangle(std::string triangleParams);
    Triangle();
};

#endif