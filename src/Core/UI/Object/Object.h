#pragma once

#include "Core/Context.h"
#include "Core/Event/Event.h"

namespace UI
{
    class Object
    {
    public:
        Object(Context& newContext);

        virtual void On(Event& event);

        virtual void Render();

        const Vector2& GetPosition() const;
        const Vector2& GetSize() const;

        void SetPosition(const Vector2& newPosition);
        void SetSize(const Vector2& newSize);

    protected:
        Context& context;

    private:
        Vector2 position;
        Vector2 size;
    };
};
