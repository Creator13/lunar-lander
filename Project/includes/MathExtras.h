#pragma once

namespace math
{
    inline float map(const float a, const float b, const float c, const float d, const float x)
    {
        return c + (x - a) * (d - c) / (b - a);
    }
}
