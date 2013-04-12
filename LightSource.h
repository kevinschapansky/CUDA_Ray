#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ParsingUtility.h"

class LightSource {
public:
    glm::vec3* Position;
    glm::vec3* Color;
    
    LightSource(std::string lightParams);
    LightSource();
};

#endif