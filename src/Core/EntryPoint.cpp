#include "Core/EntryPoint.h"

void EntryPoint::Run()
{
    _context.tty.SetMode(IO::TTYMode::Raw);
    
    _context.tty.Write(
        _context.sequence.Get(UI::SequenceString::EnterCAMode) + 
        _context.sequence.Get(UI::SequenceString::ClearScreen) + 
        "\x1b[>u\x1b[=" + std::to_string(0b1111) + "u"
    );

    _context.tty.Read([this](const String& bytes, int status)
    {
        if (bytes[0] == '\x1B')
            ParseInputSequence(bytes);
        else
            ParseInputRaw(bytes);
    });
    
    _context.loop.Run();
    
    _context.tty.Write(
        "\x1b[<u" + 
        _context.sequence.Get(UI::SequenceString::ClearScreen) +
        _context.sequence.Get(UI::SequenceString::ExitCAMode)
    );
    
    _context.tty.ResetMode();
}

void EntryPoint::On(Event& event)
{
    _buffer.On(event);
}

void EntryPoint::ParseInputRaw(const String& bytes)
{
}

void EntryPoint::ParseInputSequence(const String& bytes)
{
    UintSize cursor = 1;

    if (bytes[cursor] == '[') 
    {
        ParseInputSequenceKeyboard(bytes, cursor);
    }
}

void EntryPoint::ParseInputSequenceKeyboard(const String& bytes, UintSize& cursor)
{
    KeyEvent event;
    event.type = EventType::Key;
    event.subtype = EventSubtype::KeyPressed;

    ++cursor;
    
    if (Utility::IsIntegerByte(bytes[cursor])) 
    {
        event.key = static_cast<Key>(Utility::FindIntegerSubBytes(bytes, cursor));
        event.codepoint = static_cast<int>(event.key);

        if (bytes[cursor] == ':')
        {
            ++cursor;

            if (Utility::IsIntegerByte(bytes[cursor]))
            {
                event.codepoint = Utility::FindIntegerSubBytes(bytes, cursor);
            }
            else if (bytes[cursor] == ':')
            {
                ++cursor;
                int idk = Utility::FindIntegerSubBytes(bytes, cursor);
            }
        }
        
        if (bytes[cursor] == ';')
        {
            ++cursor;

            event.modifierKey = static_cast<ModifierKey>(Utility::FindIntegerSubBytes(bytes, cursor) - 1);

            if (bytes[cursor] == ':')
            {
                ++cursor;

                event.subtype = static_cast<EventSubtype>(Utility::FindIntegerSubBytes(bytes, cursor));
            }
        } 
    }

    On(event);
}
