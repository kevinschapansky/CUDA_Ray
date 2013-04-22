#ifndef PIGMENT_H
#define PIGMENT_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ParsingUtility.h"

typedef struct Pigment {
    glm::vec3 Color;
    float Filter;
    
    Pigment(std::string pigmentParams) {
        ParsingUtility::NamedBracketedParameterToVec3(pigmentParams, "color rgb", Color, 0, 1);
        if (ParsingUtility::NamedSingleParameterToFloat(pigmentParams, ",", 3, Filter) < 0) {
            Filter = 0;
        }
    }
    
    Pigment() {
        
    }
} Pigment;

#endif