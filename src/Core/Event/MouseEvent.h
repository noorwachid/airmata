#pragma once

#include "Core/Container/Vector.h"
#include "Core/Event/Event.h"

struct MouseEvent : Event
{
    Vector2 position;
};

enum class MouseButton 
{
    Left,
    Middle,
    Right,
};

String ToString(MouseButton button);

struct MouseButtonEvent : MouseEvent
{
    MouseButton button;

    virtual String ToString() override;
};

struct MouseScrollEvent : MouseEvent
{
    Vector2 direction;

    virtual String ToString() override;
};

