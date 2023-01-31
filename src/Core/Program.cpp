#include "Core/Program.h"
#include "Core/Event/MouseEvent.h"
#include <iostream>

void Program::Run()
{
    try 
    {
        Enter();

        loop.Run();

        Exit();
    } 
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << "\n";
    }
}

void Program::On(Event& event) 
{
    document.On(event); 

    if (terminating) 
        return;

    document.Render();
}

void Program::Enter()
{
    Listen([this](Event& event){ On(event); });

    tty.SetMode(IO::TTYMode::Raw);

    tty.Write(
        sequence.Get(UI::SequenceString::EnterCAMode) + 
        sequence.Get(UI::SequenceString::ClearScreen) +
        sequence.EnableKeyboard() +
        sequence.EnableMouse() 
    );

    tty.Read(
        [this](const String& buffer, int status)
        {
            input.Parse(buffer);
        }
    );

    Event enterEvent;
    enterEvent.name = "ProgramEnter";

    Emit(enterEvent);
}

void Program::Exit()
{
    Event exitEvent;
    exitEvent.name = "ProgramExit";

    Emit(exitEvent);

    tty.Write(
        sequence.DisableMouse() +
        sequence.DisableKeyboard() +
        sequence.Get(UI::SequenceString::ClearScreen) +
        sequence.Get(UI::SequenceString::ExitCAMode)
    );

    tty.ResetMode();
}

