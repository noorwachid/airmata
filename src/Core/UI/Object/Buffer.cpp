#include "Core/UI/Object/Buffer.h"
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

    Buffer::Buffer(Context& newContext) : Object{newContext} 
    {
        data.reserve(16);
        data = {
            "Lorem ipsum dolor sit amet, consectetur-adipiscing elit.",
            "Nunc vestibulum tristique purus, mollis rhoncus elit.",
            "",
            "Fusce varius urna tempus molestie suscipit.",
            // "Mauris accumsan posuere felis.",
            // "A Liquam sed mattis elit, eu convallis lectus.",
            // "Nam sagittis sem id viverra hendrerit.",
            // "Suspendisse hendrerit at risus pharetra aliquam.",
            // "Donec porta consectetur pellentesque.",
            // "Aliquam sed nisi quis ipsum pellentesque fermentum.",
            // "Duis sit amet condimentum arcu. Nulla at volutpat orci.",
            // "",
            // "Ut fermentum dui libero, non vestibulum urna egestas nec.",
            // "Cras sit amet commodo ex. Sed et condimentum nisi, a egestas eros.",
            // "Etiam vel est enim.",
            // "Aliquam dapibus, nulla et pretium interdum, ante lectus rhoncus est, eget dapibus odio quam ut ligula. Mauris pellentesque, ipsum vitae tristique finibus, mi justo porttitor justo, sed sagittis elit magna faucibus dui. Nunc tincidunt sapien id eleifend sagittis.",
            // ".",
            // "Nulla semper iaculis velit, eget finibus sem fermentum quis.",
            // "Phasellus ac finibus justo.",
            // "Integer commodo ligula sed tortor scelerisque, in dignissim nibh posuere.",
            // "In ac suscipit lacus, vitae malesuada risus.",
            // "Nunc porttitor laoreet nulla, vel pretium nulla dictum nec.",
            // "Nunc ut est sit amet nisl pellentesque commodo.",
            // ".",
            // "Aenean id sapien ac turpis scelerisque vehicula at sed sem.",
            // "Cras vestibulum pulvinar scelerisque.",
            // "Pellentesque sollicitudin quam nulla, ac malesuada lorem condimentum vitae.",
            // "Mauris vitae purus nec dui fringilla pharetra ac in elit.",
            // "Mauris sit amet odio neque.",
            // "Nullam sit amet massa feugiat, mattis tortor non, fermentum urna.",
            // "Nunc diam mi, feugiat eget porttitor vitae, vulputate nec ipsum.",
            // "In ut est sit amet odio consequat cursus et non lorem.",
            // "Nulla mattis justo in blandit faucibus.",
            // "Cras sit amet nibh sed lorem lacinia faucibus et et nisi.",
            // "Etiam congue dolor nisl, vitae laoreet ligula condimentum placerat.",
            // "Sed lacus tortor, placerat eu suscipit feugiat, vestibulum eu mauris.",
            // "Maecenas sed lacus sed odio viverra viverra.",
            // ".",
            // "Nulla egestas quam vel quam efficitur finibus eget non augue.",
            // "Vestibulum porttitor tortor ligula, quis suscipit velit egestas nec.",
            // "Suspendisse efficitur dui eget diam suscipit euismod.",
        };
    }

    void UI::Buffer::On(Event& event)
    {
        if (event.name == "KeyPress")
        {
            KeyEvent& keyEvent = static_cast<KeyEvent&>(event);

            if (keyEvent.key == Key::Backslash)
                return context.tty.StopReading();

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
                        JumpPreviousSentence();
                        break;

                    case Key::T:
                        JumpPreviousParagraph();
                        break;

                    case Key::N:
                        JumpNextParagraph();
                        break;

                    case Key::S:
                        JumpNextSentence();
                        break;

                    case Key::M:
                        JumpPreviousWord();
                        break;

                    case Key::W:
                        JumpPreviousLine();
                        break;

                    case Key::V:
                        JumpNextLine();
                        break;

                    case Key::Z:
                        JumpNextWord();
                        break;

                    case Key::Return:
                        context.mode = Mode::Insert;
                        break;

                    case Key::Left:
                        MoveCursorLeft();
                        break;

                    case Key::Up:
                        MoveCursorUp();
                        break;

                    case Key::Down:
                        MoveCursorDown();
                        break;

                    case Key::Right:
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
                        DeleteBefore();
                        break;

                    default:
                        Insert({ (char) keyEvent.codepoint, 0 });
                        break;
                }
            }
        }

        Render();
    }

    void Buffer::MoveCursorLeft()
    {
        if (cursor.x > 0)
            --cursor.x;
    }

    void Buffer::MoveCursorRight()
    {
        if (cursor.x < GetBoundingX() - 1)
            ++cursor.x;
    }

    void Buffer::MoveCursorUp()
    {
        if (cursor.y > 0)
        {
            --cursor.y;

            if (cursor.x > GetBoundingX() - 1) 
                MoveEOL();
        }
    }

    void Buffer::MoveCursorDown()
    {
        if (cursor.y < GetBoundingY() - 1)
        {
            ++cursor.y;

            if (cursor.x > GetBoundingX() - 1) 
                MoveEOL();
        }
    }

    void Buffer::JumpPreviousWord()
    {
        if (data.empty()) return;

        if (cursor.x > 0)
        {
            if (IsWord(data[cursor.y][cursor.x]))
            {
                if (data[cursor.y][cursor.x - 1] == ' ')
                {
                    cursor.x -= 2;
                }
                else if (!IsWord(data[cursor.y][cursor.x - 1]))
                {
                    --cursor.x;
                    return;
                }

                if (IsWord(data[cursor.y][cursor.x]))
                {
                    for (int i = cursor.x; i >= 0; --i)
                    {
                        if (!IsWord(data[cursor.y][i]))
                        {
                            cursor.x = i + 1;

                            return;
                        }
                        else if (i == 0)
                        {
                            cursor.x = 0;

                            return;
                        }
                    }
                }
                return;
            }

            if (IsWord(data[cursor.y][cursor.x - 1]))
            {
                --cursor.x;

                for (int i = cursor.x; i >= 0; --i)
                {
                    if (!IsWord(data[cursor.y][i]))
                    {
                        cursor.x = i + 1;

                        return;
                    }
                }
                return;
            }

            --cursor.x;
            return;
        }

    }

    void Buffer::JumpNextWord()
    {
        if (data.empty()) return;

        // Find next word
        if (!IsWord(data[cursor.y][cursor.x])) 
        {
            for (int i = cursor.x; i < GetBoundingX(); ++i)
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
        for (int i = cursor.x; i < GetBoundingX(); ++i)
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
            context.sequence.SetBG(0xFF0000) + Get() +
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

    void Buffer::Insert(const String& string)
    {
        if (data.empty())
        {
            return data.push_back(string);
        }

        String& line = data[cursor.y];
        line.insert(cursor.x, string);
    }

    int Buffer::GetBoundingX()
    {
        if (data.empty() || data[cursor.y].empty()) return 1;

        return data[cursor.y].size();
    }

    int Buffer::GetBoundingY()
    {
        if (data.empty())
            return 1;

        return data.size();
    }

    bool Buffer::IsEOL() { return cursor.x == GetBoundingX() - 1; }

    void Buffer::MoveEOL() 
    { 
        cursor.x = GetBoundingX() - 1; 
    }

    char Buffer::Get()
    {
        if (data.empty() || data[cursor.y].empty())
            return ' ';

        return data[cursor.y][cursor.x];
    }

    void Buffer::DeleteBefore() 
    {
        if (data.empty()) return;

        if (data[cursor.y].empty()) return;

        data[cursor.y].erase(cursor.x -1, 1);

        MoveCursorLeft();
    }

    void Buffer::Delete() 
    {
    }

    void Buffer::DeleteAfter() 
    {
    }

    void Buffer::JumpNextSentence() {}

    void Buffer::JumpPreviousSentence() {}

    void Buffer::JumpNextLine() 
    {
        if (cursor.y + 2 > GetBoundingY()) return;

        ++cursor.y;

        for (UintSize i = 0; i < GetBoundingX(); ++i) 
        {
            if (!IsWhitespace(data[cursor.y][i]))
            {
                cursor.x = i;
                return;
            }
        }
    }

    void Buffer::JumpPreviousLine() 
    {
        if (cursor.y - 1 < 0) return;

        --cursor.y;

        for (UintSize i = 0; i < GetBoundingX(); ++i) 
        {
            if (!IsWhitespace(data[cursor.y][i]))
            {
                cursor.x = i;
                return;
            }
        }
    }

    void Buffer::JumpNextParagraph() {}

    void Buffer::JumpPreviousParagraph() {}
}
