#pragma once

#include "Core/IO/Loop.h"
#include "Core/IO/Resource.h"
#include "Core/UI/Sequence.h"

enum class Mode
{
    motion,
    insertion,
};

struct Context
{
    Mode mode = Mode::motion;

    IO::Loop loop;
    IO::TTY tty{loop, 0};

    UI::Sequence sequence = UI::Sequence::createFromEnv();
};
