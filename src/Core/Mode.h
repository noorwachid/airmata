#pragma once

#include "Core/Event/EventSystem.h"
#include "Core/IO/Loop.h"
#include "Core/IO/Resource.h"
#include "Core/UI/Sequence.h"

enum class Mode
{
    WideMove,
    PrecicionMove,
    Insert,
};

String ToString(Mode mode);
