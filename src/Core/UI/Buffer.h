#pragma once

#include "Core/Container/String.h"
#include "Core/Container/Array.h"
#include "Core/UI/View.h"

namespace UI
{
    class Buffer: public View
    {
      public:
        virtual void Render(IO::TTY& tty, const Sequence& sequence) override
        {
            tty.Write(sequence.CreateCursorMover({1, 1}) + _cursor.ToString() + sequence.CreateCursorMover(_cursor));
        }

      public:
        Array<String> _lines;

        Vector2 _cursor;
    };
}
