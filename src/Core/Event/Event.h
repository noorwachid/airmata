#pragma once

#include "Core/Container/String.h"

enum class EventType
{
    Unknown = 0,

    Key,
};

enum class EventSubtype
{
    Unknown = 0,
    
    KeyPressed = 1,
    KeyHeld,
    KeyReleased,
};

struct Event 
{
    EventType type = EventType::Unknown;
    EventSubtype subtype = EventSubtype::Unknown;

    Event(EventType newType): type(newType) {}

    virtual String ToString() = 0;
};

String ToString(EventType type);

String ToString(EventSubtype subtype);
