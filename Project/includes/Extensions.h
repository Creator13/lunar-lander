#pragma once

#include <ostream>

#include "glm/vec2.hpp"

inline std::ostream &operator<< (std::ostream &out, const glm::vec2 &vec) {
    out << "{" << vec.x << "; " << vec.y << "}";

    return out;
}
