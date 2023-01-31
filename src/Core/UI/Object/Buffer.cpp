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
        lines.reserve(16);
        lines = {
            "Lorem ipsum dolor sit amet, consectetur-adipiscing elit.",
            "Nunc vestibulum, tristique purus: mollis rhoncus elit.",
            "",
            "Fusce varius urna tempus molestie... suscipit.",
            "Mauris accumsan posuere felis.",
            "    A Liquam sed mattis elit, eu convallis lectus.",
            "    Nam sagittis sem id viverra hendrerit.",
            "    Suspendisse hendrerit at risus pharetra aliquam.",
            "Donec porta consectetur pellentesque.",
            "Aliquam sed nisi quis ipsum pellentesque fermentum.",
            "Duis sit amet condimentum arcu. Nulla at volutpat orci.",
            "",
            "    ",
            "Ut fermentum dui libero, non vestibulum urna egestas nec.",
            "Cras sit amet commodo ex. Sed et condimentum nisi, a egestas eros.",
            "Etiam vel est enim.",
            // "Aliquam dapibus, nulla et pretium interdum, ante lectus rhoncus est, eget dapibus odio quam ut ligula. Mauris pellentesque, ipsum vitae tristique finibus, mi justo porttitor justo, sed sagittis elit magna faucibus dui. Nunc tincidunt sapien id eleifend sagittis.",
            "",
            "Nulla semper iaculis velit, eget finibus sem fermentum quis.",
            "Phasellus ac finibus justo.",
            "Integer commodo ligula sed tortor scelerisque, in dignissim nibh posuere.",
            "In ac suscipit lacus, vitae malesuada risus.",
            "Nunc porttitor laoreet nulla, vel pretium nulla dictum nec.",
            "Nunc ut est sit amet nisl pellentesque commodo.",
            "",
            "Aenean id sapien ac turpis scelerisque vehicula at sed sem.",
            "Cras vestibulum pulvinar scelerisque.",
            "Pellentesque sollicitudin quam nulla, ac malesuada lorem condimentum vitae.",
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
            {
                context.terminating = true;
                context.tty.StopReading();
                return;
            }

            if (context.mode == Mode::WideMove) 
            {
                switch (keyEvent.key)
                {
                    case Key::Escape:
                        context.mode = Mode::WideMove;
                        break;

                    case Key::H:
                        if (keyEvent.modifierKey == ModifierKey::None)
                            JumpPreviousWord();
                        else if ((keyEvent.modifierKey & ModifierKey::Shift) == ModifierKey::Shift)
                            JumpPreviousWordEnd();
                        break;

                    case Key::T:
                        if (keyEvent.modifierKey == ModifierKey::None)
                            JumpPreviousLine();
                        else if ((keyEvent.modifierKey & ModifierKey::Shift) == ModifierKey::Shift)
                            JumpPreviousLineEnd();
                        break;

                    case Key::N:
                        if (keyEvent.modifierKey == ModifierKey::None)
                            JumpNextLine();
                        else if ((keyEvent.modifierKey & ModifierKey::Shift) == ModifierKey::Shift)
                            JumpNextLineEnd();
                        break;

                    case Key::S:
                        if (keyEvent.modifierKey == ModifierKey::None)
                            JumpNextWord();
                        else if ((keyEvent.modifierKey & ModifierKey::Shift) == ModifierKey::Shift)
                            JumpNextWordEnd();
                        break;

                    case Key::M:
                        if (keyEvent.modifierKey == ModifierKey::None)
                            JumpPreviousSentence();
                        else if ((keyEvent.modifierKey & ModifierKey::Shift) == ModifierKey::Shift)
                            JumpPreviousSentenceEnd();
                        break;

                    case Key::Z:
                        if (keyEvent.modifierKey == ModifierKey::None)
                            JumpNextSentence();
                        else if ((keyEvent.modifierKey & ModifierKey::Shift) == ModifierKey::Shift)
                            JumpNextSentenceEnd();
                        break;

                    case Key::Return:
                        if ((keyEvent.modifierKey & ModifierKey::Shift) == ModifierKey::Shift)
                            MoveRight(1);
                            
                        context.mode = Mode::Insert;
                        break;

                    case Key::Left:
                        MoveLeft(1);
                        break;

                    case Key::Up:
                        MoveUp(1);
                        break;

                    case Key::Down:
                        MoveDown(1);
                        break;

                    case Key::Right:
                        MoveRight(1);
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

                    case Key::Left:
                        MoveLeft(1);
                        break;

                    case Key::Up:
                        MoveUp(1);
                        break;

                    case Key::Down:
                        MoveDown(1);
                        break;

                    case Key::Right:
                        MoveRight(1);
                        break;

                    default:
                        if (keyEvent.codepoint >= 32)
                            InsertAt({ (char) keyEvent.codepoint, 0 });
                        break;
                }
            }
        }
    }

    void Buffer::Render() 
    { 
        String renderData;

        String maxLines = std::to_string(lines.size());

        for (int i = 0; i < lines.size(); ++i) 
        {
            String lineRepresentation = std::to_string(i + 1);

            renderData += context.sequence.MoveCursor({ 0, i });
            renderData += ' ' + String(maxLines.size() - lineRepresentation.size(), ' ') + lineRepresentation + ' ' + lines[i] + String(GetSize().x - lines[i].size() - maxLines.size() - 2, ' ');
        }

        String cursorStyle = context.mode == Mode::Insert ? "\x1b[\x35 q" : "\x1b[\x31 q";

        context.tty.Write(
            renderData +
            RenderStatusLine() +
            context.sequence.MoveCursor({ cursor.x + 2 + (int) maxLines.size(), cursor.y }) + 
            cursorStyle +
            context.sequence.ResetAttribute()
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

    void Buffer::InsertAt(const String& string)
    {
        if (lines.empty())
        {
            return lines.push_back(string);
        }

        String& line = lines[cursor.y];
        line.insert(cursor.x, string);
    }

    void Buffer::DeleteBefore() 
    {
        if (lines.empty()) return;

        if (lines[cursor.y].empty()) return;

        lines[cursor.y].erase(cursor.x -1, 1);

        MoveLeft(1);
    }

    void Buffer::DeleteAt() 
    {
    }

    void Buffer::DeleteAfter() 
    {
    }

    int Buffer::GetBoundingX()
    {
        return lines.empty() || lines[cursor.y].empty() 
            ? 1
            : lines[cursor.y].size();
    }

    int Buffer::GetBoundingY()
    {
        return lines.empty()
            ? 1
            : lines.size();
    }

    char Buffer::GetCharacter(int cursorXOffset)
    {
        return lines[cursor.y][cursor.x + cursorXOffset];
    }

    String& Buffer::GetLine(int cursorYOffset)
    {
        return lines[cursor.y + cursorYOffset];
    }

    int Buffer::GetBeginnigLineX()
    {
        for (usize i = 0; i < GetBoundingX(); ++i) 
        {
            if (!IsWhitespace(GetCharacter(i)))
            {
                return i;
            }
        }

        return 0;
    }

    bool Buffer::IsEmpty()
    {
        return lines.empty() || lines[cursor.y].empty();
    }

    bool Buffer::IsWhitespace(char character) { return character == ' ' || character == '\t'; }

    bool Buffer::IsWhitespace(const String& line) 
    { 
        for (char character: line) 
            if (!IsWhitespace(character))
                return false;

        return true;
    }

    bool Buffer::IsWord(char character)
    {
        return (character >= 'A' && character <= 'Z') || 
               (character >= 'a' && character <= 'z') ||
               (character >= '0' && character <= '9');
    }

    bool Buffer::IsSentenceEnding(char character)
    {
        return 
            character == ',' ||
            character == '.' ||
            character == ';' ||
            character == ':' ||
            character == '!' ||
            character == '?' ||
            character == '=' ||
            character == '(' ||
            character == '{' ||
            character == '<' ||
            character == '[';
    }

    bool Buffer::IsBeginningLine() 
    {
        if (cursor.x == 0) return true;

        int x = 0;

        for (int i = 0; i < GetBoundingX(); ++i) 
        {
            if (!IsWhitespace(GetLine(0)[i])) 
            {
                x = i;
                break;
            }
        }

        return cursor.x == x;
    }

    usize Buffer::CanMoveLeft(usize repeats)
    {
        return std::min<usize>(cursor.x, repeats);
    }

    usize Buffer::CanMoveRight(usize repeats)
    {
        return std::min<usize>(repeats, GetBoundingX() - cursor.x - 1);
    }

    usize Buffer::CanMoveUp(usize repeats)
    {
        return std::min<usize>(cursor.y, repeats);
    }

    usize Buffer::CanMoveDown(usize repeats)
    {
        return std::min<usize>(repeats, GetBoundingY() - cursor.y - 1);
    }

    void Buffer::MoveLeft(usize repeats)
    {
        cursor.x -= CanMoveLeft(repeats);
    }

    void Buffer::MoveRight(usize repeats)
    {
        cursor.x += CanMoveRight(repeats);
    }

    void Buffer::MoveUp(usize repeats)
    {
        cursor.y -= CanMoveUp(repeats);

        if (cursor.x > GetBoundingX() - 1) 
            JumpEndLine();
    }

    void Buffer::MoveDown(usize repeats)
    {
        cursor.y += CanMoveDown(repeats);

        if (cursor.x > GetBoundingX() - 1) 
            JumpEndLine();
    }

    void Buffer::JumpPreviousWord()
    {
        if (IsEmpty()) return;

        // Beginning of word
        if (!IsWord(GetCharacter(0)))
        {
            if (CanMoveLeft(1))
            {
                if (!IsWord(GetCharacter(-1)))
                    return MoveLeft(1);
                else
                    MoveLeft(1);
            }
        }
        else
        {
            if (CanMoveLeft(1))
            {
                if (IsWhitespace(GetCharacter(-1)))
                    MoveLeft(2);
                else if (!IsWord(GetCharacter(-1)))
                    return MoveLeft(1);
            }
        }

        for (usize i = 0; i < cursor.x; ++i)
        {
            if (!IsWord(GetCharacter(-i)))
            {
                MoveLeft(i);

                if (!IsWord(GetCharacter(0)))
                    if (CanMoveRight(1) && !IsWhitespace(GetCharacter(1)))
                        MoveRight(1);

                return;
            }
        }

        JumpBeginningLine();
    }

    void Buffer::JumpPreviousWordEnd()
    {
        if (IsEmpty()) return;

        // Beginning of word
        if (!IsWord(GetCharacter(0)))
        {
            if (CanMoveLeft(1))
            {
                return MoveLeft(1);
            }
        }
        else 
        {
            if (CanMoveLeft(1))
            {
                if (IsWhitespace(GetCharacter(-1)))
                    return MoveLeft(2);
                else if (!IsWord(GetCharacter(-1)))
                    return MoveLeft(1);
            }
        }

        for (usize i = 0; i < cursor.x; ++i)
        {
            if (!IsWord(GetCharacter(-i)))
            {
                MoveLeft(i);

                if (!IsWord(GetCharacter(0)))
                    if (CanMoveRight(1) && IsWhitespace(GetCharacter(0)))
                        MoveLeft(1);

                return;
            }
        }

        JumpBeginningLine();
    }

    void Buffer::JumpNextWord()
    {
        if (IsEmpty()) return;

        // End of word
        if (CanMoveRight(1) && IsWhitespace(GetCharacter(1)))
            return MoveRight(2);

        if (!IsWord(GetCharacter(0)))
            return MoveRight(1);

        for (usize i = 0; i < GetBoundingX(); ++i)
        {
            if (!IsWord(GetCharacter(i)))
            {
                MoveRight(i);

                if (IsWhitespace(GetCharacter(0)))
                    MoveRight(1);

                return;
            }
        }
    }

    void Buffer::JumpNextWordEnd()
    {
        if (IsEmpty()) return;

        if (CanMoveRight(1) && IsWhitespace(GetCharacter(1)))
            MoveRight(2);

        if (!IsWord(GetCharacter(0)))
        {
            if (CanMoveRight(1))
            {
                if (!IsWord(GetCharacter(1)))
                    return MoveRight(1);
                else 
                    MoveRight(1);
            }
        }
        else 
        {
            if (CanMoveRight(1) && !IsWord(GetCharacter(1)))
                return MoveRight(1);
        }

        // End of line
        if (cursor.x == GetBoundingX() - 1)
            return;

        for (usize i = 0; i < GetBoundingX(); ++i)
        {
            if (!IsWord(GetCharacter(i)))
            {
                MoveRight(i);

                if (!IsWord(GetCharacter(0)))
                    MoveLeft(1);

                return;
            }
        }
    }

    void Buffer::JumpPreviousSentence() 
    {
        if (IsEmpty()) return;

        if (CanMoveLeft(1) && IsWhitespace(GetCharacter(-1)))
            MoveLeft(2);

        if (IsSentenceEnding(GetCharacter(0)))
            MoveLeft(1);

        for (usize i = 0; i < cursor.x; ++i)
        {
            if (IsSentenceEnding(GetCharacter(-i)))
            {
                return MoveLeft(i - 2);
            }
        }

        JumpBeginningLine();
    }

    void Buffer::JumpPreviousSentenceEnd() 
    {
        if (IsEmpty()) return;

        if (IsSentenceEnding(GetCharacter(0)))
            MoveLeft(1);

        for (usize i = 0; i < cursor.x; ++i)
        {
            if (IsSentenceEnding(GetCharacter(-i)))
            {
                MoveLeft(i);

                return;
            }
        }

        JumpBeginningLine();
    }

    void Buffer::JumpNextSentence() 
    {
        if (IsEmpty()) return;

        for (usize i = 0; i < GetBoundingX(); ++i)
        {
            if (IsSentenceEnding(GetCharacter(i)))
            {
                MoveRight(i + 1);

                if (!IsWord(GetCharacter(0)))
                    MoveRight(1);

                return;
            }
        }
    }

    void Buffer::JumpNextSentenceEnd() 
    {
        if (IsEmpty()) return;

        if (CanMoveRight(1) && IsWhitespace(GetCharacter(1)))
            MoveRight(2);

        for (usize i = 0; i < GetBoundingX(); ++i)
        {
            if (IsSentenceEnding(GetCharacter(i)))
            {
                MoveRight(i);

                return;
            }
        }
    }

    void Buffer::JumpPreviousLine() 
    {
        if (IsEmpty()) return;

        if (!IsBeginningLine()) return JumpBeginningLine();

        if (!CanMoveUp(1)) return;

        --cursor.y;

        for (int i = 0; i < GetBoundingY() && IsWhitespace(GetLine(0)); ++i)
            --cursor.y;

        JumpBeginningLine();
    }

    void Buffer::JumpPreviousLineEnd() 
    {
        if (IsEmpty()) return;

        if (!CanMoveUp(1)) return;

        --cursor.y;

        for (int i = 0; i < GetBoundingY() && IsWhitespace(GetLine(0)); ++i)
            --cursor.y;

        JumpEndLine();
    }

    void Buffer::JumpNextLine() 
    {
        if (IsEmpty()) return;

        if (!CanMoveDown(1)) return;

        ++cursor.y;

        for (int i = 0; i < GetBoundingY() && IsWhitespace(GetLine(0)); ++i)
            ++cursor.y;

        JumpBeginningLine();
    }

    void Buffer::JumpNextLineEnd() 
    {
        if (IsEmpty()) return;

        if (cursor.x != GetBoundingX() - 1) return JumpEndLine();

        if (!CanMoveDown(1)) return;

        ++cursor.y;

        for (int i = 0; i < GetBoundingY() && IsWhitespace(GetLine(0)); ++i)
            ++cursor.y;

        JumpEndLine();
    }



    void Buffer::JumpBeginningLine()
    {
        cursor.x = 0;

        for (usize i = 0; i < GetBoundingX(); ++i) 
        {
            if (!IsWhitespace(GetCharacter(i)))
            {
                cursor.x = i;
                break;
            }
        }
    }

    void Buffer::JumpEndLine()
    {
        cursor.x = GetBoundingX() - 1;
    }

    void Buffer::JumpNextParagraph() {}

    void Buffer::JumpPreviousParagraph() {}
}
