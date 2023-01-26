#include "Core/UI/Component/Component.h"

namespace UI
{
    Component::Component(Context& newContext) : context{newContext} {}

    void Component::On(Event& event){};

    void Component::Render(){};

    const Vector2& Component::GetPosition() const { return position; }

    const Vector2& Component::GetSize() const { return size; }

    void Component::SetPosition(const Vector2& newPosition) { position = newPosition; }

    void Component::SetSize(const Vector2& newSize) { size = newSize; }
}
