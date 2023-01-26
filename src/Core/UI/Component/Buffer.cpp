#include "Core/UI/Component/Buffer.h"
#include "Core/Event/KeyEvent.h"
#include "Core/IO/Action.h"

namespace UI
{
    Buffer::Buffer(Context& newContext) : Component{newContext} {}

    void UI::Buffer::On(Event& event)
    {
        if (event.subtype == EventSubtype::keyPressed)
        {
            KeyEvent& keyEvent = static_cast<KeyEvent&>(event);

            switch (keyEvent.key)
            {
                case Key::Backslash:
                    context.loop.Stop();
                    break;

                case Key::H:
                    --cursor.x;
                    break;

                case Key::T:
                    --cursor.y;
                    break;

                case Key::N:
                    ++cursor.y;
                    break;

                case Key::S:
                    ++cursor.x;
                    break;

                case Key::Space:
                    OpenFile();
                    break;

                default:
                    break;
            }

            Render();
        }
    }

    void Buffer::Render() { context.tty.Write(context.sequence.moveCursor(cursor)); }

    void Buffer::OpenFile()
    {
        context.loop.fs.OpenFile(
            "./testfile.txt",
            [this](int fd)
            {
                context.loop.fs.ReadFile(
                    fd, 16,
                    [this](const String& buffer) {
                        context.tty.Write(context.sequence.moveCursor({0, 1}) + buffer);
                    }
                );
            }
        );
    }
}
