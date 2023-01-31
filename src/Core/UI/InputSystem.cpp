#include "Core/UI/InputSystem.h"
#include "Core/Container/Vector.h"
#include "Core/Event/BufferEvent.h"
#include "Core/Event/KeyEvent.h"
#include "Core/Event/MouseEvent.h"
#include "Core/Integral.h"
#include "Core/Utility/ByteChecker.h"

namespace UI
{
    void InputSystem::Parse(const String& data)
    {
        if (data.size() > 2 && data[0] == '\x1B' && data[1] == '[')
        {
            return data[2] != '<' ? ParseKeyboard(data) : ParseMouse(data);
        }

        BufferEvent bufferEvent;
        event.Emit(bufferEvent);
    }

    void InputSystem::ParseKeyboard(const String& sequence)
    {
        KeyEvent keyEvent;
        keyEvent.name = "KeyPress";
        keyEvent.codepoint = 0;
        keyEvent.modifierKey = ModifierKey::None;

        usize cursor = 2;

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
                // Characters
                keyEvent.codepoint = Utility::FindIntegerSubBytes(sequence, cursor);
                keyEvent.key = static_cast<Key>(keyEvent.codepoint);

                if (sequence[cursor] == 'u')
                {
                    break;
                }

                if (sequence[cursor] == ':')
                {
                    ++cursor;

                    if (Utility::IsIntegerByte(sequence[cursor]))
                        keyEvent.codepoint = Utility::FindIntegerSubBytes(sequence, cursor);
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
                        keyEvent.modifierKey =
                            static_cast<ModifierKey>(Utility::FindIntegerSubBytes(sequence, cursor) - 1);
                }

                if (sequence[cursor] == ':')
                {
                    ++cursor;

                    if (Utility::IsIntegerByte(sequence[cursor]))
                    {
                        switch (Utility::FindIntegerSubBytes(sequence, cursor))
                        {
                            default:
                                break;
                            case 1:
                                break;
                            case 2:
                                break;
                            case 3:
                                keyEvent.name = "KeyRelease";
                                break;
                        }
                    }
                }

                switch (sequence[cursor])
                {
                    // Characters
                    default:
                        break;
                    case 'u':
                        break;

                        // Arrows
                    case 'A':
                        keyEvent.key = Key::Up;
                        break;
                    case 'B':
                        keyEvent.key = Key::Down;
                        break;
                    case 'C':
                        keyEvent.key = Key::Right;
                        break;
                    case 'D':
                        keyEvent.key = Key::Left;
                        break;
                }
                break;

                // Arrows
            case 'A':
                keyEvent.key = Key::Up;
                break;
            case 'B':
                keyEvent.key = Key::Down;
                break;
            case 'C':
                keyEvent.key = Key::Right;
                break;
            case 'D':
                keyEvent.key = Key::Left;
                break;
        }

        return event.Emit(keyEvent);
    }

    void InputSystem::ParseMouse(const String& sequence)
    {
        usize cursor = 3;
        bool pressed = true;

        if (Utility::IsIntegerByte(sequence[cursor]))
        {
            int value = Utility::FindIntegerSubBytes(sequence, cursor);
            usize strength = 1;
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

            for (usize i = cursor; i < sequence.size(); ++i)
                if (sequence[i] == '\x1B')
                    ++strength;

            switch (value)
            {
                case 64:
                {
                    MouseScrollEvent mouseEvent;
                    mouseEvent.name = "MouseScroll";
                    mouseEvent.position = position;
                    mouseEvent.direction.y = -1 * strength;
                    event.Emit(mouseEvent);
                    break;
                }

                case 65:
                {
                    MouseScrollEvent mouseEvent;
                    mouseEvent.name = "MouseScroll";
                    mouseEvent.position = position;
                    mouseEvent.direction.y = 1 * strength;
                    event.Emit(mouseEvent);
                    break;
                }

                case 66:
                {
                    MouseScrollEvent mouseEvent;
                    mouseEvent.name = "MouseScroll";
                    mouseEvent.position = position;
                    mouseEvent.direction.x = -1 * strength;
                    event.Emit(mouseEvent);
                    break;
                }

                case 67:
                {
                    MouseScrollEvent mouseEvent;
                    mouseEvent.name = "MouseScroll";
                    mouseEvent.position = position;
                    mouseEvent.direction.x = 1 * strength;
                    event.Emit(mouseEvent);
                    break;
                }

                default:
                {
                    MouseButtonEvent mouseEvent;
                    mouseEvent.name = pressed ? "MousePress" : "MouseRelease";
                    mouseEvent.position = position;
                    mouseEvent.button = value == 0 ? MouseButton::Left : MouseButton::Right;
                    event.Emit(mouseEvent);
                    break;
                }
            }
        }
    }
}
