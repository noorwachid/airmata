#pragma once 

#include "Core/Container/String.h"
#include "Core/Event/Event.h"

struct BufferEvent : Event
{
    String buffer;
};
