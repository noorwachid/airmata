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
    void ParseInputRaw(const String& data);

    void ParseInputSequence(const String& data);

    void ParseInputKeyboardSequence(const String& data, UintSize& cursor);

    Context context;
    UI::Buffer buffer{context};
};
