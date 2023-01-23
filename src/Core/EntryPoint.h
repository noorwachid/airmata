#pragma once

#include "Core/Event/KeyEvent.h"
#include "Core/IO/Loop.h"
#include "Core/IO/Resource.h"
#include "Core/Integer.h"
#include "Core/UI/Component/Buffer.h"
#include "Core/UI/Sequence.h"
#include "Core/Utility/ByteChecker.h"
#include "Core/Utility/EnumBitManipulator.h"

class EntryPoint
{
  public:
    void Run();

    void On(Event& event);

  private:
    void ParseInputRaw(const String& bytes);

    void ParseInputSequence(const String& bytes);

    void ParseInputSequenceKeyboard(const String& bytes, UintSize& cursor);

    Context _context;
    UI::Buffer _buffer{_context};
};
