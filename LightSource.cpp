#include "LightSource.h"

LightSource::LightSource(std::string lightParams) {
    Position = ParsingUtility::NamedBracketedParameterToVec3(lightParams, "<", 0, 1);
    Color = ParsingUtility::NamedBracketedParameterToVec3(lightParams, "color rgb", 0, 1);
}

LightSource::LightSource() {
    
}