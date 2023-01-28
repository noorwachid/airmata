#pragma once

#include "Core/IO/Loop.h"
#include "Core/IO/Resource.h"
#include "Core/UI/Sequence.h"

enum class Mode
{
    WideMove,
    PrecicionMove,
    Insert,
};

struct Context
{
    Mode mode = Mode::WideMove;

    IO::Loop loop;
    IO::TTY tty{loop, 0};

    UI::Sequence sequence = UI::Sequence::CreateFromEnv();
};
