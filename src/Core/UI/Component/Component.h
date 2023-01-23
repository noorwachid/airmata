#pragma once

#include "Core/Context.h"
#include "Core/Event/Event.h"

namespace UI {
    class Component {
      public:
        Component(Context& newContext);

        virtual void on(Event& event);

        virtual void render();

        const Vector2& getPosition() const;
        const Vector2& getSize() const;

        void setPosition(const Vector2& newPosition);
        void setSize(const Vector2& newSize);

      protected:
        Context& context;

      private:
        Vector2 position;
        Vector2 size;
    };
};
