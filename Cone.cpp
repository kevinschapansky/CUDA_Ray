#include "Cone.h"

Cone::Cone(std::string coneParams) {
    std::string pigmentInfo;
    std::string finishInfo;
    End1 = ParsingUtility::NamedBracketedParameterToVec3(coneParams, "<", 0, 1);
    ParsingUtility::NamedSingleParameterToFloat(coneParams, ",", 3, Radius1);
    End2 = ParsingUtility::NamedBracketedParameterToVec3(coneParams, "<", 0, 2);
    ParsingUtility::NamedSingleParameterToFloat(coneParams, ",", 7, Radius2);
    
    if (ParsingUtility::NamedBracketedParameterStringExtraction(coneParams, "pigment", pigmentInfo) > 0) {
        Pig = new Pigment(pigmentInfo);
    }
    if (ParsingUtility::NamedBracketedParameterStringExtraction(coneParams, "finish", finishInfo) > 0) {
        Fin = new Finish(finishInfo);
    }
    Trans = new Transformations(coneParams);
}

Cone::Cone() {
    
}