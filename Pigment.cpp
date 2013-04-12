#include "Pigment.h"

Pigment::Pigment(std::string pigmentParams) {
    Color = ParsingUtility::NamedBracketedParameterToVec3(pigmentParams, "color rgb", 0, 1);
    if (ParsingUtility::NamedSingleParameterToFloat(pigmentParams, ",", 3, Filter) < 0) {
        Filter = 0;
    }
}

Pigment::Pigment() {
    
}