#include "Core/EntryPoint.h"

void EntryPoint::Run()
{
    _tty.SetMode(IO::TTYMode::Raw);
    
    _tty.Write(
        _sequence.Get(UI::SequenceString::EnterCAMode) + 
        _sequence.Get(UI::SequenceString::ClearScreen) + 
        "\x1b[>u\x1b[=" + std::to_string(0b1111) + "u"
    );

    _tty.Read([this](const String& buffer, int status)
    {
        if (buffer == "\x1B[92u") 
        {
            return _tty.StopReading();
        }

        if (buffer[0] == '\x1B') {
            size_t cursor = 1;

            if (buffer[cursor] == '[') 
            {
                KeyEvent event;
                event.type = EventType::Key;
                event.subtype = EventSubtype::KeyPressed;

                ++cursor;
                
                if (Utility::IsIntegerByte(buffer[cursor])) 
                {
                    event.key = static_cast<Key>(Utility::FindIntegerSubBytes(buffer, cursor));
                    event.codepoint = static_cast<int>(event.key);

                    if (buffer[cursor] == ':')
                    {
                        ++cursor;

                        if (Utility::IsIntegerByte(buffer[cursor]))
                        {
                            event.codepoint = Utility::FindIntegerSubBytes(buffer, cursor);
                        }
                        else if (buffer[cursor] == ':')
                        {
                            ++cursor;
                            int idk = Utility::FindIntegerSubBytes(buffer, cursor);
                        }
                    }
                    
                    if (buffer[cursor] == ';')
                    {
                        ++cursor;

                        event.modifierKey = static_cast<ModifierKey>(Utility::FindIntegerSubBytes(buffer, cursor) - 1);

                        if (buffer[cursor] == ':')
                        {
                            ++cursor;

                            event.subtype = static_cast<EventSubtype>(Utility::FindIntegerSubBytes(buffer, cursor));
                        }
                    } 
                }

                On(event);
            }
        } else {
        }
    });
    
    _loop.Run();
    
    _tty.Write(
        "\x1b[<u" + 
        _sequence.Get(UI::SequenceString::ClearScreen) +
        _sequence.Get(UI::SequenceString::ExitCAMode)
    );
    
    _tty.ResetMode();
}

void EntryPoint::On(Event& event)
{
    if (event.subtype == EventSubtype::KeyPressed)
    {
        KeyEvent& keyEvent = static_cast<KeyEvent&>(event);

        switch (keyEvent.key) 
        {
            case Key::H:
                --_buffer._cursor.x;
                break;

            case Key::T:
                --_buffer._cursor.y;
                break;

            case Key::N:
                ++_buffer._cursor.y;
                break;

            case Key::S:
                ++_buffer._cursor.x;
                break;

            default: break;
        }

        _buffer.Render(_tty, _sequence);
    }
}
