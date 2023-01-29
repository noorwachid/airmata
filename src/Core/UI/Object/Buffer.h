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

        void Insert(const String& string);

        void DeleteBefore();

        void Delete();

        void DeleteAfter();

        int GetBoundingX();

        int GetBoundingY();

        bool IsEOL();

        void MoveEOL();

        char Get();

        String RenderStatusLine();

        void MoveCursorLeft();
        void MoveCursorRight();
        void MoveCursorUp();
        void MoveCursorDown();

        void JumpNextWord();
        void JumpPreviousWord();

        void JumpNextSentence();
        void JumpPreviousSentence();

        void JumpNextLine();
        void JumpPreviousLine();

        void JumpNextParagraph();
        void JumpPreviousParagraph();

        bool IsWhitespace(char character)
        {
            return character == ' ' || character == '\t';
        }

        bool IsWord(char character)
        {
            return 
                (character >= 'A' && character <= 'Z') ||
                (character >= 'a' && character <= 'z') ||
                (character >= '0' && character <= '9') 
            ;
        }

    public:
        Array<String> data;

        Vector2 cursor;
    };
}
