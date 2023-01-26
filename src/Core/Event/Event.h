#pragma once

#include "Core/Container/String.h"

enum class EventType
{
    unknown = 0,

    key,
};

enum class EventSubtype
{
    unknown = 0,

    keyPressed = 1,
    keyHeld,
    keyReleased,
};

struct Event
{
    EventType type = EventType::unknown;
    EventSubtype subtype = EventSubtype::unknown;

    Event(EventType newType) : type(newType) {}

    virtual String ToString() = 0;
};

String ToString(EventType type);

String ToString(EventSubtype subtype);
