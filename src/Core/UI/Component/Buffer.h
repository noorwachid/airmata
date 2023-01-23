#pragma once

#include "Core/Container/Array.h"
#include "Core/UI/Component/Component.h"

namespace UI
{
    class Buffer: public Component
    {
      public:
        Buffer(Context& context);

        virtual void On(Event& event) override;

        virtual void Render() override;

      public:
        Array<String> _data;

        Vector2 _cursor;
    };
}
