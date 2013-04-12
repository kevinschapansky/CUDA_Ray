#include "Triangle.h"

Triangle::Triangle(std::string triangleParams) {
    std::string pigmentInfo;
    std::string finishInfo;
    Corner1 = ParsingUtility::NamedBracketedParameterToVec3(triangleParams, "<", 0, 1);
    Corner2 = ParsingUtility::NamedBracketedParameterToVec3(triangleParams, "<", 0, 2);
    Corner3 = ParsingUtility::NamedBracketedParameterToVec3(triangleParams, "<", 0, 3);
    
    if (ParsingUtility::NamedBracketedParameterStringExtraction(triangleParams, "pigment", pigmentInfo) > 0) {
        Pig = new Pigment(pigmentInfo);
    }
    if (ParsingUtility::NamedBracketedParameterStringExtraction(triangleParams, "finish", finishInfo) > 0) {
        Fin = new Finish(finishInfo);
    }
    Trans = new Transformations(triangleParams);
}

Triangle::Triangle() {
    
}