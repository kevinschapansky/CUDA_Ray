#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "ParsingUtility.h"
#include "Pigment.h"
#include "Finish.h"

class Triangle {
public:
    glm::mat4 Transform;
    glm::vec3 Corner1;
    glm::vec3 Corner2;
    glm::vec3 Corner3;
    Pigment Pig;
    Finish Fin;
    
    Triangle(std::string triangleParams) {
        std::string pigmentInfo;
        std::string finishInfo;
        ParsingUtility::NamedBracketedParameterToVec3(triangleParams, "<", Corner1, 0, 1);
        ParsingUtility::NamedBracketedParameterToVec3(triangleParams, "<", Corner2, 0, 2);
        ParsingUtility::NamedBracketedParameterToVec3(triangleParams, "<", Corner3, 0, 3);
        
        if (ParsingUtility::NamedBracketedParameterStringExtraction(triangleParams, "pigment", pigmentInfo) > 0) {
            Pig = Pigment(pigmentInfo);
        }
        if (ParsingUtility::NamedBracketedParameterStringExtraction(triangleParams, "finish", finishInfo) > 0) {
            Fin = Finish(finishInfo);
        }
        ParsingUtility::ExtractTransformationMatrix(triangleParams, Transform);
    }
    
    Triangle() {
        
    }
};

#endif