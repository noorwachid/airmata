#include "Core/Mode.h"

String ToString(Mode mode)
{
    switch (mode) 
    {
        case Mode::WideMove: return "WideMove";
        case Mode::PrecicionMove: return "PrecicionMove";
        case Mode::Insert: return "Insert";
        default: return "[Unknown]";
    }
}

