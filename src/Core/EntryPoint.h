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
    void Enter();

    void Run();

    void On(Event& event);

    void Exit();

private:
    void ParseInputRaw(const String& data);

    void ParseInputSequence(const String& data);

    void ParseInputKeyboardSequence(const String& data);

    void ParseInputMouseSequence(const String& data);

    Context context;
    UI::Buffer buffer{context};
};
