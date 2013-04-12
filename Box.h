#ifndef BOX_H
#define BOX_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ParsingUtility.h"
#include "Pigment.h"
#include "Finish.h"
#include "Transformations.h"

class Box {
public:
    glm::vec3* LeftUpper;
    glm::vec3* RightLower;
    Pigment* Pig;
    Transformations* Trans;
    Finish* Fin;
    
    Box(std::string boxParams);
    Box();
};

#endif