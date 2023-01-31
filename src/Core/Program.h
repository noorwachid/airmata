#pragma once

#include "Core/Event/KeyEvent.h"
#include "Core/IO/Loop.h"
#include "Core/IO/Resource.h"
#include "Core/Integral.h"
#include "Core/Mode.h"
#include "Core/UI/InputSystem.h"
#include "Core/UI/Object/Document.h"
#include "Core/UI/Sequence.h"
#include "Core/Utility/ByteChecker.h"
#include "Core/Utility/EnumBitManipulator.h"

class Program : public EventSystem
{
public:
    void Enter();

    void Run();

    void On(Event& event);

    void Exit();

public:
    bool terminating = false;

    Mode mode = Mode::WideMove;

    // Order dependent constructors

    IO::Loop loop;
    IO::TTY tty{loop, 0};

    UI::Sequence sequence = UI::Sequence::CreateFromEnv();

    UI::Document document{*this};
    UI::InputSystem input{*this};
};
