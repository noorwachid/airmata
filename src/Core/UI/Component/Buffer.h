#pragma once

#include "Core/Container/Array.h"
#include "Core/IO/Action.h"
#include "Core/UI/Component/Component.h"

namespace UI
{
    class Buffer : public Component
    {
    public:
        Buffer(Context& newContext);

        virtual void On(Event& event) override;

        virtual void Render() override;

        void InsertUnderCursor(const String& string);

        void DeleteBeforeCursor();

        void DeleteUnderCursor();

        void DeleteAfterCursor();

        int GetCursorXBounding();

        int GetCursorYBounding();

        bool IsEOL();

        void MoveEOL();

        String GetCharacterUnderCursor();

        String RenderStatusLine();

        void MoveCursorLeft();
        void MoveCursorRight();
        void MoveCursorUp();
        void MoveCursorDown();

        void JumpNextWord();
        void JumpPreviousWord();

        bool IsWord(char character)
        {
            return 
                (character >= 'A' && character <= 'Z') ||
                (character >= 'a' && character <= 'z') ||
                (character >= '0' && character <= '9') 
            ;
        }

    public:
        Array<String> data = {
            "Lorem ipsum dolor sit amet, consectetur-adipiscing elit.",
            "Nunc vestibulum tristique purus, mollis rhoncus elit.",
            "Mauris accumsan posuere felis.",
            "Fusce varius urna tempus molestie suscipit.",
            // "Aliquam sed mattis elit, eu convallis lectus.",
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

        Vector2 cursor;
    };
}
