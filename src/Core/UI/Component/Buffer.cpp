#include "Core/UI/Component/Buffer.h"
#include "Core/Event/KeyEvent.h"
#include "Core/IO/Action.h"

namespace UI
{
    String ToString(Mode mode)
    {
        switch (mode) 
        {
            case Mode::WideMove: return "WideMove";
            case Mode::PrecicionMove: return "PrecicionMove";
            case Mode::Insert: return "Insert";
            default: return "[Unknown]";
        }
    }

    Buffer::Buffer(Context& newContext) : Component{newContext} 
    {
    }

    void UI::Buffer::On(Event& event)
    {
        if (event.name == "KeyPress")
        {
            KeyEvent& keyEvent = static_cast<KeyEvent&>(event);

            if (keyEvent.key == Key::Backslash)
                return context.tty.StopReading();

            return;

            if (context.mode == Mode::WideMove) 
            {
                switch (keyEvent.key)
                {
                    case Key::Escape:
                        if ((keyEvent.modifierKey & ModifierKey::Shift) == ModifierKey::Shift)
                            context.mode = Mode::PrecicionMove;
                        else
                            context.mode = Mode::WideMove;
                        break;

                    case Key::H:
                        JumpPreviousWord();
                        break;

                    case Key::T:
                        break;

                    case Key::N:
                        break;

                    case Key::S:
                        JumpNextWord();
                        break;

                    case Key::Return:
                        context.mode = Mode::Insert;
                        break;

                    default:
                        break;
                }
            } 
            else if (context.mode == Mode::PrecicionMove)
            {
                switch (keyEvent.key)
                {
                    case Key::Escape:
                        if ((keyEvent.modifierKey & ModifierKey::Shift) == ModifierKey::Shift)
                            context.mode = Mode::PrecicionMove;
                        else
                            context.mode = Mode::WideMove;
                        break;

                    case Key::H:
                        MoveCursorLeft();
                        break;

                    case Key::T:
                        MoveCursorUp();
                        break;

                    case Key::N:
                        MoveCursorDown();
                        break;

                    case Key::S:
                        MoveCursorRight();
                        break;

                    default:
                        break;
                }
            }
            else 
            {
                switch (keyEvent.key)
                {
                    case Key::Escape:
                        if ((keyEvent.modifierKey & ModifierKey::Shift) == ModifierKey::Shift)
                            context.mode = Mode::PrecicionMove;
                        else
                            context.mode = Mode::WideMove;

                        if (cursor.x > 0)
                            --cursor.x;
                        break;

                    case Key::Delete:
                        DeleteBeforeCursor();
                        break;

                    default:
                        InsertUnderCursor({ (char) keyEvent.codepoint, 0 });
                        break;
                }
            }
        }

        // Render();
    }

    void Buffer::MoveCursorLeft()
    {
        if (cursor.x > 0)
            --cursor.x;
    }

    void Buffer::MoveCursorRight()
    {
        if (cursor.x < GetCursorXBounding() - 1)
            ++cursor.x;
    }

    void Buffer::MoveCursorUp()
    {
        if (cursor.y > 0)
        {
            bool eol = IsEOL();

            --cursor.y;

            if (eol || cursor.x > GetCursorXBounding() - 1) 
                MoveEOL();
        }
    }

    void Buffer::MoveCursorDown()
    {
        if (cursor.y < GetCursorYBounding() - 1)
        {
            bool eol = IsEOL();

            ++cursor.y;

            if (eol || cursor.x > GetCursorXBounding() - 1) 
                MoveEOL();
        }
    }

    void Buffer::JumpPreviousWord()
    {
        if (data.empty()) return;

        for (int i = cursor.x; i >= 0; --i)
        {
            if (!IsWord(data[cursor.y][i]))
            {
                cursor.x = i;
                return;
            }
        }
    }

    void Buffer::JumpNextWord()
    {
        if (data.empty()) return;

        // Find next word
        if (!IsWord(data[cursor.y][cursor.x])) 
        {
            for (int i = cursor.x; i < GetCursorXBounding(); ++i)
            {
                if (IsWord(data[cursor.y][i]))
                {
                    cursor.x = i;
                    break;
                }
            }

            return;
        }

        // Find non word
        for (int i = cursor.x; i < GetCursorXBounding(); ++i)
        {
            if (!IsWord(data[cursor.y][i]))
            {
                cursor.x = i;
                
                // Next word
                if (data[cursor.y][i] == ' ') 
                    ++cursor.x;

                return;
            }
        }
    }

    void Buffer::Render() 
    { 
        String renderData;

        for (int i = 0; i < data.size(); ++i) 
        {
            renderData += context.sequence.MoveCursor({ 0, i });
            renderData += data[i] + String(GetSize().x - data[i].size(), ' ');
        }

        context.tty.Write(
            renderData +
            context.sequence.MoveCursor(cursor) + 
            context.sequence.SetBG(0xFF0000) + GetCharacterUnderCursor() +
            context.sequence.ResetAttribute() +
            RenderStatusLine()
        );
    }

    String Buffer::RenderStatusLine()
    {
        String modeString = " " + ToString(context.mode);
        String cursorString = cursor.ToString() + " ";

        return 
            context.sequence.MoveCursor({ 0, GetSize().y - 1}) + 
            context.sequence.SetBG(0x5500AA) +
            modeString + String(GetSize().x - (modeString.size() + cursorString.size()), ' ') + cursorString +
            context.sequence.ResetAttribute();
    }

    void Buffer::InsertUnderCursor(const String& string)
    {
        if (data.empty())
        {
            return data.push_back(string);
        }

        String& line = data[cursor.y];
        line.insert(cursor.x, string);
    }

    int Buffer::GetCursorXBounding()
    {
        if (data.empty())
            return 1;

        return data[cursor.y].size();
    }

    int Buffer::GetCursorYBounding()
    {
        if (data.empty())
            return 1;

        return data.size();
    }

    bool Buffer::IsEOL() { return cursor.x == GetCursorXBounding() - 1; }

    void Buffer::MoveEOL() { cursor.x = GetCursorXBounding() - 1; }

    String Buffer::GetCharacterUnderCursor()
    {
        if (data.empty())
            return " ";

        return {data[cursor.y][cursor.x], 0};
    }

    void Buffer::DeleteBeforeCursor() 
    {
        if (data.empty()) return;

        if (data[cursor.y].empty()) return;

        data[cursor.y].erase(cursor.x -1, 1);

        MoveCursorLeft();
    }

    void Buffer::DeleteUnderCursor() 
    {
    }

    void Buffer::DeleteAfterCursor() 
    {
    }
}
