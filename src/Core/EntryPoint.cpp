#include "Core/EntryPoint.h"
#include "Core/Event/MouseEvent.h"

void EntryPoint::Run()
{
    Enter();

    context.loop.Run();

    Exit();
}

void EntryPoint::On(Event& event) { 
    buffer.On(event); 

    context.tty.Write(event.ToString() + "\n");
}

void EntryPoint::Enter()
{
    context.tty.SetMode(IO::TTYMode::Raw);

    context.tty.Write(
        context.sequence.Get(UI::SequenceString::EnterCAMode) + 
        context.sequence.Get(UI::SequenceString::ClearScreen) +
        context.sequence.Get(UI::SequenceString::CursorInvisible) + 
        context.sequence.EnableKeyboard() +
        context.sequence.EnableMouse() 
    );

    context.tty.Read(
        [this](const String& data, int status)
        {
            data.size() > 2 && data[0] == '\x1B' && data[1] == '['
                ? ParseInputSequence(data)
                : ParseInputRaw(data);
        }
    );

    Event enterEvent;
    enterEvent.name = "ProgramEnter";

    On(enterEvent);
}

void EntryPoint::Exit()
{
    Event exitEvent;
    exitEvent.name = "ProgramExit";

    On(exitEvent);

    context.tty.Write(
        context.sequence.DisableMouse() +
        context.sequence.DisableKeyboard() +
        context.sequence.Get(UI::SequenceString::ClearScreen) +
        context.sequence.Get(UI::SequenceString::CursorVisible) + 
        context.sequence.Get(UI::SequenceString::ExitCAMode)
    );

    context.tty.ResetMode();
}

void EntryPoint::ParseInputRaw(const String& data) {}

void EntryPoint::ParseInputSequence(const String& data)
{
    String escaped;

    for (char character: data) 
    {
        if (character < ' ')
            escaped += "[" + std::to_string((int) character) + "]";
        else
            escaped += character;
    }

    context.tty.Write(escaped + "\n");

    return data[2] != '<'
        ? ParseInputKeyboardSequence(data)
        : ParseInputMouseSequence(data);
}

void EntryPoint::ParseInputKeyboardSequence(const String& sequence)
{
    KeyEvent event;
    event.name = "KeyPress";
    event.codepoint = 0;
    event.modifierKey = ModifierKey::None;

    UintSize cursor = 2;

    switch (sequence[cursor]) 
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            // Normal key
            event.codepoint = Utility::FindIntegerSubBytes(sequence, cursor);
            event.key = static_cast<Key>(event.codepoint);
            
            if (sequence[cursor] == 'u')
            {
                break;
            }

            if (sequence[cursor] == ':') 
            {
                ++cursor;

                if (Utility::IsIntegerByte(sequence[cursor])) 
                    event.codepoint = Utility::FindIntegerSubBytes(sequence, cursor);
            }

            if (sequence[cursor] == ':') 
            {
                ++cursor;

                if (Utility::IsIntegerByte(sequence[cursor])) 
                    int scancode = Utility::FindIntegerSubBytes(sequence, cursor);
            }

            if (sequence[cursor] == ';') 
            {
                ++cursor;

                if (Utility::IsIntegerByte(sequence[cursor])) 
                    event.modifierKey = static_cast<ModifierKey>(Utility::FindIntegerSubBytes(sequence, cursor) - 1);
            }

            if (sequence[cursor] == ':') 
            {
                ++cursor;

                if (Utility::IsIntegerByte(sequence[cursor])) 
                {
                    switch (Utility::FindIntegerSubBytes(sequence, cursor))
                    {
                        case 1: break;
                        case 2: break;
                        case 3: event.name = "KeyRelease"; break;
                        default: break;
                    }
                }
            }
            break;

        // Arrow
        case 'A': event.key = Key::Up; break;
        case 'B': event.key = Key::Down; break;
        case 'C': event.key = Key::Right; break;
        case 'D': event.key = Key::Left; break;
    }

    return On(event);
}

void EntryPoint::ParseInputMouseSequence(const String& sequence)
{
    UintSize cursor = 3;
    bool pressed = true;

    if (Utility::IsIntegerByte(sequence[cursor]))
    {
        int value = Utility::FindIntegerSubBytes(sequence, cursor);
        UintSize strength = 1;
        Vector2 position;

        if (sequence[cursor] == ';')
        {
            ++cursor;

            if (Utility::IsIntegerByte(sequence[cursor]))
            {
                position.x = Utility::FindIntegerSubBytes(sequence, cursor) - 1;

                if (sequence[cursor] == ';')
                {
                    ++cursor;

                    if (Utility::IsIntegerByte(sequence[cursor]))
                    {
                        position.y = Utility::FindIntegerSubBytes(sequence, cursor) - 1;

                        if (sequence[cursor] == 'm')
                            pressed = false;
                    }
                }
            }
        }


        for (UintSize i = cursor; i < sequence.size(); ++i) 
            if (sequence[i] == '\x1B')
                ++strength;

        switch (value) 
        {
            case 64: 
            {
                MouseScrollEvent event;
                event.name = "MouseScroll";
                event.position = position;
                event.direction.y = -1 * strength;
                On(event);
                break;
            }

            case 65: 
            {
                MouseScrollEvent event;
                event.name = "MouseScroll";
                event.position = position;
                event.direction.y = 1 * strength;
                On(event);
                break;
            }

            case 66: 
            {
                MouseScrollEvent event;
                event.name = "MouseScroll";
                event.position = position;
                event.direction.x = -1 * strength;
                On(event);
                break;
            }

            case 67: 
            {
                MouseScrollEvent event;
                event.name = "MouseScroll";
                event.position = position;
                event.direction.x = 1 * strength;
                On(event);
                break;
            }

            default:
            {
                MouseButtonEvent event;
                event.name = pressed ? "MousePress" : "MouseRelease";
                event.position = position;
                event.button = value == 0 ? MouseButton::Left : MouseButton::Right;
                On(event);
                break;
            }
        }
    }
}
