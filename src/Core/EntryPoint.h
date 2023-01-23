#pragma once

#include "Core/Event/KeyEvent.h"
#include "Core/IO/Loop.h"
#include "Core/IO/Resource.h"
#include "Core/Integer.h"
#include "Core/UI/Component/Buffer.h"
#include "Core/UI/Sequence.h"
#include "Core/Utility/ByteChecker.h"
#include "Core/Utility/EnumBitManipulator.h"

class EntryPoint {
  public:
    void run();

    void on(Event& event);

  private:
    void parseInputRaw(const String& data);

    void parseInputSequence(const String& data);

    void parseInputSequenceKeyboard(const String& data, UintSize& cursor);

    Context context;
    UI::Buffer buffer{context};
};
