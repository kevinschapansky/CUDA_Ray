#include "Camera.h"

Camera::Camera(std::string cameraParams) {
    Location = ParsingUtility::NamedBracketedParameterToVec3(cameraParams, "location", 0, 1);
    Up = ParsingUtility::NamedBracketedParameterToVec3(cameraParams, "up", 0, 1);
    Right = ParsingUtility::NamedBracketedParameterToVec3(cameraParams, "right", 0, 1);
    Look_At = ParsingUtility::NamedBracketedParameterToVec3(cameraParams, "look_at", 0, 1);
}

Camera::Camera() {
    
}