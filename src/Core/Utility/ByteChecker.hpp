#pragma once

#include "Core/Container/String.hpp"

namespace Utility {
    bool isControlByte(char byte);

    bool isIntegerByte(char byte);

    int findIntegerSubBytes(const String& bytes, size_t& cursor);

    bool isLowerCaseByte(char byte);

    bool isUpperCaseByte(char byte);
}
