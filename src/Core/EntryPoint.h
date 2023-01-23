#pragma once

#include "Core/Event/KeyEvent.h"
#include "Core/IO/Loop.h"
#include "Core/IO/Resource.h"
#include "Core/UI/Buffer.h"
#include "Core/UI/Sequence.h"
#include "Core/Utility/ByteChecker.h"
#include "Core/Utility/EnumBitManipulator.h"

enum class Mode 
{
    Motion,
    Insertion,
};

class EntryPoint
{
  public:
    void Run();

    void On(Event& event);

  private:
    IO::Loop _loop;
    IO::TTY _tty{_loop, 0};
    
    UI::Sequence _sequence = UI::Sequence::CreateFromEnv();

    UI::Buffer _buffer;

    Mode _mode = Mode::Motion;
};
