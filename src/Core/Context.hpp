#pragma once

#include "Core/IO/Loop.hpp"
#include "Core/IO/Resource.hpp"
#include "Core/UI/Sequence.hpp"

enum class Mode {
    motion,
    insertion,
};

struct Context {
    Mode mode = Mode::motion;

    IO::Loop loop;
    IO::TTY tty{loop, 0};

    UI::Sequence sequence = UI::Sequence::createFromEnv();
};
