#pragma once

#include "Core/Event/KeyEvent.hpp"
#include "Core/IO/Loop.hpp"
#include "Core/IO/Resource.hpp"
#include "Core/Integer.hpp"
#include "Core/UI/Component/Buffer.hpp"
#include "Core/UI/Sequence.hpp"
#include "Core/Utility/ByteChecker.hpp"
#include "Core/Utility/EnumBitManipulator.hpp"

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
