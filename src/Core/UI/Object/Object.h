#pragma once

#include "Core/Container/Vector.h"
#include "Core/Event/Event.h"

class Program;

namespace UI
{
    class Object
    {
    public:
        Object(Program& referenceProgram);

        virtual void On(Event& event);

        virtual void Render();

        const Vector2& GetPosition() const;
        const Vector2& GetSize() const;

        void SetPosition(const Vector2& newPosition);
        void SetSize(const Vector2& newSize);

    protected:
        Program& program;

    private:
        Vector2 position;
        Vector2 size;
    };
};
