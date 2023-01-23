#pragma once

#include "Core/IO/Loop.h"
#include "Core/IO/Resource.h"
#include "Core/UI/Sequence.h"

enum class Mode 
{
    Motion,
    Insertion,
};

struct Context
{
    Mode mode = Mode::Motion;

    IO::Loop loop;
    IO::TTY tty{loop, 0};

    UI::Sequence sequence = UI::Sequence::CreateFromEnv();
};
