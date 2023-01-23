#pragma once 

#include "Core/IO/Resource.h"
#include "Core/UI/Sequence.h"

namespace UI 
{
    class View 
    {
      public:
        Vector2 position;
        Vector2 size;

      public:
        virtual void Render(IO::TTY& tty, const Sequence& sequence) = 0;
    };
};
