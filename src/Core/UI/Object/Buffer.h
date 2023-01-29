#pragma once

#include "Core/Container/Array.h"
#include "Core/IO/Action.h"
#include "Core/UI/Object/Object.h"

namespace UI
{
    class Buffer : public Object
    {
    public:
        Buffer(Context& newContext);

        virtual void On(Event& event) override;

        virtual void Render() override;

        String RenderStatusLine();

        void InsertBefore(const String& string);
        void InsertAt(const String& string);
        void InsertAfter(const String& string);

        void DeleteBefore();
        void DeleteAt();
        void DeleteAfter();

        int GetBoundingX();
        int GetBoundingY();

        inline char GetCharacter(int cursorXOffset);
        String& GetLine(int cursorYOffset);

        bool IsEmpty();

        bool IsWhitespace(char character);
        bool IsWhitespace(const String& line);

        bool IsWord(char character);

        bool IsSentenceEnding(char character);

        usize CanMoveLeft(usize repeats);
        usize CanMoveRight(usize repeats);
        usize CanMoveUp(usize repeats);
        usize CanMoveDown(usize repeats);

        void MoveLeft(usize repeats);
        void MoveRight(usize repeats);
        void MoveUp(usize repeats);
        void MoveDown(usize repeats);

        void JumpPreviousWord();
        void JumpPreviousWordEnd();

        void JumpNextWord();
        void JumpNextWordEnd();

        void JumpPreviousSentence();
        void JumpPreviousSentenceEnd();

        void JumpNextSentence();
        void JumpNextSentenceEnd();

        void JumpBeginningLine();
        void JumpEndLine();

        void JumpPreviousLine();
        void JumpNextLine();

        void JumpNextParagraph();
        void JumpPreviousParagraph();

    public:
        Array<String> lines;
        String oob = " ";

        Vector2 cursor;
    };
}
