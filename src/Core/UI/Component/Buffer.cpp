#include "Core/Event/KeyEvent.h"
#include "Core/UI/Component/Buffer.h"

namespace UI 
{
    Buffer::Buffer(Context &context) : Component{context} {}

    void UI::Buffer::On(Event &event) 
    {
        if (event.subtype == EventSubtype::KeyPressed) 
        {
            KeyEvent &keyEvent = static_cast<KeyEvent &>(event);

            switch (keyEvent.key) 
            {
                case Key::Backslash:
                    _context.loop.Stop();
                    break;

                case Key::H:
                    --_cursor.x;
                    break;

                case Key::T:
                    --_cursor.y;
                    break;

                case Key::N:
                    ++_cursor.y;
                    break;

                case Key::S:
                    ++_cursor.x;
                    break;

                default:
                    break;
            }

            Render();
        }
    }

    void Buffer::Render() 
    {
        _context.tty.Write(_context.sequence.CreateCursorMover(_cursor));
    }
}
