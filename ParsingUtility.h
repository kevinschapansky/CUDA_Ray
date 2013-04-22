#ifndef PARSING_UTILITY_H
#define PARSING_UTILITY_H

#include <string>
#include <cstdlib>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define TRANSLATE_OP "translate"
#define ROTATE_OP "rotate"
#define SCALE_OP "scale"

class ParsingUtility {
public:
    static int NamedBracketedParameterToVec3(std::string source,
                                             std::string name,
                                             glm::vec3 &result,
                                             int startIdx,
                                             int instance);
    static int NamedSingleParameterToFloat(std::string source,
                                           std::string name,
                                           int instance,
                                           float &result);
    static int NamedBracketedParameterStringExtraction(std::string source,
                                                       std::string paramName,
                                                       std::string &destination);
    static int ExtractTransformationMatrix(std::string source,
                                           glm::mat4x4 &result);
private:
    static int FindNextTransform(std::string &transformName,
                                 std::string source);
};

#endif