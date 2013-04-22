#ifndef PLANE_H
#define PLANE_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ParsingUtility.h"
#include "Pigment.h"
#include "Finish.h"

typedef struct Plane {
    glm::mat4x4 Transform;
    glm::vec3 Normal;
    float Distance;
    Pigment Pig;
    Finish Fin;
    
    Plane(std::string planeParams) {
        std::string pigmentInfo;
        std::string finishInfo;
        ParsingUtility::NamedBracketedParameterToVec3(planeParams, "<", Normal, 0, 1);
        ParsingUtility::NamedSingleParameterToFloat(planeParams, ",", 3, Distance);
        
        if (ParsingUtility::NamedBracketedParameterStringExtraction(planeParams, "pigment", pigmentInfo) > 0) {
            Pig = Pigment(pigmentInfo);
        }
        if (ParsingUtility::NamedBracketedParameterStringExtraction(planeParams, "finish", finishInfo) > 0) {
            Fin = Finish(finishInfo);
        }
        ParsingUtility::ExtractTransformationMatrix(planeParams, Transform);
    }
    
    Plane() {
        
    }
} Plane;

#endif