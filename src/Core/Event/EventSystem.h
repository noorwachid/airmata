#pragma once 

#include "Core/Container/Array.h"
#include "Core/Container/Function.h"
#include "Core/Event/Event.h"
#include <cstdlib>

using EventListener = Function<void (Event&)>;

class EventSystem 
{
public:
    void Listen(const EventListener& newListener)
    {
        listeners.push_back(newListener);
    }

    void Emit(Event& event)
    {
        for (auto& listener: listeners) 
        {
            listener(event);
        }
    }

private:
    Array<EventListener> listeners;
};

