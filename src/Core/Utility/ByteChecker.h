#pragma once

#include "Core/Container/String.h"

namespace Utility
{
    bool IsControlByte(char byte);

    bool IsIntegerByte(char byte);

    int FindIntegerSubBytes(const String& bytes, size_t& cursor);

    bool IsLowerCaseByte(char byte);

    bool IsUpperCaseByte(char byte);
}
