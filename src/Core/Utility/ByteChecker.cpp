#include "Core/Utility/ByteChecker.h"

namespace Utility
{
    bool IsControlByte(char byte) { return byte < ' '; }

    bool IsIntegerByte(char byte) { return byte > '/' && byte < ':'; }

    int FindIntegerSubBytes(const String& bytes, size_t& cursor)
    {
        for (size_t i = cursor; i < bytes.size(); ++i)
            if (!IsIntegerByte(bytes[i]))
            {
                int result = std::stoi(bytes.substr(cursor, i - cursor));
                cursor = i;

                return result;
            }

        return 0;
    }

    bool IsLowerCaseByte(char byte) { return byte > '`' && byte < '{'; }

    bool IsUpperCaseByte(char byte) { return byte > '@' && byte < '['; }
}
