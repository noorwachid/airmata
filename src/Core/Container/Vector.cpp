#include "Core/Container/Vector.h"

String Vector2::ToString() const
{
    return std::to_string(x) + ", " + std::to_string(y);
}

String Vector3::ToString() const
{
    return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z);
}

String Vector4::ToString() const
{
    return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w);
}
