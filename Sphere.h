#ifndef SPHERE_H
#define SPHERE_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ParsingUtility.h"
#include "Pigment.h"
#include "Finish.h"
#include "Transformations.h"

typedef struct Sphere {
    glm::vec3 Position;
    float Radius;
    Pigment Pig;
    Transformations* Trans;
    Finish Fin;
    
    Sphere(std::string sphereParams) {
        std::string pigmentInfo;
        std::string finishInfo;
        Position = *ParsingUtility::NamedBracketedParameterToVec3(sphereParams, "<", 0, 1);
        ParsingUtility::NamedSingleParameterToFloat(sphereParams, ",", 3, Radius);
        
        if (ParsingUtility::NamedBracketedParameterStringExtraction(sphereParams, "pigment", pigmentInfo) > 0) {
            Pig = Pigment(pigmentInfo);
        }
        if (ParsingUtility::NamedBracketedParameterStringExtraction(sphereParams, "finish", finishInfo) > 0) {
            Fin = Finish(finishInfo);
        }
        Trans = new Transformations(sphereParams);
    }
    
    Sphere() {
        
    }
} Sphere;

#endif