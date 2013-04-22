#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ParsingUtility.h"

typedef struct LightSource {
    glm::vec3 Position;
    glm::vec3 Color;
    
    LightSource(std::string lightParams) {
        ParsingUtility::NamedBracketedParameterToVec3(lightParams, "<", Position, 0, 1);
        ParsingUtility::NamedBracketedParameterToVec3(lightParams, "color rgb", Color, 0, 1);
    }
    
    LightSource() {
        
    }
} LightSource;

#endif