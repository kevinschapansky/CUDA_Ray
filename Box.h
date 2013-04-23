#ifndef BOX_H
#define BOX_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "ParsingUtility.h"
#include "Pigment.h"
#include "Finish.h"

class Box {
public:
    glm::vec3 LeftUpper;
    glm::vec3 RightLower;
    glm::mat4 Transform;
    Pigment Pig;
    Finish Fin;
    
    Box(std::string boxParams) {
        std::string pigmentInfo;
        std::string finishInfo;
        ParsingUtility::NamedBracketedParameterToVec3(boxParams, "<", LeftUpper, 0, 1);
        ParsingUtility::NamedBracketedParameterToVec3(boxParams, "<", RightLower, 0, 2);
        
        if (ParsingUtility::NamedBracketedParameterStringExtraction(boxParams, "pigment", pigmentInfo) > 0) {
            Pig = Pigment(pigmentInfo);
        }
        if (ParsingUtility::NamedBracketedParameterStringExtraction(boxParams, "finish", finishInfo) > 0) {
            Fin = Finish(finishInfo);
        }
        ParsingUtility::ExtractTransformationMatrix(boxParams, Transform);
    }
    Box() {
        
    }
};

#endif