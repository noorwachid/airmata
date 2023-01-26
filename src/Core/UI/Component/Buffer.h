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

        void OpenFile();

    public:
        Array<String> data;

        Vector2 cursor;
    };
}
