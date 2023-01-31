#pragma once 

#include "Core/Container/String.h"
#include "Core/Event/Event.h"
#include "Core/Event/EventSystem.h"

namespace UI 
{
    class InputSystem
    {
    public:
        InputSystem(EventSystem& newEvent): event(newEvent) {}

        void Parse(const String& buffer);

        void ParseKeyboard(const String& buffer);

        void ParseMouse(const String& buffer);

    private:
        EventSystem& event;
    };
} 
