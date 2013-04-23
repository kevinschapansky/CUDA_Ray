#ifndef SPHERE_H
#define SPHERE_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "ParsingUtility.h"
#include "Pigment.h"
#include "Finish.h"

typedef struct Sphere {
    glm::vec3 Position;
    glm::mat4 Transform;
    float Radius;
    Pigment Pig;
    Finish Fin;
    
    Sphere(std::string sphereParams) {
        std::string pigmentInfo;
        std::string finishInfo;
        ParsingUtility::NamedBracketedParameterToVec3(sphereParams, "<", Position, 0, 1);
        ParsingUtility::NamedSingleParameterToFloat(sphereParams, ",", 3, Radius);
        
        if (ParsingUtility::NamedBracketedParameterStringExtraction(sphereParams, "pigment", pigmentInfo) > 0) {
            Pig = Pigment(pigmentInfo);
        }
        if (ParsingUtility::NamedBracketedParameterStringExtraction(sphereParams, "finish", finishInfo) > 0) {
            Fin = Finish(finishInfo);
        }
        ParsingUtility::ExtractTransformationMatrix(sphereParams, Transform);
    }

    Sphere() {
        
    }
} Sphere;

#endif