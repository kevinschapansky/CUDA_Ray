#ifndef CONE_H
#define CONE_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ParsingUtility.h"
#include "Pigment.h"
#include "Finish.h"

class Cone {
public:
    glm::mat4x4 Transform;
    glm::vec3 End1;
    float Radius1;
    glm::vec3 End2;
    float Radius2;
    Pigment Pig;
    Finish Fin;
    
    Cone(std::string coneParams) {
        std::string pigmentInfo;
        std::string finishInfo;
        ParsingUtility::NamedBracketedParameterToVec3(coneParams, "<", End1, 0, 1);
        ParsingUtility::NamedSingleParameterToFloat(coneParams, ",", 3, Radius1);
        ParsingUtility::NamedBracketedParameterToVec3(coneParams, "<", End2, 0, 2);
        ParsingUtility::NamedSingleParameterToFloat(coneParams, ",", 7, Radius2);
        
        if (ParsingUtility::NamedBracketedParameterStringExtraction(coneParams, "pigment", pigmentInfo) > 0) {
            Pig = Pigment(pigmentInfo);
        }
        if (ParsingUtility::NamedBracketedParameterStringExtraction(coneParams, "finish", finishInfo) > 0) {
            Fin = Finish(finishInfo);
        }
        ParsingUtility::ExtractTransformationMatrix(coneParams, Transform);
    }
    Cone() {
        
    }
};

#endif