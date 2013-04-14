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
        Position = *ParsingUtility::NamedBracketedParameterToVec3(lightParams, "<", 0, 1);
        Color = *ParsingUtility::NamedBracketedParameterToVec3(lightParams, "color rgb", 0, 1);
    }
    
    LightSource() {
        
    }
} LightSource;

#endif