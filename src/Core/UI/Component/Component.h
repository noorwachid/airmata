#pragma once 

#include "Core/Context.h"
#include "Core/Event/Event.h"

namespace UI 
{
    class Component
    {
      public:
        Component(Context& context);

        virtual void On(Event& event);

        virtual void Render();

        const Vector2& GetPosition() const;
        const Vector2& GetSize() const;

        void SetPosition(const Vector2& position);
        void SetSize(const Vector2& size);

      protected:
        Context& _context;

      private:
        Vector2 _position;
        Vector2 _size;
    };
};
