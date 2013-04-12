#include "Sphere.h"

Sphere::Sphere(std::string sphereParams) {
    std::string pigmentInfo;
    std::string finishInfo;
    Position = ParsingUtility::NamedBracketedParameterToVec3(sphereParams, "<", 0, 1);
    ParsingUtility::NamedSingleParameterToFloat(sphereParams, ",", 3, Radius);
    
    if (ParsingUtility::NamedBracketedParameterStringExtraction(sphereParams, "pigment", pigmentInfo) > 0) {
        Pig = new Pigment(pigmentInfo);
    }
    if (ParsingUtility::NamedBracketedParameterStringExtraction(sphereParams, "finish", finishInfo) > 0) {
        Fin = new Finish(finishInfo);
    }
    Trans = new Transformations(sphereParams);
}

Sphere::Sphere() {
    
}