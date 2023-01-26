#include "Core/EntryPoint.h"

void EntryPoint::Run()
{
    context.tty.SetMode(IO::TTYMode::Raw);

    context.tty.Write(
        context.sequence.Get(UI::SequenceString::EnterCAMode) + context.sequence.Get(UI::SequenceString::ClearScreen) +
        "\x1b[>u\x1b[=" + std::to_string(0b1111) + "u"
    );

    context.tty.Read(
        [this](const String& data, int status)
        {
            if (data[0] == '\x1B')
                ParseInputSequence(data);
            else
                ParseInputRaw(data);
        }
    );

    context.loop.Run();

    context.tty.Write(
        "\x1b[<u" + context.sequence.Get(UI::SequenceString::ClearScreen) +
        context.sequence.Get(UI::SequenceString::ExitCAMode)
    );

    context.tty.ResetMode();
}

void EntryPoint::On(Event& event) { buffer.On(event); }

void EntryPoint::ParseInputRaw(const String& data) {}

void EntryPoint::ParseInputSequence(const String& data)
{
    UintSize cursor = 1;

    if (data[cursor] == '[')
    {
        ParseInputKeyboardSequence(data, cursor);
    }
}

void EntryPoint::ParseInputKeyboardSequence(const String& data, UintSize& cursor)
{
    KeyEvent event;
    event.type = EventType::key;
    event.subtype = EventSubtype::keyPressed;

    ++cursor;

    if (Utility::IsIntegerByte(data[cursor]))
    {
        event.key = static_cast<Key>(Utility::FindIntegerSubBytes(data, cursor));
        event.codepoint = static_cast<int>(event.key);

        if (data[cursor] == ':')
        {
            ++cursor;

            if (Utility::IsIntegerByte(data[cursor]))
            {
                event.codepoint = Utility::FindIntegerSubBytes(data, cursor);
            }
            else if (data[cursor] == ':')
            {
                ++cursor;
                int idk = Utility::FindIntegerSubBytes(data, cursor);
            }
        }

        if (data[cursor] == ';')
        {
            ++cursor;

            event.modifierKey = static_cast<ModifierKey>(Utility::FindIntegerSubBytes(data, cursor) - 1);

            if (data[cursor] == ':')
            {
                ++cursor;

                event.subtype = static_cast<EventSubtype>(Utility::FindIntegerSubBytes(data, cursor));
            }
        }
    }

    On(event);
}
