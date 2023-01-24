#include "Core/UI/Component/Buffer.hpp"
#include "Core/Event/KeyEvent.hpp"
#include "Core/IO/Action.hpp"

namespace UI {
    Buffer::Buffer(Context& newContext) : Component{newContext} {}

    void UI::Buffer::on(Event& event) {
        if (event.subtype == EventSubtype::keyPressed) {
            KeyEvent& keyEvent = static_cast<KeyEvent&>(event);

            switch (keyEvent.key) {
                case Key::backslash:
                    context.loop.stop();
                    break;

                case Key::h:
                    --cursor.x;
                    break;

                case Key::t:
                    --cursor.y;
                    break;

                case Key::n:
                    ++cursor.y;
                    break;

                case Key::s:
                    ++cursor.x;
                    break;

                case Key::space:
                    openFile();
                    break;

                default:
                    break;
            }

            render();
        }
    }

    void Buffer::render() { context.tty.write(context.sequence.moveCursor(cursor)); }

    void Buffer::openFile() {}
}
