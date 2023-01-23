#include "Core/Utility/ByteChecker.h"

namespace Utility {
    bool isControlByte(char byte) { return byte < ' '; }

    bool isIntegerByte(char byte) { return byte > '/' && byte < ':'; }

    int findIntegerSubBytes(const String& bytes, size_t& cursor) {
        for (size_t i = cursor; i < bytes.size(); ++i)
            if (!isIntegerByte(bytes[i])) {
                int result = std::stoi(bytes.substr(cursor, i - cursor));
                cursor = i;

                return result;
            }

        return 0;
    }

    bool isLowerCaseByte(char byte) { return byte > '`' && byte < '{'; }

    bool isUpperCaseByte(char byte) { return byte > '@' && byte < '['; }
}
