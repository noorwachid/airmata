#include "Core/Event/Event.h"

String ToString(EventType type)
{
    switch (type)
    {
        case EventType::key:
            return "Key";
        default:
            return "[Unknown]";
    }
}

String ToString(EventSubtype subtype)
{
    return std::to_string(static_cast<int>(subtype));

    switch (subtype)
    {
        case EventSubtype::keyPressed:
            return "KeyPressed";
        case EventSubtype::keyHeld:
            return "KeyHeld";
        case EventSubtype::keyReleased:
            return "KeyReleased";
        default:
            return "[Unknown]";
    }
}
