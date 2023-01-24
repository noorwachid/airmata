#pragma once

#include "Core/Container/Array.hpp"
#include "Core/IO/Action.hpp"
#include "Core/UI/Component/Component.hpp"

namespace UI {
    class Buffer : public Component {
      public:
        Buffer(Context& newContext);

        virtual void on(Event& event) override;

        virtual void render() override;

        void openFile();

      public:
        Array<String> data;

        Vector2 cursor;
    };
}
