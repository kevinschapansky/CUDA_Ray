#include "Box.h"

Box::Box(std::string boxParams) {
    std::string pigmentInfo;
    std::string finishInfo;
    LeftUpper = ParsingUtility::NamedBracketedParameterToVec3(boxParams, "<", 0, 1);
    RightLower = ParsingUtility::NamedBracketedParameterToVec3(boxParams, "<", 0, 2);
    
    if (ParsingUtility::NamedBracketedParameterStringExtraction(boxParams, "pigment", pigmentInfo) > 0) {
        Pig = new Pigment(pigmentInfo);
    }
    if (ParsingUtility::NamedBracketedParameterStringExtraction(boxParams, "finish", finishInfo) > 0) {
        Fin = new Finish(finishInfo);
    }
    Trans = new Transformations(boxParams);
}

Box::Box() {
    
}