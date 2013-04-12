#ifndef PIGMENT_H
#define PIGMENT_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ParsingUtility.h"

class Pigment {
public:
    glm::vec3* Color;
    float Filter;
    
    Pigment(std::string pigmentParams);
    Pigment();
};

#endif