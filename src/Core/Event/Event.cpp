#include "Core/Event/Event.h"

String ToString(EventType type)
{
    switch (type) 
    {
        case EventType::Key: return "Key";
        default: return "[Unknown]";
    }
}

String ToString(EventSubtype subtype)
{
    return std::to_string(static_cast<int>(subtype));

    switch (subtype) 
    {
        case EventSubtype::KeyPressed: return "KeyPressed";
        case EventSubtype::KeyHeld: return "KeyHeld";
        case EventSubtype::KeyReleased: return "KeyReleased";
        default: return "[Unknown]";
    }
}
