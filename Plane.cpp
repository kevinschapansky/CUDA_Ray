#include "Plane.h"

Plane::Plane(std::string planeParams) {
    std::string pigmentInfo;
    std::string finishInfo;
    Normal = ParsingUtility::NamedBracketedParameterToVec3(planeParams, "<", 0, 1);
    ParsingUtility::NamedSingleParameterToFloat(planeParams, ",", 3, Distance);
    
    if (ParsingUtility::NamedBracketedParameterStringExtraction(planeParams, "pigment", pigmentInfo) > 0) {
        Pig = new Pigment(pigmentInfo);
    }
    if (ParsingUtility::NamedBracketedParameterStringExtraction(planeParams, "finish", finishInfo) > 0) {
        Fin = new Finish(finishInfo);
    }
    Trans = new Transformations(planeParams);
}

Plane::Plane() {
    
}