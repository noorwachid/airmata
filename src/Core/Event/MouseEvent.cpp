#include "Core/Event/MouseEvent.h"

String ToString(MouseButton button)
{
    switch (button)
    {
        case MouseButton::Left: return "Left";
        case MouseButton::Middle: return "Middle";
        case MouseButton::Right: return "Right";
        default: return "[Unknown]";
    }
}

String MouseButtonEvent::ToString()
{
    return name + " " + position.ToString() + " " + ::ToString(button);
}

String MouseScrollEvent::ToString()
{
    return name + " " + position.ToString() + " " + direction.ToString();
}
